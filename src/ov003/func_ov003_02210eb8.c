/* func_ov003_02210eb8 @ 0x02210eb8, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02210eb8 {
    char pad_00[0x8f0];
    unsigned char unk_8F0[1];
} UnkStruct_02210eb8;

typedef struct Pair {
    int x;
    int y;
} Pair;

extern void func_ov003_02210f3c(unsigned char *p0, unsigned char *p1, unsigned char *p2, unsigned char *p3);
extern int func_ov003_02210f58(UnkStruct_02210eb8 *s, Pair *p, unsigned char c, int n, int arg);

void func_ov003_02210eb8(UnkStruct_02210eb8 *s, int arg)
{
    unsigned char vals[3];
    Pair pair;
    func_ov003_02210f3c(s->unk_8F0, &vals[0], &vals[1], &vals[2]);
    pair.x = vals[0];
    pair.y = vals[1];
    func_ov003_02210f58(s, &pair, vals[2], 6, arg);
}
