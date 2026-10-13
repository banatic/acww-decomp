/* func_ov132_0229b2a4 @ 0x0229b2a4, 0x9c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void *p);
extern void func_ov002_02208008(void *p);
extern int func_ov002_02207ffc(void *p);
extern int func_ov002_02207ff0(void *p);
extern void func_ov132_0229b140(void *p);
extern void func_ov132_0229ae4c(void *p);
extern void func_ov132_0229ae90(void *p);
extern void func_ov132_0229b0d0(void *p);
extern void func_ov132_0229ade4(void *p);

struct UnkStruct_0229b2a4 {
    unsigned char pad_00[0x1502];
    unsigned char unk_1502;
};

void func_ov132_0229b2a4(struct UnkStruct_0229b2a4 *p)
{
    unsigned char orig;

    if (func_ov002_02208014(p) != 0) {
        func_ov132_0229b140(p);
        return;
    }

    func_ov002_02208008(p);
    orig = p->unk_1502;

    if (func_ov002_02207ffc(p) != 0) {
        if (p->unk_1502 != 0) {
            p->unk_1502 = p->unk_1502 - 1;
        }
    } else {
        if (func_ov002_02207ff0(p) != 0) {
            if (p->unk_1502 < 2) {
                p->unk_1502 = p->unk_1502 + 1;
            }
        }
    }

    if (orig != p->unk_1502) {
        func_ov132_0229ae4c(p);
    } else {
        unsigned short flags = data_021fbe40[1];
        if ((flags & 2) != 0) {
            func_ov132_0229ae90(p);
            func_ov132_0229b0d0(p);
        } else if ((flags & 1) != 0) {
            func_ov132_0229ade4(p);
        }
    }
}
