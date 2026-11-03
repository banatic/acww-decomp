/* scene_action: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02013d08 @ 0x02013d08, 0x54 bytes, Thumb
 * func_02013c98 @ 0x02013c98, 0x70 bytes, Thumb
 */

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

extern int func_02019cc8(void *, int, int, int, unsigned int, unsigned int);
extern unsigned short data_020c80f8;
extern int func_02019e00(void *ptr);
extern int func_02019de8(void *ptr);
extern int func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, unsigned int i, int j);

void func_02013d08(UnkStruct_02013d08 *a, UnkStruct_02013d08_2 *b)
{
    func_02019cc8((char *) b + 0x564, 2, a->unk_04, a->unk_06, a->unk_00, data_020c80f8);
    if ((b->flags & 2) == 0) {
        a->unk_0B = 1;
    }
    b->flags |= 2;
    a->unk_0A = 0;
}

void func_02013c98(unsigned char *param0, unsigned char *param1)
{
    if (func_02019e00(param1 + 0x564) == 7 && func_02019de8(param1 + 0x564) != 0) {
        func_02019d0c(param1 + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        if (param0[0xb] == 1) {
            *(unsigned int *) (param1 + 0x4e8) &= ~2;
        }
        param0[0xa] = 1;
        param0[0x8] = 5;
    }
}
