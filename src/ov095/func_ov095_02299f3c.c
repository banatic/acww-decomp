/* func_ov095_02299f3c @ 0x02299f3c, 0x1f8 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0xf];
    int unk_28;
    int unk_2C;
    unsigned char pad_30[0x13];
    unsigned char unk_43;
} UnkStruct_02299f3c;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern void func_ov095_0229a184(UnkStruct_02299f3c *o, int a);
extern void func_ov095_0229a280(UnkStruct_02299f3c *o);

int func_ov095_02299f3c(UnkStruct_02299f3c *o, void *in)
{
    switch (o->unk_28) {
        case 0xf8:
        case 0xf9:
        case 0xfa:
            if (func_ov002_0220889c(in) != 0) {
                if (o->unk_28 < 0xfa) {
                    o->unk_28 = o->unk_28 + 1;
                } else if (o->unk_18 != 0) {
                    o->unk_28 = 0x10c;
                } else {
                    o->unk_28 = 0x10a;
                }
                return 1;
            }
            if (func_ov002_022088ac(in) != 0) {
                if (o->unk_28 > 0xf8) {
                    o->unk_28 = o->unk_28 - 1;
                } else {
                    o->unk_28 = 0x109;
                }
                return 1;
            }
            if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184(o, o->unk_2C);
            } else if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280(o);
            }
            return 1;
        case 0x109:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280(o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184(o, o->unk_2C);
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0xf8;
            } else if (func_ov002_022088ac(in) != 0) {
                o->unk_28 = 0x10a;
                o->unk_43 = 1;
            }
            return 1;
        case 0x10a:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280(o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184(o, o->unk_2C);
            } else if (func_ov002_022088ac(in) != 0) {
                if (o->unk_18 != 0) {
                    o->unk_28 = o->unk_18 + 0x10b;
                } else {
                    o->unk_28 = 0xfa;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x109;
                o->unk_43 = 2;
            }
            return 1;
        case 0x10c:
        case 0x10d:
        case 0x10e:
        case 0x10f:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280(o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184(o, o->unk_2C);
            } else if (func_ov002_022088ac(in) != 0) {
                if (o->unk_28 > 0x10c) {
                    o->unk_28 = o->unk_28 - 1;
                } else {
                    o->unk_28 = 0xfa;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                if (o->unk_28 < o->unk_18 + 0x10b) {
                    o->unk_28 = o->unk_28 + 1;
                } else {
                    o->unk_28 = 0x10a;
                }
            }
            return 1;
    }
    return 0;
}
