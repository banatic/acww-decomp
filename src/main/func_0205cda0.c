/* func_0205cda0 @ 0x0205cda0, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c9af8;
extern unsigned char *data_020ccf94;
extern void func_020b65c4(void);
extern unsigned int func_020b5e04(void);
extern unsigned int func_020b5df8(void);
extern unsigned int func_02085f08(void);
extern unsigned int func_0205cf44(void);
extern unsigned int func_0205cf3c(void);
extern unsigned int func_0205cf34(void);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);

void func_0205cda0(unsigned int *out)
{
    unsigned int total, s1, s2, s3, tmp, size;
    unsigned int arg, n0, n;
    unsigned char field;
    unsigned int i;

    arg = data_021c9af8;
    field = data_020ccf94[0x6c];
    func_020b65c4();
    n0 = func_020b5e04();
    if (field < n0) {
        n0 = field;
    }
    if (n0 != 0) {
        n = n0;
    } else {
        n = 1;
    }

    func_020b65c4();
    tmp = func_020b5df8();
    total = tmp + func_02085f08() - n;
    s1 = func_0205cf44();
    s2 = func_0205cf3c();
    s3 = func_0205cf34();

    for (i = 0; i < n0; i++) {
        out[i] = func_020e9968(arg, s1, 4);
    }

    size = 4;
    for (i = 4; i < total + 4; i++) {
        out[i] = func_020e9968(arg, s1, size);
    }

    for (i = 9; i < n0 + 9; i++) {
        out[i] = func_020e9968(arg, s2, 4);
    }

    for (i = 13; i < total + 13; i++) {
        out[i] = func_020e9968(arg, s2, size);
    }

    for (i = 18; i < total + 18; i++) {
        out[i] = func_020e9968(arg, s3, size);
    }
}
