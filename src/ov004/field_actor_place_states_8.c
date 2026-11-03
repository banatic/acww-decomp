/* field_actor_place_states_8: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b9c0 @ 0x0222b9c0, 0x14 bytes, Thumb
 * func_ov004_0222b9bc @ 0x0222b9bc, 0x4 bytes, Thumb
 * func_ov004_0222b9b4 @ 0x0222b9b4, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_0222b9bc;

void func_ov004_0222b9c0(void *p, int a, int b, short c, unsigned char d)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
    *(short *) ((char *) p + 8) = c;
    *((unsigned char *) p + 0xa) = d;
}

void func_ov004_0222b9bc(UnkStruct_0222b9bc *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_0222b9b4(unsigned char *a, unsigned char *b)
{
    *b = *a;
}
