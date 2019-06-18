#include<stdio.h>
#include<stdlib.h>

int frobcmp(char const *a, char const *b){
  for (; *a != ' ' && *b != ' '; a++, b++){
    if ((((*a)^42) > ((*b)^42)) || *a == ' '){
      return 1;
    }
    if ((((*a)^42) < ((*b)^42)) || *b == ' '){
      return -1;
    }
  }
  return 0;
}

void input_error(){
  if(ferror(stdin) != 0){
    fprintf(stderr, "Cannot read input!");
    exit(1);
  }
}

void output_error(){
  if(ferror(stdin) != 0){
    fprintf(stderr, "Cannot print output!");
    exit(1);
  }
}

int comp(const void* a, const void* b){
  return frobcmp(*(const char**)a, *(const char**)b);
}


int main(void) {
  char* word = (char*)malloc(sizeof(char));
  char** arr = (char**)malloc(sizeof(char*));

  char curr_char = getchar();
  input_error();
  char curr_arr = getchar();
  input_error();

  int w_i = 0;
  int a_i = 0;

  while(curr_char != EOF && !ferror(stdin)){
    word[w_i] = curr_char;
    char* temp = realloc(word, sizeof(char) * (w_i+2));

    if (temp != NULL){
      word = temp;
    }
    else{
      free(word);
      fprintf(stderr, "Error allocating memory");
      exit(1);
    }

    if (curr_char == ' '){
      arr[a_i] = word;
      char** temp = realloc(arr, sizeof(char*) * (a_i+2));

      if(temp != NULL){
        arr = temp;
        a_i++;
        word = NULL;
        word = (char*)malloc(sizeof(char));
        w_i = -1;
      }
      else{
        free(arr);
        fprintf(stderr, "Error allocating memory");
        exit(1);
      }
    }

    if (curr_arr == EOF && curr_char == ' '){
      break;
    }
    else if (curr_char == ' ' && curr_arr == ' '){
      while (curr_char == ' '){
        curr_char = getchar();
        input_error();
      }
      curr_arr = getchar();
      input_error();
      w_i++;
      continue;
    }
    else if (curr_arr == EOF){
      curr_char = ' ';
      w_i++;
      continue;
    }
    curr_char = curr_arr;
    curr_arr = getchar();
    input_error();
    w_i++;
  }

  qsort(arr, a_i, sizeof(char*), comp);

  for (size_t a = 0; a < a_i; a++){
    for (size_t b = 0; ; b++){
      putchar(arr[a][b]);
      output_error();
      if (arr[a][b] == ' '){
        break;
      }
    }
  }

    for(size_t i = 0; i < a_i; i++){
      free(arr[i]);
    }
    free(arr);
    exit(0);
}

