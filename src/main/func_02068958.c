/* func_02068958 @ 0x02068958, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02068958 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
};

extern int func_0203d438(struct UnkStruct_02068958 *self);
extern unsigned char data_020cce7c[];

unsigned char func_02068958(struct UnkStruct_02068958 *self)
{
    int ret;
    int c;
    int flag;
    int index;
    ret = func_0203d438(self);
    c = self->unk_18;
    flag = (ret == 0);
    if (self->unk_14 != 7) {
        c = self->unk_14;
    }
    index = ret;
    if (c != 0 && c != 3 && flag) {
        index = 1;
    }
    if (self->unk_28 == 4 && flag) {
        index = 1;
    }
    return data_020cce7c[index];
}
