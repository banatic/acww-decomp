/* func_ov128_0229b774 @ 0x0229b774, 0x58 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkWork {
    void *unk_00;
} UnkWork;

extern char data_ov128_0229cbc0;

extern void func_02070be8(void *);
extern void func_ov127_0229a0e8(void *);
extern void func_020b18a8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220b3a4(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

UnkWork *func_ov128_0229b774(UnkWork *self)
{
    self->unk_00 = &data_ov128_0229cbc0;
    func_02070be8((char *) self + 0x2cdc);
    func_ov127_0229a0e8((char *) self + 0x4a4);
    func_020b18a8((char *) self + 0x174);
    func_ov002_02209cb4((char *) self + 0x110);
    func_ov002_0220b3a4((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
