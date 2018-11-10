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
# include <ctype.h>

# define WORD_COUNT 3000
# define WORD_LEN 60

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

/* Writes a novel to a .tex file */
int novelWriter(word *word_list) {
  FILE *fP;
  int i = 1;
  int a, b, c;
  int WORDS = 50000;

  /* Opens the novel file */
  fP = fopen("novel-files/novel.tex", "w");

  /* Checks to see if the file was found */
  if (fP == NULL) {
     perror("Error opening file");
     return -1;
  }

  c = rand() % 3000;

  fprintf(fP, "\\documentclass{article}\n");
  fprintf(fP, "\\begin{document}\n");

  /* Printes a headline */
  if (islower(word_list[c].string[0])) {

    word_list[c].string[0] = (char)((int)(word_list[c].string[0] - 32));
    fprintf(fP, "\\section*{%s}\n", word_list[c].string);
    word_list[c].string[0] = (char)((int)(word_list[c].string[0] + 32));
  }

  else {
    fprintf(fP, "\\section{%s}\n", word_list[c].string);
  }


  /* Prints words to the .tex file */
  while (i <= WORDS) {
    a = (rand() % 10) + 10;
    b = rand() % 3000;

    /* Makes the first letter in the file capitalized */
    if (i == 1) {
      word_list[b].string[0] = (char)((int)(word_list[b].string[0] - 32));
      fprintf(fP, " %s", word_list[b].string);
      word_list[b].string[0] = (char)((int)(word_list[b].string[0] + 32));
    }

    /* Inputs linechanges here and there. Makes the first letter after a punctuation capitalized */
    else if (i % a == 0) {
      fprintf(fP, ".\\\\\n");
      if (islower(word_list[b].string[0])) {

        word_list[b].string[0] = (char)((int)(word_list[b].string[0] - 32));
        fprintf(fP, " %s", word_list[b].string);
        word_list[b].string[0] = (char)((int)(word_list[b].string[0] + 32));
      }
    }

    else {
      fprintf(fP, " %s", word_list[b].string);
    }

    i++;
  }

  fprintf(fP, "\n\\end{document}");

  fclose(fP);
  return 0;
}

/* Fills an array with words */
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

/* Prints a list of words */
void listPrinter(const word *word_list) {
  for (int i = 0; i < WORD_COUNT; i++) {
    printf("%4d | %s\n", i, word_list[i].string);
  }
}
