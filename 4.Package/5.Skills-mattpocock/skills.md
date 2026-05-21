# Skills 对话记录

本文档记录当前对话中关于 Codex skills 的问答内容。

## 1. 刚才安装了 skills，这些 skills 怎么用

**用户：**

> 刚才安装了skills，这些skills怎么用

**助手：**

Skills 不需要你手动运行命令。你只要在需求里点名，或者描述的任务明显匹配某个 skill，我就会自动读取对应的 `SKILL.md` 并按它的流程做事。

常用方式：

```text
用 diagnose 帮我调这个报错
用 tdd 给这个功能加测试和实现
用 review review since main
用 prototype 做几个 UI 方案让我试
用 obsidian-vault 找一下关于 XXX 的笔记
用 to-prd 把这段想法整理成 PRD
用 to-issues 把这个计划拆成 issue
用 imagegen 生成一张产品图
```

也可以用 `$skill-name` 明确指定：

```text
$diagnose 这个接口 500 了，帮我定位
$tdd 给 checkout 流程加一个优惠码功能
$review review 当前分支相对 main 的改动
```

你不用记完整语法，自然说就行。比如“这个测试挂了，帮我 debug”会触发 `diagnose`；“按红绿重构做”会触发 `tdd`；“帮我审一下这个 PR”会触发 `review`。

如果你想看当前可用的 skills，可以直接说：

```text
列一下当前可用 skills
```

## 2. 详细介绍一下

**用户：**

> 详细介绍一下

**助手：**

Skills 可以理解成“我本地装的一组专项工作流”。你不用自己执行它们，只需要在请求里点名，或者用自然语言描述任务，我会自动选择合适的 skill，读取它的说明文件，然后按它的流程工作。

### 核心用法

你可以直接点名：

```text
用 diagnose 帮我查这个报错
用 tdd 做这个功能
用 review 审一下当前分支
用 prototype 做个原型
用 obsidian-vault 找一下我的笔记
```

也可以用 `$skill` 写法：

```text
$diagnose 这个测试为什么挂了
$tdd 给登录流程加验证码
$review review since main
```

也可以完全自然语言：

```text
这个接口 500 了，帮我定位
按红绿重构做这个功能
帮我把这段想法整理成 PRD
把这个计划拆成 issue
帮我改一下这篇文章
```

我会根据任务自动匹配。

### 当前这些 Skills 大致分组

#### 工程类

`diagnose`：调 bug、查报错、定位性能问题。

适合说：

```text
这个测试挂了，帮我 debug
接口变慢了，diagnose 一下
这个页面白屏，查原因
```

它会按“复现 -> 缩小范围 -> 假设 -> 加观测 -> 修复 -> 回归测试”的流程来。

`tdd`：测试驱动开发。

适合说：

```text
用 tdd 加一个优惠码功能
按红绿重构修这个 bug
先写测试再实现
```

`review`：代码审查。

适合说：

```text
review 当前分支
review since main
审一下这个 PR 的改动
```

它会偏向找 bug、风险、行为回归、测试缺口，不是只做风格建议。

`improve-codebase-architecture`：看架构改进机会。

适合说：

```text
看看这个代码库有什么架构问题
帮我找可重构的地方
这个模块越来越乱，帮我分析
```

`zoom-out`：让分析升高一层，看上下文和全局关系。

适合说：

```text
zoom out 一下这个模块
我不熟这块代码，帮我解释它在系统里的位置
```

`setup-pre-commit`：配置 Husky、lint-staged、typecheck、测试等提交前检查。

适合说：

```text
帮这个项目加 pre-commit hook
设置提交前格式化和测试
```

#### 产品 / 项目管理类

`to-prd`：把当前想法整理成 PRD。

适合说：

```text
把我们刚才讨论的内容写成 PRD
基于这个需求生成一个产品文档
```

`to-issues`：把计划拆成可执行 issue。

适合说：

```text
把这个 PRD 拆成 issues
把这个计划拆成几个独立任务
```

`triage`：整理、判断、推进 issue。

适合说：

```text
帮我 triage 这些 issues
创建一个 bug issue 并补全信息
把这个需求整理到可交给 agent 的程度
```

`grill-me`：追问你，压力测试方案。

适合说：

```text
grill me on this plan
帮我拷问一下这个设计有没有漏洞
```

`grill-with-docs`：结合项目文档、ADR、上下文来追问和更新文档。

适合已有项目文档时使用。

#### 原型 / 前端 / 图像类

`prototype`：做可玩的原型，适合探索 UI、状态机、交互方案。

适合说：

```text
prototype 这个想法
做几个 UI 方案让我试
先做个可运行的小原型
```

`imagegen`：生成或编辑位图图片，比如照片风格图、插画、纹理、sprite、mockup。

适合说：

```text
生成一张产品展示图
做一组游戏角色 sprite
把这张图改成更科技感
```

注意：如果是 SVG、图标系统、HTML/CSS 能直接做的东西，通常不需要 `imagegen`。

#### 写作类

`edit-article`：修改文章，提升结构、清晰度、表达。

适合说：

```text
帮我改这篇文章
让这篇文章更清楚、更有力
```

`writing-fragments`：先收集碎片，不急着成文。

适合说：

```text
帮我整理一些写作 fragments
我有些零散想法，先别成文，帮我挖出来
```

`writing-shape`：把一堆素材逐步塑造成文章。

适合说：

```text
把这个 markdown 草稿 shaped 成一篇文章
我们一起把这些笔记写成文章
```

`writing-beats`：按叙事节拍一段段写，适合故事型、旅程型文章。

适合说：

```text
用 beats 的方式写这篇
我想从这个片段开始发展成文章
```

#### 个人知识库类

`obsidian-vault`：搜索、创建、整理 Obsidian 笔记，用 wikilinks。

适合说：

```text
在 Obsidian 里找关于 AI agents 的笔记
帮我新建一篇关于 XXX 的 note
整理这些笔记并加 wikilinks
```

#### Skills / 插件管理类

`skill-installer`：安装技能。

适合说：

```text
列出可安装的 skills
安装某个 curated skill
从 GitHub repo 安装一个 skill
```

`skill-creator` / `write-a-skill`：创建新的 skill。

适合说：

```text
帮我写一个新的 skill
创建一个用于做 XXX 的 skill
```

`plugin-creator`：创建 Codex plugin 目录和 manifest。

适合说：

```text
帮我 scaffold 一个 Codex plugin
创建一个 personal plugin
```

#### 辅助类

`caveman`：极简输出模式。

适合说：

```text
caveman mode
少说点
be brief
```

`handoff`：把当前上下文压缩成交接文档。

适合说：

```text
生成一个 handoff
把当前进展整理给下一个 agent
```

`scaffold-exercises`：创建课程练习目录、题目、答案、讲解。

适合说：

```text
帮我 scaffold 一组练习
创建这一章的 exercise stubs
```

`git-guardrails-claude-code`：给 Claude Code 设置 git 安全 hook，阻止危险命令。

适合说：

```text
给 Claude Code 加 git guardrails
阻止 git push / reset --hard
```

### 使用时的几个规则

1. 你只要说任务，不需要知道 skill 内部怎么跑。
2. 如果你明确点名某个 skill，我会优先用它。
3. 如果任务明显匹配某个 skill，我会自动用。
4. 如果多个 skill 适合，我会选最少的一组，并说明顺序。
5. Skills 不是永久模式。通常每次新任务需要重新点名，除非上下文还在同一个连续任务里。
6. Skills 会指导我的工作方式，但不会绕过权限。比如需要联网、装依赖、写受限目录，我仍然会按当前环境权限处理。

最实用的记法是：

```text
debug 用 diagnose
开发功能用 tdd
审代码用 review
做原型用 prototype
写 PRD 用 to-prd
拆任务用 to-issues
改文章用 edit-article
整理笔记用 obsidian-vault
少说话用 caveman
```

## 3. prototype 是否用来生成项目框架

**用户：**

> prototype这个skill是不是用来生成项目框架的

**助手：**

不是。`prototype` 不是主要用来“生成项目框架”的。

它的定位是：**写一份可丢弃的原型代码，用来快速回答一个设计问题**。

比如：

```text
prototype 这个状态机，看看流程是否合理
prototype 这个设置页，做 3 个 UI 方案让我切换看看
prototype 这个数据模型，做个终端交互 demo
```

它会走两类之一：

1. **逻辑 / 状态模型原型**
   做一个很小的可运行终端程序，用来验证业务流程、状态机、数据结构是否顺。

2. **UI 原型**
   在现有项目里做几个明显不同的 UI 方案，通常通过 URL 参数或底部切换条来切换，方便比较。

它强调的是：

- throwaway code，可删
- 快速验证想法
- 靠近真实代码放置
- 一条命令能跑
- 不追求生产级质量
- 原型验证完要删除或吸收到正式代码里

如果你想要的是“生成项目框架 / scaffold 一个新项目”，更接近：

- `plugin-creator`：生成 Codex plugin 框架
- `scaffold-exercises`：生成课程练习目录结构
- 普通编码任务：比如“帮我用 Next.js scaffold 一个管理后台项目”
- `write-a-skill` / `skill-creator`：生成新的 skill 结构

所以简单说：**prototype 是验证想法的，不是搭项目骨架的。**

## 4. 生成项目骨架的是哪个

**用户：**

> 生成项目骨架的是哪个

**助手：**

没有一个通用的“生成任意项目骨架”的专用 skill。

现在这些 skills 里，和“脚手架 / 骨架”相关的是：

- `plugin-creator`：生成 **Codex plugin** 项目骨架
- `scaffold-exercises`：生成 **课程练习 / exercise** 目录骨架
- `skill-creator` / `write-a-skill`：生成 **Codex skill** 骨架
- `setup-pre-commit`：给已有项目加 pre-commit 配置，不是生成项目
- `prototype`：生成临时原型，不是项目骨架

如果你要生成普通项目，比如：

```text
帮我生成一个 Next.js 项目骨架
帮我 scaffold 一个 FastAPI + PostgreSQL 后端
帮我创建一个 React 组件库项目
帮我搭一个 Python CLI 工具项目
```

这不需要特定 skill，我会按普通编码任务直接做：确认技术栈、创建目录、配置依赖、加基本文件、跑验证命令。

## 5. 都有哪些具体场景需要用到哪些 skill

**用户：**

> 都有哪些具体场景需要用到哪些skill

**助手：**

可以按“你要完成什么事”来选。你不一定要记 skill 名，直接说场景也可以，我会自动匹配。

### 代码 / 工程

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 报错、测试挂了、接口 500、页面白屏 | `diagnose` | “diagnose 这个报错” / “这个测试挂了，帮我查” |
| 性能变慢、内存涨、构建异常 | `diagnose` | “这个接口最近变慢了，定位一下” |
| 想先写测试再实现功能 | `tdd` | “用 tdd 加优惠码功能” |
| 修 bug 但希望有回归测试 | `tdd` 或 `diagnose` | “按红绿重构修这个 bug” |
| 审查当前分支 / PR / WIP | `review` | “review since main” / “审一下当前分支” |
| 看模块设计、找重构机会 | `improve-codebase-architecture` | “这个模块越来越乱，帮我找架构改进点” |
| 不熟某块代码，想看全局关系 | `zoom-out` | “zoom out 一下这个支付模块” |
| 配置提交前检查 | `setup-pre-commit` | “帮项目加 pre-commit、格式化、测试检查” |
| 防止 Claude Code 执行危险 git 命令 | `git-guardrails-claude-code` | “给 Claude Code 加 git guardrails” |
| 把测试里的 `as` 迁移到 shoehorn | `migrate-to-shoehorn` | “把这些测试迁到 shoehorn” |

### 产品 / 需求 / Issue

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 把想法整理成 PRD | `to-prd` | “把这个需求写成 PRD” |
| 把计划拆成可执行任务 | `to-issues` | “把这个 PRD 拆成 issues” |
| 整理 bug / feature issue，补全信息 | `triage` | “triage 这些 issues” |
| 拷问一个方案有没有漏洞 | `grill-me` | “grill me on this design” |
| 结合项目文档和 ADR 拷问方案 | `grill-with-docs` | “结合 docs grill 一下这个架构方案” |

### 原型 / UI / 图像

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 想快速验证一个交互或状态模型 | `prototype` | “prototype 这个流程，让我试一下” |
| 想比较多个 UI 方向 | `prototype` | “做 3 个 UI 方案可切换” |
| 生成照片、插画、贴图、sprite、mockup | `imagegen` | “生成一张产品展示图” |
| 做真实前端页面或应用 | 通常不用 skill | “帮我做一个 Next.js 管理后台页面” |

### 写作

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 修改文章、优化结构和表达 | `edit-article` | “帮我改这篇文章” |
| 只有零散想法，先收集素材 | `writing-fragments` | “帮我挖一些写作 fragments” |
| 把 markdown 素材逐步写成文章 | `writing-shape` | “把这个草稿 shape 成文章” |
| 按叙事节拍一段段展开 | `writing-beats` | “用 beats 的方式写这篇” |

### 知识库 / Obsidian

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 搜索 Obsidian 笔记 | `obsidian-vault` | “在 Obsidian 找关于 agents 的笔记” |
| 新建或整理笔记、加 wikilinks | `obsidian-vault` | “帮我整理这些笔记并加链接” |

### Skill / Plugin 本身

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 安装更多 skills | `skill-installer` | “列出可安装 skills” / “安装这个 skill” |
| 创建新 skill | `skill-creator` 或 `write-a-skill` | “帮我写一个用于代码审查的 skill” |
| 创建 Codex plugin 骨架 | `plugin-creator` | “scaffold 一个 Codex plugin” |

### 辅助

| 场景 | 用哪个 skill | 你可以这样说 |
|---|---|---|
| 想让我极简回答 | `caveman` | “caveman mode” / “少说点” |
| 把当前上下文交接给另一个 agent | `handoff` | “生成一个 handoff” |
| 创建课程练习目录和题目结构 | `scaffold-exercises` | “scaffold 一组 exercises” |

最常用可以记这几个：

```text
debug / 报错 -> diagnose
功能开发 + 测试 -> tdd
代码审查 -> review
原型探索 -> prototype
需求文档 -> to-prd
任务拆分 -> to-issues
文章修改 -> edit-article
笔记管理 -> obsidian-vault
少说话 -> caveman
```

如果你不确定，就直接描述任务。我会判断是否需要 skill；如果多个都适合，我会选最少的一组并告诉你顺序。

## 6. 不指明 skill 是否也会自动调用

**用户：**

> 就算我不指明skill，你也会自动调用是吧

**助手：**

对。只要你的任务明显匹配某个 skill，我会自动用，不需要你点名。

比如你说：

```text
这个测试挂了，帮我查
```

我会自动用 `diagnose`。

```text
按红绿重构做这个功能
```

我会自动用 `tdd`。

```text
审一下当前分支
```

我会自动用 `review`。

```text
把这个想法写成 PRD
```

我会自动用 `to-prd`。

```text
帮我改这篇文章
```

我会自动用 `edit-article`。

但有两个细节：

1. **你明确点名时优先级最高**
   比如你说“用 `prototype` 做”，我就按 `prototype` 的流程来。

2. **如果不确定，我会按最合理的方式处理**
   任务很模糊时，我可能会先问一句，或者直接用普通编码流程，不强行套 skill。

所以你可以把 skill 当作“可点名的专项模式”，但平时自然说需求就行。
