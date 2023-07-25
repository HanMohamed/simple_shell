#include "main.h"

/**
 * list_path_directory - creates a linked list of PATH
 *
 * Return: a linked list of PATH
 */
list_path *list_path_directory(void)
{
	char *path_line = _getenv("PATH");
	char *path_without_delim = NULL;
	char *cpy_path_line = NULL;
	char *delim = ": ";
	list_path *head = NULL;
	list_path *new_node = NULL;

	cpy_path_line = _strdup(path_line);
	path_without_delim = strtok(cpy_path_line, delim);
	while (path_without_delim != NULL)
	{
		new_node = add_node_end(&head, path_without_delim);
		if (new_node == NULL)
		{
			free(cpy_path_line);
			free_list(head);
			return (NULL);
		}
		path_without_delim = strtok(NULL, delim);
	}
	free(cpy_path_line);
	free(path_without_delim);
	return (head);
}

/**
 * add_node_end - adds a new node at the end of a list_path list
 * @head: head to a linked list
 * @str: string element to store
 *
 * Return: the address of the new element, or NULL if it failed
 */
list_path *add_node_end(list_path **head, const char *str)
{
	list_path *new_node;
	list_path *current_node;

	new_node = malloc(sizeof(list_path));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = _strdup(str);
	new_node->next_node = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (*head);
	}

	current_node = *head;
	while (current_node->next_node != NULL)
		current_node = current_node->next_node;
	current_node->next_node = new_node;

	return (new_node);
}

/**
 * free_list - frees a list_path list
 * @head: head to a linked list
 *
 * a function that frees a list_path list.
 */
void free_list(list_path *head)
{
	list_path *current_node;

	while (head != NULL)
	{
		current_node = head;
		head = head->next_node;
		free(current_node->dir);
		free(current_node);
	}
}
