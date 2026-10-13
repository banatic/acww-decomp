/* func_ov106_0229dcb0 @ 0x0229dcb0, 0x60 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned int unk_A0;
    unsigned char pad_A4[0x2654];
    unsigned char unk_26F8;
    unsigned char pad_26F9[0x18bb];
    unsigned char unk_3FB4;
} UnkStruct_0229dcb0;

extern int func_ov002_0220b804(void *p);
extern int func_ov002_02207f3c(void *p, int n);
extern unsigned int func_ov002_02207f60(void *p);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern void func_ov002_0220a99c(void *p);
extern void func_ov002_0220a6b8(void *p);

void func_ov106_0229dcb0(UnkStruct_0229dcb0 *self)
{
    int temp = func_ov002_0220b804(&self->unk_26F8);
    temp &= func_ov002_02207f3c(self, -1);
    self->unk_A0 = func_ov002_02207f60(self);
    if (temp != 0) {
        func_ov002_02208098(self, 0x1b);
        func_ov002_02207eb4(self, 0, 0);
        func_ov002_0220a99c(&self->unk_3FB4);
        func_ov002_0220a6b8(&self->unk_3FB4);
    }
}
