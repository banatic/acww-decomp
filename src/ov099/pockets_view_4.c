/* pockets_view_4: 6 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229d940 @ 0x0229d940, 0x8 bytes, Thumb
 * func_ov099_0229d910 @ 0x0229d910, 0x30 bytes, Thumb
 * func_ov099_0229d8d8 @ 0x0229d8d8, 0x38 bytes, Thumb
 * func_ov099_0229d8b8 @ 0x0229d8b8, 0x1e bytes, Thumb
 * func_ov099_0229d8a4 @ 0x0229d8a4, 0x14 bytes, Thumb
 * func_ov099_0229d894 @ 0x0229d894, 0x10 bytes, Thumb
 */

extern void func_ov099_0229cf3c(void *p);
extern void func_ov094_0229a084(void *p);
extern void func_ov094_0229af20(void *p);
extern void func_ov094_0229bbc0(void *p);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov099_0229ca34(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(void *ptr, int value);
extern int func_ov094_0229a098(void *receiver);

void func_ov099_0229d8d8(char *self);

void func_ov099_0229d940(char *arg0)
{
    func_ov099_0229d8d8((char *) arg0);
}

void func_ov099_0229d910(void *ptr)
{
    func_ov099_0229cf3c(ptr);
    func_ov094_0229a084((char *) ptr + 0xb54);
    func_ov094_0229af20((char *) ptr + 0xcc);
    func_ov094_0229bbc0((char *) ptr + 0xb2c);
}

void func_ov099_0229d8d8(char *self)
{
    func_ov002_022091cc(self + 0x22d8);
    func_ov094_0229a05c(self + 0xb54);
    if (func_ov002_02207d5c(self + 0x218c) != 0) {
        func_ov099_0229ca34(self);
    }
}

void func_ov099_0229d8b8(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov099_0229d8a4(void *ptr)
{
    func_ov094_0229a29c((char *) ptr + 0xb54, 0);
}

int func_ov099_0229d894(int arg)
{
    return func_ov094_0229a098((void *) (arg + 0x0b54));
}
