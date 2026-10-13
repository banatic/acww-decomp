/* func_0208c1ac @ 0x0208c1ac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208c1ac UnkStruct_0208c1ac;

struct UnkStruct_0208c1ac {
    unsigned int unk_00;
    unsigned char pad_04[8];
    unsigned int unk_0C;
    unsigned char pad_10[0x18];
    unsigned int unk_28;
};

extern void func_0208c008(UnkStruct_0208c1ac *self);
extern void func_0208c804(void *obj);
extern void func_0208a1f4(void *obj);
extern void func_0208af00(UnkStruct_0208c1ac *self);

extern unsigned char data_020e2234[];

UnkStruct_0208c1ac *func_0208c1ac(UnkStruct_0208c1ac *self)
{
    self->unk_00 = (unsigned int) data_020e2234;
    func_0208c008(self);
    func_0208c804(&self->unk_28);
    func_0208a1f4(&self->unk_0C);
    func_0208af00(self);
    return self;
}
