/* func_0202d730 @ 0x0202d730, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019c6c(int arg0, int arg1, unsigned short arg2);
extern unsigned short data_020c80f8;

typedef struct {
    char pad_00[0x100];
    int unk_100;
} UnkStruct_0202d730;

int func_0202d730(UnkStruct_0202d730 *param)
{
    return func_02019c6c(param->unk_100 + 0x564, 2, data_020c80f8);
}
