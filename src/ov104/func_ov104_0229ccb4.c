/* func_ov104_0229ccb4 @ 0x0229ccb4, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern void func_ov002_0220a2b4(void *);

void func_ov104_0229ccb4(void *param0, void *param1)
{
    if (func_ov002_022088ac(param1)) {
        ((unsigned char *) param0)[0xb8] = 0x20;
    } else if (func_ov002_0220889c(param1)) {
        ((unsigned char *) param0)[0xb8] = 0x1f;
    }
    if (func_ov002_022088cc(param1)) {
        func_ov002_0220a2b4((char *) param0 + 0x24a0);
        if (((unsigned char *) param0)[0xb8] == 0x20) {
            ((unsigned char *) param0)[0xb8] = 0x1d;
        } else {
            ((unsigned char *) param0)[0xb8] = 0x13;
        }
    }
}
