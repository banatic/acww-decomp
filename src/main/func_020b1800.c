/* func_020b1800 @ 0x020b1800, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(unsigned char *self);
extern int func_020644cc(int a);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern void func_020b9b14(unsigned char *a, unsigned char *b, unsigned int c, int d, int e);

void func_020b1800(unsigned char *self)
{
    unsigned int flag;
    unsigned int zero_val;
    int i;
    unsigned char *p;

    func_020b9ccc(self);
    flag = 0;
    zero_val = 0;

    for (i = 0; i < 4; i++) {
        p = self + i;
        if (p[0x324] != 0) {
            p[0x324]--;
        } else {
            if (p[0x328] == 0) {
                p[0x328] = (unsigned char) (func_020644cc(4) + 1);
                p[0x324] = (unsigned char) (func_020644cc(15) + 5);
            } else {
                p[0x328] = (unsigned char) zero_val;
                p[0x324] = (unsigned char) (func_020644cc(30) + 10);
            }
            flag = 1;
            MI_CpuCopy8(self + 0xa4 + (p[0x328] << 7) + (i << 5), self + 0x24 + (i << 5), 32);
        }
    }

    if (flag != 0) {
        func_020b9b14(self, self + 0x24, self[0x32c], 4, 7);
    }
}
