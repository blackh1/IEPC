# 说明

## 实验题目

implement length extension attack for SM3

## 运行指导

```bash
mkdir build
cd build
cmake ..
make
../bin/main
```

## 记录

- 在main.cpp中可以设置需要扩展的消息，并且原始消息是随机生成的。
- 测试攻击示例：

```bash
原始Hash值为:                   d98241fb20dfc19ff396b00d820e9fed80954a0db48d5cd6c97fa4c5374d08d6
新消息Hash(m|padding|m3):       a0b51660dab4f2dffacde10094b3b6c98778739a832fe63a6a671ff64cede4c1
扩展攻击Hash值:                 a0b51660dab4f2dffacde10094b3b6c98778739a832fe63a6a671ff64cede4c1
cost time is 7.2e-05s
```

- 注意事项
  - 在转换原始消息摘要值时，注意大小端问题。
  - 由于使用opensssl实现sm3无法自定义IV向量，也就无法将原始消息的摘要值放入其中进行攻击，所以参考了GmSSL中的sm3实现方法。

## 运行截图

![image](http://other-file.blackh1.top/%E5%88%9B%E6%96%B0%E5%88%9B%E4%B8%9A%E5%AE%9E%E8%B7%B5/SM3_length_extension_attack.png)
