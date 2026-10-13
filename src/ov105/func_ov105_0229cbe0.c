/* func_ov105_0229cbe0 @ 0x0229cbe0, 0x7c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229c340(void *self, int a);
extern void func_ov002_02208c58(char *dst, char *src, int a);
extern int func_ov105_0229d530(void *self, unsigned char b);
extern int func_ov105_0229d4c4(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b, int c);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov002_02208098(void *self, int b);

typedef struct UnkStruct_0229cbe0 {
    unsigned char pad_00[0x2bb];
    unsigned char unk_2BB;
    unsigned char pad_2BC[0x2100];
    unsigned char arr_23bc[0x14c];
    unsigned char arr_2508[0x3e8];
    unsigned char arr_28f0[1];
} UnkStruct_0229cbe0;

void func_ov105_0229cbe0(UnkStruct_0229cbe0 *self, int flag)
{
    int a, b, c;
    a = func_ov105_0229c340(self, 0x800);
    func_ov002_02208c58((char *) self->arr_2508, (char *) self->arr_28f0, a);
    b = func_ov105_0229d530(self, self->unk_2BB);
    c = func_ov105_0229d4c4(self, self->unk_2BB);
    if (flag) {
        func_ov002_02209874((char *) self->arr_2508, (char *) self->arr_23bc, c);
    } else {
        func_ov002_02209910((char *) self->arr_2508, b, c);
    }
    func_ov002_0220970c((char *) self->arr_2508, 0);
    func_ov002_02208098(self, 0x16);
}
