/* func_ov009_02264d60 @ 0x02264d60, 0x68 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b2a68(void *dst, const void *src);
extern int func_020b2a44(void *buf);
extern void func_020b2a64(void *buf);
extern const unsigned char data_020d1f24[];

int func_ov009_02264d60(const void *p)
{
    unsigned char buf[16];
    unsigned int v;
    int flag;
    const unsigned char *table;
    int result;

    flag = 0;
    v = *(const unsigned short *) ((const unsigned char *) p + 0x136);
    if (v >= 0x5000 && v <= 0x5021) {
        flag = 1;
    }
    if (flag != 0) {
        v &= 0xfff;
    } else {
        v = -1;
    }
    if (v < 0x22) {
        table = data_020d1f24 + v * 10;
    } else {
        table = data_020d1f24;
    }
    func_020b2a68(buf, table);
    result = func_020b2a44(buf) << 13;
    func_020b2a64(buf);
    return result;
}
