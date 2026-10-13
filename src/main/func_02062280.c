/* func_02062280 @ 0x02062280, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cb634;
extern int func_0206e7bc(void *ptr, int idx);

int func_02062280(int arg0)
{
    int ret;

    if (arg0 < 74) {
        ret = func_0206e7bc(&data_021cb634, arg0);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}
