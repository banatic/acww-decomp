/* func_ov003_0220fcb4 @ 0x0220fcb4, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(char *self);
extern int func_02056f28(char *ptr, int val);
extern void func_020912d4(int a, char *b, char *c, int d);

void func_ov003_0220fcb4(char *self)
{
    func_02010f5c(self);
    if (*(int *) (self + 0x704) == 0x65) {
        if (func_02056f28(self + 0x2d0, 3) != 0 || func_02056f28(self + 0x2d0, 13) != 0) {
            func_020912d4(0x23, self + 0x5c, self + 0x8e, 0);
        }
    }
}
