/* func_020557a0 @ 0x020557a0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020557a0 UnkStruct_020557a0;

extern void func_02056044(UnkStruct_020557a0 *);
extern int data_020dd03c;

struct UnkStruct_020557a0 {
    int *unk_00;
    char pad_04[0x94];
    unsigned int unk_98;
};

UnkStruct_020557a0 *func_020557a0(UnkStruct_020557a0 *obj)
{
    func_02056044(obj);
    obj->unk_00 = &data_020dd03c;
    obj->unk_98 = 0x4e554c4c;
    return obj;
}
