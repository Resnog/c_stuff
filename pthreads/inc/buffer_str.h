#ifndef BUFFER_STR_H
#define BUFFER_STR_H

#include <stddef.h>

enum buffer_symbol { buffer_empty_char = '#' };

#define BUFF_DEF_SIZE (16)
#define BUFF_MAX_WORD_NUM (3)

char word_buffer[BUFF_DEF_SIZE * BUFF_MAX_WORD_NUM];
size_t write_index = 0;

static inline void word_buffer_clean(void);

void _remove_line(char *word);

void word_buffer_get_last_word(void);

void word_buffer_thread(void);

void word_buffer_print(void);

void word_buffer_thread(void);

#endif // BUFFER_STR_H
