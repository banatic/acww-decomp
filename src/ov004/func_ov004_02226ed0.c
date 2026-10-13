/* func_ov004_02226ed0 @ 0x02226ed0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} GameState;

extern int func_02056f94(void *p);
extern void func_ov004_02226e78(GameState *p, int a, int b);

void func_ov004_02226ed0(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_ov004_02226e78(p, 6, -1);
    }
}
