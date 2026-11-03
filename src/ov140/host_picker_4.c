/* host_picker_4: 9 functions, module ov140
 * mwccarm 1.2/base -O4,s
 * func_ov140_0229ac68 @ 0x0229ac68, 0x8 bytes, Thumb
 * func_ov140_0229ac34 @ 0x0229ac34, 0x34 bytes, Thumb
 * func_ov140_0229ac18 @ 0x0229ac18, 0x1c bytes, Thumb
 * func_ov140_0229abcc @ 0x0229abcc, 0x4c bytes, Thumb
 * func_ov140_0229ab94 @ 0x0229ab94, 0x38 bytes, Thumb
 * func_ov140_0229ab70 @ 0x0229ab70, 0x24 bytes, Thumb
 * func_ov140_0229ab28 @ 0x0229ab28, 0x48 bytes, Thumb
 * func_ov140_0229aa4c @ 0x0229aa4c, 0xdc bytes, Thumb
 * func_ov140_0229a9e4 @ 0x0229a9e4, 0x68 bytes, Thumb
 */

typedef struct UnkStruct_0229ab28 {
    unsigned char pad_00[0x8df];
    unsigned char unk_8DF;
} UnkStruct_0229ab28;

extern void func_020b9ccc(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov139_02299ac0(void *);
extern void func_ov140_0229a100(void *);
extern void func_ov140_0229a460(void *p);
extern void func_ov139_02299a80(void *p);
extern void func_02001c08(unsigned char mode);
extern void func_020029e8(int layer, int priority);
extern void func_020028bc(unsigned int layer, int a, int b, int c);
extern void func_ov139_022999f8(void *);
extern void func_ov139_022999c4(void *);
extern int func_02064af4(const void *, void *, unsigned int);
extern void func_ov140_0229a41c(void *);
extern const unsigned char data_ov140_0229b5b4[];
extern void func_ov139_02299964(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov140_0229a244(UnkStruct_0229ab28 *);
extern void func_ov140_0229a078(UnkStruct_0229ab28 *);
extern void func_ov140_0229a280(UnkStruct_0229ab28 *);
extern void func_ov140_0229a164(UnkStruct_0229ab28 *, int);
extern int func_ov140_0229a384(UnkStruct_0229ab28 *);
extern int func_ov002_02208054(void *, int);
extern void func_ov140_0229a7cc(void *);
extern void func_ov140_0229a3fc(void *, int _x);
extern void func_ov140_0229a73c(void *);
extern void func_ov140_0229a774(void *);
extern void func_ov140_0229a6dc(void *);
extern void func_0200467c(unsigned int);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;
extern int func_ov002_02208014(void *receiver);
extern void func_ov140_0229a7e8(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov140_0229a4a0(void *p, int arg);
extern int func_ov140_0229a614(void *p);
extern void func_ov140_0229a570(void *p);
extern void func_ov140_0229a638(void *p);
extern unsigned short data_021fbe40[2];

void func_ov140_0229ac18(void *p);

void func_ov140_0229ac68(void *argument0)
{
    func_ov140_0229ac18(argument0);
}

void func_ov140_0229ac34(void *self)
{
    func_020b9ccc((char *) self + 0x14bc);
    func_ov002_0220af74((char *) self + 0x12f0);
    func_ov139_02299ac0((char *) self + 0x8e8);
    func_ov140_0229a100(self);
}

void func_ov140_0229ac18(void *p)
{
    func_ov140_0229a460(p);
    func_ov139_02299a80((char *) p + 0x8E8);
}

void func_ov140_0229abcc(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 2);
    func_020028bc(3, 0, 0, 0);
}

void func_ov140_0229ab94(void *self)
{
    func_ov139_022999f8((char *) self + 0x8e8);
    func_ov139_022999c4((char *) self + 0x8e8);
    func_02064af4(data_ov140_0229b5b4, (char *) self + 0xac, 0x800);
    func_ov140_0229a41c(self);
}

void func_ov140_0229ab70(void *arg0)
{
    func_ov139_02299964((void *) ((char *) arg0 + 0x8e8));
    func_ov002_0220af94((void *) ((char *) arg0 + 0x12f0));
}

void func_ov140_0229ab28(UnkStruct_0229ab28 *p)
{
    int x = func_ov140_0229a244(p);

    if (x != p->unk_8DF) {
        p->unk_8DF = x;
        func_ov140_0229a078(p);
        func_ov140_0229a280(p);
        func_ov140_0229a164(p, 5);
    } else if (func_ov140_0229a384(p)) {
        func_ov140_0229a164(p, 5);
    }
}

void func_ov140_0229aa4c(unsigned char *self)
{
    unsigned int flag;
    int y, x;
    int idx;
    unsigned char *base;

    func_ov140_0229ab28((UnkStruct_0229ab28 *) self);
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov140_0229a7cc(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag != 0) {
        y = data_021f6c58;
        x = (int) data_021f6c54 - 0x10;
        if (y >= 0x28 && y < 0xd0 && x >= 0x30 && x < 0x90) {
            idx = (x - 0x30) >> 4;
            base = self + idx;
            if (base[0x8af] != 0 && base[0x8e0] != 4) {
                func_ov140_0229a3fc(self, idx);
                func_0200467c(0x29);
            }
        } else if (x >= 0x96 && x < 0xa7) {
            if (y >= 0x5e && y < 0x9a) {
                func_ov140_0229a73c(self);
            } else if (y >= 0x9f && y < 0xdb) {
                if (*(int *) (self + 0xa0) == 8) {
                    func_ov140_0229a774(self);
                }
            } else if (y >= 0x1d && y < 0x59) {
                if (*(int *) (self + 0xa8) == 8) {
                    func_ov140_0229a6dc(self);
                }
            }
        }
    }
}

void func_ov140_0229a9e4(void *p)
{
    func_ov140_0229ab28((UnkStruct_0229ab28 *) p);
    if (func_ov002_02208014(p) != 0) {
        func_ov140_0229a7e8(p);
        return;
    } else {
        if (func_ov140_0229a4a0(p, func_ov002_02208008(p)) != 0) {
            func_ov140_0229a614(p);
            return;
        } else {
            if (data_021fbe40[1] & 1) {
                func_ov140_0229a570(p);
                return;
            } else if (data_021fbe40[1] & 2) {
                func_ov140_0229a73c(p);
                func_ov140_0229a638(p);
            }
        }
    }
}
