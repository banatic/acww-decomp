/* func_ov003_022298c4 @ 0x022298c4, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_02229874(void *self);
void func_ov003_022297f0(void *self, void *a);

int func_ov003_022298c4(void *self, void *a)
{
    int st = *(int *) ((char *) self + 0x48);
    if (st == 1 || st == 3) {
        func_ov003_02229874(self);
    }
    func_ov003_022297f0(self, a);
    return 1;
}
