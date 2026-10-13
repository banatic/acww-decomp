/* func_ov004_02215b44 @ 0x02215b44, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02215e70(void *);
extern int data_ov004_02250f88;
extern int data_ov004_02251034;

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02215b44;

void *func_ov004_02215b44(UnkStruct_02215b44 *obj)
{
    obj->unk_00 = &data_ov004_02250f88;
    obj->unk_EC = &data_ov004_02251034;
    func_ov004_02215e70(obj);
    return obj;
}
