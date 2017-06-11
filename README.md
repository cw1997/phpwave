# phpwave
a php extension for getting wave audio file's metadata

# 简介
一个使用C语言开发的WAVE音频文件元数据获取器。

开发环境为 Ubuntu 16, PHP 5.6.30

# 编译命令：
    phpize && ./configure --with-php-config=/usr/local/bin/php-config && make && make test && make install

# 排错
- 如果phpize有错误，请检查操作系统中是否安装m4，autoconf等依赖包，或者phpize未加入环境变量，请手动指定完整路径。
- 或者--with-php-config中的文件路径不正确，请自行解决之后再执行编译命令。
- 如果在编译过程中的make阶段出现报错，请检查 `src/phpwave.c` 中include的 `wave/wave.h` 文件路径是否正确，如果频繁出现报错，请修改为绝对路径然后进行编译。
- 如果make test阶段报错，请将报错信息以issue的方式提交给我。
- 最后编译成功之后在php.ini中加上 `extension=phpwave.so` 即可。

纯C实现的项目仓库：https://github.com/cw1997/wave-resolver

# function_list:
- array phpwave(string audio_file_fullpath)

# example
print_r(phpwave(dirname(__dir__).'/test.wav'));

![](https://github.com/cw1997/phpwave/blob/master/example.png?raw=true)

