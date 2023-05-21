这个文件夹将被固定用于临时测试编译器。

你可以创建并修改config.mk文件，添加/修改如下参数：

* `dutBin`：你的待测编译器的可执行文件相对于CMake根的路径。（举例来说，如果你在`mkdir build && cmake .. && make && cd ..`后，可执行文件位于`build/bin/dut`，这项就填`bin/dut`）
* `demoSysyBase`：你用于测试的sysy文件的basename。如果不指定默认为demo。文件需要在.demo下。
* `dutOptions`：传给dut的命令行参数（除了源文件路径和`-o`参数）。默认为空。
