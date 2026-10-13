/* func_ov106_0229ca90 @ 0x0229ca90, 0x64 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229c364(void *p, int flag);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a0b4(void *p, int v1, int v2);
extern int func_ov002_0220a374(void *p, int v);

struct UnkStruct_0229ca90 {
    char pad_00[0xBD];
    unsigned char unk_BD;
    char pad_BE[0x21E2]; // up to 0x22A0
    char unk_22A0;
    char pad_22A1[0x63]; // up to 0x2304
    char unk_2304;
};

void func_ov106_0229ca90(struct UnkStruct_0229ca90 *self)
{
    int t1, t2;

    if (func_ov106_0229c364(self, 0x10000)) {
        self->unk_BD = 1;
    } else {
        self->unk_BD = 0;
    }

    t1 = func_ov002_02208ae4(&self->unk_2304);
    t2 = func_ov002_02208ad8(&self->unk_2304, self->unk_BD);
    func_ov002_0220a0b4(&self->unk_22A0, t1, t2);
    func_ov002_0220a374(&self->unk_22A0, 7);
}
