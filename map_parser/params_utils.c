
#include "map_parser.h"

void freesher(char **words)
{
	int i = 0;

	if (words)
	{
		while (words[i])
		{
			free (words[i]);
			i++;
		}
	}
	free(words);
	words = NULL;
}

int word_counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i != 2)
		return (0);
	return (1);
}

int check_is_alone(char *line)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			count++;
		i++;
	}
	if ((line[0] == 'R' || line[0] == 'S' || line[0] == 'C'
		|| line[0] == 'F') && count < 2)
		return (0);
	else if (count < 3)
		return (0);
	return (1);
}
