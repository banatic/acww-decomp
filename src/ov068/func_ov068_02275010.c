/* func_ov068_02275010 @ 0x02275010, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x298];
    unsigned char flag;
    char pad_299[0x354 - 0x299];
    char unk_354;
    char pad_355[0x3f8 - 0x355];
    char unk_3F8;
} UnkStruct_02275010;

extern void func_ov004_0222c598(void *ptr);
extern void func_ov004_0222c5b4(void *a, void *b);
extern int data_ov068_022788b0;

int func_ov068_02275010(UnkStruct_02275010 *self)
{
    func_ov004_0222c598(self);
    if (self->flag) {
        func_ov004_0222c5b4(&self->unk_354, &self->unk_3F8);
    }
    data_ov068_022788b0 = 0;
    return 1;
}
