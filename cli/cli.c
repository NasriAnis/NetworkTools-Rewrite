#include <stdio.h>
#include "features/include/tokenizer.h"

int main(){
  char user_input[50];

  printf("Welcome to the Network Spoofer !\n");

  while(1) {
    printf("> ");
    fgets(user_input, 49, stdin);
    char **tokens = tokenize(user_input);

    printf("%s ", tokens[0]);
    printf("%s ", tokens[1]);
    printf("%s \n", tokens[2]);
  }
  return 0;
}
