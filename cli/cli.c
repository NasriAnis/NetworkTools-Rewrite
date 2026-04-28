#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "features/include/tokenizer.h"

#include "../src/NetworkScans/include/ping.h"

int main(){
  int count;
  char user_input[50];

  printf("Welcome to the Network Spoofer !\n");

  while(1) {
    printf("> ");
    fgets(user_input, 49, stdin);
    char **tokens = tokenize(user_input);

    for (int i = 0; i>=0; i++){
      if (tokens[i]==NULL){
        count = i;
        break;
      }
    }

    if (strcmp(tokens[0], "ping") == 0){
      ping(tokens);
    }

    // free tokens before reusing
    free(tokens);
  }
  return 0;
}
