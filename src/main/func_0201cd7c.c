/* func_0201cd7c @ 0x0201cd7c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;
struct UnkStruct_0201cd7c {
    char pad_00[0x40];
    char unk_40;
    int unk_44;
    char unk_48;
    Pair pair;
    char pad_54[4];
    char unk_58;
    char unk_59;
    char unk_5A;
};
extern Pair data_0213dd98;
extern void func_0201ccc0(struct UnkStruct_0201cd7c *p);
void func_0201cd7c(struct UnkStruct_0201cd7c *p)
{
    p->unk_59 = 0;
    p->unk_40 = 5;
    p->unk_44 = 5;
    p->unk_48 = 0;
    p->pair = data_0213dd98;
    func_0201ccc0(p);
    p->unk_58 = 0;
    p->unk_5A = 0;
}
