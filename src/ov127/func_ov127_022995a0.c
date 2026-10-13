/* func_ov127_022995a0 @ 0x022995a0, 0x6c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov127_0229b6e0[0x11];
extern unsigned char data_ov127_0229b6f4[0x11];
extern void func_ov127_0229960c(void *self, unsigned char *table);
extern int func_020b1498(int i);

int func_ov127_022995a0(void *self)
{
    int i, k, m, id;

    func_ov127_0229960c(self, data_ov127_0229b6e0);

    for (i = 0; i < 0x10; i++) {
        id = func_020b1498(i);
        if (id != 0) {
            func_ov127_0229960c((void *) id, data_ov127_0229b6f4);
            for (k = 0; k < 0x11 && data_ov127_0229b6e0[k] != 0xff; k++) {
                for (m = 0; m < 0x11 && data_ov127_0229b6f4[m] != 0xff; m++) {
                    if (data_ov127_0229b6e0[k] == data_ov127_0229b6f4[m]) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
