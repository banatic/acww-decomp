/* func_ov049_02260ac4 @ 0x02260ac4, 0x5c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x728];
    unsigned int unk_728;
    unsigned int unk_72C;
    unsigned char pad1[0x244];
    unsigned char unk_974;
} PtrStruct;

typedef struct {
    unsigned char pad_00[0xb0];
    PtrStruct *unk_B0;
    unsigned char pad1[0x8];
    void *unk_BC;
} UnkStruct_02260ac4;

extern void func_0201b420(PtrStruct *a, void *b);
extern void func_0209a000(char *dst, int val);
extern void func_020ad8f8(unsigned int a, unsigned int b, int c);
extern void func_0207972c(void);

void func_ov049_02260ac4(UnkStruct_02260ac4 *self)
{
    self->unk_B0->unk_974 = 1;
    func_0201b420(self->unk_B0, self->unk_BC);
    func_0209a000((char *) self->unk_B0 + 0x738, 0);
    func_020ad8f8(self->unk_B0->unk_728, self->unk_B0->unk_72C, 0xa);
    func_0207972c();
}
