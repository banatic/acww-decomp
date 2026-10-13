/* func_ov122_022a1b60 @ 0x022a1b60, 0x44 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022080a0(void *self, int arg);
extern int func_0206fe60(int arg);
extern void func_ov122_022a0000(void *self);
extern void func_ov122_0229ffac(void *self);

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_022a1b60;

void func_ov122_022a1b60(UnkStruct_022a1b60 *self)
{
    if (self->unk_98 > 0x20) {
        self->unk_98 -= 0x20;
    } else {
        self->unk_98 = 0;
        if (func_0206fe60(func_ov002_022080a0(self, 2)) != 0) {
            func_ov122_022a0000(self);
        } else {
            func_ov122_0229ffac(self);
        }
    }
}
