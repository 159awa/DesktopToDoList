#include "dataDefine.h"
#include "todoOperations.h"
#include "schedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    BinarySearchTree bst;
    initBinarySearchTree(&bst);

    // 读取文件并建立二叉排序树
    readFromFileAndBuildTree(&bst, "text.txt");

    int opt, weight;
    char item[51];
    char new_item[51];

    // 页面设计
    while (1) {
        printf("|\t\t----------待办事项管理系统----------\t\t|\n");
        printf("|\t1.输出所有待办事项\t|\t2.添加待办事项\t\t|\n");
        printf("|\t3.删除待办事项\t\t|\t4.查找待办事项\t\t|\n");
        printf("|\t5.修改待办事项\t\t|\t6.生成待办事项建议表\t|\n");
        printf("|\t7.保存修改并退出\t|\n");
        printf("请输入序号选择要进行的操作：");
        scanf("%d", &opt);
        if (opt == 7) {
            saveTodos(&bst, "new_todo.txt");
            destroyBinarySearchTree(&bst);
            break;
        }
        switch (opt) {
            case 1:
                inorderTraversal(bst.root);
                break;
            case 2:
                printf("请输入事项权重以及事项内容（不超过50个字符），以空格分割：\n");
                scanf("%d %s", &weight, item);
                addTodo(&bst, weight, item);
                break;
            case 3:
                printf("请输入待删除事项完整内容：\n");
                scanf("%s", item);
                deleteTodo(&bst, item);
                break;
            case 4:
                printf("请输入关键词进行查找：");
                TreeNode** results;
                int count;
                scanf("%s", item);
                findTodosByKeyword(&bst, item, &results, &count);
                for (int i = 0; i < count; i++) {
                    printf("Found: Importance: %d, Value: %s\n", results[i]->importance, results[i]->value);
                }
                free(results);
                break;
            case 5:
                printf("请输入原事项内容、新事项内容（不超过50个字符）以及新的权重，以空格分割：\n");
                scanf("%s %s %d", item, new_item, &weight);
                modifyTodo(&bst, item, new_item, weight);
                break;
            case 6:
                printf("建议完成以下事项：\n");
                float avg = calcuAvg(&bst);
                // 根据权值范围搜索待办事项并存储到文件
                searchByFactors(&bst, avg, avg);
                // 创建计划表
                createSchedule(&bst);
                break;
        }
    }

    // // 查找待办事项
    // TreeNode* found = findTodo(&bst, "this is a new item");
    // if (found != NULL) {
    //     printf("Found: Importance: %d, Value: %s\n", found->importance, found->value);
    // } else {
    //     printf("Not Found\n");
    // }

    return 0;
}
