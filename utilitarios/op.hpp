#ifndef __UTILITARIOS_IMG__
#define __UTILITARIOS_IMG__

namespace ops{
  uint8_t isNumber(char c){return ('0' <= c && c <= '9') ? 1 : 0;}
  uint8_t isAlpha(char c){return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ? 1 : 0;}
};

#endif