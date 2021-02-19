#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

void EMSCRIPTEN_KEEPALIVE pxl(int* pixelData, int* pixelData_out, size_t width, size_t height){

  // EM_ASM_({
  //   console.log("Width: ", $0, " Height: ", $1);
  // }, width, height);
  // for(int i = 0; i < height; i++){
  //   for(int j = 0; j < width; j++){
  //     int index = (i*4) * width + (j*4);
  //     // int gray = ((pixelData[index] + pixelData[index + 1]+ pixelData[index + 2]) / 3.0);
  //     // Fake transform (not linear)
  //     int gray = (pixelData[index]*0.299 + pixelData[index + 1]*0.587 + pixelData[index + 2]*0.114);
  //     pixelData_out[index + 3] = 255;
  //     pixelData_out[index + 2] = gray;
  //     pixelData_out[index + 1] = gray;
  //     pixelData_out[index] = gray;
  //   }
  // }

  int step = 4;
  for(int *pxa = pixelData, *pxb = pixelData_out; pxa < pixelData + width*height*4; pxa+=step, pxb+=step){
      int gray = ((*pxa + *(pxa + 1) + *(pxa + 2)) / 3.0);
      *pxb = gray;
      *(pxb+1) = gray;
      *(pxb+2) = gray;
      *(pxb+3) = 255;
  }
}

void EMSCRIPTEN_KEEPALIVE toChar(int* pixelData, int* pixelData_out, size_t width, size_t height){
  const char shades[10] = {'@','%','#','*','+','=',':','-','.','_'};
  const int shades_num = 10;
  const int shades_stop = 256/shades_num;

  int step = 4;
  for(int *pxa = pixelData, *pxb = pixelData_out; pxa < pixelData + width*height*4; pxa+=step, pxb++){
      int j = ( (int)pxb % (int)pixelData_out ) / 4;
      int gray = ((*pxa + *(pxa + 1) + *(pxa + 2)) / 3.0);

      char shade;
      shade = shades[(int)(gray / shades_stop)];
      if(j%width== 0){
          shade = '\n';
        }    
      *pxb = shade;
      // EM_ASM_({
      //   console.log(" - Iteration: ", $0, "\n Shade num: ", $1, "\n Shade:", String.fromCharCode($1));
      // }, j, shade);
  }
}

int EMSCRIPTEN_KEEPALIVE fib(int n){
    if(n == 0 || n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}

int resize(int num){
  printf("Running new new! \n");
  return 1;

  // int width, height, channels;
  // unsigned char* img = stbi_load("../img/shp_og.jpg", &width, &height, &channels, 0);

  // if(img == NULL){
  //   printf("Error ocurred while loading the image! \n");
  //   exit(1);
  // }
  // printf("Loaded the image with a size of %dx%d and channels %d \n", width, height, channels);
  // stbi_image_free(img);
}


int main(int argc, char ** argv){
  printf("Loading module... \n");
  // emscripten_run_script("alert('Called from C program 4!')");
  int res = fib(33);
  printf("Result %d \n", res);
  resize(3);
}