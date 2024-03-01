#ifndef __RGB__
#define __RGB__

#include "../templates/Img.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>
using std::string;

class RGB_pixel;
//typedef struct RGB_Histograma RGB_Histograma;
class RGB_Img;

class RGB_pixel {
private:
	byte indexador[3];
public:
  RGB_pixel(byte r, byte g, byte b){
  	indexador[0] = r;
    indexador[1] = g;
    indexador[2] = b;
  }
  byte& operator[](int i){
  	return indexador[i];
  }
};

/*struct RGB_Histograma {
private:
  uint8_t escala;
public:
  uint32_t *R_abs;
  uint32_t *G_abs;
  uint32_t *B_abs;
  float *R_rel;
  float *G_rel;
  float *B_rel;
  uint32_t qnt_pixels;
  RGB_Img *ref_img;

  RGB_Histograma(RGB_Img *img, uint16_t escala);
  ~RGB_Histograma();
  string absToString();
  string relToString(uint8_t precisao = 2);
  uint8_t getEscala() { return escala; }
  void equalizar();
};*/

class RGB_Img : public Img{
protected:
	uint32_t largura, altura;
  uint8_t profundidade_cor;
	RGB_pixel ***matriz;
  void inicializar_matriz(uint32_t largura, uint32_t altura, RGB_pixel ***matriz = NULL){
    this->largura = largura;
		this->altura = altura;
		if(!matriz){
			matriz = new RGB_pixel**[altura];
			for(uint32_t i = 0; i < altura; i++){
				matriz[i] = new RGB_pixel*[largura];
        for(uint32_t j = 0; j < largura; j++){
          matriz[i][j] = new RGB_pixel(0, 0, 0);
        }
			}
		}
		this->matriz = matriz;
  }
	
public:
  RGB_Img(){}
	RGB_Img(uint32_t largura, uint32_t altura, RGB_pixel ***matriz = NULL){
		inicializar_matriz(largura, altura, matriz);
	}

  ~RGB_Img(){
  	for(uint32_t i = 0; i < this->altura; i++){
  		for(uint32_t j = 0; j < this->largura; j++){
  			delete this->matriz[i][j];
  		}
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

  /*RGB_Histograma getHistograma(uint8_t escala){
    return RGB_Histograma(this, escala);
  }*/

  RGB_pixel *getPixel(uint32_t linha, uint32_t coluna){
    return this->matriz[linha][coluna];
  }

  void negativo() override{
    for(uint32_t i = 0; i < altura; i++){
      for(uint32_t j = 0; j < largura; j++){
        RGB_pixel *pixel = matriz[i][j];
        (*pixel)[0] = profundidade_cor - (*pixel)[0];
        (*pixel)[1] = profundidade_cor - (*pixel)[1];
        (*pixel)[2] = profundidade_cor - (*pixel)[2];
      }
    }
  }  
};

/*RGB_Histograma::RGB_Histograma(RGB_Img *img, uint16_t escala){
  float tam_escala = (float)img->qntTons() / escala;
  qnt_pixels = img->getAltura() * img->getLargura();
  ref_img = img;
  R_abs = new uint32_t[escala]{};
  G_abs = new uint32_t[escala]{};
  B_abs = new uint32_t[escala]{};
  R_rel = new float[escala];
  G_rel = new float[escala];
  B_rel = new float[escala];
  this->escala = escala;
  
  for(uint32_t i = 0; i < img->getAltura(); i++){
    for(uint32_t j = 0; j < img->getLargura(); j++){
      RGB_pixel *pixel = img->getPixel(i, j);
      R_abs[(uint8_t)((float)(*pixel)[0] / tam_escala)]++;
      G_abs[(uint8_t)((float)(*pixel)[1] / tam_escala)]++;
      B_abs[(uint8_t)((float)(*pixel)[2] / tam_escala)]++;
    }
  }
  for(uint8_t i = 0; i < escala; i++){
    R_rel[i] = (float)R_abs[i] / qnt_pixels;
    G_rel[i] = (float)G_abs[i] / qnt_pixels;
    B_rel[i] = (float)B_abs[i] / qnt_pixels;
  }
}

RGB_Histograma::~RGB_Histograma(){
  delete[] R_abs;
  delete[] G_abs;
  delete[] B_abs;
}

string RGB_Histograma::absToString(){
  std::ostringstream str;
  str << "R_abs: [" << R_abs[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << R_abs[i];
  }
  str << "]\n";

  str << "G_abs: [" << G_abs[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << G_abs[i];
  }
  str << "]\n";

  str << "B_abs: [" << B_abs[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << B_abs[i];
  }
  str << "]\n";
  return str.str();
}

string RGB_Histograma::relToString(uint8_t precisao){
  std::ostringstream str;
  str << "R_rel: [" << std::fixed << std::setprecision(precisao) << R_rel[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << std::fixed << std::setprecision(precisao) << R_rel[i];
  }
  str << "]\n";

  str << "G_rel: [" << std::fixed << std::setprecision(precisao) << G_rel[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << std::fixed << std::setprecision(precisao) << G_rel[i];
  }
  str << "]\n";

  str << "B_rel: [" << std::fixed << std::setprecision(precisao) << B_rel[0];
  for(uint8_t i = 1; i < escala; i++){
    str << ", " << std::fixed << std::setprecision(precisao) << B_rel[i];
  }
  str << "]\n";
  return str.str();
}

void RGB_Histograma::equalizar(){
  float tam_escala = (float)ref_img->qntTons() / escala;
  float map_escala = (float)(ref_img->qntTons() - 1) / (escala - 1);
  float soma_R = 0, soma_G = 0, soma_B = 0;
  float R_acumulado[escala];
  float G_acumulado[escala];
  float B_acumulado[escala];
  for(uint32_t i = 0; i < escala; i++){
    soma_R += R_rel[i];
    soma_G += G_rel[i];
    soma_B += B_rel[i];
    R_acumulado[i] = soma_R;
    G_acumulado[i] = soma_G;
    B_acumulado[i] = soma_B;
  }
  for(uint32_t i = 0; i < ref_img->getAltura(); i++){
    for(uint32_t j = 0; j < ref_img->getLargura(); j++){
      RGB_pixel *pixel = ref_img->getPixel(i, j);
      uint8_t R_indice = round((escala - 1) * R_acumulado[(uint8_t)((float)(*pixel)[0] / tam_escala)]);
      uint8_t G_indice = round((escala - 1) * G_acumulado[(uint8_t)((float)(*pixel)[1] / tam_escala)]);
      uint8_t B_indice = round((escala - 1) * B_acumulado[(uint8_t)((float)(*pixel)[2] / tam_escala)]);
      (*pixel)[0] = round(R_indice * map_escala);
      (*pixel)[1] = round(G_indice * map_escala);
      (*pixel)[2] = round(B_indice * map_escala);
    }
  }
}*/

#endif