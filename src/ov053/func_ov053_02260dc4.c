/* func_ov053_02260dc4 @ 0x02260dc4, 0x38 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);

typedef struct {
    char pad_00[0x564];
    char unk_564[0x1b6];
    unsigned char unk_71A;
} UnkStruct_02260dc4;

int func_ov053_02260dc4(UnkStruct_02260dc4 *obj)
{
    unsigned short val;
    int param;

    obj->unk_71A = 100;
    val = data_020c80f8;
    param = 1;

    func_02019c20(obj->unk_564, param, 0xf1, param, val, 0);
    return 1;
}
