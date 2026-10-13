/* func_0201f814 @ 0x0201f814, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Other {
    char pad_00[0x830];
    int c;
} Other;

typedef struct Main {
    char pad_00[0x100];
    Other *q;
    char pad_104[0x24];
    int a;
    int b;
} Main;

extern void func_0202d8f8(Main *p, int *b, int *a, int c, int arg5);
extern void func_020819e0(int b);

void func_0201f814(Main *p)
{
    int arg5 = 0;
    func_0202d8f8(p, &p->b, &p->a, p->q->c, arg5);
    if (p->b != 0) {
        func_020819e0(p->b);
    }
}
