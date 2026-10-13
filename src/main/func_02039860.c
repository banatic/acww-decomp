/* func_02039860 @ 0x02039860, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x94];
    int unk_A4;
    int pad_A8;
    int unk_AC;
    int pad_B0[2];
} UnkStruct_02039860;
typedef struct {
    unsigned char pad_00[4];
    UnkStruct_02039860 arr[4];
} UnkStruct_02039860_2;
extern UnkStruct_02039860_2 *data_021c6738;

int func_02039860(void)
{
    int ret = 0;
    int i;
    UnkStruct_02039860 *e;
    unsigned int flag;
    for (i = 0; i < 4; i++) {
        e = &data_021c6738->arr[i];
        if (e->unk_0C != 0) {
            if (e->unk_A4 != 0) {
                goto set;
            }
        }
        if (e->unk_AC > 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag > 0) {
        set:
            ret = 1;
            break;
        }
    }
    return ret;
}
