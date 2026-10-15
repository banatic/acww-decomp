/* func_ov003_02218754 @ 0x02218754, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern int func_ov003_022186cc(void *a, int b, int c, int d, int e, int f, int g);

struct Sub_02218754 {
    int unk_00;
    int unk_04;
    short unk_08;
};

void func_ov003_02218754(char *a)
{
    if (func_02056f94(a + 0x2d0)) {
        struct Sub_02218754 *p = (struct Sub_02218754 *) (a + 0x7d4);
        func_ov003_022186cc(a, 1, p->unk_00, p->unk_04, p->unk_08, 6, -1);
    }
}
