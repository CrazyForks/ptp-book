# PTP源码与文档同步维护方案

## 问题背景

第4章包含源码片段和解读，但源码会持续演进，导致文档与代码不同步。

---

## 维护策略

### 1. 源码版本标记

**在源码中添加版本号**：

```c
/* ptp_common.h */
#define PTP_LITE_VERSION "1.0.0"
#define PTP_LITE_VERSION_DATE "2026-04-10"
```

### 2. 文档版本说明

**在第4章开头添加说明**：

```markdown
> **源码版本说明**
> 
> 本章源码片段基于 **ptp-lite v1.0.0 (2026-04-10)**。
> 
> ⚠️ **重要提示**：
> - 完整、最新的源码请查看 `ptp_lite/` 目录
> - 本章代码片段仅用于理解原理，可能不是最新版本
> - 如发现差异，以源码为准
> - 源码变更记录请查看 [CHANGELOG.md](CHANGELOG.md)
```

### 3. 关键代码片段标记

**在源码中添加标记注释**（可选）：

```c
/* [BOOK-CH4] ptp_servo.h - 伺服算法定义 */
#define SERVO_STEP_THRESHOLD 10000000LL
/* [BOOK-CH4-END] */
```

### 4. 文档引用策略

**使用相对引用**：

```markdown
### 源码文件

完整源码请查看：
- [ptp_servo.h](ptp_lite/ptp_servo.h)
- [ptp_servo.c](ptp_lite/ptp_servo.c)
- [ptp_slave.c](ptp_lite/ptp_slave.c)

关键代码片段如下（可能不是最新版本）：
...
```

### 5. CHANGELOG记录

**在CHANGELOG.md中详细记录源码变更**：

```markdown
## [1.1.0] - 2026-XX-XX

### Changed

#### 源码变更

- 修改 SERVO_STEP_THRESHOLD: 100ms → 10ms
  - 原因：加快同步收敛速度
  - 影响：第4章伺服算法章节
  
- 改进 adjust_clock 实现
  - 使用 clock_settime 代替 clock_adjtime(ADJ_SETOFFSET)
  - 原因：更好的兼容性
  - 影响：第4章时钟调整章节
```

### 6. 自动化工具（可选）

**创建脚本自动更新文档中的源码片段**：

```bash
#!/bin/bash
# update_ch4_code.sh - 更新第4章源码片段

# 提取源码片段
sed -n '/\[BOOK-CH4\]/,/\[BOOK-CH4-END\]/p' ptp_lite/ptp_servo.h

# 更新到第4章文档
# ... (使用sed替换)
```

---

## 维护流程

### 每次修改源码时，请检查以下项目：

- [ ] 是否更新了ptp_common.h中的版本号？
- [ ] 是否更新了CHANGELOG.md？
- [ ] 是否在CHANGELOG中记录了变更原因和影响？
- [ ] 是否在第4章添加了变更说明？
- [ ] 是否在源码中添加了注释标记？

---

## 具体实施

### 第4章已添加的版本说明

**文件**：`4.2-消息结构与编码-PTP报文的-DNA-.md`

```markdown
# 4.2 消息结构与编码：PTP报文的"DNA"

> **源码版本说明**
>
> 本章源码片段基于 **ptp-lite v1.0.0 (2026-04-10)**。
>
> ⚠️ **重要提示**：
> - 完整、最新的源码请查看 `ptp_lite/` 目录
> - 本章代码片段仅用于理解原理，可能不是最新版本
> - 如发现差异，以源码为准
> - 源码变更记录请查看 [CHANGELOG.md](CHANGELOG.md)
>
> **主要源码文件**：
> - [ptp_common.h](../ptp_lite/ptp_common.h) - 公共定义（83行）
> - [ptp_message.h](../ptp_lite/ptp_message.h) - 消息结构定义（96行）
> - [ptp_message.c](../ptp_lite/ptp_message.c) - 消息编码实现（99行）
```

---

## 维护原则

### ✅ 推荐

1. **在第4章开头添加版本说明**（已完成）
2. **在CHANGELOG中详细记录变更**（已完成）
3. **源码中添加版本标记**（已完成）
4. **提供源码文件链接**（已完成）
5. **关键概念讲解，代码仅作参考**（已完成）

### ❌ 避免

1. ~~在文档中复制完整的源码文件~~
2. ~~保证文档中的代码是最新的~~
3. ~~忽略源码变更对文档的影响~~

---

## 工具建议

### Git Hook（可选）

创建 `.git/hooks/pre-commit`：

```bash
#!/bin/bash
# 检查源码是否变更
if git diff --cached ptp_lite/*.c ptp_lite/*.h | grep -q .; then
    echo "⚠️ 源码已变更，请检查是否需要更新："
    echo "  - 第4章相关内容"
    echo "  - CHANGELOG.md"
    echo ""
    echo "继续提交？(y/n)"
    read answer
    if [ "$answer" != "y" ]; then
        exit 1
    fi
fi
```

---

## 核心原则

**理念**：
1. 文档讲解原理，源码才是权威
2. 明确标注版本，避免误导读者
3. CHANGELOG详细记录变更
4. 提供源码链接，方便查看最新代码

**目标**：
- 读者理解PTP原理和实现思路
- 源码是最权威的实现
- 文档不保证是最新的，但有版本说明
- 通过链接可以找到最新源码

---

## 总结

✅ **维护机制已建立**：
- 版本号标记
- 文档版本说明
- CHANGELOG记录
- 源码文件链接
- 维护检查清单

后续源码变更时，按照这个流程更新即可！