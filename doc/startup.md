执行需要：
* `java`环境。
* `conan`已安装和配置。请参考[conan-installation](https://docs.conan.io/1/installation.html)和[conan-getting-started](https://docs.conan.io/1/getting_started.html)来完成初始化。
* `antlr4-tools`已安装。`pip install antlr4-tools==0.2.0`。 

之后在项目根执行`make all`以完成初始化。

初始化完之后可以直接进行开发，项目可以被CLion识别，所以建议直接上CLion开发。

在CLion上，建议：

* 允许使用clang-format自动格式化。

Git相关：

建议将GitHub上的remote设为origin，GitLab上的设为类似cc(Competition Commit)的名字。GitHub上你可以使用ssh来避免每次都输入密码才能和remote交互，但是在GitLab上似乎需要别的办法：

* 点进你的账户，然后点击"Access Tokens"，之后生成一个Token，注意这个Token会显示在当前页面，刷新完了就会消失，所以记得先保存在本地。
* 在添加remote的时候，使用：`git remote set-url origin https://oauth2:<access_token>@gitlab.eduxiji.net/username/repository.git`的方式添加，其中`<access_token>`就是你刚刚拿到的token。
* 这样之后和GitLab的remote交互就不用每次都输入密码了。