#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointer to memory area
 * @b: byte to fill *s with
 * @n: number of bytes to be filled
 *
 * Return: pointer to the memory area 's'
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees an array of strings
 * @pp: array of strings
 */
void ffree(char **pp)
{
	char **temp = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous allocated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the reallocated block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: address of pointer to free
 *
 * Return: 1 if freed, otherwise 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

