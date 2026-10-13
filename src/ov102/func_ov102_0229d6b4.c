/* func_ov102_0229d6b4 @ 0x0229d6b4, 0x8c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d6b4 {
    unsigned char pad_00[0x218c];
    unsigned char sub_218c;
    unsigned char pad_218D[0x34b];
    int unk_24D8;
    int unk_24DC;
    unsigned char pad_24E0[0xc0];
    unsigned char unk_25A0;
    unsigned char unk_25A1;
} UnkStruct_0229d6b4;

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern void func_ov002_02208098(UnkStruct_0229d6b4 *self, int arg);
extern int func_ov102_0229d1e8(UnkStruct_0229d6b4 *self, unsigned char arg);
extern int func_ov102_0229d178(UnkStruct_0229d6b4 *self, unsigned char arg);
extern void func_ov002_02207cf8(unsigned char *p);
extern int func_ov102_0229d0b0(UnkStruct_0229d6b4 *self, int arg);
extern void func_ov102_0229c288(UnkStruct_0229d6b4 *self, int arg);
extern void func_ov102_0229c298(UnkStruct_0229d6b4 *self, int arg);
extern void func_ov094_022999cc(void);

void func_ov102_0229d6b4(UnkStruct_0229d6b4 *self, int val)
{
    unsigned char a;
    unsigned char b;

    self->unk_25A0 = val;
    func_ov002_02208098(self, 1);
    a = data_021f6c58;
    b = data_021f6c54;

    self->unk_24D8 = func_ov102_0229d1e8(self, self->unk_25A0) - a;
    self->unk_24DC = func_ov102_0229d178(self, self->unk_25A0) - b;

    self->unk_25A1 = val;
    func_ov002_02207cf8(&self->sub_218c);

    if (func_ov102_0229d0b0(self, val) != 0) {
        func_ov102_0229c288(self, 4);
    } else {
        func_ov102_0229c298(self, 4);
        func_ov094_022999cc();
    }
}
