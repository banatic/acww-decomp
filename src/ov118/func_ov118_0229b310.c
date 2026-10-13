/* func_ov118_0229b310 @ 0x0229b310, 0x64 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

struct UnkStruct_0229b310 {
    char pad_00[0x98];
    unsigned short unk_98;
};

extern int func_ov118_0229a460(struct UnkStruct_0229b310 *self, int arg);
extern void func_ov118_0229afd4(struct UnkStruct_0229b310 *self, unsigned char arg);

int func_ov118_0229b310(struct UnkStruct_0229b310 *self)
{
    int a = data_021f6c58;
    int b = data_021f6c54;
    int r5;

    if (a < 0x98 || a > 0xe8) {
        return 0;
    }
    if (b < 0x50 || b >= 0xb0) {
        return 0;
    }

    r5 = (b + (self->unk_98 - 0x50)) >> 4;

    if (func_ov118_0229a460(self, 1) && r5 == 5) {
        return 0;
    }

    func_ov118_0229afd4(self, (unsigned char) (r5 + 15));
    return 1;
}
