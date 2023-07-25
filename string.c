#include "main.h"

/**
 * _atoi - converts a string to an integer
 *
 * @s: string to be converted
 * Return: integer
 */
int _atoi(const char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;

	if (s[i] == '-')
	{
		sign *= -1;
		i = 1;
	}

	for (; s[i]; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
		}
		else
			return (-1);
	}

	return (sign * result);
}

/**
 * _strlen - get length of string
 * @s: A pointer to char
 *
 * computes the length of the string s up to,
 * but not including the terminating null character.
 *
 * Return: length of string
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len]; len++)
		;

	return (len);
}

/**
 *_strcmp - function to compare two strings
 *@s1: first string to be compared
 *@s2: second string to be compared
 *Return: 0: s1 = s2, +ve value: s1 > s2, -ve value: s1 < s2
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (s1[i] - s2[i]);
}

/**
 * _strdup - duple the string
 * @str: String
 *
 * A function that returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * Returns NULL if str = NULL.
 *
 * Return: A pointer to the duplicated string,
 * or NULL if insufficient memory was available.
 */
char *_strdup(const char *str)
{
	char *str_dup;
	int i, size;

	if (str == NULL)
		return (NULL);

	for (size = 0; str[size]; size++)
		;

	str_dup = malloc(sizeof(char) * (size + 1));
	if (str_dup == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		str_dup[i] = str[i];
	str_dup[i] = '\0';

	return (str_dup);
}

/**
 * str_concat - concatenates two strings.
 * @s1: First string
 * @s2: Second string
 *
 * The returned pointer should point to a newly allocated space
 * in memory which contains the contents of s1,
 * followed by the contents of s2, and null terminated
 * if NULL is passed, treat it as an empty string
 *
 * Return: A pointer to concatenated string or NULL on failure
 */
char *str_concat(const char *s1, const char *s2)
{
	char *str_concat;
	int s1_size;
	int s2_size;
	int i, j;

	if (s1 == NULL)
	{
		s1_size = 0;
	}
	else
	{
		for (s1_size = 0; s1[s1_size]; s1_size++)
			;
	}
	if (s2 == NULL)
	{
		s2_size = 0;
	}
	else
	{
		for (s2_size = 0; s2[s2_size]; s2_size++)
			;
	}

	str_concat = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (str_concat == NULL)
		return (NULL);

	for (i = 0; i < s1_size; i++)
		str_concat[i] = s1[i];

	for (j = 0; j < s2_size; j++, i++)
		str_concat[i] = s2[j];

	str_concat[i] = '\0';

	return (str_concat);
}
