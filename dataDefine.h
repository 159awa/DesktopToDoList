#ifndef DataDefine_h
#define DataDefine_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉排序树的节点
typedef struct TreeNode {
    int key;  // 键值，用于排序
    int importance;  // 权值，用于后续比较
    char value[100];  // 存储的实际数据，比如待办事项
    struct TreeNode* left;  // 左子节点
    struct TreeNode* right;  // 右子节点
} TreeNode;

// 定义二叉排序树
typedef struct {
    TreeNode* root;  // 树的根节点
} BinarySearchTree;

// 创建一个新的节点
TreeNode* createNode(int key, int importance, const char* value);

// 插入一个键值对
void insert(BinarySearchTree* bst, int key, int importance, const char* value);

// 读取文件并建立二叉排序树
void readFromFileAndBuildTree(BinarySearchTree* bst, const char* filename);

// 中序遍历，输出所有待办事项
void inorderTraversal(TreeNode* root);

// 释放树的内存
void freeTree(TreeNode* root);

// 初始化二叉排序树
void initBinarySearchTree(BinarySearchTree* bst);

// 销毁二叉排序树
void destroyBinarySearchTree(BinarySearchTree* bst);

TreeNode* deleteNode(TreeNode* root, const char* value);

TreeNode* findMin(TreeNode* node);

#endif // dataDefine.h
