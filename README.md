# IEPC

Innovation and Entrepreneurship Practice Course

- [小组成员](#小组成员)
- [已完成项目](#已完成项目)
- [Project-List](#projects-list)
  - [SM3](#sm3)
  - [SM2](#sm2)
  - [Bitcoin](#bitcoin)
  - [Ethernet](#ethernet)
  - [Real-world cryptanalysis](#real-world-cryptanalysis)
  - [Real-world-z-SNARKs](#real-world-zk-snarks)

## 小组成员

| key         | value        |
| ---------- | ------------- |
| 姓名        | 关钧         |
| 学号        | 201900460012|
| git账户名称 | blackh1      |

## 已完成项目

完成项目如下所示，均为个人完成。

|项目名称|
|-----|
|implement the naïve birthday attack of reduced SM3|
|implement the Rho method of reduced SM3|
|implement length extension attack for SM3|
|do your best to optimize SM3 implementation (software)(有数据依赖问题，运行效率很低)|

## 项目说明

- 代码使用C、C++完成

- 各项目的具体说明在每个项目的文件夹下的`README.md`文件中

- 完成项目为上面表格中的四个项目，其余项目未完成，所有完成项目均可运行并得到正确结果。

## Projects-List

### SM3

- [x] Project:implement the naïve birthday attack of reduced SM3
- [x] Project:implement the Rho method of reduced SM3
- [x] Project:implement length extension attack for SM3,SHA256,etc
- [x] Project:do your best to optimize SM3 implementation (software)
- [ ] Project:Impl Merkle Tree following RFC6962
  - Construct a Merkle tree with 10w leaf nodes
  - Build inclusion proof for specified element
  - Build exclusion proof for specified element
- [ ] Project:Try to Implement this scheme
![image](http://other-file.blackh1.top/%E5%88%9B%E6%96%B0%E5%88%9B%E4%B8%9A%E5%AE%9E%E8%B7%B5/SM3_01.png)

### SM2

- [ ] Project:report on the application of this deduce technique in Ethereum with ECDSA
- [ ] Project: impl sm2 with RFC6979
- [ ] Project: verify the above pitfalls with proof-of-concept code
- [ ] Project: Implement the above ECMH scheme
- [ ] Project: Implement a PGP scheme with SM2
- [ ] Project: implement sm2 2P sign with real network communication
- [ ] Project: PoC impl of the scheme, or do implement analysis by Google
- [ ] Project: implement sm2 2P decrypt with real network communication

### Bitcoin

- [ ] Project: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
- [ ] Project: forge a signature to pretend that you are Satoshi

### Ethernet

- [ ] Project: research report on MPT

### Real-world-cryptanalysis

- [ ] Project: Find a key with hash value “*sdu_cst_20220610*” under a message composed of *your name* followed by *your student ID*. For example, “*San Zhan 202000460001*”.
- [ ] Project: Find a 64-byte message under some k fulfilling that their hash value is symmetrical

### Real-world-zk-SNARKs

- [ ] Project:Project Idea
  1. Write a circuit to prove that your CET6 grade is larger than 425.
      a. Your gradeinfo is like(cn_id,grade,year,sig_by_moe).These grades are published as commitments onchain by MoE.
      b. When you got an interview from an employer,you can prove to them that you have passed the exam without letting them know the exact grade.
  2. The commitment scheme used by MoE is SHA256-bases.
      a. commit=SHA256(cn_id,grade,sig_by_moe,r)