/* func_0207de14 @ 0x0207de14, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0207dfd4(int, int);
extern int func_020644cc(int);

void func_0207de14(unsigned short *out, int in)
{
    unsigned short *arr;
    int count, i, k;

    *out = 0xfff1;
    arr = func_0207dfd4(in, 0);
    count = 0;
    for (i = 0; i < 4; i++) {
        if (arr[i] != 0xfff1) {
            count++;
        }
    }
    if (count > 0) {
        k = func_020644cc(count);
        i = 0;
        while (i < 4) {
            if (*arr != 0xfff1) {
                if (k == 0) {
                    *out = *arr;
                    break;
                }
                k--;
            }
            arr++;
            i++;
        }
    }
}
