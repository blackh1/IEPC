# 说明

## 实验题目

implement the Rho method of reduced SM3

## 运行指导

```bash
mkdir build
cd build
cmake ..
make
../bin/main
```

## 效率测试

所有消息都是随机生成

- 8bits

```txt
Digest1 is:4242039d3eb5e628420206d4f7c52b972245aa3fbfb42f7787ef80556164406f
Digest2 is:4208b6806c020fd41dc4b2e84f06d481a20fdbd8d9179f2bbe980b9a5504d3e3
Message is :3296wFpbjnMF1fq0zI8j0mdLYT83sO2
cost time is 0.001635s
rho attack front :8bit(s)
```

- 16bits

```txt
Digest1 is:6ffe4ec25d623e80e4d320ef17adb905796db89db04ee250b2950dc315df60c1
Digest2 is:6ffed72f749f28931478e4a8397aa08ba1ea23e1ac5714a21527dbc3df3ea374
Message is :cax634JF0BvT2cpQXdCZYFpDQv41567
cost time is 0.071348s
rho attack front :16bit(s)
```

- 24bits

```txt
Digest1 is:c92ee491e4972b7edbc7620870f1ec0cfd3dbc37c895ae763d9a4ec7c2c712d2
Digest2 is:c92ee4d046cfd29c38b17b6fbfc3a74ea5e3985794d551b2a6db7c387ecf2b31
Message is :mjbk75yt47HaYHqwwCHlN6WFZs7pFCz
cost time is 30.7174s
rho attack front :24bit(s)
```

## 运行截图

![image](http://other-file.blackh1.top/%E5%88%9B%E6%96%B0%E5%88%9B%E4%B8%9A%E5%AE%9E%E8%B7%B5/SM3_rho_attack.png)
