/* func_0205c814 @ 0x0205c814, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_020ccf94;
extern int data_021c9af8;
extern int func_020b65c4(void);
extern int func_020b5e04(unsigned int);
extern int func_020b5df8(unsigned int);
extern int func_02085f08(void);
extern int func_0205cf44(void);
extern int func_0205cf3c(void);
extern int func_0205cf34(void);
extern int func_020ea0e0(int, void *);
void func_0205c814(void *arg)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e;
    int min;
    int cond;
    cond = data_020ccf94[0x6c];
    min = func_020b5e04((unsigned int) func_020b65c4());
    if (((unsigned) cond) < ((unsigned) min)) {
        min = cond;
    }
    if (!min) {
        cond = 1;
    } else {
        cond = min;
    }
    e = func_020b5df8((unsigned int) func_020b65c4());
    cond = (func_02085f08() + e) - cond;
    a += (func_0205cf44() + 3) & (~3);
    b += (func_0205cf3c() + 3) & (~3);
    c += (func_0205cf34() + 3) & (~3);
    {
        int sum = min + cond;
        a *= sum;
        d += a;
        b *= sum;
        d += b;
        c *= cond;
        data_021c9af8 = func_020ea0e0(d + c, arg);
    }
}
