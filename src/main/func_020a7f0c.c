/* func_020a7f0c @ 0x020a7f0c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dcc(void);
extern unsigned short data_021fbe40;

int func_020a7f0c(void)
{
    int r4 = 0;
    if (!func_020a7dcc()) {
        if (data_021fbe40 & 1) {
            r4 = 1;
        }
    }
    return r4;
}
