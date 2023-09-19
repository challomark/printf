#include "main.h"
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
	char buffer[40]; /* Buffer to store the integer as a string */
	int len = 0;
	int number;
	unsigned int unint_num; /* Variable to store unsigned integer arguments */
	int character;

	(*format)++; /* Move past '%' */
	
	switch (**format)
	{
		case 'c':
			/* Handle character specifier */
			character = va_arg(args, int);
			buffer[len++] = character;

			char_print += write(1, &character, 1);
			break;
		case 's':
			/* Handle string specifier */
			char_print += write(1, va_arg(args, char *), 0);
			break;
		case '%':
			/* Handle '%' specifier */
			char_print += write(1, "%", 1); /* Write '%' */
			break;
		case 'd':
		case 'i':
			/* Handle integer specifiers ('d' and 'i') */
			number = va_arg(args, int); /* Get the integer argument */
			char_print += number < 0 ? write(1, "-", 1) : 0;
			number = number < 0 ? -number : number;
			/* Make num positive for conversion */
			do {
				buffer[len++] = number % 10 + '0';
				/* Extract and convert digits */
				number /= 10;
			} while (number > 0);
			/* Write the digits in reverse order */
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		case 'b':
			/* Handle custom binary specifier '%b' */
			unint_num = va_arg(args, unsigned int);
			/* Get the unsigned integer argument */
			if (unint_num == 0)
			{
				char_print += write(1, "0", 1);
				/* Handle the special case of 0 */
				break;
			}
			while (unint_num > 0)
			{
				buffer[len++] = (unint_num & 1) + '0';
				/* Extract and convert binary digits */
				unint_num >>= 1;
			}
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		case 'u':
			/* Handle 'u' specifier for unsigned integers */
			unint_num = va_arg(args, unsigned int);
			do {
				buffer[len++] = unint_num % 10 + '0';
				unint_num /= 10;
			} while (unint_num > 0);
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		case 'o':
			/* Handle 'o' specifier for octal numbers */
			unint_num = va_arg(args, unsigned int);
			do {
				buffer[len++] = (unint_num % 8) + '0';
				unint_num /= 8;
			} while (unint_num > 0);
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		case 'x':
			/* Handle 'x' specifier for lowercase hexadecimal */
			unint_num = va_arg(args, unsigned int);
			do {
				int digit = unint_num % 16;

				buffer[len++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
				unint_num /= 16;
			} while (unint_num > 0);
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		case 'X':
			/* Handle 'X' specifier for uppercase hexadecimal */
			unint_num = va_arg(args, unsigned int);
			do {
				int digit = unint_num % 16;

				buffer[len++] = digit < 10 ? digit + '0' : digit - 10 + 'A';
				unint_num /= 16;
			} while (unint_num > 0);
			while (len > 0)
				char_print += write(1, &buffer[--len], 1);
			break;
		default:
			/* Handle unknown specifier */
			char_print += write(1, "%", 1) + write(1, *format, 1);
	}
	return (char_print);
}
