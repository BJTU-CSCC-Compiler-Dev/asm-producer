正常的Git操作大家都知道我就不说了，这里说一个比较重要的：

我们通过GitHub的Action来做一些自动化工作，目前只有一个在push时自动格式化的workflow（见.github/workflows/auto-format-on-push.yml），后续会有其他的更有用的自动化。



关于自动格式化：

* 可以看.github/workflows/auto-format-on-push.yml了解详细过程。

* 基本原理就是：在push完成后，GitHub Action会使用clang-format自动格式化所有src文件夹下的C++文件，如果有更改就再commit更改并push上去。

* 所以我们每次push之后，都要过段时间再pull下来，因为有可能有自动格式化。

  倒不如说，每一次开发之前都应该先pull下来，再开发。
