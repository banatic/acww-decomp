/* func_02082240 @ 0x02082240, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073dd4(void *ptr, int val);

int func_02082240(void)
{
    void *p = data_020ccf94;
    if (func_02073dd4(p, *(int *) ((char *) p + 0x64)) != 0) {
        return 0;
    } else {
        return 4;
    }
}
