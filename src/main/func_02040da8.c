/* func_02040da8 @ 0x02040da8, 0x9a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_0209ded0(void);
extern void func_02040a10(void *obj);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_0203fea0(void *dst, void *src);
extern unsigned char *func_020409c8(void *obj, int n);
extern int func_0203fd38(int a, void *b, void *c);
extern void func_020408a8(void *p);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

void func_02040da8(void *obj)
{
    int flag;
    Pair a;
    unsigned char b[8];
    unsigned char c[8];
    unsigned char buf[0x58];
    int n;
    unsigned char *p;
    int i;
    int last;
    int t;

    a.unk_00 = 0;
    a.w1 = 0;
    n = func_0209ded0();
    func_0209e474(&a);
    func_02040a10(obj);
    MI_CpuCopy8(&a, b, 8);
    func_0203fea0(buf, b);
    func_0209e474(&a);
    last = n - 1;
    flag = 0;
    for (i = 0; i <= last; i++) {
        p = func_020409c8(obj, i + 1);
        if (p == 0) {
            continue;
        }
        if (p[2] == 0x63) {
            continue;
        }
        MI_CpuCopy8(&a, c, 8);
        if (func_0203fd38(p[2], c, buf) == 0) {
            t = 1;
        } else {
            t = flag;
        }
        if (t != 0) {
            func_020408a8(p);
        } else if (i != last && p[2] == 0x45) {
            func_020408a8(p);
        }
    }
}
