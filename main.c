#include "dataDefine.h"

int main() {
    BinarySearchTree bst;
    initBinarySearchTree(&bst);

    // 读取文件并建立二叉排序树
    readFromFileAndBuildTree(&bst, "text.txt");

    // 中序遍历输出所有待办事项
    printf("Inorder Traversal:\n");
    inorderTraversal(bst.root);

    // 销毁二叉排序树
    destroyBinarySearchTree(&bst);

    return 0;
}
