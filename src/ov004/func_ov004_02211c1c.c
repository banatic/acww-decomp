/* func_ov004_02211c1c @ 0x02211c1c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02252950;
extern int data_ov004_022529fc;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02211c1c;

void *func_ov004_02211c1c(UnkStruct_02211c1c *obj)
{
    obj->unk_00 = &data_ov004_02252950;
    obj->unk_EC = &data_ov004_022529fc;
    func_ov004_02210cf0(obj);
    return obj;
}
