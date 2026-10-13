/* func_02013a14 @ 0x02013a14, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(char *);
extern int func_02019e00(char *);
extern int func_0201c274(char *);
extern int func_020160d4(int);
extern int func_02019df8(char *);
extern int func_02013a94(char *);
extern int func_0203f9e0(unsigned char);
extern void func_02013aa0(char *, unsigned char);

int func_02013a14(char *p)
{
    int result = -1;
    if (func_02014868(p + 0x618) != 0) {
        if (func_02019e00(p + 0x564) == 8) {
            if (func_0201c274(p) != 0) {
                if (func_020160d4(func_0201c274(p)) == 0) {
                    int r4 = func_02019df8(p + 0x564);
                    if (r4 > 0 && r4 < 60) {
                        if (r4 != func_02013a94(p)) {
                            if (func_0203f9e0((unsigned char) r4) == -1) {
                                result = r4;
                                func_02013aa0(p, (unsigned char) r4);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}
