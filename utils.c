// utils.c
#include "utils.h"

void add_task(ToDoList* list, const char* task) {
    if (list->count < MAX_TASKS) {
        strcpy(list->tasks[list->count], task);
        list->count++;
    } else {
        printf("Task list is full!\n");
    }
}

void remove_task(ToDoList* list, int index) {
    if (index >= 0 && index < list->count) {
        for (int i = index; i < list->count - 1; i++) {
            strcpy(list->tasks[i], list->tasks[i + 1]);
        }
        list->count--;
    } else {
        printf("Invalid task index!\n");
    }
}

void print_tasks(const ToDoList* list) {
    printf("Tasks:\n");
    for (int i = 0; i < list->count; i++) {
        printf("%d. %s\n", i + 1, list->tasks[i]);
    }
}
