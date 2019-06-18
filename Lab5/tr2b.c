#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// There must be 3 arguments: FROM and TO and our program counts as another one.
// So we check that argc is 3
int main(int argc, char** argv){
  if (argc != 3){
    fprintf(stderr, "Error! Incorrect number of arguments. Please provide two arguments only.\n");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

// Check if the inputted strings have the same length using strlen-- a builtin function to find the size of strings
  if (strlen(from) != strlen(to)){
    fprintf(stderr, "Error! Arguments must have the same size.\n");
    exit(1);
  }

// Check if there are duplicate bytes in FROM
  for (size_t i = 0; i < strlen(from); i++){
    for (size_t j = i+1; j < strlen(from); j++){
      if (from[i] == from[j]){
        fprintf(stderr, "Error! There are duplicate bytes in FROM.\n");
        exit(1);
      }
    }
  }

// Finally, transliterate the bytes from stdin to stdout
int curr = getchar();
while (curr != EOF){
  int put = 0;
  if(ferror(stdin)){
    fprintf(stderr, "Error reading file.\n");
    exit(1);
  }
  for (size_t a = 0; a < strlen(from); a++){
    if (from[a] == curr){
      putchar(to[a]);
      put = 1;
    }
  }
  if (put != 1){
    putchar(curr);
  }
  if (ferror(stdin)){
    fprintf(stderr, "Error writing file.\n");
    exit(1);
  }
  curr = getchar();
}
return 0;

}
