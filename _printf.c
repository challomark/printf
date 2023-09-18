#include "main.h"

/**
 * _printf - This is a custom printf function
 * @format: The format string
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int char_print = 0;
	char *string_arg;
	char char_arg;
	va_list args;

	va_start(args, format); /* Initialize the variable argument list */
	while (*format)
	{ /* If a format specifier, write the character */
		if (*format == '%')
		{
			format++; /* Move past '%' */
			switch (*format)
			{
				case 'c':/* Fetch char argument */
					char_arg = va_arg(args, int);
					char_print += write(1, &char_arg, 1); /* Write the character */
					break;
				case 's':/* Fetch string argument */
					string_arg = va_arg(args, char *);
					if (string_arg == NULL)
						string_arg = "(null)"; /* Write each character of the string */
					char_print += write(1, string_arg, _strlen(string_arg));
					break;
				case '%':/* Write the '%' character */
					char_print += write(1, "%", 1);
					break;
				default:/* Print the '%' character if unknown specifier */
				char_print += write(1, "%", 1);
				char_print += write(1, &(*format), 1);
				break;
			}
		}
		else
		{
			char_print += write(1, &(*format), 1);
		}
		format++;
	}
	va_end(args); /* Clean up the variable argument list */
	return (char_print);
}
