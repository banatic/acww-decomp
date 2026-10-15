/* func_0205dbb8 @ 0x0205dbb8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_020b65c4(void);
extern int func_020b5e04(unsigned int);
extern int func_0205dc3c(void);
extern int func_020b5df8(unsigned int);
extern int func_02085f08(void);
extern int func_020ea0e0(int, int);

extern unsigned char data_021c9ad4[];

void func_0205dbb8(int *r6)
{
    unsigned int r4;
    unsigned int r5;
    int r7;
    unsigned char r5b;
    int r0v;

    r7 = *((int *) data_021c9ad4);
    r5b = *((unsigned char *) ((*((int *) (&data_020ccf94))) + 0x6c));
    r4 = func_020b5e04((unsigned int) func_020b65c4());
    if (r5b < r4) {
        r4 = r5b;
    }
    r5 = 0;
    while (r5 < r4) {
        r0v = func_0205dc3c();
        r6[r5] = func_020ea0e0(r0v, r7);
        r5++;
    }

    if (r4 == 0) {
        r4 = 1;
    }
    r5 = func_020b5df8((unsigned int) func_020b65c4());
    r0v = func_02085f08();
    r4 = (r5 + r0v) - r4;
    r4 = r4 + 4;
    r5 = 4;
    while (r5 < r4) {
        r0v = func_0205dc3c();
        r6[r5] = func_020ea0e0(r0v, r7);
        r5++;
    }
}
