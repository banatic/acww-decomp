/* func_020f5484 @ 0x020f5484, 0xd8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd1bc;
extern int func_020f1d3c(void *addr, int arg);

typedef struct {
    unsigned char pad_00[0x3f];
    unsigned char flags;
} S020f5484;

unsigned short func_020f5484(S020f5484 *p, unsigned short val)
{
    int s = func_020f1d3c(&data_021fd1bc, 4);
    unsigned char f = p->flags;
    int mask2 = f & 2;
    int mask4 = f & 4;

    if (f & 1) {
        if (s == 0 && mask2 == 0 && mask4 == 0) {
            val = (unsigned short) (val + 2);
            p->flags = f | 2;
        } else {
            p->flags &= ~2;
        }
    } else {
        if (s == 0 && mask2 == 0 && mask4 == 0) {
            val = (unsigned short) (val + 3);
            p->flags = f | 4;
        } else {
            p->flags &= ~4;
            val = (unsigned short) (val + 1);
        }
    }
    p->flags ^= 1;
    return val;
}
