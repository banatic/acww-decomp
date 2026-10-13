/* func_ov121_0229ae68 @ 0x0229ae68, 0x5c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_0229af58(void *p, int a);
extern int func_ov121_0229af40(void *p, int a);

int func_ov121_0229ae68(void *p, unsigned char a, unsigned char b, unsigned int c)
{
    unsigned char i;
    int amin = a - 0x10;
    int aplus = a + 0x10;
    int bmin = b - 0x10;
    int bplus = b + 0x10;
    for (i = 0; i <= c; i = (unsigned char) (i + 1)) {
        int v = func_ov121_0229af58(p, i);
        if (amin < v && v < aplus) {
            int w = func_ov121_0229af40(p, i);
            if (bmin < w && w < bplus) {
                return i;
            }
        }
    }
    return 0x18;
}
