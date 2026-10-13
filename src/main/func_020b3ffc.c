/* func_020b3ffc @ 0x020b3ffc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d208c[];

struct UnkStruct_020b3ffc {
    char pad_00[0x20];
    int unk_20;
};

int func_020b3ffc(struct UnkStruct_020b3ffc *p)
{
    return data_020d208c[p->unk_20];
}
