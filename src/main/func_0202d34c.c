/* func_0202d34c @ 0x0202d34c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a488(unsigned char v);
extern int func_02061550(unsigned char v);
extern int func_0202d3b0(int a, int b, int c);

int func_0202d34c(int key, const unsigned char *p, int n, int a3, int a4)
{
    int count;
    int prev;
    int i;
    int d;

    count = 0;
    if (p != 0 && n > 0) {
        prev = 0;
        for (i = 0; i < n; i++) {
            d = p[1] - prev;

            if (d > 0) {
                if (key == func_0209a488((unsigned char) d)) {
                    if (func_0202d3b0(func_02061550(p[0]), a3, a4) == 0) {
                        count++;
                    }
                }
            } else {
                count = 0;
                break;
            }
            prev = p[1];
            p += 2;
        }
    }
    return count;
}
