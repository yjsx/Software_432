### 异常处理

+ 命令行参数错误

| 错误内容|抛出错误 | 对应的样例|
|--|--|--|
|命令错误|Command wrong,-n,-h,-t,-w,-c is needed!
|-w后缺少参数|Command wrong, there need parameter after -w!
|-c后缺少参数|Command wrong, there need parameter after -c!
|-n后缺少参数|Command wrong, there need parameter after -n!
|-n后的参数不是合法字符|Command wrong, the parameter after -n must be number!
|-h后缺少参数|Command wrong, there need parameter after -h!
|-h后的参数不是合法字符|Command wrong, the parameter after -h must be a lower case!
|-t后缺少参数|Command wrong, there need parameter after -t!
|-t后的参数不是合法字符|Command wrong, the parameter after -t must be a lower case!

+ text_prerocess内部错误

| 错误内容|抛出错误 | 对应的样例|
|--|--|--|
|文件不存在|Error opening file!
|文件内没有有效的字符串|There is no word in the file!

+ gen_chain_word gen_chain_char 内部错误

| 错误内容|抛出错误 | 对应的样例|
|--|--|--|
|head, tail不为小写字母| head is invalid! /  tail is invalid！
|字符数组中有空字符|there is blank word in these words!
|字符数组中有错误字符|there is wrong character in words!
|len为负数|len is smaller than 0!
|字符数组中有重复字符串|there is duplicate words in the word array！