/* func_ov141_0229a6e4 @ 0x0229a6e4, 0x90 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a6e4 {
    unsigned char pad_00[0x1274];
    unsigned int unk_1274;
};

struct GlobalType {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern struct GlobalType data_021fbe40;
extern int func_ov002_02208014(struct UnkStruct_0229a6e4 *p);
extern int func_ov002_02208008(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a59c(struct UnkStruct_0229a6e4 *p);
extern int func_ov141_0229a2c4(struct UnkStruct_0229a6e4 *p, int arg);
extern void func_ov141_0229a428(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a384(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a44c(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a4e8(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a524(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a174(struct UnkStruct_0229a6e4 *p);

void func_ov141_0229a6e4(struct UnkStruct_0229a6e4 *p)
{
    if (func_ov002_02208014(p) != 0) {
        func_ov141_0229a59c(p);
        return;
    }
    if (func_ov141_0229a2c4(p, func_ov002_02208008(p)) != 0) {
        func_ov141_0229a428(p);
        return;
    }
    {
        unsigned short f = data_021fbe40.flags;
        if ((f & 1) != 0) {
            func_ov141_0229a384(p);
            return;
        }
        if ((f & 2) != 0) {
            func_ov141_0229a44c(p);
            func_ov141_0229a4e8(p);
            return;
        }
        if (((f & 8) != 0) && (p->unk_1274 == 8)) {
            func_ov141_0229a44c(p);
            func_ov141_0229a524(p);
            return;
        }
        func_ov141_0229a174(p);
    }
}
