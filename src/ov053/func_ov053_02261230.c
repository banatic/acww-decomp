/* func_ov053_02261230 @ 0x02261230, 0x30 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov053_02261524(void *, int);

int func_ov053_02261230(void *arg)
{
    if (func_02019e00((char *) arg + 0x564) == 3) {
        if (func_02019de8((char *) arg + 0x564) != 0) {
            func_ov053_02261524(arg, 1);
        }
    }
    return 1;
}
