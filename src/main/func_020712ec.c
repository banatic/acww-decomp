/* func_020712ec @ 0x020712ec, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02071318(int a, int b, int *c);

int func_020712ec(int a, int b)
{
    int temp;
    unsigned char *p;
    int idx;
    int shift;
    int result;

    p = func_02071318(a, b, &temp);
    if (p != 0) {
        idx = temp >> 1;
        shift = (temp & 1) << 2;
        result = (p[idx] >> shift) & 0xf;
    } else {
        result = 0;
    }
    return result;
}
