### **INTRO:** <h3>

The objective of `get_next_line` function (abbreviated as "GNL") is to create a function that return a line read from a given file. More than that, it also use a static variable to preserve content for future calls of the same function on the same file. For more info, check the subject on `subject_get_next_line.pdf`



### **LINKED NODES AND SPEED OF EXECUTION** <h3>

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



### **SPECIAL CASE FOR MEMORY LEAKS:** <h3>

- GNL has a special challenge, that it evolves how to prevent a memory leak in you static variable (in case you are using malloc to allocate the node and it's content on the heap). 

Suppose you call your get_next_line only one time, and now if has remaining memory on the static node. How to clean it, if you can't give free on the static node directly?

To solve it, I created a "backdoor" in a way that whenever you call GNL with a invalid file descriptor (for example, -1), the code will free everything (including the static_node, if it was allocated in a previous call) and return NULL.


		if (fd < 0 || BUFFER_SIZE <= 0)
		{
			free_all(&linked_list);
			return (NULL);
		}


So, to trigger this is only necessary to call in your main get next line with the argument "-1" instead of a previous valid FD. This will be enough to clean everything. Remember to close your fd in the end of the function. I create a special test file called gnl_special_leak_test.c to test this scenario. You can check it for yourself, using the command valgrind --leak-check=full --track-fds=yes ./a.out

![image](https://github.com/user-attachments/assets/f68d89e9-eaf3-42f2-b091-6fcefd58ec9f)



### **Testing GNL:** <h3>

To test my GNL, I created three different .c files with an int main, which are available in the folder `test_files`:
- `gnl_common_tests.c` - Will test common scenarios for get_next_line 
- `gnl_200k_test.c` - Already commented, is specially designed to test the execution time of a large file
- `gnl_special_leak_test.c` - Already commented, is specially designed to test possible leaks in a scenario with remaining content in your static variable.

Also, I used the excellent [gnlTester](https://github.com/Tripouille/gnlTester) of Tripouille to test my GNL.
