/* field_actor_41: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216698 @ 0x02216698, 0x50 bytes, Thumb
 * func_ov003_02216688 @ 0x02216688, 0xe bytes, Thumb
 * func_ov003_02216644 @ 0x02216644, 0x44 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xC];
    unsigned char sub[4];
} QType;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_022166e8(void *, int, int, int *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109a0(char *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(char *, int);

int func_ov003_02216698(void *arg1, int arg2, int arg3, int *arg4, int arg5, short arg6)
{
    int arg3_copy;
    int arr[2];
    char buf1[12];
    char buf2[20];
    int result;

    arg3_copy = arg3;
    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x4a, arg5, (int) arg6);
    arr[0] = arg4[0];
    arr[1] = arg4[1];
    func_ov003_022166e8(buf2, arg2, arg3_copy, arr);
    result = func_0200e894(arg1, buf1);
    func_0200e91c(buf1);
    return result;
}

void func_ov003_02216688(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3)
{
    r0[2] = r1;
    r0[3] = r2;
    r0[0] = (unsigned char) r3[0];
    r0[1] = (unsigned char) r3[1];
}

void func_ov003_02216644(char *a, QType *b, int previous)
{
    unsigned char *p = b->sub;
    unsigned char v2 = p[2];
    unsigned char v3 = p[3];
    unsigned char v1 = p[1];
    unsigned char v0 = b->sub[0];
    int local[3];

    local[0] = v0;
    local[1] = v1;
    func_ov003_02216688((unsigned char *) (a + 0x7d4), v2, v3, (unsigned int *) local);
    func_020109a0(a, 0x44, 3, 0);
    func_0200f27c(a, 0x1c);
}
