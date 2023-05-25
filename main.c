#include "shell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT}; /* Initialize info structure */
	int fd = 2; /* File descriptor */

	/* Using assembly code to manipulate the file descriptor */
	asm(
		"mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	/* Check if a file is specified as a command line argument */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY); /* Open the file in read-only mode */
		if (fd == -1)
		{
			/* Handle file open errors */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; /* Set the file descriptor for reading input */
	}

	populate_env_list(info); /* Populate the environment list */
	read_history(info); /* Read command history from file */
	hsh(info, av); /* Call the shell function */
	return (EXIT_SUCCESS);
}

