/* func_ov112_022a0838 @ 0x022a0838, 0x118 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern struct Flags {
    char pad_00[2];
    unsigned short flags;
} data_021fbe40;

typedef struct UnkStruct_022a0838 {
    char pad_00[0xc2];
    unsigned char unk_C2;
    char pad_C3[0x427c - 0xc2 - 1];
    char unk_427C[0x4448 - 0x427c];
    char unk_4448[0x10];
} UnkStruct_022a0838;

extern int func_ov002_02208014(void);
extern int func_ov112_0229fee4(void *);
extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_02208008(void *);
extern int func_ov002_022088ac(int arg0);
extern int func_ov002_0220889c(int);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov112_0229f328(void *, int, int);
extern void func_ov112_0229f3e0(void *);
extern void func_ov112_0229ffa0(void *);
extern void func_ov112_0229ffdc(void *);

void func_ov112_022a0838(UnkStruct_022a0838 *self)
{
    unsigned char original;
    int val;
    unsigned short flags;
    int v1, v2;

    if (func_ov002_02208014() != 0) {
        func_ov112_0229fee4(self);
        return;
    }

    if (data_021fbe40.flags & 1) {
        func_ov002_0220a1dc(&self->unk_4448);
        func_ov002_02208098(self, 0x14);
        return;
    }

    original = self->unk_C2;
    val = func_ov002_02208008(self);
    if (func_ov002_022088ac(val) != 0) {
        if (self->unk_C2 != 0) {
            self->unk_C2--;
        }
    } else {
        if (func_ov002_0220889c(val) != 0) {
            if (self->unk_C2 < 1) {
                self->unk_C2++;
            }
        }
    }

    if (original != self->unk_C2) {
        if (self->unk_C2 != 0) {
            v1 = func_ov002_0220a768(&self->unk_427C, 4);
            v2 = func_ov002_0220a72c(&self->unk_427C, 4);
            func_ov112_0229f328(self, v1, v2);
        } else {
            v1 = func_ov002_0220a768(&self->unk_427C, 3);
            v2 = func_ov002_0220a72c(&self->unk_427C, 3);
            func_ov112_0229f328(self, v1, v2);
        }
    }

    flags = data_021fbe40.flags;
    if (flags & 2) {
        func_ov112_0229f3e0(self);
        func_ov112_0229ffa0(self);
        return;
    }
    if (flags & 8) {
        func_ov112_0229f3e0(self);
        func_ov112_0229ffdc(self);
    }
}
