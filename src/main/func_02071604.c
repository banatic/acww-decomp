/* func_02071604 @ 0x02071604, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int (*data_020ccf6c[])(int);

int func_02071604(int idx, int arg)
{
    if (idx < 10) {
        return data_020ccf6c[idx](arg);
    } else {
        return 0;
    }
}
