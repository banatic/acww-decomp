/* func_020b3670 @ 0x020b3670, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b3670 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    short unk_10;
    short unk_12;
};

int func_020b3670(struct UnkStruct_020b3670 *o, int a, int b, int c, int d)
{
    o->unk_08 = d;
    if (a != 0) {
        if (o->unk_04 != 0) {
            goto fail;
        }
        o->unk_04 = 0x1000;
        if (b == 0) {
            o->unk_00 = 0x1000;
            return 0;
        } else {
            if (c != 0) {
                o->unk_0C = 1;
                o->unk_10 = 0;
                o->unk_12 = 5;
            }
            return 1;
        }
    } else {
        o->unk_0C = 0;
        if (o->unk_04 == 0) {
            goto fail;
        }
        o->unk_04 = 0;
        if (b == 0) {
            o->unk_00 = 0;
            return 0;
        } else {
            return 1;
        }
    }
fail:
    return 0;
}
