#ifndef __PGM__
#define __PGM__

#include "../padroes/Grayscale.hpp"
#include "../utilitarios/op.hpp"
#include <stdexcept>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using ops::isAlpha;
using ops::isNumber;

class PGM_Img : Grayscale_Img {
private:
  using Grayscale_Img::matriz;
  using Grayscale_Img::altura;
  using Grayscale_Img::largura;
  using Grayscale_Img::inicializar_matriz;
  using Grayscale_Img::profundidade_cor;

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

    if (strcmp(type, "P2")) throw std::invalid_argument("Tipo da imagem incorreto!");

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

    inicializar_matriz(x, y);

   for (uint32_t i = 0; i < y; i++) {
      for (uint32_t j = 0; j < x; j++) {
        fscanf(file, "%hhu", &matriz[i][j]);
      }
    }
    largura = x;
    altura = y;
    profundidade_cor = or_color_depth;
    fclose(file);
  }

public:
  PGM_Img(std::string caminho_arquivo){
    carregar(caminho_arquivo);
  }

  void salvar(std::string caminho_arquivo) override{
    FILE *file = fopen(caminho_arquivo.c_str(), "w");

    if(!file) exit(EXIT_FAILURE);
    fprintf(file, "P2\n");
    fprintf(file, "%u %u\n", largura, altura);
    fprintf(file, "%hhu\n", profundidade_cor);

    for(uint32_t i = 0; i < altura; i++){
      for(uint32_t j = 0; j < largura; j++){
        fprintf(file, "%hhu ", matriz[i][j]);
      }
      fprintf(file, "\n");
    }
    
    fclose(file);
  }

  using Grayscale_Img::negativo;
};

#endif