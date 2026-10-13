/* func_0203392c @ 0x0203392c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202f8fc(int, int, int);

struct UnkStruct_0203392c {
    int unk_00;
    int a;
    int b;
    int c;
    int d;
};

int func_0203392c(int param, struct UnkStruct_0203392c *p)
{
    int avg_x = (p->a + p->c) >> 1;
    int avg_y = (p->b + p->d) >> 1;
    return func_0202f8fc(param, avg_x, avg_y);
}
