/* func_ov068_0226e708 @ 0x0226e708, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_ov068_0226e878(void *, int);

int func_ov068_0226e708(void *arg)
{
    if (func_02019e00((char *) arg + 0x564) == 3) {
        if (func_02019de8((char *) arg + 0x564) != 0) {
            func_ov068_0226e878(arg, 4);
        }
    }
    return 1;
}
