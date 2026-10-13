/* func_ov003_02216740 @ 0x02216740, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_02008258(void *obj, int field);
extern void func_0200d4e8(void *obj, int a, int b, int c);

struct UnkStruct_02216740 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
};

void func_ov003_02216740(struct UnkStruct_02216740 *obj)
{
    if (func_02056f94(&obj->unk_2D0) != 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        func_0200d4e8(obj, 3, 1, -1);
    }
}
