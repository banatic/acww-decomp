/* func_0201298c @ 0x0201298c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0201298c;

extern void func_0204f818(int *a, int *b, int c);

int func_0201298c(UnkStruct_0201298c *s, int param)
{
    int a, b;
    a = 0;
    b = 0;
    func_0204f818(&a, &b, param);
    if (a == s->unk_0C && b == s->unk_10) {
        return 1;
    }
    return 0;
}
