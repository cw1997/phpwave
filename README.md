# phpwave
a php extension for getting wave audio file's metadata

# 简介
一个使用C语言开发的WAVE音频文件元数据获取器。

纯C实现的项目仓库：https://github.com/cw1997/wave-resolver

# function_list:
- array phpwave(string audio_file_fullpath)

# example
print_r(phpwave(dirname(__dir__).'/test.wav'));

![](https://github.com/cw1997/phpwave/blob/master/example.png?raw=true)

