/* func_020b7338 @ 0x020b7338, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int (*data_020e57ac[])(int);

int func_020b7338(int idx, int arg)
{
    if (idx < 23) {
        return data_020e57ac[idx](arg);
    } else {
        return 0;
    }
}
