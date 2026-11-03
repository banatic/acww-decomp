/* field_actor_place_states_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b3e0 @ 0x0222b3e0, 0x6 bytes, Thumb
 * func_ov004_0222b3dc @ 0x0222b3dc, 0x4 bytes, Thumb
 * func_ov004_0222b3d4 @ 0x0222b3d4, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b3dc;

void func_ov004_0222b3e0(void *p, int a, int b)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
}

void func_ov004_0222b3dc(UnkStruct_0222b3dc *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_0222b3d4(unsigned char *a, unsigned char *b)
{
    *b = *a;
}
