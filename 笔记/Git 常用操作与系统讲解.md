---
tags:
  - 工具
  - git
  - 速查
type: reference
created: 2026-07-09
---

# Git 常用操作与系统讲解

> 用途：平时查命令，同时把「Git 到底在干嘛」这件事讲透。
> 读法：**卡壳时先回到「三个区 + 四个动作」的心智模型**，再去下面查具体命令。

---

## 0. 一句话建立直觉

Git 不是"网盘同步"，而是**给你的项目拍快照（snapshot）的相机 + 一本记录每张快照的账本**。

- 每次 `commit` = 按一次快门，存下"此刻整个项目长什么样"。
- 这些快照串成一条**时间线（历史）**，你随时能跳回任何一张。
- 分支（branch）= 时间线的**岔路**，让你在不弄乱主线的情况下做实验。

类比（对你应该好使）：
- Git 像**游戏存档**。`commit` = 存档点；`branch` = 开一个新存档栏做骚操作，玩崩了删掉就行，主存档不受影响；`merge` = 把两个存档的进度合并。
- GitHub / Gitee = **云端存档柜**，本地存档柜（你电脑）通过 `push`/`pull` 和它同步。

---

## 1. 核心心智模型：三个区 + 一个仓库

这是**整个 Git 最重要的图**，90% 的困惑都来自没搞清文件"现在在哪个区"。

```
  工作区              暂存区              本地仓库             远程仓库
(Working Dir)      (Staging /         (Local Repo)        (Remote)
                    Index)
 你正在改的文件  →   git add   →   已"打包待提交"  →  git commit → 一张快照进历史
                                                          ↓
                                                    git push → 上传到 GitHub
                                                          ↑
                                                    git pull ← 从 GitHub 拉下来
```

| 区域 | 是什么 | 类比 |
|------|--------|------|
| **工作区** Working Directory | 你此刻在编辑器里看到、能直接改的文件 | 你的书桌，摊开在改的稿子 |
| **暂存区** Staging Area / Index | "我打算把这些改动放进下一次提交"的**待命清单** | 桌边的"待装订"文件盒 |
| **本地仓库** Local Repo（`.git/`） | 已经拍好的所有快照 + 完整历史 | 你自己的档案柜 |
| **远程仓库** Remote | GitHub/Gitee 上的同一个仓库 | 公司的云端档案柜 |

**四个基本动作就是在这几个区之间搬东西：**

```
改文件 ──git add──▶ 暂存区 ──git commit──▶ 本地历史 ──git push──▶ 远程
                                                        ◀──git pull──
```

> ⚠ 新手最常栽的坑：改完文件直接 `git commit`，发现"没提交上"。
> 原因：**没 `add`。** 改动还躺在工作区，没进暂存区。记住 `add` → `commit` 是两步。

---

## 2. 第一次上手：从零建一个仓库

### 场景 A：本地已有代码，想开始用 Git 管
```bash
cd 你的项目目录
git init                      # 在当前目录创建 .git/，正式变成 Git 仓库
git add .                     # 把所有文件放进暂存区（. = 当前目录全部）
git commit -m "初始提交"       # 拍第一张快照
```

### 场景 B：从 GitHub 上把别人（或自己）的项目下下来
```bash
git clone https://github.com/用户名/仓库名.git
# 会自动建好目录、下好全部历史，并且远程地址已配好，开箱即用
```

### 一次性配置身份（每台新电脑做一次）
```bash
git config --global user.name  "Henry"
git config --global user.email "binibinforgem@gmail.com"
```
> `--global` = 对这台机器所有仓库生效。不加就只对当前仓库。
> 提交记录里会写上这个名字/邮箱，作为"谁提交的"。

---

## 3. 日常主循环（80% 时间都在用这几条）

这是你每天写代码的节奏，**背下来**：

```bash
git status                    # ① 我现在处于什么状态？（最常用，多按！）
git add 文件名                 # ② 把改动放进暂存区
git add .                     # （或）把所有改动一次性放进去
git commit -m "说明这次改了啥"  # ③ 拍快照，存进本地历史
git push                      # ④ 推到 GitHub
```

配合看：
```bash
git diff                      # 工作区 vs 暂存区：我还没 add 的改动长啥样
git diff --staged             # 暂存区 vs 上次提交：我 add 了但还没 commit 的改动
git log --oneline             # 简洁地看历史（一行一个提交）
```

> 🔑 **`git status` 是你的仪表盘。** 任何时候搞不清状况，先敲它。
> 它会明确告诉你：哪些文件改了没 add（红色）、哪些 add 了待 commit（绿色）、当前在哪个分支、和远程差几个提交。

---

## 4. 命令速查表（按"我想干嘛"分类）

### 4.1 查看状态与历史
| 我想…… | 命令 |
|--------|------|
| 看当前状态（改了啥、在哪个分支） | `git status` |
| 看还没暂存的改动 | `git diff` |
| 看已暂存待提交的改动 | `git diff --staged` |
| 看提交历史（简洁） | `git log --oneline` |
| 看历史 + 分支图 | `git log --oneline --graph --all` |
| 看某个文件是谁哪次改的 | `git blame 文件名` |

### 4.2 暂存与提交
| 我想…… | 命令 |
|--------|------|
| 暂存指定文件 | `git add 文件名` |
| 暂存所有改动 | `git add .` |
| 把某文件从暂存区撤回（不删改动） | `git restore --staged 文件名` |
| 提交 | `git commit -m "消息"` |
| 提交（顺便把已跟踪文件的改动自动 add） | `git commit -am "消息"` |
| 改上一次提交的消息 / 补文件进去 | `git commit --amend` |

### 4.3 撤销与后悔药（重点，见第 6 节详解）
| 我想…… | 命令 |
|--------|------|
| 丢弃某文件工作区的改动（回到上次提交） | `git restore 文件名` |
| 把某文件恢复成某次提交的样子 | `git restore --source=提交ID 文件名` |
| 撤销某次提交（生成一个反向提交，安全） | `git revert 提交ID` |
| 回退到某次提交（危险，改历史） | `git reset --hard 提交ID` |

### 4.4 分支
| 我想…… | 命令 |
|--------|------|
| 看所有分支 | `git branch` |
| 新建分支 | `git branch 分支名` |
| 切换分支 | `git switch 分支名`（旧写法 `git checkout 分支名`） |
| 新建并切换 | `git switch -c 分支名` |
| 合并 分支名 到当前分支 | `git merge 分支名` |
| 删除分支 | `git branch -d 分支名` |

### 4.5 远程同步
| 我想…… | 命令 |
|--------|------|
| 从远程拉最新并合并 | `git pull` |
| 只下载远程更新、先不合并 | `git fetch` |
| 推送到远程 | `git push` |
| 第一次推送新分支 | `git push -u origin 分支名` |
| 看远程地址 | `git remote -v` |

---

## 5. 提交信息（commit message）怎么写

一次 `commit` 是给"未来的你"看的便签。半年后你回来找 bug，全靠它定位。

**烂例子**：`git commit -m "改了点东西"` / `"111"` / `"fix"`
**好例子**：`git commit -m "修复链表删除节点时的内存泄漏"`

常见约定（可选，了解即可）：
```
类型: 简短描述

feat:  新功能
fix:   修 bug
docs:  改文档
refactor: 重构（不改功能）
```
例：`git commit -m "fix: strcpy 越界，dst 长度没算 '\0'"`

> 原则：**写"为什么/改了什么效果"，而不是"改了哪几行"**（改了哪几行 `git diff` 自己会看）。

---

## 6. 撤销/后悔药：这几个最容易搞混，重点讲

新手最怕的就是"我搞砸了怎么退回去"。按**破坏性从小到大**排：

### ① `git restore 文件名` —— 丢弃工作区改动
"这个文件我改乱了，还没 add，我不要了，恢复成上次提交的样子。"
```bash
git restore hello.c          # hello.c 的未暂存改动全没了
```
⚠ 改动**直接丢失、不可恢复**（因为它从没被 Git 记录过）。想留就先别 restore。

### ② `git restore --staged 文件名` —— 从暂存区撤回
"我不小心 `add` 了不该 add 的文件，把它踢出暂存区，但改动保留。"
```bash
git restore --staged secret.txt   # 改动还在工作区，只是不再"待提交"
```

### ③ `git commit --amend` —— 修补刚提交的那次
"提交完发现消息写错了 / 漏了个文件。"
```bash
git add 漏掉的文件
git commit --amend -m "新的正确消息"
```
⚠ 只对**还没 push** 的提交用。已经推上去的别 amend（会和远程历史打架）。

### ④ `git revert 提交ID` —— 安全地"撤销某次提交"
"三次提交之前那个改动是错的，我要撤销它，但**不想抹掉历史**。"
```bash
git revert a1b2c3d           # 生成一个"反向操作"的新提交
```
✅ **推荐给已经 push 出去的提交用**。因为它不删历史，只是"追加一个抵消的快照"，团队协作安全。

### ⑤ `git reset` —— 移动"当前位置"指针（危险区）
"我要让分支回到三次提交之前，前面的都不算数。"
```bash
git reset --soft  HEAD~1     # 撤销上次 commit，改动退回暂存区（最温柔）
git reset --mixed HEAD~1     # 撤销上次 commit，改动退回工作区（默认）
git reset --hard  HEAD~1     # 撤销上次 commit，改动直接删掉（最狠，慎用！）
```

| reset 模式 | commit | 暂存区 | 工作区文件 |
|-----------|--------|--------|-----------|
| `--soft`  | 撤销 | 保留改动 | 保留 |
| `--mixed`（默认） | 撤销 | 清空 | 保留改动 |
| `--hard`  | 撤销 | 清空 | **删除改动** ⚠ |

> `HEAD` = "我现在在哪个提交上"这个指针。`HEAD~1` = 往回数 1 个提交，`HEAD~2` = 往回 2 个。

**决策口诀：**
- 改动还没 add，想扔 → `restore`
- 提交还没 push，想改 → `amend` 或 `reset`
- 提交已经 push 了，想撤 → **只用 `revert`**（别 reset --hard 改公共历史）

> 🛟 救命稻草：`git reflog` 记录了你 HEAD 移动的**所有**足迹。就算 `reset --hard` 删了提交，只要还没被垃圾回收，都能靠它找回来。搞砸了先别慌，敲 `git reflog`。

---

## 7. 分支：Git 的灵魂

### 为什么要分支
主线（一般叫 `main` 或 `master`）要保持随时能用。想做新功能/做实验，就**开个岔路**，做好了再合回来。做崩了删掉，主线毫发无伤。

```
        A───B───C   main（主线）
                 \
                  D───E   feature（你的实验分支）
```

### 典型流程
```bash
git switch -c feature-链表     # ① 从当前分支岔出一条新分支并切过去
# ...在上面写代码、add、commit...
git switch main               # ② 回到主线
git merge feature-链表         # ③ 把新分支的成果合并进主线
git branch -d feature-链表     # ④ 合并完，删掉这条分支
```

### 合并的两种情况
- **Fast-forward（快进）**：主线自岔出后没动过，Git 直接把指针挪过去，无冲突。
- **Three-way merge（三方合并）**：两条分支都改了 → 生成一个"合并提交"。若改了**同一处**，就产生 **冲突（conflict）**，见第 8 节。

---

## 8. 合并冲突（conflict）：不可怕，看懂标记就行

当两个分支改了**同一个文件的同一行**，Git 不敢替你决定，让你手动选。文件里会出现：

```
<<<<<<< HEAD
当前分支的版本（你这边的内容）
=======
要合并进来的分支的版本（对方的内容）
>>>>>>> feature-链表
```

**解决三步：**
1. 打开冲突文件，找到 `<<<<<<<` / `=======` / `>>>>>>>` 标记。
2. **手动编辑**成你最终想要的样子，把这三行标记**全删掉**。
3. 收尾：
```bash
git add 冲突文件         # 告诉 Git：这个冲突我解决好了
git commit             # 完成合并（消息一般自动填好，直接确认即可）
```

> 类比：两个人同时改了同一句作文，老师（Git）不知道听谁的，把两版并排贴给你，让你自己裁定最终稿。
> 冲突不是错误，是 Git 在**保护你不丢改动**。冷静删标记即可。

---

## 9. 远程协作：push / pull / fetch

```
本地仓库  ──push──▶  GitHub  ──pull──▶  队友的本地
        ◀──pull──          ◀──push──
```

| 命令 | 干嘛 | 细节 |
|------|------|------|
| `git fetch` | 只**下载**远程的新提交，不动你的工作区 | 想先看看别人改了啥再决定合不合 |
| `git pull`  | `fetch` + `merge`，下载并**合并**进当前分支 | 日常"拉最新"就用它 |
| `git push`  | 把本地提交**上传**到远程 | 推之前最好先 `pull` |

> `origin` = 远程仓库的默认代号（clone 时自动叫这名）。
> `git push -u origin main` 里的 `-u` 只需第一次，之后 `git push` 就够了。

**协作黄金习惯：动手前先 `git pull`。** 先同步队友的改动，能大幅减少冲突。

---

## 10. `.gitignore`：让 Git 别管某些文件

有些文件不该进仓库：编译产物、临时文件、密码。在项目根目录建一个名为 `.gitignore` 的文件，列出要忽略的东西：

```gitignore
# 编译产物（对你学 C 特别相关！）
*.o
*.out
a.out
main

# 系统/编辑器垃圾
.DS_Store
*.swp

# 目录（末尾加 /）
build/
```

> 对你正好有用：编译 C 生成的 `a.out`、`*.o` 这类中间产物**不该提交**，Git 只该管你的 `.c`/`.h` 源码。
> ⚠ 注意：`.gitignore` **只对"还没被 Git 跟踪过"的文件生效**。已经 commit 过的文件，得先 `git rm --cached 文件名` 让 Git 停止跟踪。

---

## 11. 一张"我该用哪条命令"决策图

```
我想做什么？
│
├─ 看现在什么情况？ ─────────────▶ git status
│
├─ 保存进度到本地？ ─── git add . → git commit -m "..."
│
├─ 上传到 GitHub？ ─────────────▶ git push
│
├─ 拉队友的最新？ ─────────────▶ git pull
│
├─ 试个新想法，怕搞乱主线？ ──── git switch -c 新分支
│
├─ 改乱了想反悔？
│   ├─ 还没 add        ─────────▶ git restore 文件
│   ├─ add 错了        ─────────▶ git restore --staged 文件
│   ├─ 刚 commit 想改  ─────────▶ git commit --amend
│   └─ 已 push 想撤    ─────────▶ git revert 提交ID
│
└─ 彻底搞砸了，找回丢的提交 ────▶ git reflog
```

---

## 12. 高频疑惑 FAQ

**Q：`add` 和 `commit` 到底区别在哪，为啥要两步？**
A：`add` 是"挑选"——从一堆改动里挑出这次要提交的（可以只提交部分文件）；`commit` 是"封存"。分两步给你**精细控制一次提交装什么**的能力。

**Q：`git checkout` 到底是干嘛的，为啥到处见它？**
A：老版本里它一词多义（切分支、恢复文件都用它），容易乱。新版拆成了两个更清楚的命令：切分支用 `git switch`，恢复文件用 `git restore`。**你记新的两个就行**，见到老代码用 `checkout` 知道是这俩之一即可。

**Q：`pull` 和 `fetch` 区别？**
A：`fetch` = 只下载，不动你手头的东西（安全，先看）；`pull` = 下载 + 立刻合并进来（省事，日常用）。`pull` ≈ `fetch` + `merge`。

**Q：`main` 和 `master` 是啥关系？**
A：同一个东西——默认主分支的名字。老仓库多叫 `master`，新仓库（GitHub 默认）叫 `main`。

**Q：提交 ID 那串乱码（`a1b2c3d`）是啥？**
A：每张快照的唯一指纹（SHA 哈希）。用 `git log --oneline` 能看到，引用某次提交时敲前 7 位就够。

---

## 13. GitHub 实操：从本地项目到云端

前面讲的是 Git 本身（本地版本控制）。这一节讲**怎么把本地仓库接到 GitHub 上**——配置流程，做一次就顺了。

### 13.0 先搞清楚：本地 Git ≠ GitHub

| | 是什么 | 谁做的 |
|---|---|---|
| **Git** | 装在你电脑上的版本控制工具 | 你本地跑的命令 |
| **GitHub** | 一个托管 Git 仓库的**网站/服务** | 云端，需要联网、需要登录 |

> 类比：Git 是 Word（你本地编辑），GitHub 是网盘（存到云、给别人看）。GitHub 不是唯一选择，Gitee、GitLab 同理。

---

### 13.1 认证方式：HTTPS vs SSH（先选一个）

推送到 GitHub 需要证明"你是你"。两种方式：

| 方式 | 地址长这样 | 认证方式 | 适合 |
|------|-----------|---------|------|
| **HTTPS** | `https://github.com/用户/仓库.git` | 用户名 + **Personal Access Token**（不是登录密码！） | 新手、临时用 |
| **SSH** ✅推荐 | `git@github.com:用户/仓库.git` | 一对密钥（配一次，永久免密） | 长期用、自己电脑 |

> ⚠ 2021 年起 GitHub **不再允许用账号密码推送**。HTTPS 方式要用 **Token**（在 GitHub 网页 Settings → Developer settings → Personal access tokens 生成）。
> 所以更省心的是配 **SSH**，配一次以后 `push`/`pull` 再也不用输密码。

---

### 13.2 配 SSH 密钥（推荐，一台电脑做一次）

**① 生成密钥对**（如果 `~/.ssh/id_ed25519.pub` 已存在就跳过）
```bash
ssh-keygen -t ed25519 -C "binibinforgem@gmail.com"
# 一路回车即可（默认路径、可不设密码）
```
这会生成一对文件：
- `~/.ssh/id_ed25519`      → **私钥**，绝不外泄（像你家钥匙）
- `~/.ssh/id_ed25519.pub`  → **公钥**，可以公开（像门锁，贴到 GitHub 上）

**② 复制公钥内容**
```bash
cat ~/.ssh/id_ed25519.pub    # 把输出的一整行全选复制
# macOS 可直接：pbcopy < ~/.ssh/id_ed25519.pub
```

**③ 贴到 GitHub**
网页 → 右上头像 → **Settings** → **SSH and GPG keys** → **New SSH key** → 粘贴 → 保存。

**④ 测试连通**
```bash
ssh -T git@github.com
# 看到 "Hi Henry! You've successfully authenticated" 就成了
```

> 原理一句话：你把"锁"（公钥）装在 GitHub 门上，只有你手里的"钥匙"（私钥）能开。推送时自动验证，无需密码。

---

### 13.3 把一个本地项目首次推上 GitHub

**① 先在 GitHub 网页建一个空仓库**
点右上 **+** → **New repository** → 填名字 → **不要**勾选 "Add README/.gitignore"（建空的，避免和本地冲突）→ Create。

建完 GitHub 会给你一段地址，形如 `git@github.com:Henry/my-c-lab.git`。

**② 回到本地，把本地仓库和它接起来**
```bash
cd 你的项目目录
git init                                    # 若还没 init 过
git add .
git commit -m "初始提交"

git remote add origin git@github.com:Henry/my-c-lab.git   # 绑定远程，代号 origin
git branch -M main                          # 把当前分支改名叫 main（和 GitHub 默认一致）
git push -u origin main                     # 首次推送，-u 记住关联
```
之后再改代码，就只需 `git add .` → `git commit -m` → `git push` 三步了。

---

### 13.4 远程仓库管理命令

| 我想…… | 命令 |
|--------|------|
| 看当前绑了哪些远程 | `git remote -v` |
| 绑定一个远程（代号 origin） | `git remote add origin 地址` |
| 改远程地址（比如 HTTPS 换成 SSH） | `git remote set-url origin 新地址` |
| 解除某个远程 | `git remote remove origin` |

---

### 13.5 一个完整的协作日常（把前面串起来）

```bash
# 早上开工，先拉最新
git pull

# 开个分支做今天的功能
git switch -c feature-双链表

# ...写代码...
git add .
git commit -m "feat: 实现双链表插入"

# 推上去（首次推新分支带 -u）
git push -u origin feature-双链表

# 到 GitHub 网页发起 Pull Request，请人 review、合并进 main
```

> **Pull Request（PR）** = "我这条分支写好了，请把它合进主线"的申请。个人练习用不上，但这是团队协作的标准姿势，见到不要懵。

---

### 13.6 常见踩坑

| 现象 | 原因 / 解决 |
|------|-----------|
| `push` 报 `Permission denied (publickey)` | SSH 没配好 → 回 13.2 跑 `ssh -T git@github.com` 排查 |
| `push` 让你输密码，输了还失败 | HTTPS 方式要用 **Token** 不是账号密码；或改用 SSH |
| `push` 报 `rejected ... behind` | 远程有你本地没有的提交 → 先 `git pull` 再 `push` |
| 传了不该传的文件（如密码、`a.out`） | 先建好 `.gitignore`（见第 10 节），已传的用 `git rm --cached 文件` |
| 初始提交时远程有 README 冲突 | 建空仓库时别勾 README；已勾就 `git pull --rebase origin main` 后再推 |

---

### 相关笔记
- [[笔记/gcc clang等编译器的参数使用.md]]
