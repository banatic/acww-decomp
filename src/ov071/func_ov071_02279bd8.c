/* func_ov071_02279bd8 @ 0x02279bd8, 0x2c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02279bd8 {
    unsigned char pad_00[0x618];
    char unk_618;
} UnkStruct_02279bd8;

extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_ov071_02279d04(void *ptr, int value);

int func_ov071_02279bd8(UnkStruct_02279bd8 *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        func_0203e020(self);
        func_ov071_02279d04(self, 2);
    }
    return 1;
}
