# 文件系统的用户界面

## 一些函数

```
int open(const char * pathname, int flags);
int open(const char * pathname, int flags, mode_t mode);
```

flags的指标：
以下三种互斥，不能同时使用
- O_RDONLY: 只读
- O_WRONLY: 只写
- O_RDWR: 可读写

- O_CREAT: 若文件不存在则自动建立该文件
- O_SYNC: 以同步的方式打开文件
### 系统调用read, write

### 库函数fread，fwrite

## 可能会出现的问题

- fread比read要快
- 运行while((n=fread(buf, 1, BUFSIZE, fp1)) > 0) {
出错， 可以改成fread(buf, bufsize* sizeof(char), 1, fp1)试试
- fscanf复制文件，如何解决空格？用fscanc？用%c读char? ^\n? %[^\n]


reference:
- https://www.cnblogs.com/ace-wu/p/6640186.html
-
