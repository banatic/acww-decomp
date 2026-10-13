/* func_ov106_0229cbdc @ 0x0229cbdc, 0x74 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229c364(void *self, int n);
extern int func_ov106_0229cc84(void *self);
extern int func_ov106_0229cc74(void *self);
extern void func_ov106_0229c344(void *self, int n);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);
extern void func_ov002_0220a05c(char *ptr, int a, int b, int c, int d);
extern void func_ov002_02208098(void *self, int n);

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x2d];
    unsigned char unk_BB;
    char pad_BC[0x21e4];
    char unk_22A0[1];
} UnkStruct_0229cbdc;

void func_ov106_0229cbdc(UnkStruct_0229cbdc *self)
{
    int a, b, flag;
    if (func_ov106_0229c364(self, 8)) {
        a = func_ov106_0229cc84(self);
        b = func_ov106_0229cc74(self);
        func_ov002_0220a0b4(self->unk_22A0, a, b);
        func_ov106_0229c344(self, 8);
    } else {
        a = func_ov106_0229cc84(self);
        b = func_ov106_0229cc74(self);
        flag = 1;
        func_ov002_0220a05c(self->unk_22A0, a, b, 3, flag);
        self->unk_BB = self->unk_8D;
        func_ov002_02208098(self, 13);
    }
}
