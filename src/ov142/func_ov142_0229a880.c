/* func_ov142_0229a880 @ 0x0229a880, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a76c(void *a, void *b, int c, int d, int e);

typedef struct {
    char pad_00[0xd2];
    unsigned short unk_D2;
    char pad_D4[0x10];
    unsigned short unk_E4;
    char pad_E6[0x1602];
    char unk_16E8[1];
} UnkStruct_0229a880;

void func_ov142_0229a880(UnkStruct_0229a880 *obj)
{
    int ret;
    obj->unk_E4 = 0;
    ret = func_ov142_0229a76c(obj, obj->unk_16E8, 0x45dc, 0x7f, 7);
    obj->unk_D2 = ret;
}
