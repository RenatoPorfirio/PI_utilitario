#ifndef __IMG_DEF__
#define __IMG_DEF__

#include <cstdint>

typedef uint8_t byte;

class Img {
protected:
  virtual void carregar(std::string caminho_arquivo) = 0;
  virtual void salvar(std::string caminho_arquivo) = 0;

public:
	virtual void negativo() = 0;
	void inverterVertical(){}
	void inverterHorizontal(){}
	void rotacionarEsquerda(){}
	void rotacionarDireita(){}
};

#endif