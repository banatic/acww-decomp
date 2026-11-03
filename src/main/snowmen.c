/* snowmen: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b0594 @ 0x020b0594, 0x78 bytes, Thumb
 * func_020b0568 @ 0x020b0568, 0x2a bytes, Thumb
 * func_020b0540 @ 0x020b0540, 0x28 bytes, Thumb
 * func_020b0518 @ 0x020b0518, 0x28 bytes, Thumb
 * func_020b048c @ 0x020b048c, 0x8c bytes, Thumb
 * func_020b0400 @ 0x020b0400, 0x8c bytes, Thumb
 * func_020b03f8 @ 0x020b03f8, 0x8 bytes, Thumb
 * func_020b03c0 @ 0x020b03c0, 0x38 bytes, Thumb
 */

typedef struct {
    unsigned short a : 7;
    unsigned short b : 4;
    unsigned short c : 5;
} Packed;

typedef struct {
    char data[6];
} UnkStruct_020b0568;

typedef struct {
    unsigned char data[5];
    unsigned char flag;
} UnkStruct_020b0540;

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
} Func020b0518Elem;

typedef struct {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
} Hdr;

extern int func_020b0a20(void *p);
extern int func_020b0918(void *p);
extern int func_020b08c0(void *p);
extern int func_020b08b8(void *p);
extern void *func_020984e8(void);
extern void func_02066694(void *);
extern void *func_02062f90(void *, void *);
extern int func_0203d7c4(int, void *);
extern void *func_02099870(void *);
extern void func_02066024(void *, void *, void *, void *, void *, void *);
extern unsigned short func_02065ed0(void *, unsigned short, int);
extern int func_020979f0(void *, int);
extern void *func_02062f4c(void *);
extern void func_02066688(void *);
extern unsigned char data_020e41d4[];
extern unsigned char data_020e41d8[];
extern unsigned char data_020e41dc[];
extern int func_020996ac(void *);
extern int func_0203cdcc(int, void *);
extern int func_020644cc(int);
extern unsigned short data_020d1e74[];
extern int data_021f4ae8;
extern unsigned char data_020e54a8;
extern int func_ov003_022361bc(int a, int b, int c, int d, int e);

int func_020b0594(char *base, unsigned int index, int *out1, int *out2, int *out3, unsigned char *out4, unsigned char *out5,
                  unsigned char *out6)
{
    char *p;

    if (index < 3) {
        p = base + index * 6;
        if (func_020b0a20(p) != 0) {
            if (out1 != 0) {
                *out1 = func_020b0918(p);
            }
            if (out2 != 0) {
                *out2 = func_020b08c0(p);
            }
            if (out3 != 0) {
                *out3 = func_020b08b8(p);
            }
            if (out4 != 0) {
                *out4 = ((Packed *) p)->a;
            }
            if (out5 != 0) {
                *out5 = ((Packed *) (base + index * 6))->b;
            }
            if (out6 != 0) {
                *out6 = ((Packed *) (base + index * 6))->c;
            }
            return 1;
        }
    }
    return 0;
}

int func_020b0568(UnkStruct_020b0568 *arg)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (func_020b0a20(arg + i) == 0) {
            return 0;
        }
    }
    return 1;
}

void func_020b0540(UnkStruct_020b0540 *base, unsigned int index)
{
    if (index < 3) {
        if (func_020b0a20((void *) (&base[index]))) {
            base[index].flag = 0;
        }
    }
}

void func_020b0518(Func020b0518Elem *array)
{
    unsigned int i = 0;
    do {
        array[i].a = 0;
        array[i].b = 0;
        array[i].c = 0;
        array[i].d = 0x800;
        i++;
    } while (i < 2);
}

void func_020b048c(unsigned int idx)
{
    Hdr hdr;
    char a[0x28];
    char b[0x100];
    void *h;

    if (idx >= 0xd) {
        return;
    }
    hdr.h = ((const unsigned short *) data_020d1e74)[idx];
    h = func_020984e8();
    if (h == 0) {
        return;
    }
    func_02066694(b);
    hdr.b = (unsigned char) idx;
    func_02062f90(a, &hdr.h);
    func_0203d7c4(1, a);
    func_02066024(b, &hdr, (void *) data_020e41dc, (void *) data_020e41d4, (void *) data_020e41d8, func_02099870(h));
    func_02065ed0(b, hdr.h, 1);
    func_020979f0(b, 0);
    func_02062f4c(a);
    func_02066688(b);
}

void func_020b0400(void)
{
    unsigned short local[2];
    int count;
    unsigned int i;
    int target;
    void *obj;

    obj = func_020984e8();
    if (obj == 0) {
        return;
    }

    count = 0;
    i = count;
    do {
        local[0] = data_020d1e74[i];
        if (func_0203cdcc(func_020996ac(obj), &local[0]) == 0) {
            count++;
        }
        i++;
    } while (i < 13);

    if (count != 0) {
        target = func_020644cc(count);
        count = 0;
        i = count;
        while (i < 13) {
            local[1] = data_020d1e74[i];
            if (func_0203cdcc(func_020996ac(obj), &local[1]) == 0) {
                if (count == target) {
                    func_020b048c(i);
                    return;
                }
                count++;
            }
            i++;
        }
    }

    func_020b048c(func_020644cc(13));
}

int func_020b03f8(void)
{
    return (int) &data_021f4ae8;
}

int func_020b03c0(int a, int b, int c, int d, short e)
{
    unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0 && d > 0) {
        return func_ov003_022361bc(a, b, c, d, e);
    }
    return 0;
}
