/* func_02044878 @ 0x02044878, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02044878 *data_020ccf94;
extern int func_02073d90(struct UnkStruct_02044878 *s);

struct UnkStruct_02044878 {
    char pad_00[0x68];
    int unk_68;
};

int func_02044878(int param)
{
    struct UnkStruct_02044878 *s;

    s = data_020ccf94;
    if (func_02073d90(s) != 0) {
        return param;
    } else {
        return s->unk_68;
    }
}
