/* func_ov003_02236028 @ 0x02236028, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02236110(unsigned short *p);

void func_ov003_02236028(char *base)
{
    unsigned int a, b;
    for (a = 0; a < 4; a++) {
        for (b = 0; b < 4; b++) {
            func_ov003_02236110((unsigned short *) (base + a * 0x88 + b * 0x22));
        }
    }
}
