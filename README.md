# 乘风龙王的代码库(C++)
随便写的一些东西。
所有代码文件编码都是**utf-8带bom**。

项目依赖项
* [boost](https://www.boost.org)

## 内容包含

### 工具
* **cflw工具**：常用工具
* **cflw工具_循环**：提供一些简化范围for的实用类
* **cflw工具_属性**：提供属性(Property)支持。*没什么用*。
* **cflw工具_运算**：为了方便函数式编程写的一些小函数。
* **cflw辅助**：c++语言强化。*没什么用*。
* **cflw时间**：封装一些时间类
* **cflw异常**：定义常用异常类
* **cflw视窗**：win32 api的一些封装
* **cflw单位**：一些量纲。*没什么用*。

### 数学
* **cflw数学**：常用数学函数
* **cflw数学_向量**：向量结构
* **cflw数学_平面几何**：圆形、矩形
* **cflw数学_函数方程**：解一些函数和方程
* **cflw数学_矩阵**：通用矩阵运算。四阶矩阵特化。
* **cflw数学_图形**：提供计算机图形学常用结构
* **cflw数学_随机**：随机分布
* **cflw数学_单位转换**：基本单位互转。*没什么用*。
* **cflw数学_分辨率**：计算分辨率的函数，分辨率结构，分辨率枚举。
* **cflw数学_杂烩**：数学大杂烩

### 图形
* ~~cflw图形_d3d9~~(已废弃)：Direct3D 9的封装
* **cflw图形_d3d11**：Direct3D 11的封装
* **cflw图形_d3d12**：Direct3D 12的封装
	* 要编译`cflw图形_d3d12.cpp`，其中的`d3dx12.h`来自[微软DirectX图形示例](https://github.com/Microsoft/DirectX-Graphics-Samples)
* **cflw图形_d2d**：Direct2D 1的封装。支持高分屏。
* **cflw图形_dx纹理**：载入常见图片格式。
* **cflw图形_d3d着色器**：旧的Direct3D着色器编译器`<d3dcompiler.h>`的封装
* **cflw图形_dx着色器**：新的[DirectX着色器编译器](https://github.com/Microsoft/DirectXShaderCompiler)`<dxcapi.h>`的封装。
	* [DirectX着色器编译器](https://github.com/Microsoft/DirectXShaderCompiler)的`dxcompiler.dll`不包含在系统中，需要手动把Windows 10 SDK里的相应文件复制到系统里。

### 输入
* **cflw输入**：统一的输入接口和按键相关实用工具。
* ~~cflw输入_di8~~(已废弃)：DirectInput 8的封装。支持鼠标、键盘、手柄。
* **cflw输入_win**：win32 api的封装，通过接收窗口消息驱动。支持鼠标、键盘、触摸。支持高分屏。
* **cflw输入_xi**：XInput的封装。支持xbox手柄。

### 多媒体
* **cflw多媒体**：读取波形声音
* ~~cflw音频_ds8~~(已废弃)：DirectSound 8的封装
* **cflw音频_xa2**：XAudio 2的封装

### 文件
* **cflw文件_csv**：对csv逗号分隔表格文件的支持
* **cflw文件_obj模型**：对对象模型文件的支持
* **cflw文件_json**：方便读写json文件的类

### 常用代码
* **窗口模板**.cpp：创建空白窗口的代码，包含主函数、窗口过程。
* **常用代码段**.txt：*没什么用*。
* **3d**.hlsl：简单的三维着色器

## 编译说明
见[编译说明](文档/编译说明.md)