#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command
 * @info: The shell information struct
 * @path: The path to the file
 *
 * Return: 1 if it is an executable command, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters
 * @str: The string to duplicate characters from
 * @start: The starting index
 * @stop: The stopping index
 *
 * Return: A pointer to the new duplicated string
 */
char *dup_chars(char *str, int start, int stop)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
	{
		if (str[i] != ':')
			buffer[j++] = str[i];
	}
	buffer[j] = '\0';
	return (buffer);
}

/**
 * find_path - Finds the full path of a command in the PATH string
 * @info: The shell information struct
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: The full path of the command if found, otherwise NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

