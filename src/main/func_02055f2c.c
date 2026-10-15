/* func_02055f2c @ 0x02055f2c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00[0x17];
    int unk_5C;
    int unk_60;
} UnkStruct_02055f2c;

extern void func_02055f6c(UnkStruct_02055f2c *obj);

int func_02055f2c(UnkStruct_02055f2c *obj, int a, int b)
{
    obj->unk_5C = a;
    obj->unk_60 = b;
    func_02055f6c(obj);
    return 1;
}
