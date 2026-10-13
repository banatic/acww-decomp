/* func_ov106_0229e67c @ 0x0229e67c, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int AOSS_FD_SET(const unsigned char *);
extern void func_ov106_0229c798(const unsigned char *, unsigned char, int);
extern void func_ov002_02208098(const unsigned char *, int);

void func_ov106_0229e67c(unsigned char *obj)
{
    if (AOSS_FD_SET(obj + 0x21b8) == 0) {
        return;
    }
    if (obj[0xbf] != 0) {
        obj[0xbf]--;
    } else {
        func_ov106_0229c798(obj, obj[0xb5], 1);
        func_ov002_02208098(obj, 2);
    }
}
