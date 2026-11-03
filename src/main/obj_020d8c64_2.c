/* obj_020d8c64_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02013aac @ 0x02013aac, 0x10 bytes, Thumb
 * func_02013aa0 @ 0x02013aa0, 0xc bytes, Thumb
 * func_02013a94 @ 0x02013a94, 0xc bytes, Thumb
 * func_02013a14 @ 0x02013a14, 0x80 bytes, Thumb
 * func_02013a0c @ 0x02013a0c, 0x6 bytes, Thumb
 */

extern int func_02014868(char *);
extern int func_02019e00(char *);
extern int func_0201c274(char *);
extern int func_020160d4(int);
extern int func_02019df8(char *);
extern int func_0203f9e0(unsigned char);

void func_02013aac(int p0)
{
    *(short *) ((char *) (p0) + (1598)) = (~0);
}

void func_02013aa0(void *base, unsigned short value)
{
    *(unsigned short *) ((char *) base + 0x63e) = value;
}

short func_02013a94(short *arg0)
{
    return arg0[0x31f];
}

int func_02013a14(char *p)
{
    int result = -1;
    if (func_02014868(p + 0x618) != 0) {
        if (func_02019e00(p + 0x564) == 8) {
            if (func_0201c274(p) != 0) {
                if (func_020160d4(func_0201c274(p)) == 0) {
                    int r4 = func_02019df8(p + 0x564);
                    if (r4 > 0 && r4 < 60) {
                        if (r4 != (int) func_02013a94((short *) p)) {
                            if (func_0203f9e0((unsigned char) r4) == -1) {
                                result = r4;
                                func_02013aa0((void *) p, (unsigned char) ((unsigned char) r4));
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

int func_02013a0c(void *object)
{
    (void) object;
    return -1;
}
