/* boot_screen: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5724 @ 0x020b5724, 0x70 bytes, Thumb
 * func_020b56a8 @ 0x020b56a8, 0x7c bytes, Thumb
 * func_020b5678 @ 0x020b5678, 0x30 bytes, Thumb
 * func_020b5650 @ 0x020b5650, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
    unsigned char unk_5D;
    unsigned char unk_5E;
    unsigned char pad_5F;
    unsigned char pad_60[4];
    unsigned int unk_64;
    unsigned int unk_68;
} UnkStruct_020b5724;

extern int func_020a16e0(void);
extern void MI_CpuCopy8(unsigned int, unsigned int, unsigned int);
extern unsigned char data_021dc7a8[];
extern void func_0205cacc(int, int);
extern int func_0209fb28(void *);
extern void func_020a01d4(int);
extern int func_020a16b0(void);
extern void func_0209ef7c(void *);
extern void func_02098540(void);
extern void func_020792c8(void);
extern void func_0209e6ec(void *, int);
extern void func_0209e604(void *);
extern void func_020792b4(void);
extern void func_0205cab0(void);
extern char data_021f3ba0[];
extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5320[];

void func_020b5724(UnkStruct_020b5724 *p)
{
    unsigned char a = p->unk_5C;

    if (a == 1 || p->unk_5D == 1) {
        p->unk_5E = 1;
        return;
    }

    if (a != 0 && p->unk_5D != 0) {
        p->unk_5E = 4;
        return;
    }

    {
        int cond;

        if (a != 0) {
            cond = 1;
        } else if (p->unk_5D != 0) {
            cond = 0;
        } else {
            cond = func_020a16e0();
        }

        if (cond == 0) {
            MI_CpuCopy8(p->unk_64, (unsigned int) data_021dc7a8, 0x173fc);
        } else {
            MI_CpuCopy8(p->unk_68, (unsigned int) data_021dc7a8, 0x173fc);
        }

        p->unk_5E = 0;
    }
}

void func_020b56a8(int param)
{
    int r4 = param;
    int r0;
    int r1;

    func_0205cacc(0x5000, 0);
    r0 = r4;
    r0 += 0x5e;
    r0 = *(unsigned char *) r0;
    if (r0 == 4 || r0 == 1) {
        if (r0 == 4) {
            if (func_0209fb28(data_021f3ba0) == 0) {
                func_020a01d4(1);
            }
        }
        r4 += 0x5e;
        r0 = *(unsigned char *) r4;
        if (r0 == 4) {
            func_020a16b0();
        }
        func_0209ef7c(((char *) data_021dc7a8));
        func_02098540();
        func_020792c8();
        func_0209e6ec(((char *) data_021dc7a8), 3);
    } else {
        func_0209e6ec(((char *) data_021dc7a8), 4);
    }
    func_0209e604(((char *) data_021dc7a8));
    func_020792b4();
    func_0205cab0();
}

void *func_020b5678(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020e5320;
    *(volatile unsigned int *) p = (unsigned int) data_020e3c94;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

void *func_020b5650(void *p)
{
    volatile unsigned int *q = p;
    *q = (unsigned int) ((int *) data_020e5320);
    *q = (unsigned int) ((int *) data_020e3c94);
    *q = (unsigned int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}
