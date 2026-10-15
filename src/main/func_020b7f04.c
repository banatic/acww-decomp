/* func_020b7f04 @ 0x020b7f04, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned char pad_11[3];
    unsigned int unk_14;
} UnkStruct_020b7f04;

extern void func_0202f268(UnkStruct_020b7f04 *s, int a, int b);

int func_020b7f04(UnkStruct_020b7f04 *s, int a, int b, int c, unsigned char d)
{
    s->unk_14 = c;
    s->unk_10 = d;
    func_0202f268(s, a, b);
    return 1;
}
