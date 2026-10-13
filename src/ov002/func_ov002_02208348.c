/* func_ov002_02208348 @ 0x02208348, 0x6e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02208348 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x4];
    int unk_14;
    unsigned char unk_18;
} UnkStruct_02208348;

extern void func_02002808(int, int, int, int, int);

void func_ov002_02208348(UnkStruct_02208348 *obj, int param2)
{
    int val = 0;
    int val2 = val;
    int val3 = 0xff;
    int val4 = 0xc0;

    switch (obj->unk_18) {
        case 0:
            val2 = obj->unk_0C - obj->unk_14;
            if (val2 < 0) {
                val2 = val;
            }
            break;
        case 1:
            val4 = obj->unk_14 + 0xc0 - obj->unk_0C;
            if (val4 > 0xbf) {
                val4 = 0xbf;
            }
            break;
        case 2:
            val3 = val3 - obj->unk_0C;
            if (val3 < 1) {
                val3 = 1;
            }
            break;
        case 3:
            val = obj->unk_0C;
            if (val > 0xfe) {
                val = 0xfe;
            }
            break;
        default:
            break;
    }

    func_02002808(param2, val, val2, val3, val4);
}
