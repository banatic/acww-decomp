/* func_ov142_02299ba4 @ 0x02299ba4, 0x78 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299ba4 {
    char pad_00[0xA8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x14C - 0xB4];
    void *unk_14C;
};

extern int func_020e895c(void *addr, int val, int size);
extern void func_ov002_0220a4c8(void *addr);
extern void func_ov142_02299a80(struct UnkStruct_02299ba4 *obj);
extern void func_ov142_02299ab8(struct UnkStruct_02299ba4 *obj);

void func_ov142_02299ba4(struct UnkStruct_02299ba4 *obj, int val, int flag)
{
    if (flag != 0) {
        val -= 0x34;
    } else {
        val += obj->unk_AC;
    }

    if (val < 0) {
        val = 0;
    }
    if (val > 90) {
        val = 90;
    }

    if (flag != 0) {
        func_020e895c(&obj->unk_A8, val, 8);
    } else {
        obj->unk_A8 = val;
    }

    func_ov142_02299a80(obj);
    func_ov142_02299ab8(obj);

    {
        int diff = obj->unk_B0 - obj->unk_A8;
        if (diff >= 4 || diff <= -4) {
            func_ov002_0220a4c8(&obj->unk_14C);
            obj->unk_B0 = obj->unk_A8;
        }
    }
}
