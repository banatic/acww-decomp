/* func_02044808 @ 0x02044808, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984fc(void);
extern int func_02099728(void);

int func_02044808(void)
{
    int r4;
    int r0;

    r4 = 0x0000fff1;
    r0 = func_020984fc();
    if (r0 != 0) {
        r0 = func_02099728();
        if (r0 != 0) {
            r4 = *(unsigned short *) r0;
        }
    }
    return r4;
}
