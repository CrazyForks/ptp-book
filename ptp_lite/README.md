# PTP Lite - 轻量级PTP时间同步实现

一个用于教学的轻量级PTP（Precision Time Protocol）实现，遵循IEEE 1588-2019标准。

## 项目特点

- **简洁易懂**：代码总量约1000行，注释详细
- **完整功能**：实现完整的E2E同步流程
- **易于学习**：适合理解PTP协议核心机制
- **可实际运行**：真正能够同步时间
- **无编译警告**：代码规范严格，适合教学

## 技术选型

- **延迟测量**：E2E（End-to-End）
- **传输方式**：UDP/IPv4组播
- **时间戳类型**：软件时间戳
- **伺服算法**：PI控制器

## 快速开始

### 编译

#### x86架构（默认）

```bash
make
```

#### ARM64架构

```bash
make arm64
```

生成文件：`ptp_master_arm64`, `ptp_slave_arm64`

#### ARM32架构

```bash
make arm32
```

生成文件：`ptp_master_arm32`, `ptp_slave_arm32`

#### 编译所有架构

```bash
make all-arch
```

#### 查看帮助

```bash
make help
```

#### 交叉编译工具链安装

**Ubuntu/Debian系统**：
```bash
# 安装ARM64工具链
sudo apt install gcc-aarch64-linux-gnu

# 安装ARM32工具链（硬浮点）
sudo apt install gcc-arm-linux-gnueabihf
```

**Fedora/CentOS系统**：
```bash
# 安装ARM64工具链
sudo yum install gcc-aarch64-linux-gnu

# 安装ARM32工具链
sudo yum install gcc-arm-linux-gnu
```

#### 验证编译结果

```bash
# 查看编译后的程序架构信息
file ptp_master        # ELF 64-bit x86-64
file ptp_master_arm64  # ELF 64-bit ARM aarch64
file ptp_master_arm32  # ELF 32-bit ARM
```

### 运行主时钟

在一台机器上运行：

```bash
sudo ./ptp_master eth0
```

### 运行从时钟

在另一台机器上运行：

```bash
sudo ./ptp_slave eth0
```

### 验证同步效果

```bash
# 在两台机器上分别查看时间
date

# 从时钟输出示例：
# Sent Delay_Req seq=0 at 1234567890.123456789
# Sync seq=0: t1=1234567890.123456789 t2=1234567890.123470000 offset=-12345 ns
# FREQ ADJ: -12.34 ppb
# Delay_Resp: t3=... t4=... delay=5678 ns corrected_offset=-12345 ns
```

## 文件结构

```
ptp_lite/
├── README.md           # 项目说明
├── Makefile            # 编译脚本
├── ptp_common.h        # 公共定义和类型
├── ptp_message.h       # 消息结构定义
├── ptp_message.c       # 消息编码实现
├── ptp_servo.h         # 伺服算法头文件
├── ptp_servo.c         # 伺服算法实现
├── ptp_master.c        # 主时钟程序
├── ptp_slave.c         # 从时钟程序
└── .gitignore          # Git忽略文件
```

## 实现的消息类型

- **Announce**：主时钟通告
- **Sync + Follow_Up**：时间同步
- **Delay_Req**：延迟请求
- **Delay_Resp**：延迟响应

## 同步原理

### E2E延迟测量

```
主时钟                从时钟
  |                     |
  |-- Sync -----------> | (t2: 接收时间)
  |                     |
  |-- Follow_Up ------> | (携带t1)
  |                     |
  |                     |-- Delay_Req --> (t3: 发送时间)
  |                     |
  |<-- Delay_Req ------ | 
  |                     |
  |-- Delay_Resp -----> | (携带t4)
  |                     |

路径延迟 = [(t2-t1) + (t4-t3)] / 2

真实偏差 = (t2-t1) - 路径延迟

其中：
- t1: Sync发送时间（主时钟）
- t2: Sync接收时间（从时钟）
- t3: Delay_Req发送时间（从时钟）
- t4: Delay_Req接收时间（主时钟）
```

### PI控制器

使用比例-积分控制器平滑调整时钟频率：

```
频率调整 = -Kp × offset - Ki × ∫offset dt

参数：
- Kp = 0.7（比例增益）
- Ki = 0.3（积分增益）
```

## 配置参数

主要配置在 `ptp_common.h` 中定义：

```c
#define PTP_PRIMARY_MCAST      "224.0.1.129"  // 组播地址
#define PTP_EVENT_PORT         319             // 事件端口
#define PTP_GENERAL_PORT       320             // 普通端口
#define PTP_DEFAULT_DOMAIN     0               // 默认域
#define PTP_DEFAULT_PRIORITY1  128             // 优先级1
#define PTP_DEFAULT_PRIORITY2  128             // 优先级2
```

## 系统要求

- Linux操作系统
- GCC编译器
- root权限（调整系统时钟）
- 两台机器在同一网络

## 防火墙配置

```bash
# 允许PTP端口
sudo iptables -A INPUT -p udp --dport 319 -j ACCEPT
sudo iptables -A INPUT -p udp --dport 320 -j ACCEPT
```

## 精度说明

由于使用软件时间戳，精度通常在：

- 典型精度：±100 微秒
- 最佳情况：±10 微秒
- 受系统负载影响

如需更高精度，请使用支持硬件时间戳的网卡。

## 常见问题

### 1. 收不到消息

检查防火墙和组播配置：

```bash
ip maddr show eth0
```

### 2. 时间不准

确保系统时钟没有被NTP等其他服务干扰：

```bash
timedatectl set-ntp false
```

### 3. 偏差很大

软件时间戳精度有限，可尝试：
- 减少系统负载
- 使用实时内核
- 升级到硬件时间戳

## 学习路径

推荐学习顺序：

1. 阅读 README 了解项目概况
2. 研究 ptp_common.h 理解基础数据类型
3. 分析 ptp_message.c 学习消息编码
4. 运行主时钟程序观察消息发送
5. 运行从时钟程序理解同步流程
6. 修改参数进行实验

## 扩展方向

可继续改进：

- [ ] 添加硬件时间戳支持
- [ ] 实现BMCA算法
- [ ] 添加管理协议
- [ ] 支持多端口
- [ ] 添加安全扩展

## 参考资料

- [IEEE 1588-2019标准](https://standards.ieee.org/standard/1588-2019.html)
- [LinuxPTP项目](http://linuxptp.sourceforge.net/)
- [PTP协议精讲](配套教程)

## 许可证

MIT License

## 作者

本代码为PTP教程配套示例，用于教学目的。

## 贡献

欢迎提交Issue和Pull Request！