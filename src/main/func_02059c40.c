/* func_02059c40 @ 0x02059c40, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020044a0(void *ptr);
extern char *data_021c9350;

int func_02059c40(void)
{
    func_020044a0(data_021c9350 + 0xDC);
    data_021c9350 = 0;
    return 1;
}
