由于比赛官方的编译方法非常鬼畜（见官方仓库的[Compiler.java脚本](https://gitlab.eduxiji.net/nscscc/compiler2023/-/blob/master/source/Compiler.java)），所以我们管理三方库的方法也是非常鬼畜：

* [Antlr 4.12.0](https://www.antlr.org/)，通过conan管理：

  在比赛OJ上，antlr是通过`-lantlr4-runtime`被链接、通过`-I/extlibs`被include的（见[Compiler.java:215]((https://gitlab.eduxiji.net/nscscc/compiler2023/-/blob/master/source/Compiler.java#L215))），因此我们提交的仓库里不能有antlr4的源码，却需要能够include和链接到antlr4，所以我们通过conan来引入antlr依赖。

* [argparse](https://github.com/p-ranav/argparse)，通过源码管理：

  由于官方的编译方法没有提供引用第三方库的方法，因此我们必须下载源码来管理。

* [dbg-macro](https://github.com/sharkdp/dbg-macro)，通过源码管理。

* [moe NakagawaNatsuki 2.0.1](https://github.com/ipChrisLee/moe/tree/NakagawaNatsuki-2.0.1)，通过源码管理。

  这是我为了2022年编译设计赛写的一些库的跟进版本，里面包括一些简单但有用的东西，比如`moe_rt_warning`。

  在这个仓库里，通过源码管理，可以自行增加新feature。

为了避免触发查重，我们暂时只引入了这些库，但是实际上还有下列优秀的开源库可以考虑引入：

* [fmtlib](https://github.com/fmtlib/fmt)
* [spdlog](https://github.com/gabime/spdlog)