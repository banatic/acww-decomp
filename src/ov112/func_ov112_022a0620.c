/* func_ov112_022a0620 @ 0x022a0620, 0x98 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern struct Global {
    unsigned char pad_00[2];
    unsigned short flag;
} data_021fbe40;

struct UnkStruct_022a0620 {
    unsigned char pad_00[0x384];
    int unk_384;
    unsigned char pad_388[0x4448 - 0x388];
    int unk_4448;
};

extern int func_ov112_0229fe70(void *, int);
extern void func_ov112_0229fe50(void *, int);
extern void func_ov112_0229fe60(void *, int);
extern void func_ov112_0229fab4(void *);
extern int func_ov095_0229cda4(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov112_0229f35c(void *);

int func_ov112_022a0620(struct UnkStruct_022a0620 *self)
{
    if ((data_021fbe40.flag & 0x800) == 0) {
        return 0;
    }

    if (func_ov112_0229fe70(self, 0x800)) {
        func_ov112_0229fe50(self, 0x800);
    } else {
        func_ov112_0229fe60(self, 0x800);
        func_ov112_0229fab4(self);
    }

    if (func_ov095_0229cda4(&self->unk_384, -1) != 0) {
        if (func_ov112_0229fe70(self, 0x800)) {
            func_ov002_0220a2b4(&self->unk_4448);
            func_ov002_02208098(self, 0xC);
        } else {
            func_ov002_0220a314(&self->unk_4448);
            func_ov002_02208098(self, 0x6);
        }
        func_ov112_0229f35c(self);
    } else {
        func_ov112_0229f35c(self);
    }
    return 1;
}
