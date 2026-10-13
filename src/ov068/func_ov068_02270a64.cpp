/* func_ov068_02270a64 @ 0x02270a64, 0x9c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02270a64 {
    char pad_00[0x9c];
    char unk_9C[8];
    int unk_A4;
};

extern "C" void func_ov068_02270d24(void *, int);
extern "C" void func_02056fcc(void *, int, int, int, unsigned short);

extern "C" void func_ov068_02270a64(void *a, struct UnkStruct_02270a64 *b, int angle)
{
    short v = (short) (((unsigned int) b->unk_A4 << 4) >> 16);
    int t = angle;
    if (angle < 0) {
        t = -angle;
    }
    if (t > 0x38e) {
        func_ov068_02270d24(a, 0);
        if (angle > 0) {
            func_02056fcc(b->unk_9C, 0, 3, 0x4000, (unsigned short) v);
        } else {
            func_02056fcc(b->unk_9C, 0x5a, 1, 0x4000, (unsigned short) v);
        }
    } else {
        func_ov068_02270d24(a, 1);
        if (v > 0x2d) {
            func_02056fcc(b->unk_9C, 0x2e, 3, 0x4000, (unsigned short) v);
        } else {
            func_02056fcc(b->unk_9C, 0x2e, 1, 0x4000, (unsigned short) v);
        }
    }
}
