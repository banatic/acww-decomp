/* func_02097e94 @ 0x02097e94, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097e94(unsigned char *param0)
{
    int i;
    unsigned char *ptr;

    for (i = 0; i < 5; i++) {
        ptr = param0 + i;
        ptr[0x100] = 0;
    }
}
