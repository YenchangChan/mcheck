`mcheck` 是一个`C`语言实现的用来检测内存泄漏的链接库。  
通过该库，可以非常直观地检查出代码中存在的内存泄漏问题。`mcheck`将每次`malloc`/`calloc`/`realloc`申请内存时的内存块及指针信息记录到一个链表中，当`free`掉内存块时，将对应的内存块信息从链表中剔除，这样，在程序结束时，链表中留存的数据，即为没有释放的内存。  
## 如何使用
首先需要编译`mcheck`库，编译直接使用`configure`生成`Makefile`，再执行`make`即可。
```bash
./configure && make
```
你可以使用`make install`命令将`libmcheck.a`安装到系统中，你只需要在你的代码`main`函数中插入如下两行代码，并引用头文件`mcheck.h`即可：
```c
#include <mcheck.h>

int main(void){
    mcheck_initialize();
    //your code
    mcheck_terminate();
    return 0;
}
```
执行你的程序，你会得到一个`mcheck.rpt`的内存泄漏报告，其中包含了你的代码中未来得及释放的内存信息。`mcheck.rpt`这个文件名你可以自己通过环境变量`MCHECK_TRACE`进行设置，如果你没有设置，则默认写入到`mcheck.rpt`中。  
具体的使用可以参考[mcheck_sample.c](./example/mcheck_sample.c)的例子。

## TodoList
- [ ] 支持`mmap`、`brk`、`sbrk`
- [ ] 调用栈记录更详细一点（目前仅记录了一层）