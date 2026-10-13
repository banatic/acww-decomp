/* func_0208fd44 @ 0x0208fd44, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208fd44 {
    unsigned int unk_00;
};

extern void func_0208fb24(struct UnkStruct_0208fd44 *p);
extern void func_0208af00(struct UnkStruct_0208fd44 *p);
extern void func_020edb3c(struct UnkStruct_0208fd44 *p);

extern unsigned char data_020e23e4[];

struct UnkStruct_0208fd44 *func_0208fd44(struct UnkStruct_0208fd44 *self)
{
    self->unk_00 = (unsigned int) data_020e23e4;
    func_0208fb24(self);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
