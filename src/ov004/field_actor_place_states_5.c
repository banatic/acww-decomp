/* field_actor_place_states_5: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b4dc @ 0x0222b4dc, 0x4 bytes, Thumb
 * func_ov004_0222b4d4 @ 0x0222b4d4, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b4dc;

void func_ov004_0222b4dc(UnkStruct_0222b4dc *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_0222b4d4(unsigned char *a, unsigned char *b)
{
    *b = *a;
}
