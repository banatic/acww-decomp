/* func_02065db8 @ 0x02065db8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051c08(unsigned char *dest, const unsigned char *src, int size);
extern int func_02065f20(unsigned char *p);
extern int func_02065e9c(unsigned char *p);

void func_02065db8(unsigned char *base1, unsigned char *base2)
{
    unsigned char *src;
    func_02051c08(base2 + 0xd8, base1 + 0x28, 0x10);
    if (func_02065f20(base2)) {
        return;
    }
    if (func_02065e9c(base2)) {
        src = base1 + 0x14;
        base1[0x49] = base2[0xf8];
    } else {
        src = base1;
        base1[0x48] = base2[0xf8];
    }
    func_02051c08(base2 + 0x44, src, 0xa);
}
