// main.c
#include "utils.h"

int main() {
    ToDoList list = {0};

    int choice;
    char task[MAX_TASK_LENGTH];

    while (1) {
        printf("\n1. Add Task\n2. Remove Task\n3. Print Tasks\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(task, MAX_TASK_LENGTH, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline character
                add_task(&list, task);
                break;
            case 2:
                printf("Enter task index to remove: ");
                scanf("%d", &choice);
                remove_task(&list, choice - 1);
                break;
            case 3:
                print_tasks(&list);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}