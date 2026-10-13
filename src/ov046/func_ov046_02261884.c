/* func_ov046_02261884 @ 0x02261884, 0x30 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov046_022619cc(void *, int);

int func_ov046_02261884(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov046_022619cc(self, 0);
        }
    }
    return 1;
}
