/* func_020339b8 @ 0x020339b8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da210;
extern void func_02034294(void *);
extern void func_0202f6dc(void *);

typedef struct {
    void *unk_00;
    char pad_04[0x20 - 4];
    char unk_20;
} UnkStruct_020339b8;

UnkStruct_020339b8 *func_020339b8(UnkStruct_020339b8 *obj)
{
    obj->unk_00 = &data_020da210;
    func_02034294(&obj->unk_20);
    func_0202f6dc(obj);
    return obj;
}
