# implement the naïve birthday attack of reduced SM3

## 项目简介

此项目针对SM3进行朴素生日攻击，通过不断生成字符串来生成摘要值，与预期进行对比，直到找到满足要求的消息。

## 代码说明

- 代码文件:`src/main.cpp`

## 运行指导

```bash
mkdir build
cd build
cmake ..
make
../bin/main
```

## 效率测试

- 8 bits

```txt
Digest1 is:f3d2b91551c6034e53a6ea5953cb8683c0bc87ee9ed6bd4cd508fa818d28e133
Digest2 is:f3e31d17b42a4c44211444c727e9783df4fe59573e9f7cf731f200c4ac16e0a0
Message1 is:4830677337646c315a437338506638383955374a636938413171314131696200
Message2 is:4437354d655a3872464c49317154644f47346b7333624b5535346e566a344f00
cost time is 0.002971s
```

- 16bits

```txt
Digest1 is:45c50fd85445a43775007d99c38aa6a01ca2c9f8bdb89bd8fb13f996da13dbc3
Digest2 is:45c5dc988148b46dd9bbf4ce933956f9a62a6cf26057ba428ec0600b6fcc8edc
Message1 is:485a364638734c3359346d42574c6b63766372634958394330415a3059683000
Message2 is:663565515067524f36495639645558566739385738735a72304f48484c347500
cost time is 0.084566s
birthday attack front :16bit(s)
```

- 24bits

```txt
Digest1 is:66d6d15ceac6beb2ebe6436717df9749e53f9fd2c8a7186ecba63354c8b72e7c
Digest2 is:66d6d1a4b1954c972d334c1365eb0abd7a3c63300179ce7cf32a4444d42a7335
Message1 is:356b6152334a53307970334e5643386e326d737a39313558766c6c7775726500
Message2 is:4f6852314e61344869775732315635746d3543323836453331697a3335426900
cost time is 8.00296s
birthday attack front :24bit(s)
```

## 运行截图

![image](http://other-file.blackh1.top/%E5%88%9B%E6%96%B0%E5%88%9B%E4%B8%9A%E5%AE%9E%E8%B7%B5/SM3_birthday_attack.png)
