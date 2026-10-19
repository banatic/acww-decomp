/* func_ov145_022998f0 @ 0x022998f0, 0x64 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkSub {
    char pad_00;
} UnkSub;

typedef struct UnkStruct_022998f0 {
    char pad_00[0xc1];
    unsigned char unk_C1;
    char pad_C2[0x6a];
    UnkSub unk_12C;
} UnkStruct_022998f0;

extern void func_0200467c(int cmd);
extern void func_ov145_02299954(UnkStruct_022998f0 *self, unsigned char param);
extern void func_ov145_0229a2e0(UnkStruct_022998f0 *self);
extern void func_ov002_0220a574(UnkSub *sub);
extern void func_ov002_0220a4bc(void *receiver);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov145_022998f0(UnkStruct_022998f0 *self, unsigned int param)
{
    if (param <= 3) {
        if (param != self->unk_C1) {
            func_0200467c(0xc);
            func_ov145_02299954(self, (unsigned char) param);
        }
        return 0;
    } else {
        switch (param) {
            case 4:
                func_ov145_0229a2e0(self);
                return 1;
            case 5:
                func_ov002_0220a574(&self->unk_12C);
                func_ov002_0220a4bc(&self->unk_12C);
                func_ov002_02208098((void *) (self), 4);
                return 1;
            default:
                return 0;
        }
    }
}
