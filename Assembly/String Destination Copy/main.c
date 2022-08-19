#include <stdio.h>
#include "strdcpy.h"

int main()
{
  char src[256] = "this is a string\n";
  char dest[256];
  char delim[256] = "\t \n";

  fgets(src, sizeof(src), stdin);
  printf("%s\n",strdcpy(dest, src, delim));
  return 0;
}
