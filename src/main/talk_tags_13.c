/* talk_tags_13: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206aae4 @ 0x0206aae4, 0x2 bytes, Thumb
 * func_0206aab0 @ 0x0206aab0, 0x34 bytes, Thumb
 * func_0206aa80 @ 0x0206aa80, 0x30 bytes, Thumb
 * func_0206aa4c @ 0x0206aa4c, 0x34 bytes, Thumb
 */

struct UnkStruct_0206aab0 {
    char pad_00[0x24];
    unsigned int unk_24;
};

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_0206aa80;

typedef struct {
    char pad_00[0x24];
    unsigned int value;
} UnkStruct_0206aa4c;

extern void func_0200467c(int);
extern void func_02067f28(int, int, int, int, int);

void func_0206aae4(void) {}

void func_0206aab0(struct UnkStruct_0206aab0 *param)
{
    func_0200467c(6);
    func_02067f28(param->unk_24, 0x6000, 0x666, 0x4cc, 0x1199);
}

void func_0206aa80(UnkStruct_0206aa80 *param)
{
    func_0200467c(7);
    func_02067f28(param->unk_24, 0xa000, 0x800, 0x800, 0x1333);
}

void func_0206aa4c(UnkStruct_0206aa4c *param)
{
    func_0200467c(8);
    func_02067f28(param->value, 0x11000, 0xa66, 0xccc, 0x1000);
}
