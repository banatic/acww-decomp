/* func_ov004_02226d68 @ 0x02226d68, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02226d68 {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x51F];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

extern int func_02056f94(void *);
extern int func_02008258(struct UnkStruct_02226d68 *, int);
extern int func_0200d4e8(struct UnkStruct_02226d68 *, int, int, int);

void func_ov004_02226d68(struct UnkStruct_02226d68 *obj)
{
    if (func_02056f94(&obj->unk_2D0) != 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        func_0200d4e8(obj, 3, 1, -1);
    }
}
