/* func_02077d84 @ 0x02077d84, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eb04c(void *friend_data);
extern long long func_020eb61c(int a);

int func_02077d84(int p0, char *p1)
{
    if (func_020eb04c((void *) p0) != 2) {
        return 0;
    }
    {
        unsigned long long v = func_020eb61c(p0);
        int i;
        for (i = 11; i >= 0; i--) {
            p1[i] = v % 10;
            v /= 10;
        }
    }
    return 1;
}
