/* func_ov004_0221bcbc @ 0x0221bcbc, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0221bbf8(char *self);
extern void func_020e9898(void *p);
int func_ov004_0221bcbc(char *self)
{
    void *p;
    func_ov004_0221bbf8(self);
    p = *(void **) (self + 0x164);
    if (p != 0) {
        func_020e9898(p);
    }
    return 1;
}
