/* func_0205d74c @ 0x0205d74c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d950(void *, int, int, int);
extern void func_0205d8f4(void *, int, int, int);
extern void func_0205d7b8(void *, int, int, int);
extern int data_021c9d7c;

void func_0205d74c(unsigned char *obj, int a, int b, int c, int d)
{
    unsigned char ch;

    ch = obj[0];

    if (a >= 0x16f) {
        func_0205d950(&data_021c9d7c, ch, 0, 0x16f);
        func_0205d8f4(&data_021c9d7c, ch, 0, 0);
    } else {
        func_0205d7b8(obj, a, c, d);
    }

    if (b >= 0x16f) {
        func_0205d950(&data_021c9d7c, ch, 1, 0x16f);
        func_0205d8f4(&data_021c9d7c, ch, 1, 0);
    } else {
        func_0205d7b8(obj, b, c, d);
    }
}
