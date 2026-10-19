/* func_ov106_0229e430 @ 0x0229e430, 0xcc bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov002_02208e28(const char *);
extern int func_0206f56c(void);
extern int func_ov002_02208054(const void *, int);
extern int func_ov002_02208b00(const char *, unsigned char, unsigned char);
extern int func_ov106_0229c364(const void *, int);
extern void func_ov106_0229c868(const void *);
extern void func_0200467c(int);
extern void func_ov002_02209114(const char *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct UnkStruct_0229e430 {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char pad_BD[0x2247];
    char unk_2304[1];
    unsigned char pad_2305[0x3ec];
    unsigned char arr26f1[1];
} UnkStruct_0229e430;

void func_ov106_0229e430(UnkStruct_0229e430 *self)
{
    int r1;
    unsigned int flag;
    int res;
    int r6;

    r1 = func_ov002_02208e28(self->unk_2304);
    if (r1 == 0) {
        return;
    }

    if (func_0206f56c() != 0) {
        func_ov106_0229c868(self);
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov106_0229c868(self);
        return;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag == 0) {
        return;
    }

    res = func_ov002_02208b00(self->unk_2304, data_021f6c58, data_021f6c54);
    if (res < 0) {
        return;
    }

    if (func_ov106_0229c364(self, 0x10000) != 0 && res == 0) {
        return;
    }

    self->unk_BC = self->arr26f1[res];
    r6 = 1;
    if (self->unk_BC == 2) {
        r6 = 0;
        func_0200467c(0x24);
    }

    func_ov002_02209114(self->unk_2304, res, r6);
    func_ov002_02208098((void *) (self), 0x17);
}
