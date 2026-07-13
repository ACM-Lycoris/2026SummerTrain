# ACM 训练赛后分析工具

这是一个直接读取当前暑期训练目录的本地复盘工具。编号目录（如 `1/`、`10/`）始终是只读数据源；程序不会修改或编译其中的 C++ 文件。

## 每天怎么用

补完题并保存 C++ 文件后，双击根目录的 `run-review.cmd`。

窗口会显示数据库和日报路径，并停留等待按键。随后打开 `reports/` 中日期最新的 Markdown 文件即可查看反馈。

也可以在 PowerShell 中运行：

```powershell
python main.py
```

常用参数：

```powershell
# 只更新训练数据库，不生成日报
python main.py --scan-only

# 重建数据库并生成指定日期的报告
python main.py --date 2026-07-13

# 分析另一个同格式训练根目录
python main.py --root E:\ACM\Training\AnotherSeason
```

## 状态规则

- 有实际解题逻辑的 C++ 文件默认记为 `AC / inferred`。
- 空文件、只有模板或明显未完成的实现记为 `ATTEMPTED / inferred`。
- 同一场同一题的多个版本会合并为一道题；只要其中一个版本有效，推断状态就是 AC。
- 文件名开头的字母是题号，大小写会统一。例如 `i.cpp` 是题目 I，`C(DSUbfs).cpp` 和 `C(setBFS).cpp` 都是题目 C。

人工结论写在 `data/manual_overrides.json`，自动运行不会覆盖该文件。例如：

```json
{
  "schema_version": 1,
  "problems": {
    "10/J": {
      "status": "ATTEMPTED",
      "note": "赛后确认尚未通过"
    }
  },
  "sessions": {
    "10": {
      "date": "2026-07-13"
    }
  }
}
```

人工状态只能是 `AC` 或 `ATTEMPTED`。

## 生成内容

- `data/sessions.json`：当前所有训练场次、题目、源码元数据、状态和分析结果。
- `data/analysis_cache.json`：按文件 SHA-256 保存的分析缓存；代码没变化时直接复用。
- `reports/YYYY-MM-DD.md`：按日期保存的训练复盘；重复运行会覆盖同一天报告，不会生成重复记录。

日报包括完成情况、算法分类、最近训练分布、带文件行号的 C++ 风险、能力画像和有历史证据的复习建议。

## 数据边界

当前目录没有比赛完整题目表或在线提交记录。因此“未解决题目”只能统计已经创建源码但被识别为未完成的题，无法统计从未创建文件的题目。算法和风险检查采用可解释的本地规则；提示为启发式线索，不等同于在线判题结论。

## 运行测试

```powershell
python -m unittest discover -s tests -v
```
