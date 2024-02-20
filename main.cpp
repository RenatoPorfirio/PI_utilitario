#include <iostream>
#include "formatos/PPM.hpp"


using std::cout;
using std::endl;

int main(){
  PPM_Img img("teste/ppm/pimentoes.ppm");
  {
    RGB_Histograma histograma = img.getHistograma(64);
    cout << histograma.relToString(3);
    histograma.equalizar();
  }
  cout << endl;
  //img.negativo();
  /*{
    RGB_Histograma histograma = img.getHistograma(8);
    cout << histograma.relToString(3);
  }*/
  img.salvar("teste/ppm/pimentoes_eq.ppm");
  return 0;
}