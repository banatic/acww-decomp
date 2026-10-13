/* func_020b7f88 @ 0x020b7f88, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f27c(void *obj);

typedef struct {
    char pad_00[0x10];
    unsigned char unk_10;
    int unk_14;
    int unk_18;
} UnkStruct_020b7f88;

UnkStruct_020b7f88 *func_020b7f88(UnkStruct_020b7f88 *obj)
{
    func_0202f27c(obj);
    obj->unk_14 = 0;
    obj->unk_10 = 0;
    obj->unk_18 = 0;
    return obj;
}
