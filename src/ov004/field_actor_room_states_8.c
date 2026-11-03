/* field_actor_room_states_8: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022283c8 @ 0x022283c8, 0x4 bytes, Thumb
 * func_ov004_022283c4 @ 0x022283c4, 0x4 bytes, Thumb
 * func_ov004_022283bc @ 0x022283bc, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned long unk_00;
} UnkStruct_022283c8;

typedef struct {
    unsigned char unk_00;
} UnkStruct_022283c4;

void func_ov004_022283c8(UnkStruct_022283c8 *p, unsigned long v)
{
    p->unk_00 = v;
}

void func_ov004_022283c4(UnkStruct_022283c4 *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_022283bc(unsigned char *a, unsigned char *b)
{
    *b = *a;
}
