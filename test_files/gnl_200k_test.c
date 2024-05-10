/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_200k_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:55:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/05/10 11:29:09 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

int main(void) 
{
    int fd;
    char *line;

    fd = open("200k_file_test.txt", O_RDONLY);
    if (fd == -1) 
	{
        printf("Failed to open the file\n");
        return 1; // Return an error code
    }
    line = get_next_line(fd);
    printf("Processed");
    close(fd);
    return (0);
}
