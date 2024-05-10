/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_common _tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:55:08 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/05/10 11:28:39 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

void create_and_write_file(char *filename, char *content) 
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    write(fd, content, strlen(content));
    close(fd);
}

void read_and_print_lines(char *filename, int num_calls) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    char *line;
    for (int i = 0; i < num_calls; i++) {
        line = get_next_line(fd);
        if (line) {
            printf("Line %d: %s\n", i + 1, line);
            free(line);
        } else {
            printf("Line %d: NULL\n", i + 1);
        }
    }
    close(fd);
}

void delete_file(char *filename) 
{
    if (remove(filename) == 0) {
        printf("Deleted file %s successfully\n", filename);
    } else {
        perror("Error deleting file");
    }
}

int main(void) 
{
    int fd;
    char *line;
    char *filename = "test_file.txt";

    printf("\n%s\n", "Test 1: File with none content");
    create_and_write_file(filename, "");
    read_and_print_lines(filename, 2);
    delete_file(filename);

    printf("\n%s\n", "Test 2: File with content 'Hello'");
    create_and_write_file(filename, "Hello");
    read_and_print_lines(filename, 2);
    delete_file(filename);

    printf("\n%s\n", "Test 3: File with content 'Hello\\nWorld'");
    create_and_write_file(filename, "Hello\nWorld");
    read_and_print_lines(filename, 3);
    delete_file(filename);

    printf("\n%s\n", "Test 4: File with content 'Hello\\nWor\\nld\\0abc'");
    create_and_write_file(filename, "Hello\nWor\nld\0abc");
    read_and_print_lines(filename, 5);
    delete_file(filename);

    printf("\n%s\n", "Test 5: File with content '\\n\\n\\n'");
    create_and_write_file(filename, "\n\n\n");
    read_and_print_lines(filename, 4);
    delete_file(filename);

    printf("\n%s\n", "Test 6: File with content '\\n'");
    create_and_write_file(filename, "\n");
    read_and_print_lines(filename, 2);
    delete_file(filename);

    printf("\n%s\n", "Test 7: File with content 'so\\nmany\\nlines\\nright?'");
    create_and_write_file(filename, "so\nmany\nlines\nright?");
    read_and_print_lines(filename, 5);
    delete_file(filename);

    printf("\n%s\n", "Test 8: File with content 'so\\nmany\\n'");
    create_and_write_file(filename, "so\nmany\n");
    read_and_print_lines(filename, 4);
    delete_file(filename);

}
