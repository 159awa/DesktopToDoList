#include "todoOperations.h"
#include "schedule.h"

// 计算平均权值
float calcuAvg(BinarySearchTree* bst) {
    if (bst->root == NULL) {
        return 0.0;
    }

    int sum = 0;
    int count = 0;
    inorderSumAndCount(bst->root, &sum, &count);
    return (float)sum / count;
}

// 中序遍历计算权值总和和节点数
void inorderSumAndCount(TreeNode* root, int* sum, int* count) {
    if (root != NULL) {
        inorderSumAndCount(root->left, sum, count);
        *sum += root->importance;
        *count += 1;
        inorderSumAndCount(root->right, sum, count);
    }
}

// 根据权值范围搜索待办事项并存储到文件
void searchByFactors(BinarySearchTree* bst, float factorIm, float factorUnim) {
    FILE* fileIm = fopen("important.txt", "w");
    FILE* fileUnim = fopen("unimportant.txt", "w");
    if (fileIm == NULL || fileUnim == NULL) {
        printf("无法打开文件\n");
        return;
    }

    inorderSearchByFactors(bst->root, factorIm, factorUnim, fileIm, fileUnim);
    fclose(fileIm);
    fclose(fileUnim);
}

// 中序遍历根据权值范围存储到文件
void inorderSearchByFactors(TreeNode* root, float factorIm, float factorUnim, FILE* fileIm, FILE* fileUnim) {
    if (root != NULL) {
        inorderSearchByFactors(root->left, factorIm, factorUnim, fileIm, fileUnim);
        if (root->importance >= factorIm) {
            fprintf(fileIm, "%d %s\n", root->importance, root->value);
        } else if (root->importance <= factorUnim) {
            fprintf(fileUnim, "%d %s\n", root->importance, root->value);
        }
        inorderSearchByFactors(root->right, factorIm, factorUnim, fileIm, fileUnim);
    }
}

// 创建计划表
void createSchedule(BinarySearchTree* bst) {
    // 读取权值大于平均值的事项构成的文件
    FILE* file = fopen("important.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 从文件中随机挑选一些事项展示作为计划表
    // 这里可以使用随机数生成和文件读取的方法来实现
    // 例如，可以先读取所有事项到一个数组中，然后使用随机数索引数组
    // 为了简化，这里只展示一个随机挑选的事项

    char line[200];
    int lines = 0;
    while (fgets(line, 200, file)) {
        lines++;
    }
    rewind(file);

    int randomLine = rand() % lines;
    for (int i = 0; i < randomLine; i++) {
        fgets(line, 200, file);
    }
    fgets(line, 200, file);
    printf("random item: %s", line);

    fclose(file);
}