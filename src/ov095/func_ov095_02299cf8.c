/* func_ov095_02299cf8 @ 0x02299cf8, 0x188 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    int unk_28;
} UnkStruct_02299cf8;

extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_0220889c(void *in);
extern void func_ov095_0229a9d4(UnkStruct_02299cf8 *o);

int func_ov095_02299cf8(UnkStruct_02299cf8 *o, void *in)
{
    int v;

    v = o->unk_28;
    if (v == 0x103) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_28 = 0x10a;
        }
        return 1;
    }
    switch (v) {
        case 0x104:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0x2c;
                        break;
                    case 1:
                        o->unk_28 = 0x6e;
                        break;
                    case 2:
                        o->unk_28 = 0x90;
                        break;
                    case 3:
                        o->unk_28 = 0xc8;
                        break;
                    case 4:
                        o->unk_28 = 0xf6;
                        break;
                }
            } else if (func_ov002_022088ac(in) != 0) {
                func_ov095_0229a9d4(o);
            }
            return 1;
        case 0x105:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0xe;
                        break;
                    case 1:
                        o->unk_28 = 0x69;
                        break;
                    case 2:
                        o->unk_28 = 0x91;
                        break;
                    case 3:
                        o->unk_28 = 0xc0;
                        break;
                    case 4:
                        o->unk_28 = 0xf4;
                        break;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x104;
            }
            return 1;
        case 0x106:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0x13;
                        break;
                    case 1:
                        o->unk_28 = 0x6b;
                        break;
                    case 2:
                        o->unk_28 = 0x91;
                        break;
                    case 3:
                        o->unk_28 = 0xc2;
                        break;
                    case 4:
                        o->unk_28 = 0xf4;
                        break;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x104;
            }
            return 1;
    }
    if (v == 0x105 || v == 0x106) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_28 = 0x103;
        } else if (func_ov002_0220889c(in) != 0) {
            o->unk_28 = 0x104;
        }
        return 1;
    }
    return 0;
}
