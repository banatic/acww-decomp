/* func_0201d4d8 @ 0x0201d4d8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02027170(unsigned short *out, unsigned int input);
extern void func_02015330(void *obj, unsigned short *field, int a, int b, int c);
extern void func_02068440(void *arg);

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x124 - 0x40 - 4];
    unsigned short unk_124;
    unsigned char pad_126[0x1a0 - 0x124 - 2];
    unsigned int unk_1A0;
} UnkStruct_0201d4d8;

void func_0201d4d8(UnkStruct_0201d4d8 *self)
{
    unsigned short value;

    func_02027170(&value, self->unk_1A0);
    self->unk_124 = value;
    func_02015330(self, &self->unk_124, 0, 5, 0);
    func_02068440(self->unk_40);
}
