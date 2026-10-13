/* func_0204ff00 @ 0x0204ff00, 0x17c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[2];
    int unk_04;
    int unk_08;
} UnkStruct_0204ff00;

extern UnkStruct_0204ff00 data_020dce10[];
extern unsigned char data_020e54a8;
extern int func_0204fee8(unsigned int a);

void func_0204ff00(unsigned int a, unsigned int v, int b, int d, int e)
{
    int ok;

    if (a >= 4) {
        return;
    }
    if (b >= 0x38) {
        return;
    }
    switch (v) {
        case 0:
            data_020dce10[a].unk_00 = (unsigned char) v;
            data_020dce10[a].unk_01 = (unsigned char) b;
            data_020dce10[a].unk_04 = d;
            data_020dce10[a].unk_08 = e;
            break;
        case 3:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 1:
            switch (data_020e54a8) {
                case 0:
                    ok = 1;
                    break;
                default:
                    ok = 0;
                    break;
            }
            if (ok != 0) {
                if (func_0204fee8(a) == 3) {
                    data_020dce10[a].unk_00 = (unsigned char) v;
                } else {
                    data_020dce10[a].unk_00 = 8;
                }
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            } else {
                data_020dce10[a].unk_00 = 8;
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            }
            break;
        case 2:
            switch (data_020e54a8) {
                case 0:
                    ok = 1;
                    break;
                default:
                    ok = 0;
                    break;
            }
            if (ok != 0) {
                if (func_0204fee8(a) == 3 || func_0204fee8(a) == 8 || func_0204fee8(a) == 1) {
                    data_020dce10[a].unk_00 = (unsigned char) v;
                } else {
                    data_020dce10[a].unk_00 = 8;
                }
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            } else {
                data_020dce10[a].unk_00 = 8;
                data_020dce10[a].unk_01 = (unsigned char) b;
                data_020dce10[a].unk_04 = d;
                data_020dce10[a].unk_08 = e;
            }
            break;
        case 4:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 5:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
        case 8:
            data_020dce10[a].unk_00 = 8;
            data_020dce10[a].unk_01 = (unsigned char) b;
            data_020dce10[a].unk_04 = d;
            data_020dce10[a].unk_08 = e;
            break;
        case 6:
        case 7:
        default:
            data_020dce10[a].unk_00 = (unsigned char) v;
            break;
    }
}
