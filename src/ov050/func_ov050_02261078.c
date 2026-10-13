/* func_ov050_02261078 @ 0x02261078, 0x1c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov050_022618d0(void *self, int a, int b);

struct UnkStruct_02261078 {
    char pad_00[0xd0];
    int unk_D0;
};

void func_ov050_02261078(struct UnkStruct_02261078 *self, int param2)
{
    if (param2 != 4) {
        func_ov050_022618d0(self, 1, param2);
        self->unk_D0 = 0x48;
    }
}
