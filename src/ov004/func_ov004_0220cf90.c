/* func_ov004_0220cf90 @ 0x0220cf90, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x16c - 0x90];
    short unk_16C;
} UnkStruct_0220cf90;

extern int func_ov004_0220ebe0(UnkStruct_0220cf90 *, int);
extern void func_ov004_0220ccf8(UnkStruct_0220cf90 *, int);
extern void func_02095380(int);

int func_ov004_0220cf90(UnkStruct_0220cf90 *p, int b)
{
    if (func_ov004_0220ebe0(p, b)) {
        p->unk_16C = p->unk_8E + b;
        func_ov004_0220ccf8(p, 2);
        func_02095380(0x4c4);
        return 1;
    }
    return 0;
}
