/* func_02093864 @ 0x02093864, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02093864 {
    char unk_00[0x54];
    unsigned int unk_54;
} UnkStruct_02093864;

typedef struct UnkStruct_02093864_2 {
    char unk_00[0xc];
    UnkStruct_02093864 *unk_0C;
} UnkStruct_02093864_2;

extern void func_02094c38(void *p, int a, int b);

void func_02093864(UnkStruct_02093864_2 *p)
{
    func_02094c38(p, 0, 0);
    p->unk_0C->unk_54 = 0xb33;
}
