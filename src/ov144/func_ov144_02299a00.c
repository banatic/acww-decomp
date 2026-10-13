/* func_ov144_02299a00 @ 0x02299a00, 0x2e bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209eec(void *p);

void func_ov144_02299a00(char *obj)
{
    int val = func_ov002_02209eec(obj + 0xc4);
    if (val < 76) {
        obj[0xc1] = 11;
    } else if (val < 116) {
        obj[0xc1] = 13;
    } else {
        obj[0xc1] = 12;
    }
}
