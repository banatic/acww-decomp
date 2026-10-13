/* func_ov129_0229bbd8 @ 0x0229bbd8, 0x5c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_022996d8(int x);
extern int func_ov127_022996c8(int x);
extern int func_ov127_022996e4(unsigned short *dst, int x, int y);
extern unsigned char *func_ov127_022996bc(unsigned short x);

unsigned short func_ov129_0229bbd8(int unused, int p1, unsigned char p2)
{
    int k = 0;
    unsigned short arr[8];
    int i;
    int j;
    int count;
    unsigned char *s;
    int x = func_ov127_022996d8(p1);
    int y = func_ov127_022996c8(p1);

    count = func_ov127_022996e4(arr, x, y);
    for (i = 0; i < count; i++) {
        s = func_ov127_022996bc(arr[i]);
        for (j = k; j < 2; j++) {
            if (p2 == s[j]) {
                return arr[i];
            }
        }
    }
    return 0xffff;
}
