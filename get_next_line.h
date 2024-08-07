/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:50:11 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 14:02:47 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct node
{
	char		*str;
	struct node	*next;
}	t_node;

char	*get_next_line(int fd);
int		free_all(t_node **linked_list);
char	*get_line(t_node *linked_list, size_t *str_len);
int		node_concat(t_node **first_node, char *buf, t_node **last_node);
int		node_creation(t_node **list, int fd, t_node **last_node, size_t *s_len);
int		custom_malloc(void **allocate, size_t size, t_node **linked_list);
int		has_new_line(t_node *node_to_check, size_t *str_len);
int		node_to_str(t_node *linked_list, char *line);
int		surplus_treatment(t_node **list, t_node **last_node);
int		list_redefine(t_node **linked_list, t_node *clean_node, char *buf);

#endif
