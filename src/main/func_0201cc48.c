/* func_0201cc48 @ 0x0201cc48, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x58];
    unsigned char unk_58;
} UnkStruct_0201cc48;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GlobStruct_0201cc48;

extern GlobStruct_0201cc48 *data_020ccf94;
extern int func_02073dd4(GlobStruct_0201cc48 *p, int x);

void func_0201cc48(UnkStruct_0201cc48 *arg)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        arg->unk_58 = 1;
    }
}
