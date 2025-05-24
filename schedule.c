#include "todoOperations.h"
#include "schedule.h"
#include <time.h>

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

    // 读取所有事项到一个数组中
    char** lines = NULL;
    int linesCount = 0;
    char line[200];
    while (fgets(line, 200, file)) {
        linesCount++;
        lines = (char**)realloc(lines, linesCount * sizeof(char*));
        lines[linesCount - 1] = strdup(line);
    }
    fclose(file);

    // 初始化随机数生成器
    srand(time(NULL));

    // 打开一个新的文件用于输出计划表
    FILE* scheduleFile = fopen("schedule.txt", "w");
    if (scheduleFile == NULL) {
        printf("无法打开文件 schedule.txt\n");
        return;
    }

    // 随机挑选多个事项
    int numItemsToPick = 3;  // 假设我们随机挑选3个事项
    if (numItemsToPick > linesCount) {
        numItemsToPick = linesCount;
    }

    for (int i = 0; i < numItemsToPick; i++) {
        int randomIndex = rand() % linesCount;
        printf("%s", lines[randomIndex]);
        fprintf(scheduleFile, "%s", lines[randomIndex]);
        free(lines[randomIndex]);  // 释放已使用的行
        lines[randomIndex] = lines[linesCount - 1];  // 将最后一行移到随机位置
        linesCount--;
    }

    // 释放剩余的内存
    for (int i = 0; i < linesCount; i++) {
        free(lines[i]);
    }
    free(lines);
    fclose(scheduleFile);
}