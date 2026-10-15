/* func_ov128_0229c1bc @ 0x0229c1bc, 0x4c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov127_02299bbc(unsigned char *ptr, unsigned char val);
extern void func_ov127_02299c08(unsigned char *ptr, unsigned char val, int flag);
extern void func_ov128_0229bb20(void *s);

typedef struct {
    unsigned char pad_00[0x4A4];
    unsigned char unk_4A4;
    unsigned char pad_4A5[0x2D6B - 0x4A4 - 1];
    unsigned char unk_2D6B;
} UnkStruct_0229c1bc;

void func_ov128_0229c1bc(UnkStruct_0229c1bc *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (s), 2);
        func_ov127_02299bbc(&s->unk_4A4, s->unk_2D6B);
        func_ov128_0229bb20(s);
    } else {
        func_ov127_02299c08(&s->unk_4A4, s->unk_2D6B, 1);
        func_ov128_0229bb20(s);
    }
}
