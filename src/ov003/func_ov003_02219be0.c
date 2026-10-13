/* func_ov003_02219be0 @ 0x02219be0, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);

struct UnkStruct_02219be0 {
    char pad_00[0x7d4];
    unsigned char unk_7D4[0x1c];
    int unk_7F0;
    char pad_7F4[0x820 - 0x7f4];
    unsigned short unk_820;
};

unsigned int func_ov003_02219be0(void)
{
    unsigned int r;
    struct UnkStruct_02219be0 *o = (struct UnkStruct_02219be0 *) func_02096718(4);
    r = 0xfff1;
    if (o != 0) {
        switch (o->unk_7F0) {
            case 0x57: {
                unsigned char *p = o->unk_7D4;
                if (p[6] == 0) {
                    unsigned int i = p[8];
                    if (i < 0x38) {
                        r = (unsigned short) (i + 0x12b0);
                    } else {
                        r = 0x12b0;
                    }
                }
                break;
            }
            case 0x54: {
                unsigned char *p = o->unk_7D4;
                if (p[4] == 0) {
                    unsigned int i = p[3];
                    if (i < 0x38) {
                        if (i < 0x38) {
                            r = (unsigned short) (i + 0x12e8);
                        } else {
                            r = 0x12e8;
                        }
                    }
                }
                break;
            }
            case 0x5f: {
                int in = 0;
                unsigned int v = o->unk_820;
                if (v >= 0x1549 && v <= 0x1549) {
                    in = 1;
                }
                if (in) {
                    r = v;
                }
                break;
            }
        }
    }
    return r;
}
