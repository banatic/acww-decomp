/* func_02070854 @ 0x02070854, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051608(int a0, int a1, int a2, int a3, int a4);

typedef struct {
    char pad_00[0x68];
    int unk_68;
} UnkStruct_02070854;

void func_02070854(UnkStruct_02070854 *obj, int a1, int a2, int a3, int a4)
{
    if (obj->unk_68 != 0) {
        func_02051608(obj->unk_68, a1, a2, a3, a4);
    }
}
