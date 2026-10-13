/* func_ov106_0229d60c @ 0x0229d60c, 0x98 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d60c {
    char pad_00[0xa4];
    int x;
    int y;
    char pad_AC[0x09];
    unsigned char b5;
    unsigned char b6;
    char pad_B7[0x08];
    unsigned char bf;
    char pad_C0[0x20f8];
    char region[1];
} UnkStruct_0229d60c;

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov002_02208098(void *self, int);
extern int func_ov106_0229d170(void *self, int);
extern int func_ov106_0229d128(void *self, int);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02207d00(void *);
extern int func_ov106_0229d0d0(void *self, int);
extern void func_ov106_0229c344(void *self, int);
extern void func_ov106_0229c354(void *self, int);
extern void func_ov094_022999cc(void);

void func_ov106_0229d60c(UnkStruct_0229d60c *self, int val)
{
    unsigned char g58;
    unsigned char g54;

    self->b5 = val;
    func_ov002_02208098(self, 1);
    g58 = data_021f6c58;
    g54 = data_021f6c54;
    self->x = func_ov106_0229d170(self, self->b5) - g58;
    self->y = func_ov106_0229d128(self, self->b5) - g54;
    self->b6 = val;
    func_ov002_02207cf8(self->region);
    func_ov002_02207d00(self->region);
    self->bf = 2;
    if (func_ov106_0229d0d0(self, val)) {
        func_ov106_0229c344(self, 4);
    } else {
        func_ov106_0229c354(self, 4);
        func_ov094_022999cc();
    }
}
