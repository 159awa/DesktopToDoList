#include "dataDefine.h"
#include "todoOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    BinarySearchTree bst;
    initBinarySearchTree(&bst);

    // 读取文件并建立二叉排序树
    readFromFileAndBuildTree(&bst, "text.txt");

    // 添加待办事项
    addTodo(&bst, 4, "this is a new item");
    addTodo(&bst, 5, "this is a second new item");

    // 删除待办事项
    deleteTodo(&bst, "abcde");

    // 查找待办事项
    TreeNode* found = findTodo(&bst, "this is a new item");
    if (found != NULL) {
        printf("Found: Importance: %d, Value: %s\n", found->importance, found->value);
    } else {
        printf("Not Found\n");
    }

    // 修改已有待办事项
    modifyTodo(&bst, "this is a new item", "this is a newwwwwwwwwww item", 7);

    // 保存到新文件
    saveTodos(&bst, "new_todo.txt");

    // 销毁二叉排序树
    destroyBinarySearchTree(&bst);

    return 0;
}
