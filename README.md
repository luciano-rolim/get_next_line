### **INTRO:** <h3> tag

The objective of `get_next_line` function (abbreviated as "GNL") is to create a function that return a line read from a given file. More than that, it also use a static variable to preserve content for future calls of the same function on the same file. For more info, check the subject on `subject_get_next_line.pdf`


**LINKED NODES AND SPEED OF EXECUTION**

To make this project, I used linked nodes instead of strjoin or other previous functions created on libft. The reason for that was primarly speed of execution. When you using nodes, you dont need to allocate/dealocate memory each time you call the read function, which is specially function in case of a large file with a small BUFFER_SIZE.

To prove it, I ran a file with 200k characters and BUFFER_SIZE of 1 on two different codes, one using strjoin and the second (my own) using a linked list, to compare the time of execution.

External code - using strjoin
![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/5192d601-bd9b-4f0c-a212-cf86c443bc7d)

My code - using linked lists
![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/93883f8b-03cc-4529-93e4-388d764b19dd)

As you can see, in the GNL project the use of a linked list made it way much faster.

If you want to replicate this test with your code, do as it follows:
1 - Download/move the files `gnl_200k_test.c` and `200k_file_test.txt`, which are avaible on the `test_files` folder, to the same folder with your .c get_next_line files
2 - Compile and run with the command: `cc get_next_line.c get_next_line_utils.c gnl_test.c -D BUFFER_SIZE=1 && time ./a.out`
The key point, here, is to compile with a BUFFER_SIZE of 1 and to execute the ./a.out with the "time" flag, which will record the time of execution of the program
3 - The execution time will be printed on the terminal screen


**SPECIAL CASE FOR MEMORY LEAKS:**

- GNL has a special challenge, that it evolves how to prevent a memory leak in you static variable (in case you are using malloc to allocate the node and it's content on the heap). 

Suppose you call your get_next_line only one time, and now if has remaining memory on the static node. How to clean it, if you can't give free on the static node directly?

To solve it, I created a "backdoor" in a way that whenever you dont have access to the file (thereby, when the read function returns -1), my code free everything (including the static_node) and return NULL.

![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/9ee29ea6-c5ac-4242-935d-343a690186b6)

So, it's only necessary to change the file permission and call GNL again to clean everything. To prove it, I created the file gnl_special_leak_test.c, which consist in a int main that calls the first line and on the sequence uses `fd = open(filename, O_WRONLY)` to change the file permission. When calling GNL for the second time, it will properly clean any remaining bytes allocated on heap, even if we did not reach the end of the file. 

To test, use valgrind --leak-check=full ./a.out

As you can see, the valgrind results in no memory leak.

![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/5410fccf-b3af-4658-afbb-1e25056b0862)


**Testing GNL:**

To test my GNL, I created three different .c files with an int main, which are available in the folder `test_files`:
- `gnl_common_tests.c` - Will test common scenarios for get_next_line 
- `gnl_200k_test.c` - Already commented, is specially designed to test the execution time of a large file
- `gnl_special_leak_test.c` - Already commented, is specially designed to test possible leaks in a scenario with remaining content in your static variable.

Also, I used the excellent [gnlTester](https://github.com/Tripouille/gnlTester) of Tripouille to test my GNL.
