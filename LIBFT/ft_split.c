/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:01:10 by mgreshne          #+#    #+#             */
/*   Updated: 2024/02/03 16:01:10 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count_word;

	i = 0;
	count_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count_word += 1;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count_word);
}

static size_t	ft_str_revers_len(const char *s, const char reject)
{
	size_t	word_len;

	word_len = 0;
	while (*s && *s != reject)
	{
		word_len++;
		s++;
	}
	return (word_len);
}

static size_t
	ft_split_word_in_array(char const *s, char c, char **after_split)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = ft_str_revers_len(s, c);
			if (word_len > 0)
			{
				after_split[i] = (char *)malloc((word_len + 1) * sizeof(char));
				if (after_split[i] == NULL)
					return (0);
				ft_memcpy(after_split[i], s, word_len);
				after_split[i][word_len] = '\0';
				i++;
			}
			s += word_len;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**after_split;
	size_t	count_words;
	size_t	i;

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c);
	if (count_words == 0)
	{
		after_split = (char **)malloc(sizeof(char *));
		if (after_split == NULL)
			return (NULL);
		after_split[0] = NULL;
		return (after_split);
	}
	after_split = (char **)malloc((count_words + 1) * sizeof(char *));
	if (after_split == NULL)
		return (NULL);
	i = ft_split_word_in_array(s, c, after_split);
	if (i == 0)
		return (NULL);
	after_split[count_words] = NULL;
	return (after_split);
}

/*int main(void)
{
	char str[] = "     ";
	char **result = ft_split(str, ' ');
	int i;

	if (result)
	{
		i = 0;
		while (result[i] != NULL)
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	else
	{
		printf("Error in ft_split\n");
	}

	return 0;
}*/
