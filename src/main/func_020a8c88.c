/* func_020a8c88 @ 0x020a8c88, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d94[];
extern char data_020da6dc[];
extern void func_020a9b44(void *);

typedef struct {
    void *unk_00;
    int pad_04;
    int unk_08;
} UnkStruct_020a8c88;

UnkStruct_020a8c88 *func_020a8c88(UnkStruct_020a8c88 *obj)
{
    obj->unk_00 = data_020e3d94;
    func_020a9b44(&obj->unk_08);
    obj->unk_00 = data_020da6dc;
    return obj;
}
