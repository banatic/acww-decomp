/* func_ov147_02299e5c @ 0x02299e5c, 0x160 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299e5c;

extern unsigned short data_021fbe40[2];
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021c75b8;

extern void func_0208ffcc(void);
extern void func_0208ffc0(void);
extern int func_020e8840(unsigned short *p);
extern void func_ov147_02299154(struct UnkStruct_02299e5c *p);
extern void func_ov147_02299134(struct UnkStruct_02299e5c *p);
extern void func_ov147_0229a628(unsigned char *p);
extern void func_ov147_0229a630(unsigned char *p, unsigned int arg);
extern void func_ov147_02299fc8(struct UnkStruct_02299e5c *self, unsigned int arg);

struct UnkStruct_02299e5c {
    unsigned char pad_00[0xa2];
    unsigned char unk_A2;
    unsigned char pad_A3[0x07];
    unsigned char unk_AA;
    unsigned char unk_AB;
    unsigned short unk_AC;
    unsigned char pad_AE[0x02];
    unsigned char unk_B0[0x10];
    unsigned char pad_C0[0x34];
    unsigned char unk_F4;
};

void func_ov147_02299e5c(struct UnkStruct_02299e5c *self)
{
    unsigned int flag1;
    unsigned int flag2;
    unsigned int flag3;
    unsigned short flags;

    if (data_021fbe40[1] != 0) {
        func_0208ffcc();
    } else {
        flag1 = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
        if (flag1 != 0) {
            func_0208ffc0();
        }
    }

    flags = data_021fbe40[1];

    if ((flags & 0x2) != 0) {
        goto tail;
    }
    if ((flags & 0x400) != 0) {
        goto tail;
    }
    if ((flags & 0x800) != 0) {
        goto tail;
    }
    if (self->unk_F4 != 0) {
        goto flag2_true;
    }
    if (self->unk_A2 != 0) {
        goto flag2_true;
    }
    if ((flags & 0x8) != 0) {
        goto flag2_true;
    }
    if ((flags & 0x1) != 0) {
        goto flag2_true;
    }

    flag2 = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (flag2 != 0) {
    flag2_true:
        flag3 = (data_021c75b8 == 2) ? 1 : 0;
        if (flag3 != 0) {
            if (self->unk_AA == 0) {
                goto tail;
            }
            if (self->unk_AA == 1) {
                func_ov147_02299154(self);
                self->unk_AB = 12;
            } else {
                if (self->unk_AB == 0) {
                    func_ov147_02299134(self);
                    func_ov147_0229a628(self->unk_B0);
                    func_ov147_02299fc8(self, 1);
                }
            }
        }
    }

tail:
    if (self->unk_AB != 0) {
        self->unk_AB--;
        if (self->unk_AB == 0) {
            func_ov147_0229a630(self->unk_B0, 0);
        }
    }

    if ((unsigned char) (self->unk_AA + 0xfc) <= 1) {
        if (func_020e8840(&self->unk_AC) == 0) {
            func_ov147_0229a628(self->unk_B0);
            func_ov147_02299fc8(self, 0xb);
        }
    } else {
        self->unk_AC = 0xe10;
    }
}
