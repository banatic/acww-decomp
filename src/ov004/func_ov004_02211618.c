/* func_ov004_02211618 @ 0x02211618, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02210cf0(void *);
extern int data_ov004_022526f8;
extern int data_ov004_022527a4;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02211618;

void *func_ov004_02211618(UnkStruct_02211618 *obj)
{
    obj->unk_00 = &data_ov004_022526f8;
    obj->unk_EC = &data_ov004_022527a4;
    func_ov004_02210cf0(obj);
    return obj;
}
