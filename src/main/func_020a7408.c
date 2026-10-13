/* func_020a7408 @ 0x020a7408, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7704(int *p, int *a, int *b);
extern void func_020a7710(int *p, int a, int b);

typedef struct {
    int x, y;
} Pair;

extern Pair data_021f432c[];

void func_020a7408(int p0, int p1)
{
    Pair *base = data_021f432c;
    int i;
    for (i = 3; i >= 0; i--) {
        int b, a;
        func_020a7704((int *) base, &a, &b);
        if (a >= 4) {
            func_020a7710((int *) base, p0, p1);
            break;
        }
        base++;
    }
}
