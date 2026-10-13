/* func_ov138_0229ce68 @ 0x0229ce68, 0x94 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_02208054(void *self, int arg);
extern void func_ov138_0229c9e0(void *self);
extern int func_ov002_0220a784(void *ptr, int idx);
extern void func_ov138_0229c978(void *self);
extern void func_ov138_0229c950(void *self);
extern int func_ov134_0229ab80(void *ptr, unsigned char a, unsigned char b);
extern void func_ov138_0229c924(void *self, int result);

typedef struct {
    char pad_00[0xfc];
    void *unk_FC;
    char pad_100[0x1c8];
    void *unk_2C8;
} UnkStruct_0229ce68;

void func_ov138_0229ce68(UnkStruct_0229ce68 *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov138_0229c9e0(self);
        return;
    }

    {
        unsigned int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (cond > 0) {
            if (func_ov002_0220a784(&self->unk_FC, 6) != 0) {
                func_ov138_0229c978(self);
                return;
            } else {
                if (func_ov002_0220a784(&self->unk_FC, 7) != 0) {
                    func_ov138_0229c950(self);
                    return;
                } else {
                    int result = func_ov134_0229ab80(&self->unk_2C8, data_021f6c58, data_021f6c54);
                    if (result != 6) {
                        func_ov138_0229c924(self, result);
                    }
                }
            }
        }
    }
}
