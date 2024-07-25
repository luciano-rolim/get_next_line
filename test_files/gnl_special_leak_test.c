/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_special_leak_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:55:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/07/25 14:03:56 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>

#include "../get_next_line.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif


int main() 
{
    const char *filename = "test_file.txt";
    int fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    const char *text = "Hello\nWorld";
    if (write(fd, text, 11) != 11) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    lseek(fd, 0, SEEK_SET);

    char *line = get_next_line(fd);
    if (line) {
        printf("First call to get_next_line: %s", line);
        free(line);
    }

    line = get_next_line(-1);
    if (line == NULL) {
        printf("get_next_line correctly returned NULL after called with -1\n");
    } else {
        printf("Unexpected behavior: get_next_line did not return NULL. It returned: '%s'\n", line);
        free(line);
    }

    close(fd);
    remove(filename);
}
