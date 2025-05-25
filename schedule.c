#include "todoOperations.h"
#include "schedule.h"
#include <time.h>

// 将待办事项分为重要和不重要两部分，然后从重要的事项中随机挑几个作为建议
// 如果挑的不好，还可以选择重来哈哈哈

// 计算平均权值，作为判断事项是否重要的依据。
// 这里是在调用方法的时候才计算，如果要把这个作为二叉树的性质一开始就算的话
// 那相应的增删改操作也需要对这个平均值做调整，很麻烦。
float calcuAvg(BinarySearchTree* bst) {
    if (bst->root == NULL) {
        return 0.0;
    }

    int sum = 0;
    int count = 0;
    inorderSumAndCount(bst->root, &sum, &count); // 中序遍历结点，传递引用（指针）是常见的方法当想要函数的“返回值”不止一个时。
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
// 很简单的二分类，大于平均值放在一个文件，小于放在另一个
// 我一开始想的是重要是大于4/3平均值，不重要是小于2/3平均值，所以可以看到有写 factorIm 和 factorUnim，但最后嫌麻烦就用平均值了，这两个变量是一样的
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
        lines = (char**)realloc(lines, linesCount * sizeof(char*)); // 动态分配数组大小
        lines[linesCount - 1] = strdup(line); // strdup函数，根据一个字符串的指针复制字符串，返回的也是一个字符串的指针。适合用来动态分配内存
    }
    fclose(file);

    // 初始化随机数生成器，用来随机抽取
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
        numItemsToPick = linesCount; // 不要比一共有的待办事项总数大了
    }

    for (int i = 0; i < numItemsToPick; i++) {
        int randomIndex = rand() % linesCount; // 随机找一个序号，然后输出！
        printf("%s", lines[randomIndex]);
        fprintf(scheduleFile, "%s", lines[randomIndex]);
        free(lines[randomIndex]);  // 释放已使用的行
        lines[randomIndex] = lines[linesCount - 1];  // 将最后一行补到删掉的这里
        linesCount--;
    }

    // 释放剩余的内存
    for (int i = 0; i < linesCount; i++) {
        free(lines[i]);
    }
    free(lines);
    fclose(scheduleFile);
}