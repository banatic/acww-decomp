/* func_020653d0 @ 0x020653d0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[20];
    int unk_14;
} UnkStruct_020653d0;

extern void func_020653b0(UnkStruct_020653d0 *param);
extern void func_02065354(UnkStruct_020653d0 *param);

void func_020653d0(UnkStruct_020653d0 *param)
{
    switch (param->unk_14) {
        case 1:
            func_020653b0(param);
            break;
        case 2:
            func_02065354(param);
            break;
    }
}
