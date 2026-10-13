/* func_ov004_0221d560 @ 0x0221d560, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_02253868;
extern char data_ov004_022537d8;
extern void func_0202de4c(void *p);
extern void func_0202e5e0(void *p);

typedef struct {
    void *unk_00;
    char pad_04[0x89c - 4];
    void *unk_89C;
} UnkStruct_0221d560;

void *func_ov004_0221d560(UnkStruct_0221d560 *obj)
{
    obj->unk_00 = &data_ov004_02253868;
    obj->unk_89C = &data_ov004_022537d8;
    func_0202de4c((void *) &obj->unk_89C);
    func_0202e5e0(obj);
    return obj;
}
