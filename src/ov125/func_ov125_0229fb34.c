/* func_ov125_0229fb34 @ 0x0229fb34, 0x48 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229fe4c(void *p, int x);
extern int func_ov125_0229f76c(void *p, int x);

int func_ov125_0229fb34(void *p)
{
    int a = func_ov125_0229fe4c(p, ((unsigned char *) p)[0x87c]);
    if (func_ov125_0229f76c(p, 8) != 0) {
        a += 0x100;
    } else if (func_ov125_0229f76c(p, 4) != 0) {
        a -= 0x100;
    }
    return a + 11;
}
