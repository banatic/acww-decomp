/* func_02067c20 @ 0x02067c20, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02067c20 {
    unsigned char pad_00[0x1a64];
    int unk_1A64;
    short unk_1A68;
    short unk_1A6A;
    int unk_1A6C;
    int unk_1A70;
    int unk_1A74;
};

extern int func_0209dee8(void);
extern void func_0209df94(short *);
extern void func_0209def4(short *);
extern int func_0209ded0(void);
extern int func_0209dedc(void);
extern int func_0209dcac(void);

void func_02067c20(struct UnkStruct_02067c20 *self)
{
    self->unk_1A64 = func_0209dee8();
    func_0209df94(&self->unk_1A68);
    func_0209def4(&self->unk_1A6A);
    self->unk_1A6C = func_0209ded0();
    self->unk_1A70 = func_0209dedc();
    self->unk_1A74 = func_0209dcac();
}
