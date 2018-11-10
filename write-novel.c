/* Name: Ane Søgaard Jørgensen
 * Date: 01/11-2018
 * Description: A C-program that writes a novel,
                based on the 3000 most used words in English,
                found on https://bit.ly/2Fg3K9r
 */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <time.h>

# define WORD_COUNT 3000
# define WORD_LEN 60
# define NOVEL_LENGTH 50000

typedef struct {
  char string[WORD_LEN];
} word;

int novelWriter(word *);
int fillWords(word *);
void listPrinter(const word *);

int main (void) {
   word word_list[WORD_COUNT];

   time_t t;
   srand((int) time(&t));

   fillWords(word_list);

   novelWriter(word_list);

   return 0;
}

int novelWriter(word *word_list) {
  FILE *fP;
  int i = 0;

  fP = fopen("novel.txt", "w");

  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }

  while (i < 50000) {
    fprintf(fP, "%s ", word_list[rand() % 3000].string);

    i++;
  }
  fclose(fP);

  return 0;
}

int fillWords(word *word_list) {
  FILE *fP;

  fP = fopen("word-list.txt", "r");

  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }

  for (int i = 0; i < WORD_COUNT; i++) {
    fscanf(fP, "%s", word_list[i].string);
  }

  fclose(fP);
  return 0;
}

void listPrinter(const word *word_list) {
  for (int i = 0; i < WORD_COUNT; i++) {
    printf("%4d | %s\n", i, word_list[i].string);
  }
}
