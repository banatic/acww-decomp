/* func_ov123_022999b0 @ 0x022999b0, 0x12c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern void RtcSendPxiCommand(int cmd);
extern void func_020041bc(unsigned char byte);
extern int func_ov123_0229ae7c(void *obj, unsigned char byte);

typedef struct {
    char pad_00[0xaf];
    unsigned char unk_AF;
    unsigned char unk_B0;
    char pad_B1[2];
    unsigned char unk_B3;
} UnkStruct_022999b0;

int func_ov123_022999b0(UnkStruct_022999b0 *obj, int param1, int param2)
{
    unsigned char new_af, new_b0;

    new_af = obj->unk_AF;
    new_b0 = obj->unk_B0;

    if (data_021fbe40[0] & 0x20) {
        if (data_021fbe40[1] & 0x20) {
            obj->unk_B3 = 4;
        }
        if (new_af != 0) {
            new_af--;
        }
    } else {
        if (data_021fbe40[0] & 0x10) {
            if (data_021fbe40[1] & 0x10) {
                obj->unk_B3 = 4;
            }
            if (new_af < 0x1F) {
                new_af++;
            }
        }
    }

    if (data_021fbe40[0] & 0x40) {
        if (data_021fbe40[1] & 0x40) {
            obj->unk_B3 = 4;
        }
        if (new_b0 != 0) {
            new_b0--;
        }
    } else {
        if (data_021fbe40[0] & 0x80) {
            if (data_021fbe40[1] & 0x80) {
                obj->unk_B3 = 4;
            }
            if (new_b0 < 0x1F) {
                new_b0++;
            }
        }
    }

    if (obj->unk_AF != new_af) {
        goto else_part;
    }
    if (obj->unk_B0 == new_b0) {
        goto return0;
    }

else_part:
    if (obj->unk_B3 == 0) {
        goto common;
    }
    if (obj->unk_B3 == 4) {
        obj->unk_B3--;
        goto common;
    }
    obj->unk_B3--;
    return 0;

common:
    obj->unk_AF = new_af;
    obj->unk_B0 = new_b0;
    if (param2 == 0) {
        RtcSendPxiCommand(0x865);
    }
    func_020041bc((unsigned char) func_ov123_0229ae7c(obj, new_af));
    return 1;

return0:
    obj->unk_B3 = 0;
    return 0;
}
