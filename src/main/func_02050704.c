/* func_02050704 @ 0x02050704, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020551e0(void *ptr);
extern void func_0209d104(void *ptr);
extern void func_0209d340(void *ptr);
extern void func_020f5948(void *ptr);

struct UnkStruct_02050704 {
    unsigned char pad_00[0x48];
    unsigned char unk_48[4];
    unsigned char unk_4C[4];
    unsigned char pad_50[0x48];
    unsigned char unk_98[4];
};

struct UnkStruct_02050704 *func_02050704(struct UnkStruct_02050704 *self)
{
    func_020551e0(self->unk_98);
    func_0209d104(self->unk_4C);
    func_0209d340(self->unk_48);
    func_020f5948(self);
    return self;
}
