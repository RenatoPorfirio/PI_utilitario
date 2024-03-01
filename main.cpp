#include <iostream>
#include "formatos/PPM.hpp"
#include "formatos/PGM.hpp"


using std::cout;
using std::endl;

void teste_PGM_neg();
void teste_PPM_neg();

int main(){
  //teste_PGM_neg();
  teste_PPM_neg();
  return 0;
}

void teste_PGM_neg(){
  PGM_Img img("teste/pgm/feep.pgm");
  img.negativo();
  img.salvar("teste/pgm/feep_neg.pgm");
}

void teste_PPM_neg(){
  PPM_Img img("teste/ppm/lua.ppm");
  img.negativo();
  img.salvar("teste/ppm/lua_neg.ppm");
}