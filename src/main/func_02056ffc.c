/* func_02056ffc @ 0x02056ffc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
} UnkStruct_02056ffc;

void func_02056ffc(UnkStruct_02056ffc *o)
{
    int field8;
    unsigned char flag;
    int result;

    field8 = o->unk_08;
    o->unk_0C = field8;
    flag = o->unk_14;

    if (flag & 2) {
        int field10 = o->unk_10;
        if (field8 >= field10) {
            result = field8 - field10;
        } else {
            if (!(flag & 1)) {
                int field4 = o->unk_04;
                result = field8 + (field4 - field10);
            } else {
                result = 0;
            }
        }
    } else {
        int field10 = o->unk_10;
        int sum = field8 + field10;
        int field4 = o->unk_04;
        if (sum >= field4) {
            if (!(flag & 1)) {
                result = sum - field4;
            } else {
                result = field4 - 0x1000;
            }
        } else {
            result = sum;
        }
    }
    o->unk_08 = result;
}
