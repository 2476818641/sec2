# AdaptixC2 v1.2 — i18n-Edition (sec2)

本项目基于 [AdaptixC2 v1.2](https://github.com/Adaptix-Framework/AdaptixC2) 进行汉化，并对服务端及 Agent 进行了安全加固修改。

---

## 声明

本项目仅供 **授权安全测试** 与 **红队行动** 使用。未经授权使用本工具可能违反当地及国际法律，使用者自行承担一切责任。

本项目为 AdaptixC2 的第三方修改版，与原项目开发者无关。原始项目使用 [GPL v3](LICENSE) 协议，本修改版持续沿用该协议。

```
Copyright (C) Adaptix-Framework
Modifications (C) 2025 sec2
Licensed under GNU General Public License v3.0
```

---

## 修改内容

| 类别 | 说明 |
|------|------|
| 流量特征 | 移除 `Server: AdaptixC2` / `Adaptix-Version` 等标识头，404 页面去特征化，TLS 仅保留 GCM 套件 |
| 加密升级 | RC4 → AES-128-GCM（服务端 Go 标准库 + Agent 紧凑型自实现），覆盖所有通信层级 |
| DNS 传输 | 移除 `encrypt_key` 重复加密层，仅保留 `SessionKey` 保护 |
| 内存特征 | 睡眠 XOR 混淆改为 AES-128-GCM；DJB2 哈希种子可构建时定制；Syscall stub 指令多样化；ETW/AMSI 补丁运行时混淆；DLL 名称 XOR 键可定制 |
| i18n | 客户端界面简体中文本地化 |

---

## 构建与兼容性

构建方式与原项目相同。自定义哈希种子（可选）：

```bash
# 生成自定义 API 哈希头文件
python hashes.py --seed <value> > ApiDefines.h

# 构建代理时传递种子和 XOR 密钥
make CFLAGS="-DDJb2_SEED=<value> -DSTR_XOR_KEY=<value>"
```

跨版本通信不兼容（AES-GCM 格式不同于原始 RC4），须配套使用修改版服务端与代理。

---

## 原始项目

- [AdaptixC2 GitHub](https://github.com/Adaptix-Framework/AdaptixC2)
- [官方文档](https://adaptix-framework.gitbook.io/adaptix-framework)
- 版本：v1.2

---

> 汉化 + 加固 by sec2 · GPL v3
