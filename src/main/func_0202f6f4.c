/* func_0202f6f4 @ 0x0202f6f4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8fc(void *dst, int arg1, int arg2);
extern void func_0202f6ac(void *self, int a, int b, int c);

struct UnkStruct_0202f6f4 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0202f6f4_2 {
    int unk_00;
    struct UnkStruct_0202f6f4 unk_04;
    struct UnkStruct_0202f6f4 unk_0C;
    struct UnkStruct_0202f6f4 unk_14;
};

extern unsigned char data_020da1a4[];

struct UnkStruct_0202f6f4_2 *func_0202f6f4(struct UnkStruct_0202f6f4_2 *self, int a, int b, int c)
{
    self->unk_00 = (unsigned int) data_020da1a4;
    func_0202f8fc(&self->unk_04, 0, 0);
    func_0202f8fc(&self->unk_0C, 0, 0);
    func_0202f8fc(&self->unk_14, 0, 0);
    func_0202f6ac(self, a, b, c);
    return self;
}
