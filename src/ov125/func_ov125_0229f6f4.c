/* func_ov125_0229f6f4 @ 0x0229f6f4, 0x58 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov125_022a0ab8;
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov124_0229f43c(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

typedef struct {
    void *unk_00;
} UnkStruct_0229f6f4;

UnkStruct_0229f6f4 *func_ov125_0229f6f4(UnkStruct_0229f6f4 *self)
{
    self->unk_00 = (void *) &data_ov125_022a0ab8;
    func_ov002_0220afdc((char *) self + 0x6a8);
    func_ov002_02209cb4((char *) self + 0x644);
    func_ov002_02207e28((char *) self + 0x574);
    func_ov002_02209ac8((char *) self + 0x180);
    func_ov124_0229f43c((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
