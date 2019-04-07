### 运行方式
1. 编译
运行make.sh,生成test.exe,即可（使用GUI之前也需编译）。
2. 运行方式
+ 提交版本为命令行执行版本，直接运行为：

```shell
./test.exe (-h param) (-t param) (-n param) -w or -c filename
```
+ GUI 运行方式为(需进行编译)：
```shell
python gui.py
```
### 文本处理API设计

### 异常处理
异常分为以下几类：
+ 命令行参数错误

| 错误内容|抛出错误 |对应的错误
|--|--|--|
|命令错误|Command wrong,-n,-h,-t,-w,-c is needed!|./test.exe -w -c example.txt <br>./test.exe example.txt <br>./test.exd -r example.txt
|-w后缺少参数|Command wrong, there need parameter after -w!| ./test.exe -w
|-c后缺少参数|Command wrong, there need parameter after -c!|./test.exe -c
|-n后缺少参数|Command wrong, there need parameter after -n!|./test.exe -n -w example.txt
|-n后的参数不是合法字符|Command wrong, the parameter after -n must be number!|./test.exe -n b -w example.txt
|-h后缺少参数|Command wrong, there need parameter after -h!|./test.exe -h -w example.txt
|-h后的参数不是合法字符|Command wrong, the parameter after -h must be a lower case!|./test.exe -h 3 -w example.txt
|-t后缺少参数|Command wrong, there need parameter after -t!|./test.exe -t -w example.txt
|-t后的参数不是合法字符|Command wrong, the parameter after -t must be a lower case!|./test.exe -t 3 -w example.txt

+ text_prerocess内部错误

| 错误内容|抛出错误 | 对应的样例|
|--|--|--|
|文件不存在|Error opening file!|./test.exe -w ../test/example12.txt
|文件内没有有效的字符串|There is no word in the file!|example11.txt

+ gen_chain_word gen_chain_char 内部错误
**注：由于提交版本为命令行对文件进行处理，所以text_preprocess模块已将字符内部可能出现的问题进行了排除，所以要想查看这些的报错，可将test.cpp文件中的main函数中被注释掉的测试方法2取消注释，然后用example中的例子代替测试方法2中input的内容，并将原有的测试方法1注释掉，以查看这些报错。**

| 错误内容|抛出错误 | 对应的样例|
|--|--|--|
|head, tail不为小写字母| head is invalid! /  tail is invalid！
|字符数组中有空字符|there is blank word in these words!
|字符数组中有错误字符|there is wrong character in words!|example13.txt
|len为负数|len is smaller than 0!
|字符数组中有重复字符串|there is duplicate words in the word array！| example14.txt