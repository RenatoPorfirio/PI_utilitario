#ifndef __PPM__
#define __PPM__

#include "../padroes/RGB.hpp"
#include "../utilitarios/op.hpp"
#include <stdexcept>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using ops::isAlpha;
using ops::isNumber;

class PPM_Img : RGB_Img {
private:
  using RGB_Img::matriz;
  using RGB_Img::altura;
  using RGB_Img::largura;
  using RGB_Img::inicializar_matriz;
  using RGB_Img::profundidade_cor;

  void carregar(std::string caminho_arquivo) override{
    FILE *file = fopen(caminho_arquivo.c_str(), "r");
    if (file == NULL) exit(EXIT_FAILURE);
    char type[3];
   char trash[1024];
    uint32_t x, y;
    uint8_t or_color_depth;
    char test;
    long chkpt;

    do{
      do{
        chkpt = ftell(file);
        fscanf(file, "%c", &test);
      } while(!isNumber(test) && !isAlpha(test) && test != '#');
      if(test == '#'){
       fscanf(file, "%[^\n]", trash);
      } else if(test == 'P'){
        fseek(file, chkpt, SEEK_SET);
        fscanf(file, "%s", type);
      } else exit(EXIT_FAILURE);
    } while(test == '#');

    do{
      do{
        chkpt = ftell(file);
       fscanf(file, "%c", &test);
      } while(!isNumber(test) && !isAlpha(test) && test != '#');
     if(test == '#'){
        fscanf(file, "%[^\n]", trash);
     } else if(isNumber(test)){
        fseek(file, chkpt, SEEK_SET);
        fscanf(file, "%u %u", &x, &y);
     } else exit(EXIT_FAILURE);
    } while(test == '#');

    do{
     do{
        chkpt = ftell(file);
        fscanf(file, "%c", &test);
     } while(!isNumber(test) && !isAlpha(test) && test != '#');
     if(test == '#'){
       fscanf(file, "%[^\n]", trash);
     } else if(isNumber(test)){
       fseek(file, chkpt, SEEK_SET);
       fscanf(file, "%hhu", &or_color_depth);
      } else exit(EXIT_FAILURE);
    } while(test == '#');

    if (strcmp(type, "P3")) throw std::invalid_argument("Tipo da imagem incorreto!");
    inicializar_matriz(x, y);

   for (uint32_t i = 0; i < x; i++) {
      for (uint32_t j = 0; j < y; j++) {
       RGB_pixel *tmp = matriz[i][j];
        fscanf(file, "%hhu", &(*tmp)[0]);
        fscanf(file, "%hhu", &(*tmp)[1]);
        fscanf(file, "%hhu", &(*tmp)[2]);
      }
    }
    altura = x;
    largura = y;
    profundidade_cor = or_color_depth;
    fclose(file);
  }

public:
  PPM_Img(std::string caminho_arquivo){
    carregar(caminho_arquivo);
  }

  void salvar(std::string caminho_arquivo) override{
    FILE *file = fopen(caminho_arquivo.c_str(), "w");

    if(!file) exit(EXIT_FAILURE);
    fprintf(file, "P3\n");
    fprintf(file, "%u %u\n", altura, largura);
    fprintf(file, "%hhu\n", profundidade_cor);

    for(uint32_t i = 0; i < altura; i++){
      for(uint32_t j = 0; j < largura; j++){
        RGB_pixel *pixel = matriz[i][j];
        fprintf(file, "%hhu %hhu %hhu ", (*pixel)[0], (*pixel)[1], (*pixel)[2]);
      }
      fprintf(file, "\n");
    }
    
    fclose(file);
  }

  using RGB_Img::negativo;
  using RGB_Img::getHistograma;
};

#endif