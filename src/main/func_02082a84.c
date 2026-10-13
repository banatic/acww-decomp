/* func_02082a84 @ 0x02082a84, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    int a;
    unsigned short b;
};

extern int func_02082afc(struct Entry *arr);

int func_02082a84(struct Entry *arr)
{
    int idx = func_02082afc(arr);
    int ret = 0;
    if (idx >= 0 && idx < 8) {
        arr[idx].a = 0;
        arr[idx].b = 0xfff1;
        ret = 1;
    }
    return ret;
}
