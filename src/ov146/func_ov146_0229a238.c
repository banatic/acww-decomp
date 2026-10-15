/* func_ov146_0229a238 @ 0x0229a238, 0x1c8 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064170(void *);
extern void *func_020641c8(void *);
extern void __register_global_object(void *, void *destructor, void *);
extern unsigned int func_ov146_0229a174(void *);
extern void *func_ov146_0229a42c(void *);
extern void func_020a8c1c(void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_020b496c(void *, void *);
extern int func_0207094c(void *, int);
extern void func_020708e4(void *, void *, int);
extern void func_02070adc(void *, int, int, int, unsigned char, int, int);
extern void func_02070a04(void *, void *, void *);

extern void *func_02064158(void *arg0);
extern void *func_020641b0(void *arg0);

extern int data_ov146_0229b78c;
extern int data_ov146_0229b7a8;
extern int data_ov146_0229b79c;
extern int data_ov146_0229b780;
extern int data_ov146_0229b7e4;
extern int data_ov146_0229b790;

#define DisposeGlobal_func_02064158 ((void *) &func_02064158)

#define DisposeGlobal_func_020641b0 ((void *) &func_020641b0)

void func_ov146_0229a238(char *self)
{
    int val, rem;
    void *val_c, *val_10;
    int i;
    unsigned char *base;
    int c;
    unsigned char *q;

    if ((data_ov146_0229b78c & 1) == 0) {
        func_02064170(&data_ov146_0229b7a8);
        __register_global_object(&data_ov146_0229b7a8, DisposeGlobal_func_02064158, &data_ov146_0229b79c);
        data_ov146_0229b78c |= 1;
    }
    if ((data_ov146_0229b780 & 1) == 0) {
        func_020641c8(&data_ov146_0229b7e4);
        __register_global_object(&data_ov146_0229b7e4, DisposeGlobal_func_020641b0, &data_ov146_0229b790);
        data_ov146_0229b780 |= 1;
    }

    func_ov146_0229a174(self);

    val = *(short *) (self + 0xae);
    rem = val % 7;

    for (i = 0; i < 7; i++) {
        if (val >= 0x20) {
            base = (unsigned char *) (self + rem);
            base[0xbc] = 0x20;
        } else {
            q = (unsigned char *) (self + val);
            c = q[0xea];
            base = (unsigned char *) (self + rem);
            if (c == base[0xbc]) {
                val_c = 0;
            } else if (c >= 0x20) {
                val_c = func_ov146_0229a42c(self);
                func_020a8c1c(val_c);
                val_10 = func_ov146_0229a42c(self);
                func_020a8c1c(val_10);
                base += 0xbc;
                *base = 0x20;
            } else {
                base += 0xbc;
                *base = (unsigned char) c;
                val_c = func_ov146_0229a42c(self);
                c = c * 0x23;
                func_020a8874(&data_ov146_0229b7a8, self + 0x13a + c, 6);
                func_020a8a70(&data_ov146_0229b7e4, &data_ov146_0229b7a8, 0, 0);
                func_020b496c(0, &data_ov146_0229b7e4);
                func_0207094c(val_c, 0x66);
                val_10 = func_ov146_0229a42c(self);
                func_020708e4(val_10, self + 0x12a + c, 6);
            }
            if (val_c != 0) {
                func_02070adc(val_c, 4, 0x11e + rem * 0x14, 0xa, (unsigned char) (0xe - rem), 0xf, 0);
                func_02070a04(val_c, 0, 0);
                func_02070adc(val_10, 4, 0x1d2 + (rem << 4), 8, (unsigned char) (0xe - rem), 0xf, 0);
                func_02070a04(val_10, 0, 0);
            }
        }
        val++;
        rem++;
        if (rem >= 7) {
            rem = 0;
        }
    }
}

#undef DisposeGlobal_func_02064158
#undef DisposeGlobal_func_020641b0
