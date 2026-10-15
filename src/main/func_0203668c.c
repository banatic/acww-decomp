/* func_0203668c @ 0x0203668c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203668c {
    char pad_00[8];
    unsigned char unk_08;
    char pad_09;
    unsigned short unk_0A;
};

extern int func_020b65c4(void);
extern int func_02036754(int a);
extern void func_020366c0(struct UnkStruct_0203668c *s);
extern void func_020366e0(struct UnkStruct_0203668c *s, int a);

void func_0203668c(struct UnkStruct_0203668c *s)
{
    int a;
    int b;

    a = func_020b65c4();
    if (s->unk_08 == a) {
        return;
    }

    b = func_02036754(a);
    if (s->unk_0A != b) {
        func_020366c0(s);
        func_020366e0(s, a);
    }

    s->unk_08 = a;
}
