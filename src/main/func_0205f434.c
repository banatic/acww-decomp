/* func_0205f434 @ 0x0205f434, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern unsigned int func_0205f634(void);
extern unsigned int func_0205f630(void);
extern unsigned int func_0205f62c(void);
extern int func_02055c80(unsigned char *, unsigned int, unsigned int, unsigned int);
extern unsigned int func_0205f644(void);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);
extern unsigned int data_021c9ad8;
extern unsigned char *data_020ccf94;

void func_0205f434(unsigned int *param0)
{
    unsigned char cnt;
    unsigned int i;
    unsigned int count;
    unsigned int countOrOne;
    unsigned int a, b;
    unsigned int end;
    unsigned int g;
    unsigned int r1, r2, r3;

    cnt = data_020ccf94[0x6c];
    count = func_020b5e04((unsigned int) func_020b65c4());
    if (cnt < count) {
        count = cnt;
    }

    if (count != 0) {
        countOrOne = count;
    } else {
        countOrOne = 1;
    }

    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    end = (a + b) - countOrOne;

    for (i = 0; i < count; i++) {
        r1 = func_0205f634();
        r2 = func_0205f630();
        r3 = func_0205f62c();
        func_02055c80((unsigned char *) param0 + 0xdc + i * 0x14, r1, r2, r3);
    }

    for (i = 4; i < end + 4; i++) {
        r1 = func_0205f634();
        r2 = func_0205f630();
        r3 = func_0205f62c();
        func_02055c80((unsigned char *) param0 + 0xdc + i * 0x14, r1, r2, r3);
    }

    g = data_021c9ad8;

    for (i = 0; i < count; i++) {
        param0[i] = func_020e9968(g, func_0205f644(), 4);
    }

    for (i = 4; i < end + 4; i++) {
        param0[i] = func_020e9968(g, func_0205f644(), 4);
    }
}
