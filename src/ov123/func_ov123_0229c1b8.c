/* func_ov123_0229c1b8 @ 0x0229c1b8, 0x90 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c1b8;

extern int func_ov002_02207f48(UnkStruct_0229c1b8 *self, int a);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229c1b8 *self, unsigned char value);
extern void func_ov123_0229b600(UnkStruct_0229c1b8 *self);
extern int func_ov123_02299650(UnkStruct_0229c1b8 *self, int a);
extern void func_ov123_02299684(UnkStruct_0229c1b8 *self);
extern void func_ov123_02299630(UnkStruct_0229c1b8 *self, int a);
extern void func_ov123_0229c044(UnkStruct_0229c1b8 *self);

void func_ov123_0229c1b8(UnkStruct_0229c1b8 *self)
{
    if (func_ov002_02207f48(self, -1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov123_0229b600(self);
        if (func_ov123_02299650(self, 0x400) != 0) {
            func_ov123_02299684(self);
            self->unk_98 = 0x10;
            func_ov123_02299630(self, 0x400);
        }
    } else {
        if (func_ov123_02299650(self, 0x400) != 0) {
            if (self->unk_98 < 0x10) {
                self->unk_98 = self->unk_98 + 2;
            } else {
                func_ov123_02299684(self);
                self->unk_98 = 0x10;
                func_ov123_02299630(self, 0x400);
            }
        }
    }
    func_ov123_0229c044(self);
}
