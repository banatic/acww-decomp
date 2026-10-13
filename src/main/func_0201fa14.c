/* func_0201fa14 @ 0x0201fa14, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201fa14 {
    char pad_00[0x830];
    void *unk_830;
} UnkStruct_0201fa14;

typedef struct Game {
    char pad_00[0x100];
    void *b;
    char pad_104[0x24];
    void *unk_128;
    void *unk_12C;
} Game;

extern void func_0202d8f8(void *self, void *a, void *b, void *c, int d);
extern void func_020819e0(void *a);

void func_0201fa14(Game *p)
{
    int local = 0;
    func_0202d8f8(p, &p->unk_12C, &p->unk_128, ((UnkStruct_0201fa14 *) p->b)->unk_830, local);
    if (p->unk_12C) {
        func_020819e0(p->unk_12C);
    }
}
