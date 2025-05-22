#ifndef TODO_OPERATIONS_H
#define TODO_OPERATIONS_H

#include "dataDefine.h"

// 添加待办事项
void addTodo(BinarySearchTree* bst, int importance, const char* value);

// 删除待办事项
void deleteTodo(BinarySearchTree* bst, const char* value);

// 查找待办事项
TreeNode* findTodo(BinarySearchTree* bst, const char* value);


void inorderSave(TreeNode* root, FILE* file);

// 保存待办事项到文件
void saveTodos(BinarySearchTree* bst, const char* filename);

// 修改已有待办事项
void modifyTodo(BinarySearchTree* bst, const char* old_value, const char* new_value, int new_importance);

#endif // TODO_OPERATIONS_H
