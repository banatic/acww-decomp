/* func_ov102_0229cd08 @ 0x0229cd08, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d84(void *p);
extern int func_ov002_02209d7c(void *p);

typedef struct {
    char pad_00[0x225c];
    char unk_225C;
    char pad_225D[0x24e0 - 0x225c - 1];
    int unk_24E0;
    int unk_24E4;
} UnkStruct_0229cd08;

void func_ov102_0229cd08(UnkStruct_0229cd08 *obj)
{
    obj->unk_24E0 = func_ov002_02209d84(&obj->unk_225C);
    obj->unk_24E4 = func_ov002_02209d7c(&obj->unk_225C);
}
