/* func_ov003_02215f4c @ 0x02215f4c, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02215f4c {
    int a;
    int b;
};
struct UnkStruct_02215f4c_2 {
    int a;
    int pad_04;
    int c;
};
void func_ov003_02215f4c(struct UnkStruct_02215f4c *d, struct UnkStruct_02215f4c_2 *s)
{
    d->a = s->a;
    d->b = s->c;
}
