/* func_02077a64 @ 0x02077a64, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec1e8(void);

int func_02077a64(void)
{
    int mode;

    mode = func_020ec1e8();
    return (mode == 3 || mode == 4);
}
