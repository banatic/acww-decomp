/* func_ov130_02299a08 @ 0x02299a08, 0x50 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_022999a8(unsigned short *p, int i);

void func_ov130_02299a08(unsigned short *base, int a, int b, int c)
{
    unsigned short idx;
    int row;
    unsigned short *arr;

    idx = (unsigned short) ((a << 1) + 0x160);
    row = b + (c << 5);
    arr = (unsigned short *) ((char *) base + 0x290);

    arr[row] = (arr[row] & 0xFC00) | idx;

    row += 0x20;
    idx = (unsigned short) (idx + 1);
    arr[row] = (arr[row] & 0xFC00) | idx;

    func_ov130_022999a8(base, 1);
}
