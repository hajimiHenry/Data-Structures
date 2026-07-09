# 13 函数指针与 qsort

> 这一章你其实已经"负分起步"过一次了。还记得这个 bug 吗——
>
> ```c
> printf("len = %d\n", length);      // 忘了写 (head)
> // 输出: len = 40407748
> ```
>
> 当时的结论:**函数名不带括号 = 这个函数在内存里的地址**,40407748 就是 `length` 函数的门牌号被 `%d` 硬印了出来。当时它是 bug;这一章教你把它变成武器——**把函数当数据一样存起来、传出去**。

## 13.1 函数指针:存函数门牌号的变量

代码也住在内存里(和 malloc 的堆、局部变量的栈并列,有个专门的**代码区**)。既然函数有地址,就能有指针指向它:

```c
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int (*fp)(int, int);   // 声明 fp:一个指向"(int,int) → int 函数"的指针
fp = add;              // 函数名就是地址(像数组名一样),存进去
int r = fp(3, 5);      // 通过指针调用 → 8
fp = sub;              // 换个目标
r = fp(3, 5);          // 同一行代码,行为变了 → -2
```

最后两行是全章的灵魂:**`fp(3,5)` 这行代码,干什么取决于 fp 此刻装着谁**——行为成了可以在运行时替换的零件。

### 读懂声明:那对括号是命根

```c
int (*fp)(int, int);   // fp 是指针,指向"收(int,int)返回 int 的函数"
int *fp(int, int);     // 完全不同!这声明的是一个函数 fp,返回 int*
```

`(*fp)` 的括号强行让"`fp` 先是个指针"成立,再拿参数表和返回值修饰它。你在 ASan 报错里见过的咒语 `int (*)(Node *)` 就是这个东西没有名字的版本——"指向'收 Node* 返回 int 的函数'的指针"。当时你能读懂,现在只是反过来会写。

实际工程里都用 `typedef` 起个可读的名字,一次痛,处处爽:

```c
typedef int (*CmpFunc)(int, int);   // CmpFunc = 这类函数指针的类型名
CmpFunc fp = add;                   // 从此像普通类型一样用
```

## 13.2 它解决什么问题:把"怎么比"交给调用者

设想你给 10 章的链表写排序。写完按 data 升序的,又要按降序的,又要"按离 100 的距离排"的……**排序的骨架(遍历、交换)每次一模一样,唯一变的是"两个元素谁在前"这一句**。

笨办法:复制三份函数改一行。聪明办法:骨架只写一份,**"谁在前"这一句由调用者塞函数进来**。这就是回调(callback):我提供机器,你提供刀头。

C 标准库的 `qsort` 就是这么设计的——一个函数排**所有类型**的数组:

```c
#include <stdlib.h>
void qsort(void *base, size_t n, size_t size,
           int (*cmp)(const void *, const void *));
```

| 参数 | 含义 | 常见错误 |
|---|---|---|
| `base` | 数组首地址 | — |
| `n` | 元素**个数** | — |
| `size` | **每个元素**多大,`sizeof(元素)` | 手滑写成 `sizeof(数组)` |
| `cmp` | 你写的比较函数 | 见下,全章坑最密处 |

`cmp` 的契约:**a 应排在 b 前 → 返回负数;相等 → 0;a 在后 → 正数**。(记法:想升序,就 `return a的值 - b的值`,"小减大得负,小的在前"。)

### 为什么参数是 const void *

`qsort` 要通用,就不能预设元素类型,所以用 `void *`(万能指针,你在 malloc 那章见过它:`malloc` 返回的就是 `void *`)。代价是:**`void *` 不能解引用**(编译器不知道它指的东西多大),你必须在 cmp 里第一时间把它转回真实类型:

```c
int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;   // ① 转回 int* ② 解引用
    int y = *(const int *)b;
    return (x > y) - (x < y);  // 升序;降序交换两个比较
}

int a[] = {5, 2, 8, 1, 9};
qsort(a, 5, sizeof(int), cmp_int);
```

那行 `(x > y) - (x < y)` 值得驻足:比较运算的结果是 1 或 0,所以它恰好输出 1/0/-1。为什么不用顺手的 `x - y`?——想想 `x = 20亿, y = -20亿`,减出来 40 亿,int 装不下,**溢出翻成负数,排序结果直接错乱**。408 不一定考,但工程里 `x - y` 是著名地雷;double 更不能减(返回值截断成 int,0.5 变 0)。**养成肌肉记忆:cmp 一律 `(x>y)-(x<y)`。**

### 排结构体:cmp 里想比谁就比谁

```c
typedef struct { char name[20]; int score; int age; } Student;

int cmp_student(const void *a, const void *b) {
    const Student *x = a;              // void* 转 Student*(C 里可隐式转)
    const Student *y = b;
    if (x->score != y->score)
        return (y->score > x->score) - (y->score < x->score); // 主关键字:分数降序(x、y 反着比)
    return (x->age > y->age) - (x->age < y->age);             // 次关键字:同分按年龄升序
}

qsort(stu, n, sizeof(Student), cmp_student);
```

**多关键字排序 = cmp 里逐级比,主关键字相等才看次关键字**——408 排序大题的常客,而它只是 cmp 里一个 if 的事。

## 13.3 回调不止 qsort:给你的链表装刀口

把回调用到你自己的代码上,感受会深一层。给 10 章的链表加一个"对每个结点执行任意操作"的函数:

```c
void list_foreach(Node *head, void (*op)(int *)) {
    for (Node *cur = head->next; cur != NULL; cur = cur->next)
        op(&cur->data);              // 把每个 data 的地址递给刀头
}

// 三个刀头
void print_it(int *p)  { printf("%d ", *p); }
void double_it(int *p) { *p *= 2; }
void zero_neg(int *p)  { if (*p < 0) *p = 0; }

list_foreach(head, double_it);   // 全体翻倍
list_foreach(head, print_it);    // 全体打印
```

遍历骨架写一次,行为无限扩展——以后想加新操作,**连 list.c 都不用改**,在 main 里写个新刀头就行。408 树的遍历代码里那个 `visit(root)` 形参,就是同一个思想。

## 易错点

1. `int (*fp)(int,int)` 的括号不能丢:丢了就成了"返回 int* 的函数声明"。
2. cmp 里 `void *` 必须先转型再解引用;排 `char *` 数组时元素本身是指针,参数要按 `char **` 转(最绕的一个,见例 13.2)。
3. `x - y` 溢出、double 截断——一律 `(x>y)-(x<y)`。
4. `size` 传 `sizeof(元素)`,别传 `sizeof(数组)`;`n` 是个数不是字节数。
5. 传刀头时写 `qsort(..., cmp_int)` 不是 `cmp_int()`——**带了括号就是"调用后把返回值传进去"**,又绕回 40407748 那个坑,只是方向相反。

## 例题

**例 13.1** 不跑代码,说出下面每行是"合法/非法/合法但意思变了":

```c
int (*f)(int, int) = add;
int *g(int, int) = add;
int r1 = f(1, 2);
int r2 = (*f)(1, 2);     // 提示:老派写法,和 f(1,2) 等价,读代码要认识
qsort(a, 5, sizeof(a), cmp_int);
```

**例 13.2(绕,值得画图)** 排字符串数组 `char *words[] = {"banana","apple","cherry"}`。cmp 收到的 `a` 是"指向数组元素的指针",而元素本身是 `char *`——所以 `a` 实际是 `char **`:

```c
int cmp_str(const void *a, const void *b) {
    const char *x = *(const char **)a;   // 先转 char** 再解引用一层,得到 char*
    const char *y = *(const char **)b;
    return strcmp(x, y);                 // 字典序:strcmp 的返回值天生符合 cmp 契约
}
```

画内存图:`words` 数组的三个格子里装的是什么?`a` 指向格子,格子里装 `char *`——两层指针就是这么来的。(这题和你 5 章"二维退化"的老坑同源,正好清算。)

## 动手工程:练习/13-函数指针

新建 `练习/13-函数指针/`,两个实验:

**实验 1:qsort 三连(`qsort练习.c`,单文件)**
1. int 数组升序、降序各排一次(两个 cmp)
2. `Student` 结构体数组:总分降序,同分按名字典序(`strcmp` 直接当次关键字用)
3. 例 13.2 的字符串数组排序,亲手敲一遍并画内存图
- [ ] 每次 qsort 前把预期结果写在注释里,跑完对照
- [ ] 故意把某个 cmp 的返回值改成恒 0,预测 qsort 会输出什么顺序,跑了验证(答案:实现相关的"随缘序"——体会 cmp 就是 qsort 的眼睛,眼睛瞎了机器不报错,只是排了个寂寞)

**实验 2:给自己的链表装 foreach(多文件复习)**
回到 `练习/10-单链表/`,在 `list.h/list.c` 里加上 13.3 的 `list_foreach`,main 里写三个刀头玩一遍。
- [ ] `typedef void (*OpFunc)(int *);` 放进 list.h,声明用 OpFunc,练 typedef
- [ ] ASan 全绿
- [ ] 【默写关卡】合上教材,默写:`CmpFunc` 的 typedef、一个防溢出的 int 升序 cmp、qsort 的完整调用行。3 分钟内为过

---

## 全书收尾:出关自测

四道题,**全部合卷、全部要跑通**,是你离开这本教材的出关考试:

1. 徒手写动态 int 数组:读 n → malloc → 读入 → 求最大 → free(08 章,你的老朋友)
2. 徒手写带哨兵单链表:init / push_back / 按序号 insert / remove / print / destroy,含压线边界测试(10 章)
3. 徒手写递归:链表倒序打印 + fact,标注地板与递缩(12 章)
4. 用 qsort 排 Student 数组,双关键字(13 章)

四关全过,你的 C 已经足以承载 408 数据结构的全部代码——顺序表、栈、队列、树、图,那些教材代码在你眼里将不再是天书,只是"换了个结构体的老朋友"。

下一站:正式的数据结构教材。带上你的 ASan 和"先预测再运行"的习惯,它们比任何天赋都值钱。
