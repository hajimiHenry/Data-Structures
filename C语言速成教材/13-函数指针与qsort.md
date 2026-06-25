# 13 函数指针与 qsort

补充章。函数指针在数据结构里主要用来「把比较规则传给排序函数」（qsort）和「回调」。理解即可，不必深究。

## 13.1 函数指针是什么

指针存「数据」的地址。**函数指针存「函数」的地址**——拿到它就能间接调用那个函数。

```c
int add(int a, int b) { return a + b; }

int (*fp)(int, int);   // 声明：fp 是「指向 (int,int)->int 函数」的指针
fp = add;              // 指向 add（函数名即地址，像数组名）
int r = fp(3, 5);      // 通过指针调用，r = 8
```

语法丑但意思简单：`int (*fp)(int, int)` 读作「fp 是指针，指向接收两个 int、返回 int 的函数」。

## 13.2 为什么需要它：qsort

C 标准库的 `qsort`（快速排序）能排**任意类型**数组，秘密就是：你把**比较规则**作为函数传给它。它不知道怎么比两个东西，你告诉它。

```c
#include <stdlib.h>

void qsort(void *base, size_t n, size_t size,
           int (*cmp)(const void *, const void *));
```

- `base`：数组首地址。
- `n`：元素个数。
- `size`：每个元素多大（`sizeof`）。
- `cmp`：**你写的比较函数**，返回 `<0 / 0 / >0`。

### 排整数数组

```c
int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;      // 把 void* 强转 int* 再解引用
    int y = *(const int *)b;
    return x - y;                 // 升序：x<y 返回负
}

int main(void) {
    int a[] = {5, 2, 8, 1, 9, 3};
    qsort(a, 6, sizeof(int), cmp_int);
    // a = 1 2 3 5 8 9
}
```

- 比较函数的参数是 `const void *`（万能指针），函数里强转回真实类型再解引用。
- 升序 `return x - y`；**降序 `return y - x`**（交换被减数）。
- `x - y` 当心大数溢出，严谨写 `return (x > y) - (x < y);`，一般题目 `x - y` 够用。

### 排结构体数组（你做过类似题）

```c
typedef struct { char name[20]; int score; } Student;

int cmp_score(const void *a, const void *b) {
    const Student *x = a;     // void* 转 Student*
    const Student *y = b;
    return y->score - x->score;   // 降序（高分在前）
}

qsort(arr, n, sizeof(Student), cmp_score);
```

> 这正是你写过的「结构体数组排序」用标准库的版本。多关键字时在 cmp 里逐级比：先比主，相等再比次。

## 13.3 函数指针回调（概念）

把函数当参数传，让被调用方在合适时机「回调」你。例如一个「对每个元素做某事」的函数：

```c
void foreach(int *a, int n, void (*op)(int *)) {
    for (int i = 0; i < n; i++) op(&a[i]);
}

void double_it(int *p) { *p *= 2; }
void print_it(int *p)  { printf("%d ", *p); }

foreach(a, n, double_it);   // 全翻倍
foreach(a, n, print_it);    // 全打印
```

数据结构里「访问者模式」、树的遍历回调都是这个思路。408 不深考，认得出来即可。

## 易错点

1. 比较函数返回 `x - y` 大数溢出（如两个接近 INT_MAX 的值相减）。
2. `void *` 忘强转就解引用——`void *` 不能直接解引用。
3. qsort 传错 `size`（用 `sizeof(元素)` 不是 `sizeof(数组)`）。
4. 升降序搞反：`a-b` 升序，`b-a` 降序。

## 例题

**例 13.1** 写 cmp 让 double 数组降序。
```c
int cmp_double(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    if (x < y) return 1;      // 降序
    if (x > y) return -1;
    return 0;
}
```
> 注意：double 不能用 `x - y`（返回 int 会截断），要用 if 比较返回 -1/0/1。

**例 13.2** 排字符串数组（`char *` 数组）按字典序。
```c
int cmp_str(const void *a, const void *b) {
    // a, b 指向数组元素，元素是 char*，所以要 char**
    const char *x = *(const char **)a;
    const char *y = *(const char **)b;
    return strcmp(x, y);
}
```

## 小练习

1. 用 qsort 把 `int a[] = {4,1,7,3,9,2}` 降序排列。
2. 结构体 `Point {int x,y;}`，用 qsort 按 x 升序，x 相同按 y 降序。

<details><summary>答案</summary>

```c
// 1
int cmp(const void *a, const void *b) {
    return *(const int *)b - *(const int *)a;   // 降序
}
qsort(a, 6, sizeof(int), cmp);

// 2
typedef struct { int x, y; } Point;
int cmp(const void *a, const void *b) {
    const Point *p = a, *q = b;
    if (p->x != q->x) return p->x - q->x;       // x 升序
    return q->y - p->y;                          // y 降序
}
qsort(pts, n, sizeof(Point), cmp);
```
</details>

---

## 全书收尾

到这里你完成了：基础速过 → 指针 → 动态内存 → 自引用结构体 → 单链表 → 双链表/循环 → 递归 → 函数指针。

**自测**：能徒手（不看教材）写出——
- 一个动态数组（malloc + realloc 扩容 + free）
- 单链表的建表、遍历、插入、删除、反转、释放
- 一个递归函数（如求和、链表长度）
- 用 qsort 排结构体数组

四样都写得出来，408 数据结构部分的 C 门槛就彻底过了。可以正式进入数据结构教材（顺序表、栈队列、树、图、排序），那些章节的 C 代码对你将不再有阅读障碍。

继续加油 💪
