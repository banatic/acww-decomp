/* func_02081a14 @ 0x02081a14, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int count);
struct UnkStruct_02081a14 {
    char pad_00[0x70];
    unsigned int unk_70;
};
int func_02081a14(struct UnkStruct_02081a14 *this)
{
    int count = 0;
    int i;
    int rnd;
    int result = 0;
    if (this->unk_70 == -1) {
        this->unk_70 = 0;
    }
    for (i = 0; i < 32; i++) {
        if (((this->unk_70 >> i) & 1) == 0) {
            count++;
        }
    }
    rnd = func_020644cc(count);
    for (i = 0; i < 32; i++) {
        if (((this->unk_70 >> i) & 1) == 0) {
            if (rnd == 0) {
                result = i;
                break;
            }
            rnd--;
        }
    }
    if (count == 1) {
        this->unk_70 = 0;
    }
    this->unk_70 |= (1 << result);
    return result;
}
