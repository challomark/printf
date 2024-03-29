#ifndef MAIN_H
#define MAIN_H
#define BUFFER_SIZE 1024
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int _printf(const char *format, ...);
int handle_format_specifier(va_list args, const char **format);
int print_binary(va_list args);

#endif
