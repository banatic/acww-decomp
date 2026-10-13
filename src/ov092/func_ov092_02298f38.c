/* func_ov092_02298f38 @ 0x02298f38, 0x20 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220826c(void *ptr);
extern void func_ov002_02207f6c(void *ptr);

struct UnkStruct_02298f38 {
    void *unk_00;
};

extern unsigned char data_ov092_02299508[];

struct UnkStruct_02298f38 *func_ov092_02298f38(struct UnkStruct_02298f38 *self)
{
    self->unk_00 = (void *) data_ov092_02299508;
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
