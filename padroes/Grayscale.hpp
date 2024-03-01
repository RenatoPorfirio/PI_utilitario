#ifndef __GRAYSCALE__
#define __GRAYSCALE__

#include "../templates/Img.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>
using std::string;

//typedef struct Grayscale_Histograma Grayscale_Histograma;
class Grayscale_Img;

/*struct Grayscale_Histograma {
private:
  uint8_t escala;
public:
  uint32_t *abs;
  float *rel;
  uint32_t qnt_pixels;
  Grayscale_Img *ref_img;

  RGB_Histograma(Grayscale_Img *img, uint16_t escala);
  ~RGB_Histograma();
  string absToString();
  string relToString(uint8_t precisao = 2);
  uint8_t getEscala() { return escala; }
  void equalizar();
};*/

class Grayscale_Img : public Img{
protected:
	uint32_t largura, altura;
  uint8_t profundidade_cor;
	byte **matriz;
  void inicializar_matriz(uint32_t largura, uint32_t altura, byte **matriz = NULL){
    this->largura = largura;
		this->altura = altura;
		if(!matriz){
			matriz = new byte*[altura];
			for(uint32_t i = 0; i < altura; i++){
				matriz[i] = new byte[largura];
			}
		}
		this->matriz = matriz;
  }
	
public:
  Grayscale_Img(){}
	Grayscale_Img(uint32_t largura, uint32_t altura, byte **matriz = NULL){
		inicializar_matriz(largura, altura, matriz);
	}

  ~Grayscale_Img(){
  	for(uint32_t i = 0; i < this->altura; i++){
  		delete [] this->matriz[i];
  	}
  	delete [] this->matriz;
  }

  uint16_t qntTons(){
    return (uint16_t)profundidade_cor + 1;
  }

  uint32_t getAltura(){
    return this->altura;
  }

  uint32_t getLargura(){
    return this->largura;
  }

  /*Grayscale_Histograma getHistograma(uint8_t escala){
    return Grayscale_Histograma(this, escala);
  }*/

  byte getPixel(uint32_t linha, uint32_t coluna){
    return this->matriz[linha][coluna];
  }

  void negativo() override{
    for(uint32_t i = 0; i < altura; i++){
      for(uint32_t j = 0; j < largura; j++){
        matriz[i][j] = profundidade_cor - matriz[i][j];
      }
    }
  }
};

#endif
