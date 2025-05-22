#include "todoOperations.h"
#include "dataDefine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 添加待办事项
void addTodo(BinarySearchTree* bst, int importance, const char* value) {
    insert(bst, 0, importance, value);
}

// 删除待办事项
void deleteTodo(BinarySearchTree* bst, const char* value) {
    bst->root = deleteNode(bst->root, value);
}

// 查找待办事项
TreeNode* findTodo(BinarySearchTree* bst, const char* value) {
    TreeNode* current = bst->root;
    while (current != NULL) {
        if (strcmp(value, current->value) < 0) {
            current = current->left;
        } else if (strcmp(value, current->value) > 0) {
            current = current->right;
        } else {
            return current;
        }
    }
    return NULL;
}

// 中序遍历并保存到文件
void inorderSave(TreeNode* root, FILE* file) {
    if (root != NULL) {
        inorderSave(root->left, file);
        fprintf(file, "%d %s\n", root->importance, root->value);
        inorderSave(root->right, file);
    }
}

// 保存待办事项到文件
void saveTodos(BinarySearchTree* bst, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    inorderSave(bst->root, file);
    fclose(file);
}

// 修改已有待办事项
void modifyTodo(BinarySearchTree* bst, const char* old_value, const char* new_value, int new_importance) {
    // 查找旧的待办事项
    TreeNode* node = findTodo(bst, old_value);
    if (node == NULL) {
        printf("item '%s' unfounded, cannot change\n", old_value);
        return;
    }

    // 更新节点的值和权值
    strcpy(node->value, new_value);
    node->importance = new_importance;

    printf("item '%s' had been changed to '%s', the new weight is %d.\n", old_value, new_value, new_importance);
}
