/* npc_plc_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3c18 @ 0x020c3c18, 0x6 bytes, Thumb
 * func_020c3c08 @ 0x020c3c08, 0x10 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_020c3c18;

struct UnkStruct_020c3c08 {
    int *ptr;
    char flag;
};

extern int data_020d315c;

void func_020c3c18(UnkStruct_020c3c18 *p, unsigned long v)
{
    p->unk_B0 = v;
}

void func_020c3c08(int unused, struct UnkStruct_020c3c08 *s)
{
    s->ptr = &data_020d315c;
    s->flag = 0;
}
