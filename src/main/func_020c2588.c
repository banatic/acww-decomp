/* func_020c2588 @ 0x020c2588, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c814c;
extern unsigned short data_020c80f8;

extern void func_0201ad18(void *dst, unsigned int a, unsigned int b, unsigned int c, const void *p, unsigned int v1,
                          unsigned int v2, unsigned int v3);
extern void func_02019c20(void *dst, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int func_0204e414(void);
extern void func_0204e08c(unsigned int id, void *dst, unsigned int a, unsigned int b);
extern void func_0204f7e0(void *dst, const void *src);

struct Out1 {
    int a;
    int b;
    int c;
};
struct Out2 {
    int x;
    int y;
    int z;
};

extern unsigned char data_021fbee8[];

int func_020c2588(void *self)
{
    int *flags = (int *) ((char *) self + 0x4e8);
    struct Out1 out1;
    struct Out2 out2;
    unsigned int id;

    *flags |= 2;

    func_0201ad18((char *) self + 0x3b0, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);

    func_02019c20((char *) self + 0x564, 1, 0x53, 1, data_020c80f8, 0);

    id = func_0204e414();

    func_0204e08c(id, &out1, 0, 0);
    func_0204f7e0(&out2, (char *) self + 0x5c);

    if (out2.z >= out1.c) {
        goto skip;
    }
    if (out2.x < out1.a - 0x4000) {
        goto skip;
    }
    if (out2.x > out1.a + 0x4000) {
        goto skip;
    }

    *(int *) ((char *) self + 0x64) = out1.c + 0x1000;

skip:
    *((unsigned char *) self + 0x510) = 1;
    return 1;
}
