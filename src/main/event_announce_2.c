/* event_announce_2: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02041788 @ 0x02041788, 0x24 bytes, Thumb
 * func_02041718 @ 0x02041718, 0x70 bytes, Thumb
 * func_02041644 @ 0x02041644, 0xd4 bytes, Thumb
 * func_0204162c @ 0x0204162c, 0x16 bytes, Thumb
 * func_02041620 @ 0x02041620, 0xc bytes, Thumb
 * func_02041614 @ 0x02041614, 0xc bytes, Thumb
 * func_02041608 @ 0x02041608, 0xc bytes, Thumb
 * func_02041604 @ 0x02041604, 0x2 bytes, Thumb
 * func_020415e8 @ 0x020415e8, 0x1c bytes, Thumb
 * func_020415d0 @ 0x020415d0, 0x18 bytes, Thumb
 * func_020415a8 @ 0x020415a8, 0x28 bytes, Thumb
 * func_020414e0 @ 0x020414e0, 0xc8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_02041718;

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Eight;

struct UnkStruct_020414e0 {
    unsigned char unk_00;
    unsigned char _p1;
    unsigned char unk_02;
    unsigned char _p3;
    unsigned char unk_04;
    unsigned char _p5[3];
    int unk_08;
};

extern unsigned int data_020ccf94;
extern void func_020417ac(void);
extern int func_02073d90(unsigned int);
extern volatile unsigned char data_021c75b8;
extern int func_020b65c4(void);
extern int func_020a6c98(int);
extern UnkStruct_02041718 *data_021f42f4;
extern int data_020db6e4;
extern int data_020db6e0;
extern int data_020db6dc;
extern unsigned char data_020ca508[];
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0203fcb4(int, void *, int);
extern void func_0204130c(int, int, int);
extern int data_021c7590;
extern int func_0206e980(void);
extern unsigned char data_021c75a0[];
extern void func_020413f8(int);
extern int func_0203e37c(void);
extern int func_0203e370(void);
extern int func_0203e364(void);
extern int func_0204e414(void);
extern int func_0204df68(int, void *);
extern int func_0204e188(int, void *, int, int);
extern int func_020b5e10(void);
extern int func_020b5ee4(int, int);
extern int func_020b63f4(int, int, void *, int, int, int, int);
extern void func_02035c64(int, int, int);
extern int data_021c526c;
extern int data_021c758c;

void func_02041644(void);

void func_02041788(void)
{
    func_020417ac();
    if (func_02073d90(data_020ccf94) == 0) {
        func_02041644();
    }
}

int func_02041718(void)
{
    int flag;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag == 0) {
        return 0;
    }
    if (func_020b65c4() == 0x3f) {
        return 0;
    }
    if (func_020b65c4() == 0x2c) {
        return 0;
    }
    if (func_020b65c4() == 6) {
        return 0;
    }
    if (func_020a6c98((int) func_020b65c4()) != 0) {
        return 0;
    }
    if (data_021f42f4 != 0) {
        if (data_021f42f4->unk_0C != 6) {
            return 0;
        }
    }
    return 1;
}

void func_02041644(void)
{
    int x;
    Eight a, b, c;
    int i, zero;

    a.unk_00 = 0;
    a.w1 = 0;
    func_0209e474(&a);

    if (data_020db6e4 == 0x63) {
        i = 0;
        x = i;
        zero = i;
        do {
            int r;
            unsigned char ch;

            MI_CpuCopy8(&a, &b, 8);
            ch = data_020ca508[i];
            r = func_0203fcb4(ch, &b, zero);
            switch (r) {
                case 2:
                    if (ch == 0x13) {
                        data_020db6e4 = ch;
                        data_020db6e0 = ch;
                    } else {
                        if (((unsigned char *) &a)[2] < 6) {
                            data_020db6e0 = ch;
                        } else {
                            func_0204130c(ch, ch, x);
                        }
                    }
                    break;
                case 3:
                    if (ch == 0x12) {
                        data_020db6e4 = 0x12;
                        data_020db6e0 = 0x12;
                        data_020db6dc = 0x12;
                    }
                    break;
                default:
                    break;
            }
            i++;
        } while (i < 11);
    }

    if (data_020db6e0 != 0x63) {
        MI_CpuCopy8(&a, &c, 8);
        if (func_0203fcb4(data_020db6e0, &c, 0) == 0) {
            if (data_020db6e0 == 0x13) {
                data_020db6e4 = 0x63;
                data_020db6e0 = 0x63;
            } else {
                func_0204130c(data_020db6e0, 0x63, 1);
            }
        }
    }
}

void func_0204162c(void)
{
    if (func_02041718()) {
        func_02041644();
    }
}

int func_02041620(void)
{
    return data_021c7590;
}

unsigned int func_02041614(void)
{
    return (*(unsigned int *) &data_020db6dc);
}

unsigned int func_02041608(void)
{
    return (*(unsigned int *) &data_020db6e0);
}

void func_02041604(void *receiver) {}

void func_020415e8(void *receiver)
{
    if (func_0206e980() != 0) {
        *((volatile unsigned char *) data_021c75a0) = 2;
    }
}

void func_020415d0(void *receiver)
{
    int result;
    result = func_0206e980();
    if (result == 0) {
        func_020413f8(3);
    }
}

int func_020415a8(void)
{
    int ret = 0;

    if (func_0203e37c() == 0) {
        data_021c75a0[0] = 0;
        data_021c75a0[2] = 0;
    } else {
        ret = 1;
        data_021c75a0[2] = 1;
    }
    return ret;
}

void func_020414e0(void *receiver)
{
    unsigned int local[4];
    int r0;

    if (func_0203e370() == 0) {
        if (func_0203e37c() == 0) {
            (*(struct UnkStruct_020414e0 *) data_021c75a0).unk_00 = 0;
            (*(struct UnkStruct_020414e0 *) data_021c75a0).unk_02 = 0;
        }
        return;
    }

    r0 = (*(struct UnkStruct_020414e0 *) data_021c75a0).unk_08;
    data_020db6e4 = r0;
    data_020db6e0 = r0;

    if (func_0203e364() == 0) {
        return;
    }
    if (func_0206e980() != 0) {
        return;
    }

    r0 = func_0204e414();
    if (r0 == 0) {
        return;
    }

    if ((*(struct UnkStruct_020414e0 *) data_021c75a0).unk_04 == 0xe) {
        r0 = func_0204df68(r0, local);
    } else {
        r0 = func_0204e188(r0, local, 0, 0);
    }
    if (r0 == 0) {
        return;
    }

    r0 = func_020b5e10();
    func_020b5ee4(r0, 0);
    r0 = func_020b5e10();
    func_020b63f4(r0, 0x31, local, 0x400000, 0, 2, 2);
    func_02035c64(data_021c526c + 0x2d0, data_021c758c, (*(struct UnkStruct_020414e0 *) data_021c75a0).unk_04);
    (*(struct UnkStruct_020414e0 *) data_021c75a0).unk_00 = 4;
    data_021c7590 = 1;
}
