#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <wb.h>

#define BLOCK_SIZE 512 

#define wbCheck(stmt)                                                     \
  do {                                                                    \
    cudaError_t err = stmt;                                               \
    if (err != cudaSuccess) {                                             \
      wbLog(ERROR, "Failed to run stmt ", #stmt);                         \
      wbLog(ERROR, "Got CUDA error ...  ", cudaGetErrorString(err));      \
      return -1;                                                          \
    }                                                                     \
  } while (0)

__global__ void scan(float* input, float* output, float* aux, int len) {
    //@@ Modify the body of this kernel to generate the scanned blocks
    //@@ Make sure to use the workefficient version of the parallel scan
    //@@ Also make sure to store the block sum to the aux array 
    __shared__ float scan_array[BLOCK_SIZE];
    int bxx = blockIdx.x * blockDim.x;
    int tx = threadIdx.x;

    if (bxx + tx < len)
        scan_array[tx] = input[bxx + tx];
    else
        scan_array[tx] = 0;

    __syncthreads();

    for (unsigned int stride = 1; stride < blockDim.x; stride *= 2)
    {
        int index = (tx + 1) * stride * 2 - 1;

        if (index < blockDim.x)
            scan_array[index] += scan_array[index - stride];
        __syncthreads();
    }

    for (unsigned int stride = BLOCK_SIZE / 4; stride > 0; stride /= 2)
    {
        int index = (tx + 1) * stride * 2 - 1;

        if (index + stride < BLOCK_SIZE)
            scan_array[index + stride] += scan_array[index];
        __syncthreads();
    }

    __syncthreads();

    if (bxx + tx < len)
        output[bxx + tx] = scan_array[tx];
    if ((aux != 0) && (tx == blockDim.x - 1))
        aux[blockIdx.x] = scan_array[tx];
}

__global__ void addScannedBlockSums(float* output, float* aux, int len) {
    //@@ Modify the body of this kernel to add scanned block sums to 
    //@@ all values of the scanned blocks
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    if ((blockIdx.x != 0) && (index < len))
        output[index] += aux[blockIdx.x - 1];
    __syncthreads();
}

int main(int argc, char** argv) {
    wbArg_t args;
    float* hostInput;  // The input 1D list
    float* hostOutput; // The output 1D list
    float* deviceInput;
    float* deviceOutput;
    float* deviceAuxArray, * deviceAuxScannedArray;
    int numElements; // number of elements in the input/output list
    int numBlocks;

    args = wbArg_read(argc, argv);

    wbTime_start(Generic, "Importing data and creating memory on host");
    hostInput = (float*)wbImport(wbArg_getInputFile(args, 0), &numElements);
    hostOutput = (float*)malloc(numElements * sizeof(float));
    wbTime_stop(Generic, "Importing data and creating memory on host");

    wbLog(TRACE, "The number of input elements in the input is ",
        numElements);

    numBlocks = BLOCK_SIZE * 2;

    wbTime_start(GPU, "Allocating device memory.");
    //@@ Allocate device memory
    //you can assume that aux array size would not need to be more than BLOCK_SIZE*2 (i.e., 1024)
    cudaMalloc((void**)&deviceInput, numElements * sizeof(float));
    cudaMalloc((void**)&deviceOutput, numElements * sizeof(float));
    cudaMalloc((void**)&deviceAuxArray, numBlocks * sizeof(float));
    cudaMalloc((void**)&deviceAuxScannedArray, numBlocks * sizeof(float));
    wbTime_stop(GPU, "Allocating device memory.");

    wbTime_start(GPU, "Clearing output device memory.");
    //@@ zero out the deviceOutput using cudaMemset() by uncommenting the below line
    wbCheck(cudaMemset(deviceOutput, 0, numElements * sizeof(float)));
    wbTime_stop(GPU, "Clearing output device memory.");

    wbTime_start(GPU, "Copying input host memory to device.");
    //@@ Copy input host memory to device
    cudaMemcpy(deviceInput, hostInput, numElements * sizeof(float), cudaMemcpyHostToDevice);
    wbTime_stop(GPU, "Copying input host memory to device.");

    //@@ Initialize the grid and block dimensions here
    dim3 Grid(numBlocks, 1, 1);
    dim3 Block(BLOCK_SIZE, 1, 1);

    wbTime_start(Compute, "Performing CUDA computation");
    //@@ Modify this to complete the functionality of the scan
    //@@ on the deivce
    //@@ You need to launch scan kernel twice: 1) for generating scanned blocks 
    //@@ (hint: pass deviceAuxArray to the aux parameter)
    //@@ and 2) for generating scanned aux array that has the scanned block sums. 
    //@@ (hint: pass NULL to the aux parameter)
    //@@ Then you should call addScannedBlockSums kernel.
    scan << < Grid, Block >> > (deviceInput, deviceOutput, deviceAuxArray, numElements);
    cudaDeviceSynchronize();
    scan << < Grid, Block >> > (deviceAuxArray, deviceAuxScannedArray, NULL, numBlocks);
    addScannedBlockSums << < Grid, Block >> > (deviceOutput, deviceAuxScannedArray, numElements);
    cudaDeviceSynchronize();
    wbTime_stop(Compute, "Performing CUDA computation");

    wbTime_start(Copy, "Copying output device memory to host");
    //@@ Copy results from device to host	
    cudaMemcpy(hostOutput, deviceOutput, numElements * sizeof(float), cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying output device memory to host");

    wbTime_start(GPU, "Freeing device memory");
    //@@ Deallocate device memory
    cudaFree(deviceInput);
    cudaFree(deviceOutput);
    cudaFree(deviceAuxArray);
    cudaFree(deviceAuxScannedArray);
    wbTime_stop(GPU, "Freeing device memory");

    wbSolution(args, hostOutput, numElements);

    free(hostInput);
    free(hostOutput);

    return 0;
}