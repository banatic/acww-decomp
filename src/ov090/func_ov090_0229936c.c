/* func_ov090_0229936c @ 0x0229936c, 0x60 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229936c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[5];
    unsigned char unk_93;
    unsigned char pad_94[3];
    unsigned char unk_97;
};

extern void func_0206ef8c(void);
extern void func_ov090_0229934c(struct UnkStruct_0229936c *);

unsigned char func_ov090_0229936c(struct UnkStruct_0229936c *p)
{
    switch (p->unk_93) {
        case 7:
            if (p->unk_97 == 0) {
                func_0206ef8c();
                func_ov090_0229934c(p);
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            p->unk_8D = 1;
            break;
        default:
            break;
    }
    return p->unk_93;
}
