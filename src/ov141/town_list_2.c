/* town_list_2: 2 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229a428 @ 0x0229a428, 0x24 bytes, Thumb
 * func_ov141_0229a3c4 @ 0x0229a3c4, 0x64 bytes, Thumb
 */

extern void *func_ov141_0229a490(void *);
extern void *func_ov141_0229a470(void *);
extern int func_ov141_02299f7c(void *p, int a);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov141_02299f5c(void *p, int a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov141_0229a3c4(void *p1, int p2, int p3);

void func_ov141_0229a428(void *p)
{
    void *a;
    void *b;
    a = func_ov141_0229a490(p);
    b = func_ov141_0229a470(p);
    func_ov141_0229a3c4(p, (int) a, (int) b);
}

void func_ov141_0229a3c4(void *p1, int p2, int p3)
{
    int arg;
    if (func_ov141_02299f7c(p1, 0x10)) {
        arg = 0;
        func_ov002_0220a05c((char *) p1 + 0x0a38, p2, p3, 3, arg);
        func_ov141_02299f5c(p1, 0x10);
    } else {
        arg = 1;
        func_ov002_0220a05c((char *) p1 + 0x0a38, p2, p3, 3, arg);
    }
    *((unsigned char *) ((char *) p1 + 0x1a7e)) = *((unsigned char *) ((char *) p1 + 0x8d));
    func_ov002_02208098((void *) (p1), 2);
}
