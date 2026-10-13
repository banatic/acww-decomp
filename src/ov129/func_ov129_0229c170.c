/* func_ov129_0229c170 @ 0x0229c170, 0x64 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229c1d4(void *);
extern void func_ov127_02299a00(void *, int, int);

void func_ov129_0229c170(char *p0)
{
    int v;
    unsigned char byte;

    p0[0xb4] = 5;
    if (*(unsigned short *) (p0 + 0xaa) != *(unsigned short *) (p0 + 0xa8)) {
        func_ov129_0229c1d4(p0);
    }

    v = *(unsigned short *) (p0 + 0xaa);
    if (v != 0xffff) {
        byte = *(unsigned char *) (p0 + v + 0x2f98);
        if ((unsigned char) (byte + 0xfe) <= 1) {
            func_ov127_02299a00(p0 + 0x734, v, 10);
        }
    }
    *(unsigned short *) (p0 + 0xa8) = *(unsigned short *) (p0 + 0xaa);
}
