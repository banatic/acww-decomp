/* func_ov048_02262e68 @ 0x02262e68, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201aff4(void *, int);

typedef struct {
    char pad_00[0x350];
    char unk_350[0xb1c];
    short unk_E6C;
    char pad_E6E[0x3];
    char unk_E71;
} UnkStruct_02262e68;

int func_ov048_02262e68(UnkStruct_02262e68 *obj)
{
    obj->unk_E71 = 0;
    func_0201aff4(obj->unk_350, obj->unk_E6C);
    return 1;
}
