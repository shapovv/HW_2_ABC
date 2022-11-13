#include <stdio.h>
#include <stdlib.h>

char *get_string(FILE *input, int *len, int *check) {
    *len = 0;
    *check = 0;
    int capacity = 1;
    char *s = (char*) malloc(sizeof(char));
    char c = fgetc(input);
    if(c > 127){
      (*check)++;
    }
    while (c != EOF) {
        s[(*len)++] = c;
        if (*len >= capacity) {
            capacity *= 2;
            s = (char*) realloc(s, capacity * sizeof(char));
        }
        c = fgetc(input);
	if(c > 127){
          (*check)++;
        }
    }
    s[*len] = '\0';
    return s;
}
void reverse(FILE *out, char *s, int len){
  char c;
  int counter;
  counter = len - 1;
  for(int i = 0; i < len / 2;i++){
        c = s[i];
	s[i] = s[counter];
	s[counter] = c;
	counter = counter - 1;
  }
}

int main(int argc, char * argv[]) {
  if(argc != 3){
      printf("Incorrect input!\n");
      return 0;
  }
  FILE *input = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  if((input == NULL) || (out == NULL)){
      printf("Incorrect file!\n");
      return 0;
  }
  int len, check;
  char *s = get_string(input, &len, &check);
  if(check == 0){
      reverse(out, s, len);
      fprintf(out, "%s", s);
      free(s);
      fclose(input);
      fclose(out);
      return 0;
  }
  else{
      fprintf(out, "Incorrect input!");
      free(s);
      fclose(input);
      fclose(out);
      return 0;
  }
}