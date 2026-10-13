/* func_ov004_0221137c @ 0x0221137c, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a : 26;
    unsigned int b : 2;
    unsigned int c : 4;
} BF;
typedef union {
    unsigned int w;
    BF unk_00;
} UnkStruct_0221137c;
unsigned int func_ov004_0221137c(unsigned int v)
{
    UnkStruct_0221137c u;
    u.w = v;
    return u.unk_00.b;
}
