/* func_020ab2e0 @ 0x020ab2e0, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1C];
    void *unk_1C;
    void *unk_20;
} UnkStruct_020ab2e0;

extern void func_020ab130(UnkStruct_020ab2e0 *obj);
extern void func_020ab558(void *ptr);

void func_020ab2e0(UnkStruct_020ab2e0 *obj)
{
    func_020ab130(obj);
    func_020ab558(obj->unk_20);
    obj->unk_1C = 0;
    obj->unk_20 = 0;
}
