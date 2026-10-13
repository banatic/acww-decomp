/* func_02090764 @ 0x02090764, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020904ac(char *ptr);

void func_02090764(char *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_020904ac(param + 4 + i * 328);
    }
}
