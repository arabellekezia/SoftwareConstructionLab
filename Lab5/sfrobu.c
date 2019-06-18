#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <ctype.h>

// compare frobnicated arrays, like old sfrob.c
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

// comp function based on old sfrob.c
int comp(const void* a, const void* b){
  return frobcmp(*(char**)a, *(char**)b);
}

// new fromcmp for -f flags
int ffrobcmp(char const *a, char const *b)
{
  for(;; a++, b++)
  {
    char f_a = *a^42;
    char f_b = *b^42;

    if(f_a >= 0 && f_a <= UCHAR_MAX){
      f_a = toupper(f_a);
    }
    if (f_b >= 0 && f_b <= UCHAR_MAX){
      f_b = toupper(f_a);
    }
    else if (f_a < f_b || *a == ' '){
      return 1;
    }
    else if ( f_a > f_b || *b == ' '){
      return 1;
    }
  }
}

int fcomp(const void* a,const void* b)
{
  return ffrobcmp(*(char**) a, *(char**) b);
}

void mem_error(void *ptr)
{
  if (ptr == NULL)
    {
      fprintf(stderr, "Memory allocation error.");
      free(ptr);
      exit(1);
    }
  return;
}

int main(int argc, char* argv[])
{
  if (argc > 2){
    fprintf(stderr, "Error! Too many arguments.");
    exit(1);
  }

  int fflag = 0;
  if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'f'){
    fflag = 1;
  }

  struct stat f_stat;

  if(fstat(0,&f_stat) < 0){
      fprintf(stderr, "Unable to read, IO error with fstat.");
      exit(1);
    }

  char* temp;
  char* word = (char*)malloc(sizeof(char));
  char** arr = (char**)malloc(sizeof(char*));
  int count_word = 0;
  int count_arr = 0;
  char curr, next;

  if (S_ISREG(f_stat.st_mode)){
    temp = (char*)malloc(sizeof(char) * (f_stat.st_size+2));

    // read file and set it to curr and next
    read(0, temp, f_stat.st_size);
    curr = temp[0];
    next = temp[1];

    for (int count = 2; count < f_stat.st_size+2; count++){
      word[count_word] = curr;
      char* temp_word = realloc(word, sizeof(char) * (count_word+2));
      mem_error(temp_word);
      word = temp_word;
      
      if (curr == ' '){
        arr[count_arr] = word;
        char** temp_arr = realloc(arr, sizeof(char*) * (count_arr+2));
        mem_error(temp_arr);
        arr = temp_arr;
        count_arr++;
        word = NULL;
        word = (char*)malloc(sizeof(char));
        mem_error(word);
        count_word = -1;
      }

      if (curr == ' ' && count >= f_stat.st_size){
        break;
      }
      else if (curr != ' ' && count >= f_stat.st_size){
        curr = ' ';
        count_word++;
        continue;
      }
      curr = next;
      next = temp[count];
      count_word++;
    }
  }


    word = NULL;
    word = (char*)malloc(sizeof(char));

    int check_curr = read(0, &curr, 1);
    int check_next = read(0, &next, 1);
    count_word = 0;

    while (check_curr > 0){
      word[count_word] = curr;
      char* temp_word = realloc(word, sizeof(char) * (count_word+2));
      mem_error(temp_word);
      word = temp_word;

      if (curr == ' '){
        arr[count_arr] = word;
        char** temp_arr = realloc(arr, sizeof(char*) * (count_arr+2));
        mem_error(temp_arr);
        arr = temp_arr;
        count_arr++;
        word = NULL;
        word = (char*)malloc(sizeof(char));
        mem_error(word);
        count_word = -1;
      }
      
      if (curr == ' ' && check_next < 1){
        break;
      }
      else if (curr != ' ' && check_next < 1){
        curr = ' ';
        count_word++;
        continue;
      }
      curr = next;
      check_next = read(0, &next, 1);
      count_word++;
    }

    if (fflag){
      qsort(arr, count_arr, sizeof(char*), fcomp);
    }
    else{
      qsort(arr, count_arr, sizeof(char*), comp);
    }

    int counter = 0;
    while (counter < count_arr){
      for (int i = -1; arr[counter][i] != ' ';){
        i++;
        write(1, &arr[counter][i], 1);
      }
      counter++;
    }

    for (int j = 0; j < count_arr; j++){
      free(arr[j]);
    }
    free(arr);
    free(temp);
    exit(0);
}
