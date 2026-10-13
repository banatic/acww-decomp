/* func_020264b4 @ 0x020264b4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02026528(unsigned short *buf, int bits, int count, int result, int arg5, int arg6);

void func_020264b4(unsigned short *out, const unsigned char *p, int arg2)
{
    unsigned short bits;
    int count;
    int i;
    int result;
    unsigned short buf[2];

    *out = 0xfff1;
    bits = 0;
    count = 0;

    for (i = 0; i < 10; i++) {
        if (i != p[1]) {
            bits = (unsigned short) (bits | (1 << i));
            count++;
        }
    }

    result = func_020984e8();
    func_02026528(buf, bits, count, result, 1, arg2);

    *out = buf[0];
    if (*out == 0xfff1) {
        func_02026528(buf + 1, bits, count, 0, 0, arg2);
        *out = buf[1];
    }
}
