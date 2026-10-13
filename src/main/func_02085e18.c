/* func_02085e18 @ 0x02085e18, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char flag;
    unsigned char pad_01[2];
    unsigned char unk_03;
    unsigned char unk_04[0x1a];
} Slot;

typedef struct {
    int a, b, c;
} Work;

extern Slot data_021d213c[8];
extern int data_021e5a2c;

extern void MI_CpuFill8(void *dst, int val, int len);
extern void *func_0207cec0(int *g, int i);
extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern unsigned char *func_020800d0(void *p);
extern void func_0204f794(Work *w, int a, int b);
extern void func_020779b8(void *p, int a, int b);
extern void func_02077a54(void *p, int a, int b);

void func_02085e18(void)
{
    int zero = 0;
    Work w;
    Slot *s;
    int i;
    void *obj;
    unsigned char *p;

    s = data_021d213c;
    MI_CpuFill8(s, 0, 0xf0);
    for (i = 0; i < 8; s++, i++) {
        obj = func_0207cec0(&data_021e5a2c, i);
        if (obj != 0) {
            if (func_02003704(func_0208150c(obj))) {
                w.a = 0;
                w.b = 0;
                w.c = 0;
                p = func_020800d0(obj);
                func_0204f794(&w, p[0] + 1, p[1] + 2);
                func_020779b8(s->unk_04, w.a, w.c);
                func_02077a54(&s->unk_03, zero, zero);
                s->flag = 1;
            }
        }
    }
}
