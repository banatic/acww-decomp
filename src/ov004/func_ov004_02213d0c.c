/* func_ov004_02213d0c @ 0x02213d0c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02251ff0;
extern int data_ov004_0225209c;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02213d0c;

void *func_ov004_02213d0c(UnkStruct_02213d0c *obj)
{
    obj->unk_00 = &data_ov004_02251ff0;
    obj->unk_EC = &data_ov004_0225209c;
    func_ov004_02210cf0(obj);
    return obj;
}
