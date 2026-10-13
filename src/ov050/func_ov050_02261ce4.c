/* func_ov050_02261ce4 @ 0x02261ce4, 0x44 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_020154b4(void *self, short *ptr, int arg2, int arg3, int arg4);
extern void func_0209a000(short *ptr, int arg);

struct UnkStruct_02261ce4 {
    char pad_00[0xCC];
    int unk_CC;
    int unk_D0;
};

void func_ov050_02261ce4(struct UnkStruct_02261ce4 *self)
{
    int a;
    short v1;
    short v2;
    v1 = 0x4a30;
    a = 0;
    func_020154b4(self, &v1, 0, 5, a);
    v2 = 0x4a30;
    func_0209a000(&v2, 0);
    self->unk_CC = -1;
    self->unk_D0 = 0x38;
}
