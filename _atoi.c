#include "shell.h"

/**
 * interactive - returns 1 if shell is interactive mode
 * or 0 if not in interactive mode.
 * 
 * @struct address
 * Printf; 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks the character if its delimeter
 * @charc: the char to check
 * #delim: the delimeter string
 * Output: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - check the alphabetic character
 * Output is 1 if c is alphabetic, else 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert a string into an integer
 * 
 * #n is the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *n)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; n[i] != '\0' && flag != 2; i++)
	{
		if (n[i] == '-')
			sign *= -1;

		if (n[i] >= '0' && n[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (n[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
