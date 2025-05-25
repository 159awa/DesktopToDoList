#include "dataDefine.h"

// 创建一个新的节点
TreeNode* createNode(int key, int importance, const char* value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key; // key在这里其实没啥用，排序用的是字典序
    newNode->importance = importance;
    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入一个节点
void insert(BinarySearchTree* bst, int key, int importance, const char* value) {
    // 树为空直接创建
    if (bst->root == NULL) {
        bst->root = createNode(key, importance, value);
    } else {
        // 树不为空开始找要插入的位置，按字典序插进去
        TreeNode* current = bst->root;
        while (1) {
            if (strcmp(value, current->value) < 0) {
                // 在左边
                if (current->left == NULL) { // 到叶子节点
                    current->left = createNode(key, importance, value);
                    break;
                } else {
                    current = current->left;
                }
            } else if (strcmp(value, current->value) > 0) {
                // 在右边
                if (current->right == NULL) { // 到叶子节点
                    current->right = createNode(key, importance, value);
                    break;
                } else {
                    current = current->right;
                }
            } else { // 直接找到一样的了
                // 如果待办事项已存在，仅更新权值
                current->importance = importance;
                break;
            }
        }
    }
}

// 读取文件并建立二叉排序树
void readFromFileAndBuildTree(BinarySearchTree* bst, const char* filename) {
    // 打开文件
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    char line[200]; // 用一个字符数组接收每一行的数据
    while (fgets(line, 200, file)) { // 一行一行处理
        int importance;
        char value[100];
        if (sscanf(line, "%d %[^\n]", &importance, value) == 2) {
            insert(bst, 0, importance, value);  // 这里key设为0，因为排序是根据value的字典序
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
    // 空树不需要删除
    if (root == NULL) {
        return NULL;
    }
    // 这里只是在找待删除结点，root指针指向的是待删除结点
    // 这里用递归找到待删除结点，不太好理解。
    // 如果要删除的节点在左子树
    if (strcmp(value, root->value) < 0) {
        root->left = deleteNode(root->left, value); // 很聪明，在往左子树找的时候，如果有删除顺便就直接接上了
    }
    // 如果要删除的节点在右子树
    else if (strcmp(value, root->value) > 0) {
        root->right = deleteNode(root->right, value);
    }
    // 找到要删除的节点
    else {
        // 节点没有子节点 直接删掉就好
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // 节点有一个子节点
        if (root->left == NULL) { // 有右子树
            TreeNode* temp = root->right; // 把右子树保存一下
            free(root);
            return temp;
        }
        if (root->right == NULL) { // 同理，有左子树
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // 节点有两个子节点，找到右子树的最小节点替换（或者左子树的最大结点）
        TreeNode* minNode = findMin(root->right);
        strcpy(root->value, minNode->value);
        root->importance = minNode->importance;
        root->right = deleteNode(root->right, minNode->value);
    }
    return root;
}

// 找到最小节点 二叉排序中的最小节点是最左下的节点（最大是最右下）
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}