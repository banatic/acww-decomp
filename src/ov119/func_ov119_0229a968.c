/* func_ov119_0229a968 @ 0x0229a968, 0xb0 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099664(void *);
extern int func_02077bd8(void *);
extern int func_02077bd0(void *);
extern void func_020b4980(void *, unsigned char *, int);
extern void *func_ov119_0229bb44(void *);
extern int func_020a7bf4(void *, int);
extern void func_020a8a34(void *, int);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern const unsigned char data_021f43ec;

void func_ov119_0229a968(void *obj)
{
    int z1, z2;
    unsigned char b;
    void *h, *p;
    int i;

    b = data_021f43ec;
    h = func_020984e8();
    if (func_02077bd8(func_02099664(h)) == 0) {
        b = 0xd4;
    } else if (func_02077bd0(func_02099664(h)) == 0) {
        b = 0xec;
    } else {
        b = 0xd5;
    }
    func_020b4980((char *) obj + 0xcd4, &b, 0);
    z1 = 0;
    z2 = 0;
    for (i = 0; i < 3; i++) {
        p = func_ov119_0229bb44(obj);
        func_020a8a34(p, func_020a7bf4((char *) obj + 0xce6, i));
        func_02070adc(p, 4, i * 0x28 + 0x8a, 0x14, 0xf, z1, z1);
        func_02070a04(p, z2, z2);
    }
}
