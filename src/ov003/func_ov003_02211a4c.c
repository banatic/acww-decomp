/* func_ov003_02211a4c @ 0x02211a4c, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_020109a0(void *, int, int, int);
extern int func_02008258(void *, int);
extern int func_0200d4e8(void *, int, int, int);

struct UnkStruct_02211a4c {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x704 - 0x2d0 - 1];
    int unk_704;
    char pad_708[0x7d4 - 0x704 - 4];
    unsigned char unk_7D4;
    char pad_7D5[0x7f0 - 0x7d4 - 1];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
};

void func_ov003_02211a4c(struct UnkStruct_02211a4c *this)
{
    if (func_02056f94(&this->unk_2D0) != 0) {
        if (this->unk_704 == 0x49) {
            if (this->unk_7D4 != 0) {
                func_020109a0(this, 0x4e, 3, 0);
            } else {
                func_020109a0(this, 0x4b, 3, 0);
            }
        } else {
            this->unk_7FC = func_02008258(this, this->unk_7F0);
            func_0200d4e8(this, 3, 1, -1);
        }
    }
}
