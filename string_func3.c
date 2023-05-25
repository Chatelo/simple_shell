#include "shell.h"

/**
 * **strtow - splits a string into words.
 * @str the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings or NULL on err
 */

char **strtow(char *str, char *d)
{
	int i, a, b, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, a = 0; a < numwords; a++)
	{
		while (is_delim(str[i], d))
			i++;
		b = 0;
		while (!is_delim(str[i + b], d) && str[i + b])
			b++;
		s[a] = malloc((b + 1) * sizeof(char));
		if (!s[a])
		{
			for (b = 0; b < a; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < b; m++)
			s[a][m] = str[i++];
		s[a][m] = 0;
	}
	s[a] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string
 * @str: the input str
 * @d: the delim
 * Return: a pointer to an array of str, or NULL on err
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
