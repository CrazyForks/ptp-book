# PTP技术书 — 从思想实验到协议实现

一本从思想实验到源码、从理论到动手实现的开源PTP技术书。

### 实际运行效果

![ptp_demo](https://github.com/user-attachments/assets/d6544ebd-833d-48e3-9830-e8b5e57791c3)

## 这本书讲了什么

全书 41 节，分四章：

- **第一章（4 节）**：从“你周围的一切都静止了”这个思想实验开始，讲时间的本质与同步的意义
- **第二章（18 节）**：逐机制拆解 PTP 协议——BMCA 选举、四个时间戳的数学、透明时钟、硬件时间戳、安全机制
- **第三章（13 节）**：走进 LinuxPTP 源码，看工业级实现如何驾驭 9 种端口状态、PI 伺服控制器怎么让时钟“追上”主时钟
- **第四章（6 节）**：亲手实现一个轻量级 PTP 程序（ptp-lite，约 1000 行 C），主时钟和从时钟可以实际运行起来做同步

**不需要网络协议的先修知识。第一章的四节思想实验足够让你进入状态。**

## 快速开始

在线阅读：直接浏览 `chapters/` 目录下的 Markdown 文件，按文件名顺序阅读。

推荐 VS Code + Markdown Preview Enhanced 插件，或者 Typora、Obsidian。

运行示例代码：

```bash
git clone https://github.com/Lularible/ptp-book.git
cd ptp-book/ptp_lite
make

# 终端 A
sudo ./ptp_master eth0[替换为实际网卡名]

# 终端 B
sudo ./ptp_slave eth0[替换为实际网卡名]
```

## 许可证

书籍内容：[CC BY-NC-ND 4.0](LICENSE) · ptp-lite 源码：MIT

## 姊妹篇

本书是"汽车电子七部曲"系列中的一部。另外两部已发布：

- **[从沙子到车辙——一个工程师的理解](https://github.com/Lularible/from-sand-to-ruts)** — 从图灵机到 CAN 总线，从半导体物理到 AUTOSAR，一部为汽车电子工程师写的全景入门
- **[HSM 技术书——从思想实验到安全基石](https://github.com/Lularible/hsm-book)** — 从岩画密码学到硬件安全模块，完整覆盖车载 HSM 的技术链路

"汽车电子七部曲"是一个持续更新的系列——还有存储、诊断、功能安全、软件工程四本在打磨中。
如果觉得这系列对你有用，不妨给个 ⭐ 关注进度。
