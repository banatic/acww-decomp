/* func_ov049_02262344 @ 0x02262344, 0x30 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov049_02262a94(void *, int);

int func_ov049_02262344(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov049_02262a94(self, 10);
        }
    }
    return 1;
}
