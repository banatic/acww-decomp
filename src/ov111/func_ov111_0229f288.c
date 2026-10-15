/* func_ov111_0229f288 @ 0x0229f288, 0x64 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f288 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x98 - 0x8d - 1];
    unsigned char unk_98;
    char pad_99[0xac - 0x98 - 1];
    unsigned char unk_AC;
};

struct UnkStruct_0229f288_2 {
    char pad_00[2];
    unsigned short unk_02;
};

extern struct UnkStruct_0229f288_2 data_021fbe40;

extern int func_ov095_0229cf64(unsigned char *p, int value);
extern int func_ov111_0229f730(struct UnkStruct_0229f288 *s, int value);
extern void func_ov095_0229c8e4(unsigned char *p, int value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

int func_ov111_0229f288(struct UnkStruct_0229f288 *self)
{
    if (!(data_021fbe40.unk_02 & 0x200)) {
        return 0;
    }
    if (func_ov095_0229cf64(&self->unk_AC, 0xb) != 0) {
        return 0;
    }
    func_ov111_0229f730(self, 0x118);
    func_ov095_0229c8e4(&self->unk_AC, 0x109);
    self->unk_98 = self->unk_8D;
    func_ov002_02208098((void *) (self), 0xb);
    return 1;
}
