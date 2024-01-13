# PopStar
消灭星星是一款经典的消除类游戏

## 游戏介绍
- 总共有五种颜色的星星为，分别为：黄、红、蓝、绿、粉
- 游戏区域为 10 x 10 的矩形，每个位置的颜色随机
- 两个及两个以上的同色星星即可被消除
- 消除得分规则为：num * num * 5（num为同色星星的数量）
- 奖励分数规则为: 2000 - (num * num * 20) （num为剩余的星星数量）
- 关卡分数为：1000 + 2000 * (level-1) + level/3 * 1000 （第一关为1000， 接下来的关卡为3的倍数则加3000，否则加2000）
- 通关要求：不存在可以消除的星星，并且当前分数大于等于关卡分数
- 道具主要有刷新和锤子，一个可以重新刷新当前星星的颜色，一个可以使指定位置的星星直接消失

## 游戏界面
![image](https://user-images.githubusercontent.com/98899771/154812931-efaa1f1d-dadc-4839-9fc0-e8e44a65c7ad.png)

![game_interface](https://user-images.githubusercontent.com/98899771/157398542-dd9f69d9-cc52-4d50-97a2-f5795b92f5cd.gif)

## 编译和运行

### 克隆仓库

```shell
mkdir PopStar && cd PopStar
git clone git@github.com:Lesords/PopStar.git
```

### QT Creator

- 使用 QT Creator 打开 PopStar 路径下的 `PopStar.pro` 文件
- 首次打开，可根据默认选项配置编译器
- 使用 `Ctrl + B` 构建项目，接着再使用 `Ctrl + R` 运行项目即可

### CMake

环境要求：环境变量中需要包含 CMake 和 QT 以及 G++ 的路径

对应工具的验证方法

```shell
cmake --version
qmake --version
g++ --version
```

如果 `qmake --version` 输出的结果中包含 `mingw` 则使用以下方法进行编译

```shell
mkdir build && cd build

# 编译 Debug 版本
cmake ../PopStar/ -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
cmake --build .

# 运行 Debug 版本程序
./output/bin-dbg/PopStar.exe

# 编译 Release 版本
cmake ../PopStar/ -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build .

# 运行 Release 版本程序
./output/bin/PopStar.exe
```

如果 `qmake --version` 输出的结果中包含 `msvc**_64` 则使用以下方法进行编译

```shell
mkdir build && cd build

cmake ../PopStar/ -G "Visual Studio 15 2017 Win64"

# 编译 Debug 版本
cmake --build . --config Debug

# 运行 Debug 版本程序
./output/bin/Debug/PopStar.exe

# 编译 Release 版本
cmake --build . --config Release

# 运行 Release 版本程序
./output/bin/Release/PopStar.exe
```

注：目前仅在 Windows 平台编译运行