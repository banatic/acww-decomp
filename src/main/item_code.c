/* item_code: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b268 @ 0x0204b268, 0x28 bytes, Thumb
 * func_0204b260 @ 0x0204b260, 0x8 bytes, Thumb
 */

int func_0204b268(unsigned short *p)
{
    int ret = 0;

    if (*p >= 0x1000 && *p <= 0x10ff) {
        ret = 1;
    }

    if (ret) {
        return 1;
    } else {
        return 0;
    }
}

void func_0204b260(unsigned short *argument0)
{
    func_0204b268((unsigned short *) argument0);
}
