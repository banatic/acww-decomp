/* func_020aad08 @ 0x020aad08, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020515b8(void *ptr);

typedef struct {
    char pad_00[0x14];
    void *unk_14;
    char pad_18[0x24 - 0x14 - 4];
    void *unk_24;
    unsigned int unk_28;
} UnkStruct_020aad08;

void func_020aad08(UnkStruct_020aad08 *obj)
{
    unsigned int max;
    unsigned int v;

    max = 0;
    if (obj->unk_24 != 0) {
        v = func_020515b8(obj->unk_24);
        if (v > max) {
            max = v;
        }
    }
    if (obj->unk_14 != 0) {
        v = func_020515b8(obj->unk_14);
        if (v > max) {
            max = v;
        }
    }
    obj->unk_28 = max;
}
