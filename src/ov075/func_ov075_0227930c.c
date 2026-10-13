/* func_ov075_0227930c @ 0x0227930c, 0x58 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0227930c {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_ov075_0227930c(int unused, struct UnkStruct_0227930c *p1, struct UnkStruct_0227930c *p2)
{
    int result = 0;
    unsigned int second_flag = 0;
    unsigned int first_flag = 0;
    int f0a = p1->unk_00;
    int f0b = p2->unk_00;

    if (f0b > f0a - 0x10000 && f0b < f0a + 0x10000) {
        first_flag = 1;
    }
    if (first_flag > 0) {
        int f8a = p1->unk_08;
        int f8b = p2->unk_08;
        if (f8b > f8a - 0x1a000) {
            second_flag = 1;
        }
    }
    if (second_flag > 0) {
        int f8a2 = p1->unk_08;
        int f8b2 = p2->unk_08;
        if (f8b2 < f8a2 + 0xa000) {
            result = 1;
        }
    }
    return result;
}
