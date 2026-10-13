/* func_020a8ecc @ 0x020a8ecc, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020a8ecc;

extern void func_02051340(UnkStruct_020a8ecc *obj);
extern void func_020515ac(UnkStruct_020a8ecc *obj);

void func_020a8ecc(UnkStruct_020a8ecc *obj)
{
    int value = obj->unk_7C;
    if (value == 1) {
        func_02051340(obj);
    } else if (value == 2) {
        func_020515ac(obj);
    }
}
