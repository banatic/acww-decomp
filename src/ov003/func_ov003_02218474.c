/* func_ov003_02218474 @ 0x02218474, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2d8 - 4];
    unsigned int unk_704;
} Stru_02218474;

extern void func_02010f5c(void);
extern void func_0200f888(Stru_02218474 *);

void func_ov003_02218474(Stru_02218474 *p)
{
    int v;

    func_02010f5c();

    if (p->unk_704 == 0x32) {
        v = (p->unk_2D8 << 4) >> 16;
        switch (v) {
            case 8:
            case 12:
            case 22:
            case 27:
            case 34:
                func_0200f888(p);
                break;
        }
    } else if (p->unk_704 == 0x33) {
        v = (p->unk_2D8 << 4) >> 16;
        switch (v) {
            case 9:
            case 17:
            case 26:
                func_0200f888(p);
                break;
        }
    }
}
