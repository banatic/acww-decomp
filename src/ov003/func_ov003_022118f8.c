/* func_ov003_022118f8 @ 0x022118f8, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, short c);
extern void func_ov003_022119d8(void *out, const void *in, int a, int b);
extern int func_02073908(int a, int b);
extern int func_0200e894(void *a, void *b);
extern void func_0200e91c(void *p);

struct UnkStruct_022118f8 {
    int a, b, c;
};
struct Buf {
    int a, b, c;
};
struct UnkStruct_022118f8_2 {
    int a, b, c, d;
};
struct Copied {
    int a, b, c;
};

int func_ov003_022118f8(int *p0, struct UnkStruct_022118f8 *p1, int p2, int p3, int p4, short p5)
{
    struct Buf buf;
    struct UnkStruct_022118f8_2 out;
    struct Copied copied;
    int ret;

    func_0200e92c(&buf);
    func_0200e90c(&buf, 0x5f, p4, p5);
    copied.a = p1->a;
    copied.b = p1->b;
    copied.c = p1->c;
    func_ov003_022119d8(&out, &copied, p2, p3);
    if (func_02073908(data_020ccf94, p0[0x200]) == 0) {
        *(volatile unsigned short *) ((char *) p0 + 0x822) = 0xfff1;
        *(volatile unsigned short *) ((char *) p0 + 0x820) = *(volatile unsigned short *) ((char *) p0 + 0x822);
    }
    ret = func_0200e894(p0, &buf);
    func_0200e91c(&buf);
    return ret;
}
