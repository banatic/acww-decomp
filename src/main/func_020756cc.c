/* func_020756cc @ 0x020756cc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(const unsigned char *p);
extern int func_020a132c(int x);
extern int func_020a1284(int x, unsigned short y);
extern void func_020a127c(int x, unsigned char y);

void func_020756cc(const unsigned char *p)
{
    int a = func_020b65c4(p);
    if (a == 12) {
        int b = func_020a132c(a);
        if (b != 0) {
            unsigned char c = *p;
            int d = func_020a132c(b);
            func_020a127c(func_020a132c(func_020a1284(d, (unsigned short) (c & 0xf))), (unsigned char) ((c >> 6) & 3));
        }
    }
}
