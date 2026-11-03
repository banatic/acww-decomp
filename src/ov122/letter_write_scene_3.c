/* letter_write_scene_3: 2 functions, module ov122
 * mwccarm 1.2/base -O4,s
 * func_ov122_0229f250 @ 0x0229f250, 0x80 bytes, Thumb
 * func_ov122_0229f21c @ 0x0229f21c, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad_A4[0xf];
    unsigned char unk_B3;
    unsigned char unk_B4;
    char pad_B5[0xb];
    int unk_C0;
    char pad_C4[0x3f94];
    int unk_4058;
} UnkStruct_0229f250;

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x26];
    unsigned char unk_B4;
    unsigned char pad_B5[0x3fa3];
    unsigned char unk_4058;
} UnkStruct_0229f21c;

extern int func_ov122_0229efe8(void *self, int arg);
extern void func_ov002_0220a000(void *dest, int a, int b, int c, int d);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov122_0229f250(UnkStruct_0229f250 *self)
{
    if (func_ov122_0229efe8(self, 0x100) != 0) {
        func_ov002_0220a000(&self->unk_4058, self->unk_9C, self->unk_A0 - self->unk_B3, 3, 2);
        self->unk_B4 = 12;
    } else {
        int a = func_ov095_02299b7c(&self->unk_C0);
        int b = func_ov095_02299b38(&self->unk_C0);
        func_ov002_0220a000(&self->unk_4058, a, b, 3, 2);
        self->unk_B4 = 6;
    }
    func_ov002_02208098((void *) (self), 7);
}

void func_ov122_0229f21c(UnkStruct_0229f21c *this, int a, int b)
{
    func_ov002_0220a000(&this->unk_4058, a, b, 3, 2);
    this->unk_B4 = this->unk_8D;
    func_ov002_02208098((void *) (this), 7);
}
