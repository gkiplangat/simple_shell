#include "shell.h"

/* Function declarations */
void exit_shell(void);
void print_environment(void);
void execute_command(char **cmd_tokens);

/**
 * main -entry point
 *
 * @ac: - argument count
 * @argv: - argument vector
 * Return: 0 on success
 */
int main(int ac, char **argv)
{
	char *prompt = "(ourshell) $ "; /*Holds the prompt message*/
	/*Buffer to store the what user typed in stdin*/
	char *lineptr = NULL;
	/*Buffer to store the copy of what user typed in stdin*/
	char *lineptr_copy = NULL;
	/*size of the memory to be allocated to the buffer*/
	size_t n = 0;
	/*stores the number of characters read by getline*/
	ssize_t written;
	const char *delim = " \n";    /*store delimeters*/
	int ntokens = 0;              /*number of tokens*/
	char *tokens;                 /*tokens generated*/
	char **cmd_tokens;
	int i;

	/* declaring void variables */
	(void)ac;
	(void)argv;

	/*creating a while loop*/
	while (1)
	{
	write(STDOUT_FILENO, prompt, strlen(prompt));

	written = getline(&lineptr, &n, stdin);

	if (written > 0 && lineptr[written - 1] == '\n')
	{
		lineptr[written - 1] = '\0';
	}


	/*exit shell*/
	if (strcmp(lineptr, "exit") == 0)
	{
		exit_shell();
	}

	/*print enviroment variables*/
	if (strcmp(lineptr, "env") == 0)
	{
	print_environment();
	continue;
	}
	/*Check whether it is the End Of File EOF*/
	if (written == EOF)
	{
		perror("Exiting ...");
		return (-1);
	}

	/*allocate space to store lineptr_copy*/
	lineptr_copy = malloc(sizeof(char) * written);

	/*Check wether memory allocation was successfully*/
	if (lineptr_copy == NULL)
	{
		perror("Error: memory allocation failed...\n");
		return (-1);
	}

	/*copy the content of lineptr to lineptr_copy*/
	strcpy(lineptr_copy, lineptr);

	/* split the string into an array of words */
	tokens = strtok(lineptr, delim);

	/* determine number of tokens*/
	while (tokens != NULL)
	{
		ntokens++;
		tokens = strtok(NULL, delim);
	}
	ntokens++;

	/*allocate space to hold array of strings*/
	cmd_tokens = malloc(sizeof(char *) * ntokens);
	tokens = strtok(lineptr_copy, delim);

	for (i = 0; tokens != NULL; i++)
	{
		cmd_tokens[i] = malloc(sizeof(char) * strlen(tokens));
		strcpy(cmd_tokens[i], tokens);
		tokens = strtok(NULL, delim);
	}
	cmd_tokens[i] = NULL;

	/* execute the command */
	execmd(cmd_tokens);

	/* write(STDOUT_FILENO, lineptr, strlen(lineptr)); */

	/*free up the allocated space*/

	free(lineptr);
	free(cmd_tokens);
	free(lineptr_copy);
	return (0);
}
