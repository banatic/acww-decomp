/* scene_talk_state: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a7ec @ 0x0201a7ec, 0x10 bytes, Thumb
 * func_0201a7e8 @ 0x0201a7e8, 0x2 bytes, Thumb
 * func_0201a7dc @ 0x0201a7dc, 0xa bytes, Thumb
 * func_0201a7d4 @ 0x0201a7d4, 0x6 bytes, Thumb
 * func_0201a7cc @ 0x0201a7cc, 0x6 bytes, Thumb
 * func_0201a7bc @ 0x0201a7bc, 0xe bytes, Thumb
 * func_0201a7b8 @ 0x0201a7b8, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
} UnkStruct_0201a7dc;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0201a7d4;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0201a7cc;

void func_0201a7dc(UnkStruct_0201a7dc *p);

void *func_0201a7ec(void *arg)
{
    func_0201a7dc((UnkStruct_0201a7dc *) arg);
    return arg;
}

void func_0201a7e8(void *object) {}

void func_0201a7dc(UnkStruct_0201a7dc *p)
{
    p->unk_00 = 0;
    p->unk_04 = 2;
}

void func_0201a7d4(UnkStruct_0201a7d4 *p)
{
    p->unk_00 = 1;
}

void func_0201a7cc(UnkStruct_0201a7cc *p)
{
    p->unk_00 = 0;
}

int func_0201a7bc(const unsigned char *ptr)
{
    if (*ptr == 1) {
        return 1;
    } else {
        return 0;
    }
}

void func_0201a7b8(int *p0, int p1)
{
    p0[1] = p1;
}
