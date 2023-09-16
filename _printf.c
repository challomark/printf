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
	/* Check for NULL format string */
	if (format == NULL)
		return (-1);
	/* Initialize the variable argument list */
	va_start(args, format);

	while (*format)
	{ /* If not a format specifier, write the character */
		if (*format != '%')
		{
			write(1, format, 1);
			char_print++;
		}
		else
		{ /* Handle format specifiers */
			format++; /* Move past '%' */
			switch (*format)
			{
				case 'c':
				{ /* Fetch char argument */
					char c = va_arg(args, int);

					write(1, &c, 1); /* Write the character */
					char_print++;
					break;
				}
				case 's':
				{ /* Fetch string argument */
					char *string = va_arg(args, char *);

					if (string == NULL)
						string = "(null)";
					while (*string)
					{ /* Write each character of the string */
						write(1, string, 1);
						string++;
						char_print++;
					}
					break;
				}
				case '%':
				{ /* Write the '%' character */
					write(1, "%", 1);
					char_print++;
					break;
				}
				default: /* Print the '%' character if unknown specifier */
				write(1, "%", 1);
				write(1, format, 1);
				char_print += 2;
				break;
			}
		}
		format++;
	}

	va_end(args); /* Clean up the variable argument list */
	return (char_print);
}
