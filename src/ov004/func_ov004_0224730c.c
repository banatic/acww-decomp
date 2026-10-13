/* func_ov004_0224730c @ 0x0224730c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c67a4;
extern int func_0203c0ac(void *obj, int id);

int func_ov004_0224730c(void)
{
    if (data_021c67a4 != 0) {
        return func_0203c0ac(data_021c67a4, 0xb);
    }
    return 0;
}
