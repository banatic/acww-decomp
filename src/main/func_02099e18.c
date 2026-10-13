/* func_02099e18 @ 0x02099e18, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642e0(void *);
extern void func_02003738(void *);

typedef struct {
    char pad_00[0xe];
    char unk_0E;
    char pad_0F[0x1e - 0xe - 1];
    unsigned short unk_1E;
    char unk_20;
} UnkStruct_02099e18;

void func_02099e18(UnkStruct_02099e18 *s)
{
    func_020642e0(s);
    func_02003738(&s->unk_0E);
    s->unk_1E = 0xfff1;
    s->unk_20 = -128;
}
