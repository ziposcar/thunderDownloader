# thunderDownloader

---
## 编译环境

* 使用vs2017编译的vc++（请使用 Release x86 编译器，官方SDK不支持 x64）控制台程序，输出文件放在./Release/outfile中，将其设置为环境变量后可全局使用。注意两个dll文件请放在同一目录或Path中。

## Example

* 将命令行目录调到outfile文件夹下（或配置环境变量），如果想要下载的url为Url，下载后文件放在Path的话，
```
thunder Url Path
```
（没错就是这么简单，剩下优化的事情交给迅雷内核去吧）

## Doc

* win下利用脚本编写下载程序一直比较别扭，即使最新的powershell有了wget，或者使用了aria2c这种linux下广受好评的下载工具，有时在我们临时使用时，或者任务量较大时，依然体现出下载环节的薄弱。

* 而早期的迅雷提供了SDK以调用其核心，实现非常稳定的并行下载，以及相当自然的多线程。

* 当然，这是一组提供给C++的开发包，我在这里只是简单的封装，实现了传两个参数（一个url一个dirpath）的类似wget的使用方法的小命令工具。以期为脚本编写中遇到的下载环节提供帮助。

* http://xldoc.xl7.xunlei.com/ "迅雷官方开发文档"与两个头文件中的注释是大部分信息的来源，可供参考。（目前提供内核协议之支持http，估计也永远就只有http了，这东西虽然好用但基本死了）

* 下一步着力于发挥SDK本身的应对多任务的特性。