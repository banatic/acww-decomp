/* func_ov009_02262f54 @ 0x02262f54, 0x1e bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200451c(void *p);

struct UnkStruct_02262f54 {
    unsigned char pad_00[0x40];
    unsigned char flag;
};

void func_ov009_02262f54(struct UnkStruct_02262f54 *this)
{
    if (this->flag == 0) {
        func_0200451c(this);
        this->flag = 1;
    }
}
