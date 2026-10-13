/* func_ov068_02275868 @ 0x02275868, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern void func_02019c6c(void *, int, unsigned short);
extern unsigned short data_020c80f8;

void func_ov068_02275868(void *self)
{
    if (func_02014868((char *) self + 0x618)) {
        func_02019c6c((char *) self + 0x564, 2, data_020c80f8);
    } else {
        func_02019c6c((char *) self + 0x564, 1, data_020c80f8);
    }
}
