/* func_ov004_0221284c @ 0x0221284c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_02210cf0(void *);
extern int data_ov004_02250e5c;
extern int data_ov004_02250f08;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_0221284c;

void *func_ov004_0221284c(UnkStruct_0221284c *obj)
{
    obj->unk_00 = &data_ov004_02250e5c;
    obj->unk_EC = &data_ov004_02250f08;
    func_ov004_02210cf0(obj);
    return obj;
}
