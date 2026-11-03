/* sky_2: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba6f4 @ 0x020ba6f4, 0x98 bytes, Thumb
 * func_020ba6b8 @ 0x020ba6b8, 0x3c bytes, Thumb
 * func_020ba540 @ 0x020ba540, 0x178 bytes, Thumb
 * func_020ba518 @ 0x020ba518, 0x28 bytes, Thumb
 * func_020ba4e4 @ 0x020ba4e4, 0x34 bytes, Thumb
 * func_020ba4d4 @ 0x020ba4d4, 0x10 bytes, Thumb
 * func_020ba4c4 @ 0x020ba4c4, 0x10 bytes, Thumb
 * func_020ba4b8 @ 0x020ba4b8, 0xc bytes, Thumb
 * func_020ba4a0 @ 0x020ba4a0, 0x18 bytes, Thumb
 * func_020ba494 @ 0x020ba494, 0xc bytes, Thumb
 * func_020ba488 @ 0x020ba488, 0xc bytes, Thumb
 * func_020ba3bc @ 0x020ba3bc, 0xcc bytes, Thumb
 * func_020ba3ac @ 0x020ba3ac, 0x10 bytes, Thumb
 * func_020ba39c @ 0x020ba39c, 0x10 bytes, Thumb
 * func_020ba38c @ 0x020ba38c, 0x10 bytes, Thumb
 * func_020ba37c @ 0x020ba37c, 0x10 bytes, Thumb
 * func_020ba36c @ 0x020ba36c, 0x10 bytes, Thumb
 */

typedef struct {
    char pad_00[8];
    unsigned char b;
    char pad_09[3];
} UnkStruct_020ba6b8;

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x0c];
    int unk_34;
} Unk021F8AB0;

struct UnkStruct_020ba4c4 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned int unk_28;
};

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned char pad_2C[0x38];
    unsigned int unk_64;
    unsigned char pad_68[0x04];
    unsigned int unk_6C;
} UnkStruct_020ba4a0;

struct UnkStruct_020ba494 {
    unsigned char pad_00[0x3c];
    unsigned short unk_3C;
};

extern void *data_021fbe94;
extern unsigned char data_020d22b8[];
extern char data_020e7aa8[];
extern char data_020e7abc[];
extern char data_021f7280[];
extern int func_02002c6c(void *, void *, unsigned char, int, int, int);
extern void *func_020e9958(void *, int);
extern int func_02064af4(void *, void *, int);
extern void func_020b0f54(void *);
extern int func_02002b40(void *, unsigned char, int, int);
extern void func_020e993c(void *, void *);
extern void func_020b177c(void *, unsigned char);
extern void func_020becbc(void *addr, int value);
extern void func_020be388(void *addr);
extern void func_020bde5c(void *addr);
extern unsigned char data_021fa678[];
extern char data_021fba00[];
extern char data_021f8b48[];
extern void func_02001c08(int);
extern void func_02001c30(int);
extern void func_0209def4(unsigned char *);
extern void func_02001afc(int);
extern void func_02001b0c(int);
extern void func_02001b34(int);
extern void func_02001b44(int);
extern void *func_0205bfd0(int, int, void *);
extern int func_020961a8(int);
extern int func_020ba86c(int);
extern int func_020ba78c(int);
extern int data_021f8b44;
extern void func_020babb4(void);
extern void func_020bad44(void);
extern unsigned char data_021f6d2c[];
extern void func_01ffcd50(void);
extern void func_01ffceb8(void);
extern void func_01ffcd4c(void);
extern void func_020bab74(void);
extern int func_020bb6b0(void *param1, int param2);
extern unsigned char data_021f75b0[];
extern unsigned short data_021f8ab0[];
extern void func_0209e474(void *);
extern int func_020bb1d4(void *, void *);
extern void func_0209e100(void *, int);
extern int func_020bb214(void *, void *);
extern void MI_CpuCopy8(void *, const void *, int);
extern void func_0209e29c(void *, int);
extern void func_0209e234(void *, int);
extern int func_0209e3ac(void *, const void *, int);
extern void func_020bbc90(void *arg);
extern void func_020bdfd8(int a, int b);

int func_020ba6f4(int idx)
{
    void *gptr;
    unsigned char byte;
    void *buf;

    gptr = data_021fbe94;
    byte = data_020d22b8[idx];

    if (func_02002c6c(data_020e7aa8, gptr, byte, 0x10, 0x10, 0x1f) == 0) {
        return 0;
    }

    buf = func_020e9958(gptr, 0x1000);
    if (buf == 0) {
        return 0;
    }

    func_02064af4(data_020e7abc, buf, 0x1000);
    func_020b0f54(buf);

    if (func_02002b40(buf, byte, 0x1000, 0) == 0) {
        func_020e993c(gptr, buf);
        return 0;
    } else {
        func_020e993c(gptr, buf);
        func_020b177c(data_021f7280, byte);
        return 1;
    }
}

void func_020ba6b8(void)
{
    UnkStruct_020ba6b8 *p = (UnkStruct_020ba6b8 *) data_021fa678;
    int i = 0;
    unsigned char val = (unsigned char) i;
    do {
        p->b = val;
        p++;
        i++;
    } while (i < 5);
    func_020becbc(data_021fba00, -1);
    func_020be388(data_021f8b48);
    func_020bde5c(data_021f8b48);
}

int func_020ba540(int param)
{
    int result = 0;
    unsigned char data[8];

    if (param == 0) {
        func_02001c08(1);
        func_0209def4(data);
        if (data[1] >= 6 && data[1] < 0x12) {
            func_02001afc(2);
        } else {
            func_02001b0c(2);
        }
        func_02001b0c(0x10);
        func_02001b0c(8);

        *(volatile unsigned short *) 0x0400100a = (*(volatile unsigned short *) 0x0400100a & ~3) | 3;
        *(volatile unsigned short *) 0x0400100e = (*(volatile unsigned short *) 0x0400100e & ~3) | 2;
        *(volatile unsigned short *) 0x0400100a = (*(volatile unsigned short *) 0x0400100a & 0x43) | 0x4c00;
        *(volatile unsigned short *) 0x0400100e = (*(volatile unsigned short *) 0x0400100e & 0x43) | 0x6f00;

        func_0205bfd0((unsigned int) data_021f6d2c, (unsigned int) func_01ffceb8, (void *) func_020bad44);
    } else {
        func_02001c30(1);
        func_0209def4(data);
        if (data[1] >= 6 && data[1] < 0x12) {
            func_02001b34(2);
        } else {
            func_02001b44(2);
        }
        func_02001b44(0x10);
        func_02001b44(8);

        *(volatile unsigned short *) 0x0400000a = (*(volatile unsigned short *) 0x0400000a & ~3) | 3;
        *(volatile unsigned short *) 0x0400000e = (*(volatile unsigned short *) 0x0400000e & ~3) | 2;
        *(volatile unsigned short *) 0x0400000a = (*(volatile unsigned short *) 0x0400000a & 0x43) | 0x4400;
        *(volatile unsigned short *) 0x0400000e = (*(volatile unsigned short *) 0x0400000e & 0x43) | 0x6700;

        func_0205bfd0((unsigned int) data_021f6d2c, (unsigned int) func_01ffcd50, (void *) func_020babb4);
    }

    if (param != (*(int *) data_021f75b0) || param == 1) {
        if (func_020ba86c(param) && func_020ba78c(param) && func_020ba6f4(param)) {
            (*(int *) data_021f75b0) = param;
            func_020ba6b8();
            result = 1;
        }
    }

    {
        int *p = (int *) func_020961a8(4);
        int *tail = &data_021f8b44;
        *tail = 0;
        if (p != 0) {
            p = (int *) ((char *) p + 0x5c);
            if (p != 0) {
                *tail = *(int *) ((char *) p + 8);
            }
        }
    }

    return result;
}

void func_020ba518(void)
{
    func_0205bfd0((int) ((void *) data_021f6d2c), (int) ((void *) func_01ffcd4c), (void *) func_020bab74);
    func_02001b34(0xa);
}

int func_020ba4e4(void)
{
    switch ((*(Unk021F8AB0 *) data_021f8ab0).unk_24) {
        case 2:
        case 3:
        case 4:
            switch ((*(Unk021F8AB0 *) data_021f8ab0).unk_34) {
                case 1:
                    return 1;
                case 2:
                    return 2;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

int func_020ba4d4(void)
{
    return func_020bb6b0((void *) data_021f75b0, 0);
}

void func_020ba4c4(unsigned int *out0, unsigned int *out1)
{
    *out0 = (*(struct UnkStruct_020ba4c4 *) data_021f8ab0).unk_24;
    *out1 = (*(struct UnkStruct_020ba4c4 *) data_021f8ab0).unk_28;
}

int func_020ba4b8(void)
{
    return (*(struct UnkStruct_020ba4b8 { char pad_00[0x34]; int value; } *) data_021f8ab0).value;
}

unsigned int func_020ba4a0(void)
{
    if ((*(UnkStruct_020ba4a0 *) data_021f8ab0).unk_28 != (*(UnkStruct_020ba4a0 *) data_021f8ab0).unk_24) {
        return (*(UnkStruct_020ba4a0 *) data_021f8ab0).unk_6C;
    } else {
        return (*(UnkStruct_020ba4a0 *) data_021f8ab0).unk_64;
    }
}

unsigned short func_020ba494(void)
{
    return (*(struct UnkStruct_020ba494 *) data_021f8ab0).unk_3C;
}

unsigned short func_020ba488(void)
{
    return data_021f8ab0[31];
}

void func_020ba3bc(unsigned char *dst, int num, int idx)
{
    int local[2];
    int ret;

    local[0] = 0;
    local[1] = 0;

    func_0209e474(local);
    func_020bb1d4(((unsigned char *) data_021f75b0), local);
    func_0209e100(local, 6);
    ret = func_020bb214(((unsigned char *) data_021f75b0), local);
    MI_CpuCopy8(local, dst, 8);

    if (num < 0) {
        num += 0x200;
    }
    if (num < ret) {
        num += 0x200;
    }

    func_0209e29c(dst, (num - ret) / 8);

    if (idx < 0) {
        idx = 0;
    } else if (idx > 0x68) {
        idx = 0x68;
    }

    dst[2] = 0x12;
    dst[1] = 0;
    dst[0] = 0;

    func_0209e234(dst, idx * 0x2d0 / 0x68);

    if (dst[2] == 6) {
        func_0209e100(dst, 1);
    }

    func_0209e474(local);
    func_0209e234(local, 0x1e);

    if (func_0209e3ac(local, dst, 0x3c) == 1) {
        func_0209e29c(dst, 0x40);
    }
}

void func_020ba3ac(void)
{
    func_020bbc90(((char *) data_021f75b0));
}

void func_020ba39c(void)
{
    func_020bbc90(((int *) data_021f75b0));
}

void func_020ba38c(void)
{
    func_020bbc90((void *) data_021f75b0);
}

void func_020ba37c(void)
{
    func_020bbc90((void *) ((unsigned int) data_021f75b0));
}

void func_020ba36c(int arg)
{
    func_020bdfd8((unsigned int) ((unsigned char *) data_021f8b48), arg);
}
