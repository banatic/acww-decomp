/* func_02082ab0 @ 0x02082ab0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    int value;
    unsigned short extra;
};

extern int func_02082afc(struct Entry *a, unsigned short *b);

int func_02082ab0(struct Entry *a, int val, unsigned short *c)
{
    int flag = 0;
    if (func_02082afc(a, c) == -1) {
        unsigned short temp = 0xfff1;
        int index = func_02082afc(a, &temp);
        if (index >= 0 && index < 8) {
            a[index].value = val;
            a[index].extra = *c;
            flag = 1;
        }
    }
    return flag;
}
