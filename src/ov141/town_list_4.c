/* town_list_4: 2 functions, module ov141
 * mwccarm 1.2/base -O4,s
 * func_ov141_0229a774 @ 0x0229a774, 0xc0 bytes, Thumb
 * func_ov141_0229a6e4 @ 0x0229a6e4, 0x90 bytes, Thumb
 */

struct UnkStruct_0229a6e4 {
    unsigned char pad_00[0x1274];
    unsigned int unk_1274;
};

struct GlobalType {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern int func_ov002_02208054(void *self, int flag);
extern void func_ov141_0229a580(void *self);
extern void func_ov141_0229a174(void *self);
extern int func_ov141_02299f94(void *self, int _x);
extern void func_ov141_0229a4e8(void *self);
extern void func_ov141_0229a524(void *self);
extern void func_0200467c(int cmd);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern struct GlobalType data_021fbe40;
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a59c(struct UnkStruct_0229a6e4 *p);
extern int func_ov141_0229a2c4(struct UnkStruct_0229a6e4 *p, int arg);
extern void func_ov141_0229a428(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a384(struct UnkStruct_0229a6e4 *p);
extern void func_ov141_0229a44c(struct UnkStruct_0229a6e4 *p);

void func_ov141_0229a774(void *self)
{
    unsigned int cond;
    int x;
    int y;

    if (func_ov002_02208054(self, 1)) {
        func_ov141_0229a580(self);
        return;
    }

    cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (cond) {
        y = (int) data_021f6c58;
        x = (int) data_021f6c54 - 0x10;
        if (y >= 0x28 && y < 0xd0 && x >= 0x30 && x < 0x90) {
            int idx;
            idx = (x - 0x30) >> 4;
            if (((unsigned char *) self + idx)[0x1a7f] == 0) {
                return;
            }
            if (!func_ov141_02299f94(self, idx)) {
                return;
            }
            func_0200467c(0x29);
        } else if (x >= 0x96 && x < 0xa7) {
            if (y >= 0x37 && y < 0x7b) {
                func_ov141_0229a4e8(self);
            } else if (y >= 0x89 && y < 0xc5) {
                if (*(int *) ((char *) self + 0x1274) == 8) {
                    func_ov141_0229a524(self);
                }
            }
        }
    } else {
        func_ov141_0229a174(self);
    }
}

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
            func_ov141_0229a4e8((void *) p);
            return;
        }
        if (((f & 8) != 0) && (p->unk_1274 == 8)) {
            func_ov141_0229a44c(p);
            func_ov141_0229a524((void *) p);
            return;
        }
        func_ov141_0229a174((void *) p);
    }
}
