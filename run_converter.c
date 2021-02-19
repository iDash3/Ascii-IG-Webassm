#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(void) {
  int width, height, channels;
  unsigned char* img = stbi_load("img/robin_r.jpg", &width, &height, &channels, 0);
  if(img == NULL){
    printf("Error ocurred while loading the image!");
    exit(1);
  }
  printf("Loaded the image with a size of %dx%d and channels %d \n", width, height, channels);

  size_t img_size = width * height * channels;
  int gray_channels = channels == 4 ? 2 : 1;
  size_t gray_img_size = width * height * gray_channels;

  unsigned char* gray_img = malloc(gray_img_size);
  if (gray_img == NULL) {
      printf("Unable to allocate the memory for gray image.\n");
      exit(1);
  }

  const int shades_num = 10;
  // const int shades[10] = {'_', '.', '-',':','=','+','*','#','%','@'};
  const char shades[10] = {'@','%','#','*','+','=',':','-','.','_'};
  // const int shades[10] = {64,37,35,42,43,61,58,45,46,95};
  // const int shades_num = 9;
  // const int shades[9] = {0,32,64,96,128,160,192,224,255};
  // Sacrifices some quality by not being a float but thats fine
  const int shades_stop = 256/shades_num;

  FILE *fp;
  fp = fopen("res.txt", "wb");
  if(fp == NULL){
    printf("file not opened. Error!");
    exit(1);
  }
  printf("file loaded!");

  // Check running time for opt
  clock_t start = clock();
  for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) {
      int i = (int)(pg) % (int)(gray_img);
      // Grayscale this mf
      *pg = ((*p + *(p + 1) + *(p + 2)) / 3.0);

      // I think this one is faster (we already know the nums are well behaved)
      // int p_check = ((int)(*pg) + shades_stop - 1) / shades_stop;
      // int p_check = (int)(*pg)/shades_stop + ((int)(*pg) % shades_stop != 0);
      // *pg = shades[p_check - 1];
      // Im fucking stupid: 
      *pg = shades[(int)(*pg / shades_stop)];

      if(i%width == 0){
        *pg = '\n';
      } 
      fputc(*pg, fp);

      // For alpha and shit
      if(channels == 4){
        *(pg + 1) = *(pg + 3);
      }
  }
  clock_t end = clock();
  float sec = (float)(end - start) / CLOCKS_PER_SEC;
  printf("This took %f seconds to run.", sec);

  // puts(gray_img);
  fclose(fp);

  // stbi_write_png("res/hot.png", width, height, channels, img, width * channels);
  // stbi_write_jpg("res/res.jpg", width, height, gray_channels, gray_img, 33);

  // Free mem
  stbi_image_free(img);
  free(gray_img);
}