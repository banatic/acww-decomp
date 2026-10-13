/* func_ov073_022796f0 @ 0x022796f0, 0x30 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(char *);
extern void func_0201c280(char *, char *);
extern void func_ov073_02278d60(char *, char *);

int func_ov073_022796f0(char *x)
{
    if (func_0202edc8(x) == 0) {
        return 0;
    }
    func_0201c280(x, x + 0x658);
    func_ov073_02278d60(x + 0x658, x);
    return 1;
}
