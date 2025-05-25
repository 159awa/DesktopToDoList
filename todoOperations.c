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

// 查找待办事项，这是一个完全匹配查找，遍历树，根据二叉排序树的特性，可以比较方便的找到。
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

// 但是对于待办事项清单，怎么会有人记忆的完全一样，所以这里显然需要一个关键词通配查找
// 通过关键词查找待办事项
void findTodosByKeyword(BinarySearchTree* bst, const char* keyword, TreeNode*** result, int* count) {
    *result = NULL; // 结果数组，作为一个容器传递进来，函数把找到的东西塞进去。
    *count = 0; // 表示塞了几个进去
    findTodosByKeywordHelper(bst->root, keyword, result, count);
}

// 辅助函数：递归查找所有匹配的节点
void findTodosByKeywordHelper(TreeNode* root, const char* keyword, TreeNode*** result, int* count) {
    // 递归结束的条件，当前节点为空
    if (root == NULL) {
        return;
    }

    // 用strstr检查当前节点的值是否包含关键词
    if (strstr(root->value, keyword) != NULL) {
        // 有关键词就把这个结点存到结果数组里去（这里因为结果数组大小未知，所以重新分配一下内存）
        *result = (TreeNode**)realloc(*result, (*count + 1) * sizeof(TreeNode*));
        (*result)[*count] = root;
        (*count)++;
    }

    // 递归查找左子树和右子树
    findTodosByKeywordHelper(root->left, keyword, result, count);
    findTodosByKeywordHelper(root->right, keyword, result, count);
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
    // 查找旧的待办事项，这里用完全匹配查找，总不能把含有关键词的都删掉了吧
    TreeNode* node = findTodo(bst, old_value);
    if (node == NULL) {
        printf("未找到事项 '%s' \n", old_value);
        return;
    }

    // 更新节点的值和权值
    strcpy(node->value, new_value);
    node->importance = new_importance;

    printf("事项 '%s' 已修改为 '%s'，新的权重是 %d。\n", old_value, new_value, new_importance);
}
