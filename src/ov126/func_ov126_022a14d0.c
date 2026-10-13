/* func_ov126_022a14d0 @ 0x022a14d0, 0x1dc bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    int unk_A0;
    short unk_A4;
    unsigned char unk_A6;
    unsigned char pad_A7[4];
    unsigned char unk_AB;
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char pad_AE;
    unsigned char unk_AF;
    unsigned char unk_B0[0xec];
    unsigned char unk_19C[0x40ac];
    unsigned char unk_4248[0x20];
    unsigned char unk_4268[0x20];
} UnkStruct_022a14d0;

extern int func_0206fca4(void);
extern void func_ov126_0229f7b8(UnkStruct_022a14d0 *o, int a);
extern void func_ov095_0229c084(void *p, int a);
extern int func_ov124_0229f27c(void *p);
extern void func_02051bf8(void *p, int a);
extern int func_02051ca8(void *p, int a);
extern void func_ov126_0229fb9c(UnkStruct_022a14d0 *o);

void func_ov126_022a14d0(UnkStruct_022a14d0 *o)
{
    int v;

    o->unk_A4 = 0;
    o->unk_A0 = 0;
    v = func_0206fca4();
    switch (v) {
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x1a:
            o->unk_AD = 2;
            break;
        case 0x19:
        case 0x1b:
            func_ov126_0229f7b8(o, 0x20);
            o->unk_AD = 0;
            break;
    }
    switch (o->unk_AD) {
        case 0:
            func_ov095_0229c084(o->unk_19C, 5);
            break;
        case 1:
        case 2:
            func_ov095_0229c084(o->unk_19C, 4);
            break;
        case 3:
            func_ov095_0229c084(o->unk_19C, 3);
            break;
    }
    switch (func_ov124_0229f27c(o->unk_B0)) {
        case 0:
            o->unk_A6 = 0xa;
            o->unk_AB = 0x52;
            o->unk_AC = 0xb8;
            o->unk_AF = 0x68;
            break;
        case 1:
            o->unk_A6 = 6;
            o->unk_AB = 0x62;
            o->unk_AC = 0xa0;
            o->unk_AF = 0x40;
            break;
        case 2:
            o->unk_A6 = 0x10;
            o->unk_AB = 0x30;
            o->unk_AC = 0xd0;
            o->unk_AF = 0xa0;
            break;
        case 3:
            o->unk_A6 = 4;
            o->unk_AB = 0x68;
            o->unk_AC = 0x90;
            o->unk_AF = 0x28;
            break;
        case 4:
            o->unk_A6 = 8;
            o->unk_AB = 0x58;
            o->unk_AC = 0xa8;
            o->unk_AF = 0x50;
            break;
    }
    func_02051bf8(o->unk_4248, 0x10);
    func_02051bf8(o->unk_4268, 0x10);
    func_ov126_0229fb9c(o);
    if (func_02051ca8(o->unk_4248, o->unk_A6) == 0) {
        func_02051bf8(o->unk_4248, 0x10);
    }
    if (v == 0x10 || v == 0x18 || v == 0x19 || v == 0x12) {
        func_ov126_0229f7b8(o, 0x100);
    }
}
