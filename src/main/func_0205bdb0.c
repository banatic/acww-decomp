/* func_0205bdb0 @ 0x0205bdb0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205bd90(int);
extern int func_0204df30(int);
extern void func_0205bbf4(void *, int);
extern int func_0205bd88(void *);
extern int func_0205bd84(void *);
extern int func_0205bd80(void *);
extern void func_0205bd8c(void *);

extern unsigned char data_021c95e0;
extern unsigned char data_021c95e4;
extern unsigned char data_021c95e8;

void func_0205bdb0(void)
{
    unsigned char buf[3];
    unsigned int i;

    data_021c95e0 = 0;
    data_021c95e8 = 0;
    data_021c95e4 = 0;

    for (i = 0; i < 5; i++) {
        int r;

        func_0205bd90((int) &buf);
        r = func_0204df30(i);
        if (r != 0) {
            func_0205bbf4(&buf, r);
            data_021c95e4 += func_0205bd88(&buf);
            data_021c95e8 += func_0205bd84(&buf);
            data_021c95e0 += func_0205bd80(&buf);
        }
        func_0205bd8c(&buf);
    }
}
