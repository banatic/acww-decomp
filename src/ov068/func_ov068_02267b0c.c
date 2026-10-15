/* func_ov068_02267b0c @ 0x02267b0c, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[0x16];
    unsigned short unk_3A;
} UnkStruct_02267b0c;

extern void func_ov068_0226cce8(UnkStruct_02267b0c *obj, int param2, int zero);
extern void func_0203eddc(int param);
extern int func_0203e0a8(int param, int zero);

void func_ov068_02267b0c(UnkStruct_02267b0c *obj, int param2)
{
    if (obj->unk_20 == 0) {
        obj->unk_3A = 0x4b0;
        func_ov068_0226cce8(obj, param2, 0);
        func_0203eddc(param2);
    } else {
        func_0203e0a8(param2, 0);
    }
}
