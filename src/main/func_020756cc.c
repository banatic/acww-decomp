/* func_020756cc @ 0x020756cc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1284(int x, unsigned short y);
extern void func_020a127c(int x, unsigned char y);

void func_020756cc(unsigned char *payload, unsigned int length, int player)
{
    int a = func_020b65c4();
    if (a == 12) {
        int b = (a, func_020a132c());
        if (b != 0) {
            unsigned char c = *payload;
            int d = (b, func_020a132c());
            func_020a127c((((int) (func_020a1284(d, (unsigned short) (c & 0xf)), d)), func_020a132c()),
                          (unsigned char) ((c >> 6) & 3));
        }
    }
}
