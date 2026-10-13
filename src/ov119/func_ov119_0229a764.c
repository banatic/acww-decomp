/* func_ov119_0229a764 @ 0x0229a764, 0x188 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_020641c8(void *);
extern void func_02064170(void *);
extern void func_02064158(void *);
extern void func_020641b0(void *);
extern void *func_ov119_0229ae50(void *);
extern void *func_ov119_0229bb44(void *);
extern int func_02077c3c(void *);
extern int func_02077e50(int);
extern int func_02077c34(void *);
extern int func_02077c38(void *);
extern int func_02077d6c(int);
extern void func_020a8874(void *, int, int);
extern void func_020a8a70(void *, void *, int, int);
extern void func_020b496c(int, void *);
extern void func_0207094c(void *, int);
extern void func_020708e4(void *, int, int);
extern void func_020a8c1c(void *);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern void func_ov119_0229a8ec(void *, void *, int);

void func_ov119_0229a764(unsigned char *self)
{
    int k;
    int i;
    void *base, *objA, *objB, *entry;
    int incA, incB;
    int j;
    int idx;
    int buf1[8];
    int buf2[7];

    base = func_ov119_0229ae50(self);
    k = self[0x9c] << 3;
    incA = 0x1ce;
    incB = 0x14e;
    j = 0xc3;
    func_020641c8(buf1);
    func_02064170(buf2);

    for (i = 0; i < 8; i++) {
        objA = func_ov119_0229bb44(self);
        objB = func_ov119_0229bb44(self);

        idx = (self + k)[0xbc];
        if (idx < 0x20) {
            entry = (unsigned char *) base + idx * 0x24;
        } else {
            entry = 0;
        }

        if (entry != 0 && func_02077e50(func_02077c3c(entry)) != 0) {
            func_020a8874(buf2, func_02077c34(entry), 6);
            func_020a8a70(buf1, buf2, 0, 0);
            func_020b496c(0, buf1);
            func_0207094c(objA, 0x66);
            func_020708e4(objB, func_02077c38(entry), 6);
            self[0xaf]++;

            if (func_02077d6c(func_02077c3c(entry)) != 0) {
                func_ov119_0229a8ec(self, (unsigned short *) (self + 0xe0c) + j, 0x50);
            } else {
                func_ov119_0229a8ec(self, (unsigned short *) (self + 0xe0c) + j, 0x54);
            }
        } else {
            func_020a8c1c(objA);
            func_020a8c1c(objB);
            func_ov119_0229a8ec(self, (unsigned short *) (self + 0xe0c) + j, 0x10);
        }

        func_02070adc(objA, 4, incA, 0xa, 0xf, 0, 0);
        func_02070a04(objA, 0, 0);
        func_02070adc(objB, 4, incB, 8, 0xf, 0, 0);
        func_02070a04(objB, 0, 0);

        incA += 0x14;
        incB += 0x10;
        k++;
        j += 0x40;
    }

    func_02064158(buf2);
    func_020641b0(buf1);
}
