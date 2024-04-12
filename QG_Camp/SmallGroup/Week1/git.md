# Git

## 创建版本库

### step 1 创建空目录

```
$ mkdir learngit
$ cd learngit
$ pwd //显示当前目录
```

### step 2 变成git仓库

```
$ git init
```



## 把文件放进git

### step 1 把文件添加到仓库

```
$ git add test.txt
```

### step 2 把文件提交到仓库

```
$ git commit -m "it's a test about git learning,son"
[master (root-commit) 878c875] it's a test about git learning,son."
 1 file changed, 1 insertion(+)
 create mode 100644 test.txt
```

-m 后面输入的是本次提交的说明

1 file changed 表示一个文件被改动
1 insertion 表示插入了一行内容

## Q&A

### 为什么需要`add`和`commit`两步

​	`commit`可以一次提交多个文件，所以我们可以多次`add`然后一口气全部`commit`



## 修改文件

### git statua

修改文件内容后运行`git status`

```
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   test.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

`git status`可以让我们掌握仓库当前的状态，上面的命令输出告诉我们，`test.txt`被修改，但还没有准备提交的修改（提示你还需要使用add和commit）

### git diff

需要查看被修改的内容可以使用`git diff`

```diff
$ git diff
diff --git a/test.txt b/test.txt
index a72a79c..6c2eae0 100644
--- a/test.txt
+++ b/test.txt
@@ -1 +1,3 @@
-Hello Wolrd
\ No newline at end of file
+Hello Wolrd
+As you can see,
+Git is a great tool that I'm learning it.
\ No newline at end of file
```



## 提交修改

### 执行完add

使用`git status`查看仓库情况

```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   test.txt
```

`git status`告诉我们，将要被提交的修改包括`readme.txt`

### 执行完commit

使用`git status`查看仓库情况

```
$ git status
On branch master
nothing to commit, working tree clean
```

Git告诉我们当前没有需要提交的修改，而且，工作目录是干净（working tree clean）的。



## 版本回退

当你觉得文件修改到一定程度的时候，就可以“保存一个快照”，这个快照在Git中被称为`commit`。一旦你把文件改乱了，或者误删了文件，还可以从最近的一个`commit`恢复

### git log

`git log`命令显示从最近到最远的提交日志，我们可以看到3次提交，最近的一次是`append GPL`，上一次是`add distributed`，最早的一次是`wrote a readme file`。

```
$ git log
commit 7015d9b8fc8e289b6a9da1d037e6eded300bb0b0 (HEAD -> master)
Author: Yosen <gy_lingyi@foxmail.com>
Date:   Tue Jan 16 18:15:47 2024 +0800

    version 3

commit 2ee52c83719c3c5eea4c01f6df4b4eae2c3b571b
Author: Yosen <gy_lingyi@foxmail.com>
Date:   Tue Jan 16 17:43:37 2024 +0800

    it's a new test, son

commit 878c87564bc598f123c34e0185b7f6693d555070
Author: Yosen <gy_lingyi@foxmail.com>
Date:   Tue Jan 16 16:53:14 2024 +0800

    it's a test about git learning,son.
```

如果嫌输出信息太多，可以试试加上`--pretty=oneline`参数：

```
$ git log --pretty=oneline
7015d9b8fc8e289b6a9da1d037e6eded300bb0b0 (HEAD -> master) version 3
2ee52c83719c3c5eea4c01f6df4b4eae2c3b571b it's a new test, son
878c87564bc598f123c34e0185b7f6693d555070 it's a test about git learning,son.
```

类似`1094adb...`的是`commit id`（版本号）

### reset

首先，Git必须知道当前版本是哪个版本。在Git中，用`HEAD`表示当前版本，也就是最新的提交`1094adb...`，上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，当然往上100个版本写100个`^`比较容易数不过来，所以写成`HEAD~100`。

然后我们可以使用`git reset`把当前版本`version 3`回退到上一个版本`it's a new test, son`

```
$ git reset --hard HEAD^
HEAD is now at 2ee52c8 it's a new test, son
```

然后我们打开文件，就能发现内容已经回到了上个版本

但此时我们使用`git log`已经看不见回退前的版本了

```
$ git log
commit 2ee52c83719c3c5eea4c01f6df4b4eae2c3b571b (HEAD -> master)
Author: Yosen <gy_lingyi@foxmail.com>
Date:   Tue Jan 16 17:43:37 2024 +0800

    it's a new test, son

commit 878c87564bc598f123c34e0185b7f6693d555070
Author: Yosen <gy_lingyi@foxmail.com>
Date:   Tue Jan 16 16:53:14 2024 +0800

    it's a test about git learning,son.
```

如果此时需要找回回退前版本，需要在该窗口未关闭前找到其`commit id`--`7015d9b8fc8e289b6a9da1d037e6eded300bb0b0`

```
$ git reset --hard 705d
HEAD is now at 7015d9b version 3
```

版本号可以不写全，git会自己去找



## HEAD指针

git内部有个指向当前版本的`HEAD`指针，当你回退版本时，指针从指向`version 3`版本

```ascii
┌────┐
│HEAD│
└────┘
   │
   └──▶ ○ version 3
        │
        ○ it's a new test, son
        │
        ○ it's a test about git learning,son.
```

指向`it's a new test, son`版本

```ascii
┌────┐
│HEAD│
└────┘
   │
   │    ○ version 3
   │    │
   └──▶ ○ it's a new test, son
        │
        ○ it's a test about git learning,son.
```

然后把工作区的文件更新



## git reflog

当你一不小心关闭了窗口又想找回未来版本时，可以使用`git reflog`来找到未来版本的`commit id`

```diff
$ git reflog
7015d9b (HEAD -> master) HEAD@{0}: reset: moving to 7015d
2ee52c8 HEAD@{1}: reset: moving to HEAD^
7015d9b (HEAD -> master) HEAD@{2}: commit: version 3
2ee52c8 HEAD@{3}: commit: it's a new test, son
878c875 HEAD@{4}: commit (initial): it's a test about git learning,son.
```



## 工作区与暂存区

### 1. 工作区（Working Directory）

电脑里能看见的目录

### 2. 版本库（Repository）

工作区里面那个隐藏的目录(`.git`)就是git的版本库

里面比较重要的有一个叫stage（或index）的暂存区，git自动创建的第一个分支`master`，还有指向`master`的一个指针`HEAD`

### 3. 与添加文件的关系

`git add`是把文件添加进去，实际上是把文件修改添加到暂存区

`git master`是提交修改，把暂存区的所有内容提交到当前分支

### 4. 练习

新建一个`LICENSE.txt`文件并修改`test.txt`，查看其状态

```
$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   test.txt

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        LICENSE.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

`LICENSE`未被添加过，所以状态是`Untraced`

使用`add`后，再使用`commit`完成提交

## 撤销修改

### 撤销工作区修改

在`commit`提交之前，使用

```
$ git checkout -- test.txt
```

把`test.txt`在工作区的修改撤销

这里有两种情况

1. 使用`add`之前：`test.txt`变成和版本库一样的状态
2. 使用`add`之后，`commit`之前：`test.txt`变成和暂存区里一样的状态

### 撤销暂存区修改

不小心把错误版本上传到了暂存区，可以使用`git reset HEAD <file>`撤销（unstage）暂存区的修改

```diff
$ git reset HEAD test.txt
Unstaged changes after reset:
M       test.txt
```

所以`reset`不仅能回退版本，也能撤销暂存区的修改



## 参考文献

[廖雪峰](https://www.liaoxuefeng.com/wiki/896043488029600)

