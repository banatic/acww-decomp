/* func_ov048_02262114 @ 0x02262114, 0x28 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02262114 UnkStruct_02262114;
struct UnkStruct_02262114 {
    unsigned char pad_00[0xe6e];
    unsigned short val;
};

typedef struct UnkStruct_02262114_2 UnkStruct_02262114_2;
struct UnkStruct_02262114_2 {
    unsigned char pad_00[0xb8];
    UnkStruct_02262114 *sub;
};

extern void func_ov048_02262390(UnkStruct_02262114_2 *self, int a);
extern void func_ov048_022616b8(UnkStruct_02262114_2 *self, int a);

void func_ov048_02262114(UnkStruct_02262114_2 *self)
{
    func_ov048_02262390(self, 1);
    self->sub->val = 0xc8;
    func_ov048_022616b8(self, 8);
}
