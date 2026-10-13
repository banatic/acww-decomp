/* func_ov103_0229d4e4 @ 0x0229d4e4, 0x9c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(void *);
extern int func_ov103_0229c350(void *, int, int);
extern void func_ov103_0229ca48(void *);
extern void func_ov103_0229c774(void *);
extern void func_ov002_02207d24(void *, int);
extern int func_ov103_0229cc08(void *, unsigned char);
extern void func_ov103_0229c604(void *, unsigned char);
extern void func_ov103_0229c5b8(void *, unsigned char);
extern void func_ov103_0229c994(void *);
extern void func_ov002_02207d00(void *);
extern unsigned short data_021fbe40[2];

typedef struct {
    unsigned char pad_00[0x2da3];
    unsigned char unk_2DA3;
    unsigned char unk_2DA4;
} UnkStruct_0229d4e4;

void func_ov103_0229d4e4(UnkStruct_0229d4e4 *self)
{
    if (func_ov103_0229c350(self, func_ov002_02208008(self), 1) != 0) {
        func_ov103_0229ca48(self);
        func_ov103_0229c774(self);
        func_ov002_02207d24((char *) self + 0x218c, 0);
        return;
    }

    {
        unsigned short flags = data_021fbe40[1];

        if (flags & 1) {
            if (func_ov103_0229cc08(self, self->unk_2DA4) != 0) {
                func_ov103_0229c604(self, self->unk_2DA4);
                return;
            } else {
                func_ov103_0229c5b8(self, self->unk_2DA4);
                return;
            }
        } else if (flags & 2) {
            func_ov103_0229c604(self, self->unk_2DA3);
            return;
        } else {
            func_ov103_0229c994(self);
            func_ov002_02207d00((char *) self + 0x218c);
        }
    }
}
