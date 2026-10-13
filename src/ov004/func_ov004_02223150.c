/* func_ov004_02223150 @ 0x02223150, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov004_02223388(void *, int);

int func_ov004_02223150(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov004_02223388(self, 0);
        }
    }
    return 1;
}
