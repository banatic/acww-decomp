/* func_ov068_02273158 @ 0x02273158, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *ptr, int value);
extern void func_0200467c(int cmd);

void func_ov068_02273158(void *param)
{
    if (func_02056f28((char *) param + 0x188, 0) != 0) {
        func_0200467c(0x886);
    } else if (func_02056f28((char *) param + 0x188, 0x1c) != 0) {
        func_0200467c(0x887);
    }
}
