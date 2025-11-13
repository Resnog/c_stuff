#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer_str.h"
#include "some_math_threads.h"
#include "string_printing.h"

static inline void user_buffer_clean(void) {
  memset(word_buffer, buffer_empty_char, sizeof(word_buffer));
}

void user_buffer_get_all_words() {

  char word[BUFF_DEF_SIZE];
  memset(word, 0, sizeof(word));
  printf("User buffer contents:\n");
  for (int i = 0; i < BUFF_MAX_WORD_NUM; i++) {
    memcpy(word, word_buffer + BUFF_DEF_SIZE * i, sizeof(word));
    printf("Word %d:", i + 1);
    printf("%s\n", word);
    memset(word, 0, sizeof(word));
  }
  printf("\n");
}

void user_buffer_print() {
  for (int i = 0; i < BUFF_DEF_SIZE * BUFF_MAX_WORD_NUM; i++) {
    printf("%c", word_buffer[i]);
  }
  printf("\n");
}

void remove_new_line(char *word) {
  for (int i = 0; i < BUFF_DEF_SIZE; i++) {
    if (word[i] == '\n' || word[i] == '\0') {
      word[i] = buffer_empty_char;
    }
  }
}

void copy_word_to_buffer(char *word) {

  remove_new_line(word);

  write_index = write_index % BUFF_MAX_WORD_NUM;
  memcpy(word_buffer + BUFF_DEF_SIZE * write_index, word, sizeof(word));
  memset(word, 0, sizeof(word));
  write_index++;
}

void get_last_word() {
  char last_word[BUFF_DEF_SIZE];
  memcpy(last_word, word_buffer + BUFF_DEF_SIZE * (write_index - 1),
         sizeof(last_word));
  printf("Word >> %s", last_word);
}

int main() {

  char word[BUFF_DEF_SIZE];
  memset(word, 0, sizeof(word));

  user_buffer_clean();

  while (1) {

    word_buffer_print();
    fgets(word, BUFF_DEF_SIZE - 1, stdin);

    if (strcmp(word, "Exit\n") == 0) {
      printf("Input loop ending\n");
      break;
    }

    printf("Word is : %s | Write index %lu\n", word,
           BUFF_DEF_SIZE * write_index);

    copy_word_to_buffer(word);
  };

  word_buffer_get_last_word();

  user_buffer_get_all_words();

  return 0x00;
}
