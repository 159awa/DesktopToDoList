#ifndef UTILS_H
// ifndef 和 endif 是用来防止头文件重复包含的预处理指令。它们的作用是确保头文件的内容在同一个编译单元中只被包含一次，从而避免重复定义问题
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 100

typedef struct {
    char tasks[MAX_TASKS][MAX_TASK_LENGTH];
    int count;
} ToDoList;

void add_task(ToDoList* list, const char* task);
// 使用const可以明确地告诉调用者和编译器，这个参数的值在函数内部不会被修改。这是一种编程约定，可以提高代码的可读性和可维护性。
// 使用const可以防止函数内部意外修改传入的参数。这有助于减少错误，特别是在处理字符串时。
void remove_task(ToDoList* list, int index);
void print_tasks(const ToDoList* list);

#endif // UTILS_H