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
	va_list args;

	va_start(args, format); /* Initialize the variable argument list */

	if (format == NULL)
		return (-1);

	while (*format)
	{
		/* If a format specifier, write the character */
		if (*format != '%')
		{
			/* If not a format specifier, write the character */
			write(1, format, 1);
			char_print++;
		}
		else
		{
			/* Handle format specifiers and update count */
			char_print += handle_format_specifier(args, &format);
		}
		format++;
	}
	va_end(args); /* Clean up the variable argument list */
	return (char_print);
}
