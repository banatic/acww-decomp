/* func_ov118_0229ae64 @ 0x0229ae64, 0x2a bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ae64 {
    char pad_00[0xA3];
    unsigned char unk_A3;
    char pad_A4[6];
    unsigned char unk_AA;
};

extern void func_ov118_0229adf0(struct UnkStruct_0229ae64 *p, int v);

void func_ov118_0229ae64(struct UnkStruct_0229ae64 *p)
{
    unsigned char c;
    int v;

    c = p->unk_AA;
    if (c <= 5 || c == 13) {
        v = 0;
    } else {
        v = (c - 5) << 4;
    }
    func_ov118_0229adf0(p, v);
    p->unk_A3 = 0xFF;
}
