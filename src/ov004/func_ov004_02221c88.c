/* func_ov004_02221c88 @ 0x02221c88, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f9d8(void *);
extern int func_0206fa28(int, int);
extern void func_ov004_02222178(void *, int);
extern void func_ov004_02222a30();

void func_ov004_02221c88(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x8e0) + 0x4) == 0x5 &&
        func_0206fa28(func_0206f9d8((void *) func_ov004_02222a30), 0xd) != 0x0) {
        func_ov004_02222178(self, 0x6);
        return;
    }
}
