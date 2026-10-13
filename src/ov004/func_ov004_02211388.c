/* func_ov004_02211388 @ 0x02211388, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a : 8;
    unsigned int b : 16;
    unsigned int c : 8;
} BF;
typedef union {
    unsigned int w;
    BF unk_00;
} UnkStruct_02211388;
unsigned int func_ov004_02211388(unsigned int v)
{
    UnkStruct_02211388 u;
    u.w = v;
    return u.unk_00.b;
}
