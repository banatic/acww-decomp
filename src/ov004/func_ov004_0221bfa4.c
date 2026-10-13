/* func_ov004_0221bfa4 @ 0x0221bfa4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_02253674;
extern char data_ov004_022535e4;
extern void func_0202de4c(void *p);
extern void func_0202e5e0(void *p);

typedef struct {
    void *unk_00;
    char pad_04[0x8a0 - 4];
    void *unk_8A0;
} UnkStruct_0221bfa4;

void *func_ov004_0221bfa4(UnkStruct_0221bfa4 *obj)
{
    obj->unk_00 = &data_ov004_02253674;
    obj->unk_8A0 = &data_ov004_022535e4;
    func_0202de4c((void *) &obj->unk_8A0);
    func_0202e5e0(obj);
    return obj;
}
