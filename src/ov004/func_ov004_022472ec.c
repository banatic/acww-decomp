/* func_ov004_022472ec @ 0x022472ec, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c67a4;
extern int func_0203c0ac(void *obj, int id);

int func_ov004_022472ec(void)
{
    if (data_021c67a4 != 0) {
        return func_0203c0ac(data_021c67a4, 0xc);
    }
    return 0;
}
