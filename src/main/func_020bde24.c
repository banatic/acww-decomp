/* func_020bde24 @ 0x020bde24, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2f18];
    unsigned short unk_2F18;
    unsigned short unk_2F1A;
    unsigned int unk_2F1C;
    unsigned int unk_2F20;
} UnkStruct_020bde24;

extern void func_0209def4(unsigned short *p);
extern unsigned int func_0209dedc(void);

void func_020bde24(UnkStruct_020bde24 *self)
{
    self->unk_2F1A = self->unk_2F18;
    self->unk_2F20 = self->unk_2F1C;
    func_0209def4(&self->unk_2F18);
    self->unk_2F1C = func_0209dedc();
}
