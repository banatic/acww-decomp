/* func_ov104_0229c3dc @ 0x0229c3dc, 0x17c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char d[0x100];
} UnkStruct_0229c3dc;

typedef struct {
    unsigned char pad_00[0xb0];
    unsigned short b0;
    unsigned short b2;
    unsigned char pad_B4[0xa];
    unsigned char be;
    unsigned char pad_BF[0x2cf5];
    UnkStruct_0229c3dc arr[10];
} UnkStruct_0229c3dc_2;

extern int func_ov104_0229c364(UnkStruct_0229c3dc_2 *o, int mask);
extern void func_ov104_0229c344(UnkStruct_0229c3dc_2 *o, int mask);
extern void func_ov104_0229c354(UnkStruct_0229c3dc_2 *o, int mask);
extern int func_ov104_0229c378(UnkStruct_0229c3dc_2 *o, UnkStruct_0229c3dc *p);
extern int func_0207059c(void);
extern int func_02065e9c(UnkStruct_0229c3dc *p);
extern int func_02065ec0(UnkStruct_0229c3dc *p);
extern int func_020979ac(UnkStruct_0229c3dc *p);

void func_ov104_0229c3dc(UnkStruct_0229c3dc_2 *o)
{
    int v;
    UnkStruct_0229c3dc *p;

    if (func_ov104_0229c364(o, 0x800) == 0) {
        func_ov104_0229c344(o, 0x1000);
        return;
    }
    if (func_ov104_0229c364(o, 0x1000) == 0) {
        return;
    }
    v = 0x18;
    if (func_ov104_0229c364(o, 0x2000) != 0) {
        v = func_0207059c();
        switch (v) {
            case 8:
                return;
            case 11:
                o->b0 |= 0x400;
                func_ov104_0229c344(o, 0x1000);
                func_ov104_0229c344(o, 0x2000);
                return;
            case 9:
            case 10:
                o->b0 |= 0x200;
                o->b2 |= 1 << o->be;
                o->be = o->be + 1;
                func_ov104_0229c344(o, 0x2000);
                break;
        }
    }
    while (o->be < 10) {
        p = &o->arr[o->be];
        if (func_02065e9c(p) == 0 && func_02065ec0(p) == 1) {
            o->b0 |= 0x100;
            if (func_020979ac(p) != 0) {
                if (v == 0xa) {
                    o->b0 |= 0x400;
                    func_ov104_0229c344(o, 0x1000);
                    return;
                }
                if (func_ov104_0229c378(o, p) != 0) {
                    func_ov104_0229c354(o, 0x2000);
                    return;
                }
            } else {
                o->b0 |= 8;
            }
        }
        o->be = o->be + 1;
    }
    func_ov104_0229c344(o, 0x1000);
}
