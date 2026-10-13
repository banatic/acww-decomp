/* func_ov110_0229ca7c @ 0x0229ca7c, 0x4c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xfa];
    unsigned char unk_FA;
    unsigned char pad_FB[0x21e5];
    char unk_22E0;
    unsigned char pad_22E1[0x63];
    char unk_2344;
} UnkStruct_0229ca7c;

extern int func_ov002_02208ae4(const char *);
extern int func_ov002_02208ad8(const char *, unsigned char);
extern void func_ov002_0220a0b4(const char *, int, int);
extern void func_ov002_0220a374(const char *, int);

void func_ov110_0229ca7c(UnkStruct_0229ca7c *s)
{
    int a, b;
    s->unk_FA = 0;
    a = func_ov002_02208ae4(&s->unk_2344);
    b = func_ov002_02208ad8(&s->unk_2344, s->unk_FA);
    func_ov002_0220a0b4(&s->unk_22E0, a, b);
    func_ov002_0220a374(&s->unk_22E0, 7);
}
