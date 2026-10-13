/* func_020037c8 @ 0x020037c8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011f1c(unsigned int);

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
    char pad_28[0x0A];
    unsigned char unk_32;
    unsigned char unk_33;
    unsigned int unk_34;
    unsigned int unk_38;
} UnkStruct_020037c8;

void func_020037c8(UnkStruct_020037c8 *p)
{
    if (p->unk_24 != 0) {
        return;
    }
    if (p->unk_38 == 5) {
        return;
    }
    if (p->unk_38 == p->unk_34) {
        return;
    }

    func_02011f1c(p->unk_38);
    p->unk_34 = p->unk_38;
    p->unk_38 = 5;

    {
        unsigned int flag = 0;
        if (p->unk_34 <= 4) {
            if ((1U << p->unk_34) & 0x19U) {
                flag = 1;
            }
        }
        p->unk_32 = (unsigned char) flag;
    }
    p->unk_33 = 1;
}
