/* func_ov106_0229e014 @ 0x0229e014, 0x64 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_0200467c(int cmd);
extern void func_ov002_02209114(void *ptr, int idx, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    unsigned char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char pad_BE[0x22a0 - 0xbe];
    char unk_22A0;
    unsigned char pad_22A1[0x2304 - 0x22a1];
    char unk_2304;
    unsigned char pad_2305[0x26f1 - 0x2305];
    unsigned char unk_26F1[1];
} UnkStruct_0229e014;

void func_ov106_0229e014(UnkStruct_0229e014 *self)
{
    if (func_0208e484(&self->unk_22A0) == 0) {
        return;
    }
    self->unk_BC = self->unk_26F1[self->unk_BD];
    {
        int flag = 1;
        if (self->unk_BC == 2) {
            flag = 0;
            func_0200467c(0x24);
        }
        func_ov002_02209114(&self->unk_2304, self->unk_BD, flag);
    }
    func_ov002_02208098((void *) (self), 0x17);
}
