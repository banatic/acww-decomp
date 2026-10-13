/* func_ov142_0229a9bc @ 0x0229a9bc, 0x1ac bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc4];
    unsigned short c4;
    char pad_C6[0xd6 - 0xc6];
    short d6;
    char pad_D8[0x9d8 - 0xd8];
    unsigned short arr[1];
} UnkStruct_0229a9bc;

extern int func_020984e8(void);
extern int func_0204c2b4(volatile unsigned short *);
extern int func_020996ac(int);
extern int func_0203cdcc(int, volatile unsigned short *);

void func_ov142_0229a9bc(UnkStruct_0229a9bc *self)
{
    int i;
    unsigned int f1, f2, f3, f4, f5, f6, f7, f8, f9;
    volatile unsigned short v;
    unsigned short a, b;
    int ctx;
    int n;
    unsigned short id;

    n = 0;
    self->c4 = 0;
    self->d6 = 0;
    id = 0x3000;
    v = 0xfff1;
    ctx = func_020984e8();

    for (i = 0; i < 0x6e9; i++) {
        v = id;
        f1 = 0;
        a = v;
        b = v;
        if (b >= 0x45dc && a <= 0x47d7) {
            f1 = 1;
        }
        if (f1 == 0) {
            f2 = 0;
            if (a >= 0x4384 && a <= 0x4463) {
                f2 = 1;
            }
            if (f2 == 0) {
                f3 = 0;
                if (a >= 0x42a4 && a <= 0x4383) {
                    f3 = 1;
                }
                if (f3 == 0) {
                    f4 = 0;
                    if (a >= 0x3e24 && a <= 0x3ea3) {
                        f4 = 1;
                    }
                    if (f4 == 0) {
                        f5 = 0;
                        if (a >= 0x3984 && a <= 0x3d83) {
                            f5 = 1;
                        }
                        if (f5 == 0) {
                            f6 = 0;
                            if (a >= 0x450c && a <= 0x45db) {
                                f6 = 1;
                            }
                            if (f6 == 0) {
                                f7 = 0;
                                if (a >= 0x3fa4 && a <= 0x40a3) {
                                    f7 = 1;
                                }
                                if (f7 == 0) {
                                    f8 = 0;
                                    if (a >= 0x4124 && a <= 0x4223) {
                                        f8 = 1;
                                    }
                                    if (f8 == 0) {
                                        f9 = 0;
                                        if (a >= 0x40a4 && a <= 0x4123) {
                                            f9 = 1;
                                        }
                                        if (f9 == 0) {
                                            if (func_0204c2b4(&v) != 0) {
                                                self->d6 = (short) (self->d6 + 1);
                                                if (func_0203cdcc(func_020996ac(ctx), &v) != 0) {
                                                    self->arr[n] = id;
                                                    n++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        id = id + 4;
    }
    self->c4 = n;
}
