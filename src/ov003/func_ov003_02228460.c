/* func_ov003_02228460 @ 0x02228460, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x30];
    char unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_02228460;
extern UnkStruct_02228460 data_ov003_0225f35c[];

void func_ov003_02228460(void)
{
    UnkStruct_02228460 *p = data_ov003_0225f35c;
    int i;
    for (i = 0; i < 4; i++) {
        p->unk_30 = 0;
        p->unk_58 = 0;
        p++;
    }
}
