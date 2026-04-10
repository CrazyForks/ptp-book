# 更新日志 (CHANGELOG)

本文档记录PTP技术书项目的所有重要变更。

格式基于 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.0.0/)，
版本号遵循 [语义化版本](https://semver.org/lang/zh-CN/)。

---

## [1.0.0] - 2026-04-10

### 新增

#### 书籍内容

- **第一章**：一切从"对表"开始（4节）
  - 1.1 如果你周围的一切都静止了
  - 1.2 人类为时间画下的刻度
  - 1.3 为什么你手机上的时间和我不一样？
  - 1.4 那个按电子表的小学生，已经懂了PTP的核心

- **第二章**：PTP协议深度解析（18节）
  - 2.1-2.9：核心机制（角色、BMCA、域、数据集、状态机、透明时钟、延迟测量、偏移计算）
  - 2.10-2.18：高级特性（频率同步、硬件时间戳、报文格式、TLV、管理协议、单播协商、安全机制、White Rabbit、Profile）

- **第三章**：LinuxPTP源码深度解析（13节）
  - 3.1-3.9：核心模块（项目全景、数据结构、状态机、BMCA、伺服、PHC、传输层、硬件时间戳、TLV）
  - 3.10-3.13：工具与运维（pmc、phc2sys、单播协商、故障诊断）

- **第四章**：从零开始实现PTP（6节）
  - 4.1 项目概述
  - 4.2 消息结构与编码
  - 4.3 主时钟程序实现
  - 4.4 从时钟程序实现
  - 4.5 编译运行与测试
  - 4.6 问题排查与优化

#### 源码实现

- **ptp-lite**：轻量级PTP实现（约1000行代码）
  - ptp_common.h：公共定义和类型（83行）
  - ptp_message.h：消息结构定义（96行）
  - ptp_message.c：消息编码实现（99行）
  - ptp_servo.h：PI伺服控制器定义（40行）
  - ptp_servo.c：PI伺服控制器实现（53行）
  - ptp_master.c：主时钟程序（219行）
  - ptp_slave.c：从时钟程序（324行）
  - Makefile：编译脚本（86行）

#### 项目文档

- README.md：项目主文档（详细的项目介绍、目录结构、快速开始指南）
- CONTRIBUTING.md：贡献指南（详细的贡献流程、规范、模板）
- CHANGELOG.md：更新日志（本文档）
- SUMMARY.md：GitBook目录索引
- CODE_DOC_SYNC.md：源码与文档同步维护方案

#### GitHub模板

- Issue模板（3个）：
  - Bug报告模板
  - 功能建议模板
  - 内容问题模板
- Pull Request模板

#### 技术特性

- **符合IEEE 1588-2019标准**：
  - 完整的消息结构定义（34字节Header）
  - E2E延迟测量机制
  - 支持超大偏差修正（测试通过38年偏差）
  - 双Socket监听（Event端口319、General端口320）

- **多架构编译支持**：
  - x86-64
  - ARM64（aarch64）
  - ARM32（armhf）

- **完整的时钟调整机制**：
  - 相位跳变（SERVO_JUMP）：使用clock_settime
  - 频率调整（SERVO_LOCKED）：使用clock_adjtime(ADJ_FREQUENCY)
  - PI伺服控制器
  - 10ms步进阈值

#### 统计数据

- **总章节**：40节
- **总字数**：约48,000字
- **代码量**：约1,000行
- **支持架构**：3个（x86、ARM64、ARM32）
- **文档文件**：45个.md文件

---

## 版本说明

### 版本号规则

本项目版本号遵循语义化版本（Semantic Versioning）：

- **MAJOR**（主版本号）：重大变更，如书籍结构重组
- **MINOR**（次版本号）：新增章节或重要功能
- **PATCH**（修订号）：内容修正、错误修复

### 变更类型

遵循 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.0.0/) 格式：

- **新增（Added）**：新功能、新章节
- **变更（Changed）**：现有内容的变更
- **弃用（Deprecated）**：即将移除的功能
- **移除（Removed）**：已移除的功能
- **修复（Fixed）**：错误修复
- **安全（Security）**：安全相关的修复

---

## 相关链接

- [项目主页](https://github.com/Lularible/ptp-book)
- [贡献指南](CONTRIBUTING.md)
- [许可证](LICENSE)

---

[1.0.0]: https://github.com/Lularible/ptp-book/releases/tag/v1.0.0