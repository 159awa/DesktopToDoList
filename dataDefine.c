#include "dataDefine.h"

// 创建一个新的节点
TreeNode* createNode(int key, int importance, const char* value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->importance = importance;
    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入一个键值对
void insert(BinarySearchTree* bst, int key, int importance, const char* value) {
    if (bst->root == NULL) {
        bst->root = createNode(key, importance, value);
    } else {
        TreeNode* current = bst->root;
        while (1) {
            if (strcmp(value, current->value) < 0) {
                if (current->left == NULL) {
                    current->left = createNode(key, importance, value);
                    break;
                } else {
                    current = current->left;
                }
            } else if (strcmp(value, current->value) > 0) {
                if (current->right == NULL) {
                    current->right = createNode(key, importance, value);
                    break;
                } else {
                    current = current->right;
                }
            } else {
                // 如果待办事项已存在，可以选择更新权值
                current->importance = importance;
                break;
            }
        }
    }
}

// 读取文件并建立二叉排序树
void readFromFileAndBuildTree(BinarySearchTree* bst, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    char line[200];
    while (fgets(line, 200, file)) {
        int importance;
        char value[100];
        if (sscanf(line, "%d %[^\n]", &importance, value) == 2) {
            insert(bst, 0, importance, value);  // 这里键值可以设为0，因为排序是根据value的字典序
        }
    }

    fclose(file);
}

// 中序遍历，输出所有待办事项
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Importance: %d, Value: %s\n", root->importance, root->value);
        inorderTraversal(root->right);
    }
}

// 释放树的内存
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// 初始化二叉排序树
void initBinarySearchTree(BinarySearchTree* bst) {
    bst->root = NULL;
}

// 销毁二叉排序树
void destroyBinarySearchTree(BinarySearchTree* bst) {
    freeTree(bst->root);
}