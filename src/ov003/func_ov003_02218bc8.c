/* func_ov003_02218bc8 @ 0x02218bc8, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int argument0);
extern int func_02056f28(void *ptr, int size);
extern void func_ov003_022189d8(void *ptr);

void func_ov003_02218bc8(void *arg0)
{
    void *ptr = arg0;
    func_02010f5c((int) arg0);
    if (func_02056f28((char *) ptr + 0x2d0, 10) != 0) {
        func_ov003_022189d8(ptr);
    }
}
