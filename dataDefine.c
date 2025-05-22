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

// 删除一个节点
TreeNode* deleteNode(TreeNode* root, const char* value) {
    if (root == NULL) {
        return NULL;
    }

    // 如果要删除的节点在左子树
    if (strcmp(value, root->value) < 0) {
        root->left = deleteNode(root->left, value);
    }
    // 如果要删除的节点在右子树
    else if (strcmp(value, root->value) > 0) {
        root->right = deleteNode(root->right, value);
    }
    // 找到要删除的节点
    else {
        // 节点没有子节点
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // 节点有一个子节点
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // 节点有两个子节点，找到右子树的最小节点替换
        TreeNode* minNode = findMin(root->right);
        strcpy(root->value, minNode->value);
        root->importance = minNode->importance;
        root->right = deleteNode(root->right, minNode->value);
    }
    return root;
}

// 找到最小节点
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}