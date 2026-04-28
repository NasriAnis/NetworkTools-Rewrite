#include <string.h>
#include <stdlib.h>

char** tokenize(char *input)
{
/* Parse user input into tokens
* Return a pointer to pointers
* allocated using malloc + a
* NULL delimiter at the end. */

  char **token_alloc = NULL;
  char *token;
  char **tmp;
  int i = 1;

  token = strtok(input, " ");

  while (token != NULL)
  {

    if (strcmp(token, "\n") == 0) {
      token = strtok(NULL,  " ");
      continue;
    }

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
  tmp = realloc(token_alloc, i * sizeof(char*));
  if (tmp == NULL){
    free(tmp);
    return NULL;
  } else { token_alloc = tmp; }

  token_alloc[i-1] = NULL;

  return token_alloc;
}
