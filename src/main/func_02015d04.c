/* func_02015d04 @ 0x02015d04, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char unk_54;
} UnkStruct_02015d04;

extern int func_02015da0(UnkStruct_02015d04 *self, unsigned char b);
extern int func_02015d44(void);
extern void func_0201ad18(int a, int b, int c, int d, void *e, int f, int g, int h);
extern int data_021fbee8;

void func_02015d04(UnkStruct_02015d04 *self)
{
    int ret0 = func_02015da0(self, self->unk_54);
    if (ret0 != 0) {
        int ret1 = func_02015d44();
        func_0201ad18(ret0 + 0x3b0, 4, 0, 0, &data_021fbee8, ret1, 0, 0);
    }
}
