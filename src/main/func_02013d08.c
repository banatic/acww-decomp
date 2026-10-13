/* func_02013d08 @ 0x02013d08, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019cc8(void *, int, int, int, unsigned int, unsigned int);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char pad[2];
    unsigned char unk_0A;
    unsigned char unk_0B;
} UnkStruct_02013d08;

typedef struct {
    char pad[0x4e8];
    unsigned int flags;
} UnkStruct_02013d08_2;

void func_02013d08(UnkStruct_02013d08 *a, UnkStruct_02013d08_2 *b)
{
    func_02019cc8((char *) b + 0x564, 2, a->unk_04, a->unk_06, a->unk_00, data_020c80f8);
    if ((b->flags & 2) == 0) {
        a->unk_0B = 1;
    }
    b->flags |= 2;
    a->unk_0A = 0;
}
