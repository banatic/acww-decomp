/* func_ov003_02213914 @ 0x02213914, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int value);

typedef struct {
    char pad_00[0x45c];
    unsigned short unk_45C;
    unsigned short unk_45E;
    char pad_460[0x374];
    int unk_7D4;
} UnkStruct_02213914;

void func_ov003_02213914(UnkStruct_02213914 *obj)
{
    if (obj->unk_7D4 != -1) {
        func_0209129c(obj->unk_7D4);
    }
    obj->unk_45C = 0;
    obj->unk_45E = 0;
}
