#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void CreateEmptyStack (Stack *S){
  Top(*S) = NilStack;
};

boolean IsStackEmpty (Stack S){
  return Top(S) == NilStack;
};

void Push (Stack * S, infotypeStack X){
  if (!IsStackEmpty(*S)) {
    // if(Top(*S) == 10){
    //   realloc();
    // }
    Top(*S)++;
  } else {
    Top(*S) = 1;
  }
  InfoTop(*S) = X;
  // printf("c");
};

void Pop (Stack * S, infotypeStack* X){
  *X = InfoTop(*S);
  Top(*S)--;
}
