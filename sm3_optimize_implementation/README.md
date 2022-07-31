# 说明

## 实验题目

optimize SM3 implementation(software)

## 运行指导

```bash
mkdir build
cd build
cmake ..
make
../bin/main
```

## 效率测试

- 只使用循环展开
  第一行为使用循环展开，第二行为普通的算法。
  数据长度为1024byte，测试16777214次总计时间。

```bash
00890c04745adaa255bd0a33600b362292e5e771b1bead4ad31551aa2485fcd9
cost time is 127.302s
00890c04745adaa255bd0a33600b362292e5e771b1bead4ad31551aa2485fcd9
cost time is 128.495s
```

- 只使用SIMD
  数据量相同，测试次数1048574次(有可能还有其他问题，如果处理16777214次时间过长)

```bash
27425277a6a21bddeadf13c16607a6f4b93149b5dc038014e71c38f3afc938f8
cost time is 22.1582s
```

## 运行截图

![image](http://other-file.blackh1.top/%E5%88%9B%E6%96%B0%E5%88%9B%E4%B8%9A%E5%AE%9E%E8%B7%B5/SM3_optimize.png)
