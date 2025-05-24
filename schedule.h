#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "dataDefine.h"
#include "todoOperations.h"

// 计算平均权值
float calcuAvg(BinarySearchTree* bst);

// 中序遍历计算权值总和和节点数
void inorderSumAndCount(TreeNode* root, int* sum, int* count);

// 根据权值范围搜索待办事项并存储到文件
void searchByFactors(BinarySearchTree* bst, float factorIm, float factorUnim);

// 中序遍历根据权值范围存储到文件
void inorderSearchByFactors(TreeNode* root, float factorIm, float factorUnim, FILE* fileIm, FILE* fileUnim);

// 创建计划表
void createSchedule(BinarySearchTree* bst);

#endif // SCHEDULE_H