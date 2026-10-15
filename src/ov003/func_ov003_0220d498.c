/* func_ov003_0220d498 @ 0x0220d498, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

struct UnkStruct_0220d498 {
    unsigned char pad_00[12];
    unsigned char b0;
    unsigned char b1;
    unsigned char pad_0E[14];
};

int func_ov003_0220d498(void *a0, unsigned char *a1, int a2, int a3, short a4)
{
    struct UnkStruct_0220d498 local;
    unsigned char *p;
    int res;

    p = &local.b0;
    func_0200e92c(&local);
    func_0200e90c(&local, 0x8f, a3, a4);
    *p = *a1;
    *(p + 1) = (unsigned char) a2;
    res = func_0200e894(a0, &local);
    func_0200e91c(&local);
    return res;
}
