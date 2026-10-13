/* func_ov003_02225f68 @ 0x02225f68, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int (*data_ov003_0223b8a4[])(void);
int func_ov003_02225f68(void)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (data_ov003_0223b8a4[i]() == 0) {
            return 0;
        }
    }
    return 1;
}
