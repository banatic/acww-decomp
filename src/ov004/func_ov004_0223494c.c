/* func_ov004_0223494c @ 0x0223494c, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02089bec(void *d, void *a, int b, int c, int e, int f, int g, int h, int i);
extern void func_02089fc8(void *d);
extern unsigned char data_ov004_022593a0;

void func_ov004_0223494c(void *self, int n)
{
    int i;
    int z;
    char *d;
    char *e;

    i = 0;
    z = i;
    for (; i < n; i++) {
        e = (char *) self + i * 0x64;
        d = (char *) self + 0x50 + i * 0x64;
        func_02089bec(d, (char *) self + 0xa0 + i * 0x64, *(int *) (e + 0xac), *(int *) (e + 0xb0), 0x102, 0x140, z, 0xff,
                      0x1000);
        func_02089fc8(d);
    }
    if (data_ov004_022593a0 == 1) {
        func_02089bec((char *) self + 0x244, (char *) self + 0x294, *(int *) ((char *) self + 0x2a0),
                      *(int *) ((char *) self + 0x2a4), 0x202, 0x140, 0, 0xff, 0x1000);
        func_02089fc8((char *) self + 0x244);
    }
}
