/* func_ov096_022a0688 @ 0x022a0688, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a0688 {
    int pad_00;
} UnkStruct_022a0688;

typedef struct UnkStruct_022a0688_2 {
    unsigned char pad_00[0x00b5];
    unsigned char unk_B5;
    unsigned char pad_B6[0x04];
    unsigned char unk_BA;
    unsigned char pad_BB[0x2500 - 0xbb];
    UnkStruct_022a0688 sub;
} UnkStruct_022a0688_2;

extern int func_ov002_02209f64(const UnkStruct_022a0688 *);
extern void func_ov002_02208098(UnkStruct_022a0688_2 *, unsigned char);
extern void func_ov096_0229ed74(UnkStruct_022a0688_2 *, unsigned char);
extern void func_ov096_022a1a0c(UnkStruct_022a0688_2 *);
extern void func_ov096_0229ea5c(UnkStruct_022a0688_2 *);

void func_ov096_022a0688(UnkStruct_022a0688_2 *self)
{
    if (func_ov002_02209f64(&self->sub) == 0) {
        func_ov002_02208098(self, self->unk_BA);
        if ((unsigned char) (self->unk_BA + 0xf6) <= 2) {
            func_ov096_0229ed74(self, self->unk_B5);
        }
        func_ov096_022a1a0c(self);
    }
    func_ov096_0229ea5c(self);
}
