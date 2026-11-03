/* villager_town_3: 2 functions, module main
 * mwccarm 1.2/base -O1,s
 * func_0207bddc @ 0x0207bddc, 0xb0 bytes, Thumb
 * func_0207bd80 @ 0x0207bd80, 0x5c bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

extern void func_0209e474(void *);
extern int func_0209e3ac(void *a, void *b, int n);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_0207b4a8(void *a, void *b);
extern void func_0207bf38(void *a, void *b);
extern void func_0207c190(void *a, void *b);
extern void func_0207bfa4(void *a, void *b);
extern void func_0207c4e8(void *a, void *b);
extern void func_0207b41c(void *a, int b);
extern void func_0207b05c(void *a);
extern void func_0207ab0c(void *a);
extern void func_0207a964(void *a);
extern void func_0209dfd8(void *dst, const void *src, int c, int d, int e);
extern void func_0207f5e4(void *p);
extern void func_0209df64(void *p);

void func_0207bd80(void *obj);

void func_0207bddc(void *obj, int flag)
{
    Pair a;

    a.unk_00 = 0;
    a.w1 = 0;
    func_0209e474(&a);
    if (func_0209e3ac(&a, (char *) obj + 0x4050, 0x3f) == -1) {
        MI_CpuCopy8(&a, (char *) obj + 0x4050, 8);
        if (*(unsigned long long *) ((char *) obj + 0x4058) != 0) {
            MI_CpuCopy8(&a, (char *) obj + 0x4058, 8);
        }
    }
    func_0207b4a8(obj, &a);
    func_0207bf38(obj, &a);
    func_0207c190(obj, &a);
    func_0207bfa4(obj, &a);
    func_0207c4e8(obj, &a);
    func_0207bd80(obj);
    func_0207b41c(obj, flag);
    func_0207b05c(obj);
    if (flag == 0) {
        func_0207ab0c(obj);
    }
    func_0207a964(obj);
}

void func_0207bd80(void *obj)
{
    Pair a;
    Pair b;
    char *p;
    int i;

    func_0209dfd8(&a, (char *) obj + 0x407a, 0, 0, 0);
    b.unk_00 = 0;
    b.w1 = 0;
    func_0209e474(&b);
    if (func_0209e3ac(&b, &a, 0x38) != 0) {
        p = (char *) obj;
        i = 0;
        do {
            func_0207f5e4(p);
            p += 0x7ec;
            i++;
        } while (i < 8);
        func_0209df64((char *) obj + 0x407a);
    }
}
