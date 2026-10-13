/* func_0205cc1c @ 0x0205cc1c, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cd40(void *, int, int);
extern void func_0205ccf0(void *, int, int);
extern int func_0205cd4c(void *, int);
extern int func_0205cd08(void *, int);
extern int func_0205cd58(void *, int);
extern char data_021c9b58[];
extern void func_0205cba8(unsigned char *, int);
extern int func_0205cf3c(void);
extern int func_0205cf44(void);
extern int func_0205cf4c(int);
extern int func_02064af4(int, int, int);

void func_0205cc1c(unsigned char *self, int n, int x, int flag)
{
    unsigned char b = *self;

    if (n >= 0x144) {
        func_0205cd40(data_021c9b58, b, 0x144);
        func_0205ccf0(data_021c9b58, b, 0);
        return;
    }

    if (flag == 0) {
        int v = func_0205cd4c(data_021c9b58, b);
        if (n == v) {
            return;
        }
    }

    if (x != 0) {
        int w = func_0205cd08(data_021c9b58, n);
        if (w != 0x19) {
            func_0205cba8(self, w);
            return;
        }
    }

    {
        int x2 = func_0205cd58(data_021c9b58, b);
        int y;
        int z;
        int result;

        if ((int) b > 8) {
            y = func_0205cf3c();
        } else {
            y = func_0205cf44();
        }

        z = func_0205cf4c(n);
        result = func_02064af4(z, x2, y);
        if (result == 0) {
            return;
        }

        func_0205cd40(data_021c9b58, b, n);
        func_0205ccf0(data_021c9b58, b, result);
    }
}
