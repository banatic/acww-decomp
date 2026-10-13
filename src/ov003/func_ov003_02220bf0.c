/* func_ov003_02220bf0 @ 0x02220bf0, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_02045cec(int *, int);
extern int func_0204ee7c(int, int, int);
extern unsigned char data_ov003_02236670[];

int func_ov003_02220bf0(int *pos)
{
    int result;
    int a;
    int d;
    int c;
    int temp[2];
    int i;

    a = func_0204e414();
    result = 2;
    if (a == 0) {
        return result;
    }

    c = 0;
    d = 0;

    for (i = 0; i < 9; i++) {
        unsigned char byte = data_ov003_02236670[i];
        int x = pos[0] + (((int) byte >> 4) - 8);
        int y = pos[1] + (((int) byte & 0xf) - 8);
        int xq = x >> 4;
        int yq = y >> 4;
        int xm = x - (xq << 4);
        int ym = y - (yq << 4);
        unsigned short *p = (unsigned short *) func_0204f5e0(a, xq, yq, xm, ym, d);
        if (p != 0 && *p == 0xfff1) {
            temp[0] = x;
            temp[1] = y;
            if (func_02045cec(temp, c) < 0) {
                if (func_0204ee7c(a, x, y) != 0) {
                    pos[0] = x;
                    pos[1] = y;
                    result = 0;
                }
                break;
            }
        }
    }

    return result;
}
