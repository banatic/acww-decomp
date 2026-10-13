/* func_ov003_0222c130 @ 0x0222c130, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222c130;
struct UnkStruct_0222c130_2;
typedef void (UnkStruct_0222c130::*PMF)(UnkStruct_0222c130_2 *);

struct UnkStruct_0222c130_2 {
    unsigned char pad_00[0x30];
    unsigned char unk_30;
};

extern PMF data_ov003_0225f100[];

extern "C" void func_ov003_0222c130(UnkStruct_0222c130 *self, UnkStruct_0222c130_2 *b)
{
    if (data_ov003_0225f100[b->unk_30] != 0) {
        (self->*data_ov003_0225f100[b->unk_30])(b);
    }
}
