/* func_020afad8 @ 0x020afad8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020af854(void *p, unsigned int i, unsigned short *c);
extern int func_0204bcdc(int x);
extern int func_0206300c(int x, int y);

int func_020afad8(void *p)
{
    unsigned int i = 0;
    int j = i;
    for (; i < 0x25; i++) {
        unsigned short c = 0xfff1;
        int r = func_020af854(p, i, &c);
        if (func_0204bcdc(r)) {
            if (func_0206300c(r, j) == 4) {
                return 1;
            }
        }
    }
    return 0;
}
