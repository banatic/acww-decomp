/* func_02031af0 @ 0x02031af0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(void);
extern unsigned char data_020c9081[];

int func_02031af0(void)
{
    int r0;
    int r1;

    r0 = func_01ffcb2c();
    if (r0 < 0x7c) {
        r1 = 0x1e;
        r0 = r0 * r1;
        return data_020c9081[r0];
    } else {
        return 0;
    }
}
