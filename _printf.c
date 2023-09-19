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
	{ /* If a format specifier, write the character */
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

/**
 * handle_format_specifier - Handles a format specifier and prints the value
 * @args: The va_list containing the arguments
 * @format: A pointer to the current position in the format string
 *
 * Return: The number of characters printed for this specifier
 */
int handle_format_specifier(va_list args, const char **format)
{
	int char_print = 0;
	char buffer[12]; /* Buffer to store the integer as a string */
	int len = 0;
	int num;

	(*format)++; /* Move past '%' */

	switch (**format)
	{
		case 'c':
		{
			char c = va_arg(args, int); /* Fetch char argument */

			write(1, &c, 1); /* Write the character */
			char_print++;
			break;
		}
		case 's':
		{
			char *str = va_arg(args, char *); /* Fetch string argument */

			if (str == NULL)
				str = "(null)";
			while (*str)
			{
				write(1, str, 1); /* Write each character of the string */
				str++;
				char_print++;
			}
			break;
		}
		case '%':
			write(1, "%", 1); /* Write the '%' character */
			char_print++;
			break;
		case 'd':
		case 'i':
		{
			num = va_arg(args, int); /* Fetch integer argument */

			if (num < 0)
			{
				write(1, "-", 1); /* Write the negative sign for negative numbers */
				char_print++;
				num = -num; /* Make num positive for conversion */
			}

			do {
				buffer[len++] = num % 10 + '0';
				num /= 10;
			} while (num > 0);
			/* Write the digits in reverse order */
			while (len > 0)
			{
				write(1, &buffer[--len], 1);
				char_print++;
			}
			break;
		}
		default:
			write(1, "%", 1); /* Print the '%' character if unknown specifier */
			write(1, *format, 1);
			char_print += 2;
			break;
	}
	return (char_print);
}
