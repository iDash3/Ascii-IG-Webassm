#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../stb/stb_image_resize.h"

int main(void){
  resize("../img/shp_og.jpg");
}

int resize(char path[]){

  int width, height, channels;
  unsigned char* img = stbi_load(path, &width, &height, &channels, 0);

  if(img == NULL){
    printf("Error ocurred while loading the image!");
    exit(1);
  }
  printf("Loaded the image with a size of %dx%d and channels %d \n", width, height, channels);


int new_width = 300;
int new_height = 300;
size_t image_size = new_height * new_width * channels;
unsigned char* output_pixels = malloc(image_size);
// unsigned char* output_pixels;
stbir_resize_uint8(img,width,height,0,output_pixels,new_width,new_height,0,channels);

  stbi_write_jpg("../res/resi.jpg", new_width, new_height, channels, output_pixels, 100);

  stbi_image_free(img);
  free(output_pixels);
}