/* func_0203e020 @ 0x0203e020, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(int);
extern int func_0203efbc(int);

typedef struct {
    char pad_00[0x10];
    int unk_10;
    char pad_14[2];
    unsigned char unk_16;
} UnkStruct_0203e020;

extern UnkStruct_0203e020 *data_021c72b8;

int func_0203e020(int param)
{
    UnkStruct_0203e020 *p;
    if (func_0203e4c0(2) != 0) {
        goto outer_success;
    }
    if (func_0203e4c0(6) != 0) {
        goto outer_success;
    }
    if (func_0203e4c0(7) != 0) {
        goto outer_success;
    }
    return 0;

outer_success:
    p = data_021c72b8;
    if (p->unk_10 == func_0203efbc(param)) {
        goto inner_success;
    }
    return 0;

inner_success:
    p->unk_16 = 6;
    return 1;
}
