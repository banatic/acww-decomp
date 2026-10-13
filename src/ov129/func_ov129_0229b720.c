/* func_ov129_0229b720 @ 0x0229b720, 0x54 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov129_0229dc38;
extern void func_ov127_0229a0e8(void *p);
extern void func_020b18a8(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_0220ba0c(void *p);
extern void func_ov002_0220826c(void *p);

typedef struct {
    void *unk_00;
} UnkStruct_0229b720;

UnkStruct_0229b720 *func_ov129_0229b720(UnkStruct_0229b720 *self)
{
    self->unk_00 = &data_ov129_0229dc38;
    func_ov127_0229a0e8((char *) self + 0x734);
    func_020b18a8((char *) self + 0x404);
    func_ov002_02209cb4((char *) self + 0x3a0);
    func_ov002_0220afdc((char *) self + 0x1d4);
    func_ov002_0220ba0c((char *) self + 0xb8);
    func_ov002_0220826c(self);
    return self;
}
