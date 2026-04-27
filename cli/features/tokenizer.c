#include <string.h>
#include <stdlib.h>

// Parse user input into tokens
char** tokenize(char *input){
  char **token_alloc = NULL;
  char *token;
  char **tmp;
  int i = 1;

  token = strtok(input, " ");

  while (token != NULL){
    tmp = realloc(token_alloc, i * sizeof(char*));

    if (tmp == NULL){
      free(tmp);
      return NULL;
    }
    else {
      token_alloc = tmp;
    }

    token_alloc[i-1] = token;

    i = i + 1;
    token = strtok(NULL,  " ");
  }

  // adding a NULL delimiter
  i++;
  tmp = realloc(token_alloc, i * sizeof(char*));

  if (tmp == NULL){
    free(tmp);
    return NULL;
  } else { token_alloc = tmp; }

  token_alloc[i-1] = NULL;

  return token_alloc;
}
