/* func_02060d7c @ 0x02060d7c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060e78(const void *ptr);
extern unsigned short data_020cc9c0[];
extern char data_021ebcd4;

unsigned short func_02060d7c(void *addr)
{
    int res;
    res = func_02060e78(&data_021ebcd4);
    if (res < 7) {
        return data_020cc9c0[res];
    } else {
        return 0x1003;
    }
}
