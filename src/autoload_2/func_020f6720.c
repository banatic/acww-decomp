/* func_020f6720 @ 0x020f6720, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_02138ff4[];

void *func_020f6720(unsigned char *self)
{
    unsigned char idx = self[0x3b];
    unsigned char *src = data_02138ff4 + (idx << 4);
    int i;
    for (i = 0; i < 0x10; i++) {
        (self + i)[0x28] = src[i];
    }
    return self + 0x28;
}
