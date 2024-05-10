
The reason for using linked_lists instead of strjoin and other functions was primarly speed of execution.

As you can see, those are the tests results when comparing a file with 200k characters and BUFFER SIZE 1 for two different codes

My code - using linked lists
![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/93883f8b-03cc-4529-93e4-388d764b19dd)

External code - using strjoin
![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/5192d601-bd9b-4f0c-a212-cf86c443bc7d)

**Check for memory leaks:
**
- Using gnl_special_leak_test.c, i comproved that by using fd = open(filename, O_WRONLY) and calling the get_next_line a second time, it will properly clean any reameaning bytes allocated on heap, even if we did not reach the end of the file. 

To test, use valgrind --leak-check=full ./a.out

![image](https://github.com/luciano-rolim/get_next_line/assets/40547130/5410fccf-b3af-4658-afbb-1e25056b0862)
