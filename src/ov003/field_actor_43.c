/* field_actor_43: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216ab8 @ 0x02216ab8, 0x50 bytes, Thumb
 * func_ov003_02216aa8 @ 0x02216aa8, 0xe bytes, Thumb
 * func_ov003_02216a90 @ 0x02216a90, 0x18 bytes, Thumb
 * func_ov003_02216a70 @ 0x02216a70, 0x20 bytes, Thumb
 */

extern unsigned int func_0200e92c(char *);
extern void func_0200e90c(char *, int, int, short);
extern void func_ov003_02216b08(char *, int, int, int *);
extern int func_0200e894(int, char *);
extern int func_0200e91c(char *);

int func_ov003_02216ab8(int arg1, int arg2, int arg3, int *arg4, int arg5, short arg6)
{
    int pair[2];
    char buf1[12];
    char buf2[20];
    int result;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x49, arg5, arg6);
    pair[0] = arg4[0];
    pair[1] = arg4[1];
    func_ov003_02216b08(buf2, arg2, arg3, pair);
    result = func_0200e894(arg1, buf1);
    func_0200e91c(buf1);
    return result;
}

void func_ov003_02216aa8(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3)
{
    r0[2] = r1;
    r0[3] = r2;
    r0[0] = (unsigned char) r3[0];
    r0[1] = (unsigned char) r3[1];
}

void func_ov003_02216a90(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned char r3, unsigned char r4,
                         unsigned char r5)
{
    r0[0] = r1;
    r0[1] = r2;
    r0[2] = r3;
    r0[3] = r4;
    r0[4] = r5;
}

void func_ov003_02216a70(const unsigned char *src, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                         unsigned char *e)
{
    *a = src[0];
    *b = src[1];
    *c = src[2];
    *d = src[3];
    *e = src[4];
}
