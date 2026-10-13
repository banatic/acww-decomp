/* func_ov145_0229a080 @ 0x0229a080, 0x50 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_02071298(int addr, unsigned short *ptr);

extern unsigned char data_021f38f8[];

int func_ov145_0229a080(int unused, unsigned short *arr, unsigned short start, int count, int delta)
{
    int n = 0;
    unsigned short cur = 0xfff1;
    int i;

    for (i = 0; i < count; i++) {
        cur = start;
        if (func_02071298((unsigned int) data_021f38f8, &cur)) {
            arr[n] = start;
            n++;
        }
        start = (unsigned short) (start + delta);
    }
    return n;
}
