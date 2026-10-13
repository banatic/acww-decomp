/* func_ov122_0229f21c @ 0x0229f21c, 0x34 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a000(void *ptr, int a, int b, int c, int d);
extern void func_ov002_02208098(void *ptr, int n);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x26];
    unsigned char unk_B4;
    unsigned char pad_B5[0x3fa3];
    unsigned char unk_4058;
} UnkStruct_0229f21c;

void func_ov122_0229f21c(UnkStruct_0229f21c *this, int a, int b)
{
    func_ov002_0220a000(&this->unk_4058, a, b, 3, 2);
    this->unk_B4 = this->unk_8D;
    func_ov002_02208098(this, 7);
}
