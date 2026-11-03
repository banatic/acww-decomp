/* villager_talk_lines_10: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201ffa0 @ 0x0201ffa0, 0x74 bytes, Thumb
 * func_0201ff3c @ 0x0201ff3c, 0x64 bytes, Thumb
 * func_0201fed0 @ 0x0201fed0, 0x6c bytes, Thumb
 * func_0201fe6c @ 0x0201fe6c, 0x64 bytes, Thumb
 * func_0201fe34 @ 0x0201fe34, 0x38 bytes, Thumb
 */

typedef struct {
    int first;
    unsigned char second;
} Data020c8ce8_t;

struct Dst {
    void *ptr;
    unsigned char byte;
};

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobalData;

typedef struct {
    void *ptr;
    unsigned char byte;
} Output;

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair_0201fe34;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_020819e0(int);
extern Data020c8ce8_t data_020c8ce8;
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);
extern void func_0202da74(void *object, Pair value);
extern Pair data_020d9390;
extern char data_021c234c;
extern char data_021c231c;
extern void func_02015774(int, int, const void *, int, int);
extern int func_02015828(int, int);
extern void func_0202dbf0(int, Pair_0201fe34);
extern Pair_0201fe34 data_020d9430;
extern unsigned char data_021c1e84[];

void func_0201ffa0(unsigned char *param0, unsigned char *param1)
{
    int val0, val1, val4;
    unsigned char *p;
    int v;

    p = *(unsigned char **) (param0 + 0x100);
    v = *(int *) (p + 0x830);
    val0 = func_020036e8(func_0208150c(v));

    val1 = data_020c8ce8.first;
    val4 = data_020c8ce8.second;

    func_0202da38((void *) param0, (void *) (param0 + 0x104), (void *) (param0 + 0x122), 30, val0, val1, 1, 2, val4);

    *(unsigned char **) param1 = param0 + 0x104;
    *(unsigned char *) (param1 + 4) = *(unsigned char *) (param0 + 0x122);

    v = *(int *) (param0 + 0x12c);
    if (v != 0) {
        func_020819e0(v);
    }
}

void func_0201ff3c(void *src, struct Dst *dst)
{
    int tmp;
    tmp = func_020036e8(func_0208150c(*(int *) ((char *) (*(char **) ((char *) src + 0x100)) + 0x830)));
    func_0202da38(src, (char *) src + 0x104, (char *) src + 0x122, 30, tmp, (*(int *) &data_020c8ce8), 1, 7, 3);
    dst->ptr = (char *) src + 0x104;
    dst->byte = *((unsigned char *) src + 0x122);
}

void func_0201fed0(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x5a, 0x5a, (void *) &data_021c234c);
    func_0201cf90(param, buf, 1, 0x6f, 0x6f, (void *) &data_021c231c);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d9390);
    func_02068388(param->unk_40, 1);
}

void func_0201fe6c(void *self, Output *out)
{
    int a5 = func_020036e8(func_0208150c(*(int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830)));
    int a6 = (*(GlobalData *) &data_020c8ce8).unk_00;
    int a9 = (*(GlobalData *) &data_020c8ce8).unk_04;
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, a5, a6, 1, 0xc, a9);
    out->ptr = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((char *) self + 0x122);
}

void func_0201fe34(int param, int event)
{
    func_02015774(param, 23, (const void *) data_021c1e84, 10, 0);
    func_02015828(param, 6);
    func_0202dbf0(param, data_020d9430);
}
