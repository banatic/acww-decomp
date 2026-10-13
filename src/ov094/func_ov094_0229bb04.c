/* func_ov094_0229bb04 @ 0x0229bb04, 0x58 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b384(int a, int b);
extern int func_ov094_0229b328(int a, int b);

unsigned char func_ov094_0229bb04(int p0, int p1, int p2, int p3, unsigned char limit)
{
    int i = p3;
    int a = p1 - 20;
    int b = p1 + 4;
    int c = p2 - 20;
    int d = p2 + 4;
    unsigned char lim = limit;

    for (; i <= lim; i++) {
        int x = func_ov094_0229b384(p0, i);
        if (a < x && x < b) {
            int y = func_ov094_0229b328(p0, i);
            if (c < y && y < d) {
                return (unsigned char) i;
            }
        }
    }
    return 0x37;
}
