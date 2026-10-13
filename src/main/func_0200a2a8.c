/* func_0200a2a8 @ 0x0200a2a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200a2a8;

extern int func_02057d34(UnkStruct_0200a2a8 *);
extern int func_02008258(UnkStruct_0200a2a8 *, int);
extern int func_0200c3b0(UnkStruct_0200a2a8 *, int, int, int);

int func_0200a2a8(UnkStruct_0200a2a8 *param)
{
    int ret;

    ret = func_02057d34(param);
    if (ret != 0) {
        return ret;
    }

    param->unk_7FC = func_02008258(param, param->unk_7F0);
    return func_0200c3b0(param, 7, 5, -1);
}
