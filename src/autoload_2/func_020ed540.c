/* func_020ed540 @ 0x020ed540, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int data_0213e6c4;
extern unsigned char *data_021fbf3c;

extern int func_0210132c(unsigned char *p);
extern unsigned char func_ov065_022798d0(unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d, int *e);

void func_020ed540(void *arg)
{
    unsigned int i;
    int local;

    if (arg != 0) {
        return;
    }

    data_0213e6c4 = 0;

    for (i = 0; i < 32; i++) {
        if (func_0210132c(data_021fbf3c + i * 12)) {
            *(data_021fbf3c + 0x1a0 + i * 0x23) =
                func_ov065_022798d0(data_021fbf3c + i * 12, data_021fbf3c + 0x1a1 + i * 0x23, data_021fbf3c + 0x1a2 + i * 0x23,
                                    data_021fbf3c + 0x180 + i * 0x23, &local);
        }
    }
}
