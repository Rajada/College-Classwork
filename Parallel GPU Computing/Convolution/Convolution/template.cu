#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <wb.h>

#define MASK_WIDTH 5
#define MASK_RADIUS (MASK_WIDTH / 2)
#define O_TILE_WIDTH 16
#define clamp(x) (min(max((x), 0.0), 1.0))
#define BLOCK_WIDTH (O_TILE_WIDTH + (MASK_WIDTH - 1))

//@@ INSERT CODE HERE 
//implement the tiled 2D convolution kernel with adjustments for channels
//use shared memory to reduce the number of global accesses, handle the boundary conditions when loading input list elements into the shared memory
//clamp your output values

__global__ void convolutionKernel(float *P, float *N, int height, int width, int channels, const float* __restrict__ M)
{
	__shared__ float Ns[BLOCK_WIDTH][BLOCK_WIDTH];

	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int outRow = blockIdx.y * O_TILE_WIDTH + ty;
	int outColumn = blockIdx.x * O_TILE_WIDTH + tx;
	int inRow = outRow - MASK_RADIUS;
	int inColumn = outColumn - MASK_RADIUS;
	float output = 0.0;

	for (int i = 0; i < channels; i++)
	{
		if ((inRow >= 0) && (inRow < height) && (inColumn >= 0) && (inColumn < width))
			Ns[ty][tx] = N[(inRow * width + inColumn) * channels + i];
		else
			Ns[ty][tx] = 0.0;

		__syncthreads();
		output = 0.0;

		if ((ty < O_TILE_WIDTH) && (tx < O_TILE_WIDTH) && (outRow < height) && (outColumn < width))
		{
			for (int j = 0; j < MASK_WIDTH; j++)
			{
				for (int k = 0; k < MASK_WIDTH; k++)
				{
					output += M[j * MASK_WIDTH + k] * Ns[j + ty][k + tx];
				}
			}

			P[(outRow * width + outColumn) * channels + i] = clamp(output);
		}
	}
}

int main(int argc, char *argv[])
{
  wbArg_t arg;
  int maskRows;
  int maskColumns;
  int imageChannels;
  int imageWidth;
  int imageHeight;
  char *inputImageFile;
  char *inputMaskFile;
  wbImage_t inputImage;
  wbImage_t outputImage;
  float *hostInputImageData;
  float *hostOutputImageData;
  float *hostMaskData;
  float *deviceInputImageData;
  float *deviceOutputImageData;
  float *deviceMaskData;

  arg = wbArg_read(argc, argv); /* parse the input arguments */

  inputImageFile = wbArg_getInputFile(arg, 0);
  inputMaskFile  = wbArg_getInputFile(arg, 1);

  inputImage   = wbImport(inputImageFile);
  hostMaskData = (float *)wbImport(inputMaskFile, &maskRows, &maskColumns);

  assert(maskRows == MASK_WIDTH);    /* mask height is fixed to 5 */
  assert(maskColumns == MASK_WIDTH); /* mask width is fixed to 5 */

  imageWidth    = wbImage_getWidth(inputImage);
  imageHeight   = wbImage_getHeight(inputImage);
  imageChannels = wbImage_getChannels(inputImage);

  outputImage = wbImage_new(imageWidth, imageHeight, imageChannels);

  hostInputImageData  = wbImage_getData(inputImage);
  hostOutputImageData = wbImage_getData(outputImage);

  wbTime_start(GPU, "Doing GPU Computation (memory + compute)");

  wbTime_start(GPU, "Doing GPU memory allocation");
  //@@ INSERT CODE HERE
  //allocate device memory
  cudaMalloc((void**) &deviceInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
  cudaMalloc((void**) &deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
  cudaMalloc((void**) &deviceMaskData, maskColumns * maskRows * sizeof(float));
  wbTime_stop(GPU, "Doing GPU memory allocation");

  wbTime_start(Copy, "Copying data to the GPU");
  //@@ INSERT CODE HERE
  //copy host memory to device
  cudaMemcpy(deviceInputImageData, hostInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(deviceMaskData, hostMaskData, maskRows * maskColumns * sizeof(float), cudaMemcpyHostToDevice);
  wbTime_stop(Copy, "Copying data to the GPU");

  wbTime_start(Compute, "Doing the computation on the GPU");
  //@@ INSERT CODE HERE
  //initialize thread block and kernel grid dimensions
  //invoke CUDA kernel
  dim3 block(BLOCK_WIDTH, BLOCK_WIDTH);
  dim3 grid((imageWidth - 1) / O_TILE_WIDTH + 1, (imageHeight - 1) / O_TILE_WIDTH + 1, 1);
  convolutionKernel <<< grid, block >>> (deviceOutputImageData, deviceInputImageData, imageHeight, imageWidth, imageChannels, deviceMaskData);
  wbTime_stop(Compute, "Doing the computation on the GPU");

  wbTime_start(Copy, "Copying data from the GPU");
  //@@ INSERT CODE HERE
  //copy results from device to host
  cudaMemcpy(hostOutputImageData, deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float), cudaMemcpyDeviceToHost);
  wbTime_stop(Copy, "Copying data from the GPU");

  wbTime_stop(GPU, "Doing GPU Computation (memory + compute)");

  wbSolution(arg, outputImage);

  //@@ INSERT CODE HERE
  //deallocate device memory
  cudaFree(deviceInputImageData);
  cudaFree(deviceOutputImageData);
  cudaFree(deviceMaskData);

  free(hostMaskData);
  wbImage_delete(outputImage);
  wbImage_delete(inputImage);

  return 0;
}
