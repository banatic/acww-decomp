/* func_ov142_0229b43c @ 0x0229b43c, 0x6c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *, int);
extern int func_ov002_0220a784(void *, int);
extern void func_ov142_0229b1d8(void *);
extern void func_ov142_0229b350(void *);
extern void func_ov142_0229b2f8(void *);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

typedef struct UnkStruct_0229b43c {
    unsigned char pad_00[0x194];
    unsigned char unk_194;
} UnkStruct_0229b43c;

void func_ov142_0229b43c(UnkStruct_0229b43c *self)
{
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov142_0229b1d8(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc);
    if (flag > 0) {
        if (func_ov002_0220a784(&self->unk_194, 3)) {
            func_ov142_0229b350(self);
        } else if (func_ov002_0220a784(&self->unk_194, 4)) {
            func_ov142_0229b2f8(self);
        }
    }
}
