/* villager_catchphrase: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02080b50 @ 0x02080b50, 0x14 bytes, Thumb
 * func_02080af0 @ 0x02080af0, 0x60 bytes, Thumb
 * func_02080ac8 @ 0x02080ac8, 0x28 bytes, Thumb
 * func_02080a94 @ 0x02080a94, 0x32 bytes, Thumb
 * func_02080a7c @ 0x02080a7c, 0x18 bytes, Thumb
 * func_02080a4c @ 0x02080a4c, 0x30 bytes, Thumb
 */

extern void MI_CpuFill8(int a, int b, int c);
extern unsigned int *func_02082164(void *);
extern void func_020a8c1c(void *);
extern int func_0207dd84(void *);
extern int func_020644cc(int);
extern int func_020b4a20(void *, char *, int *);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_0208214c(void *);
extern int data_020e1968[];
extern void func_0205195c(void *param1);
extern void func_020a8874(void *param1, void *param2, int param3);
extern int func_020a87e0(void *, void *);
extern void func_02082114(int a, int b, int c);
extern void MI_CpuCopy8(void *dst, const void *src, int size);

void func_02080ac8(void *param1, void *param2);
void func_02080a7c(int a, int b);

void func_02080b50(int a)
{
    MI_CpuFill8(a + 0x7c6, 0, 8);
}

void func_02080af0(void *arg0, void *arg1, int arg2)
{
    char c;
    int local[7];

    func_02082164(local);
    func_020a8c1c(arg1);
    if (arg2 != 0 && func_0207dd84(arg0)) {
        c = (char) func_020644cc(0x10);
        func_020b4a20(arg1, &c, data_020e1968);
    } else {
        func_02080ac8(arg0, local);
        func_020a8a70(arg1, local, 0, 0);
    }
    func_0208214c(local);
}

void func_02080ac8(void *param1, void *param2)
{
    void *r4 = param1;
    void *r5 = param2;
    func_0205195c(r5);
    func_020a8874(r5, (char *) r4 + 0x7c6, 4);
}

void func_02080a94(void *param0, void *param1)
{
    char sp[0x1c];
    void *r5 = param0;
    void *r4 = param1;

    func_02082164(sp);
    func_0205195c(sp);
    func_020a87e0(sp, r4);
    func_02080a7c((int) r5, (int) sp);
    func_0208214c(sp);
}

void func_02080a7c(int a, int b)
{
    func_02082114(b, a + 0x7c6, 4);
}

void func_02080a4c(void *param0, void *param1, int param2)
{
    int r4;
    void *r5;
    void *r6;

    r5 = param0;
    r6 = param1;
    r4 = param2;

    MI_CpuFill8((int) ((char *) r5 + 0x7c6), 0, 8);

    if (r4 > 4) {
        r4 = 4;
    }

    MI_CpuCopy8(r6, (char *) r5 + 0x7c6, r4 << 1);
}
