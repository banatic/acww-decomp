/* func_0200a354 @ 0x0200a354, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
} GameState;

extern int func_02056f94(void *p);
extern void func_0200a300(GameState *p, int a, int b);

void func_0200a354(GameState *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        func_0200a300(p, 6, -1);
    }
}
