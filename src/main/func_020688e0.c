/* func_020688e0 @ 0x020688e0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020688e0_2;
struct VT {
    unsigned char pad_00[0x6c];
    int (*unk_6C)(struct UnkStruct_020688e0_2 *o);
};
struct UnkStruct_020688e0_2 {
    struct VT *vt;
};
typedef struct {
    unsigned char pad_00[4];
    unsigned char *unk_04;
    unsigned char pad_08[0x1c];
    int unk_24;
    int unk_28;
} UnkStruct_020688e0;
extern void func_02068b88(UnkStruct_020688e0 *p, int m);
void func_020688e0(UnkStruct_020688e0 *p)
{
    int m = 5;
    if (p->unk_24 == 0) {
        if (p->unk_28 == 9) {
            m = 4;
        }
    } else if (p->unk_24 == 4) {
        if (p->unk_28 != 9) {
            struct UnkStruct_020688e0_2 *o = *(struct UnkStruct_020688e0_2 **) (p->unk_04 + 0x14a8);
            m = o->vt->unk_6C(o);
        }
    }
    if (m != 5) {
        func_02068b88(p, m);
    }
}
