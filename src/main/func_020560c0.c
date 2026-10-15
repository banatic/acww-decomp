/* func_020560c0 @ 0x020560c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020560c0 {
    int unk_00;
    void *unk_04;
} UnkStruct_020560c0;

extern void func_02105178(UnkStruct_020560c0 *obj, unsigned int key);
extern void DC_FlushRange(UnkStruct_020560c0 *obj, void *ptr);
extern void NNS_G3dPlttLoad(UnkStruct_020560c0 *obj, int value);

int func_020560c0(UnkStruct_020560c0 *obj, unsigned int key)
{
    func_02105178(obj, key);
    DC_FlushRange(obj, obj->unk_04);
    NNS_G3dPlttLoad(obj, 1);
    return 1;
}
