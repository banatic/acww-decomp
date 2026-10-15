/* func_ov131_0229b338 @ 0x0229b338, 0x9c bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_02208054(void *self, int arg);
extern void func_ov131_0229b0f0(void *self);
extern int func_ov002_0220a784(void *ptr, int idx);
extern int func_ov131_0229b07c(void *self);
extern void func_ov131_0229b04c(void *self);
extern int func_ov130_0229a278(void *ptr, unsigned char a, unsigned char b);
extern void func_ov130_0229a254(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    char pad_00[0xf8];
    void *unk_F8;
    char pad_FC[0x1c8];
    void *unk_2C4;
} UnkStruct_0229b338;

void func_ov131_0229b338(UnkStruct_0229b338 *self)
{
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov131_0229b0f0(self);
        return;
    }

    {
        unsigned int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (cond > 0) {
            if (func_ov002_0220a784(&self->unk_F8, 6) != 0) {
                func_ov131_0229b07c(self);
                return;
            } else {
                if (func_ov002_0220a784(&self->unk_F8, 7) != 0) {
                    func_ov131_0229b04c(self);
                    return;
                } else {
                    if (func_ov130_0229a278(&self->unk_2C4, data_021f6c58, data_021f6c54) != 0xd) {
                        func_ov130_0229a254(&self->unk_2C4);
                        func_ov002_02208098((void *) (self), 1);
                    }
                }
            }
        }
    }
}
