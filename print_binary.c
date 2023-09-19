#include "main.h"

/**
 * print_binary - Converts and prints an unsigned integer in binary format
 * @args: The va_list containing the unsigned integer argument
 *
 * Return: The number of characters printed
 */
int print_binary(va_list args)
{
	int len = 0;
	/* Buffer to store the binary representation (up to 32 bits) */
	char buffer[33];

	char_print = 0;
	unsigned int number = va_arg(args, unsigned int);

	if (number == 0)
	{
		write(1, "0", 1); /* Handle the special case of 0 */
		return (1);
	}

	while (number > 0)
	{
		/* Extract and convert the least significant bit */
		buffer[len++] = (number & 1) + '0';
		number >>= 1; /* Shift right to process the next bit */
	}

	/* Write the binary representation in reverse order */
	while (len > 0)
	{
		write(1, &buffer[--len], 1);
		char_print++;
	}

	return (char_print);
}
