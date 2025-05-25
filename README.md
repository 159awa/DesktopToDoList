# DesktopToDoList
---



这是一个简单的桌面待办事项管理系统，使用 C 语言实现。它支持读取待办事项、添加、删除、查找和修改待办事项，并生成计划表。


项目结构


```
project/
├── dataDefine.c
├── dataDefine.h
├── todoOperations.c
├── todoOperations.h
├── schedule.c
├── schedule.h
├── main.c
├── todo.txt
└── README.md
```



功能


• 读取待办事项：从文件`todo.txt`中读取待办事项。

• 添加待办事项：在运行时添加新的待办事项。

• 删除待办事项：根据待办事项的内容删除指定的待办事项。

• 查找待办事项：通过关键词查找多个符合的待办事项。

• 修改待办事项：根据关键词查找并修改待办事项。

• 生成计划表：根据权值生成计划表，并随机挑选事项展示。


使用方法


编译

确保所有源文件都在同一个目录下，然后使用以下命令编译：


```sh
gcc -finput-charset=UTF-8 -o test main.c bst.c todo_operations.c schedule.c
```



运行

运行程序：


```sh
./test
```



输入文件格式

`todo.txt`文件的格式如下：


```
3 fdsai dasfjia
1 fqefsa
2 abcde
```


每行包含一个权值和一个待办事项，权值和待办事项之间用空格分隔。


输出文件

程序会生成以下输出文件：


• `new_todo.txt`：保存当前的待办事项列表。

• `important.txt`：保存权值大于平均值的待办事项。

• `unimportant.txt`：保存权值小于平均值的待办事项。

• `schedule.txt`：保存随机挑选的计划表事项。


示例

假设`todo.txt`文件内容如下：


```
3 fdsai dasfjia
1 fqefsa
2 abcde
```


运行程序后，你可以在控制台看到随机挑选的计划表事项，并且在`schedule.txt`文件中找到相同的输出。


注意事项


• 文件编码：确保所有文件（源代码文件、输入文件）都使用 UTF-8 编码。

• 终端支持：确保你的终端支持显示中文字符。

• 编译选项：根据需要添加其他编译选项，例如`-Wall`（启用所有警告信息）或`-g`（生成调试信息）。


贡献

欢迎提出改进建议和贡献代码。请通过 GitHub 提交问题和拉取请求。


---