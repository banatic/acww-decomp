/* func_0208af30 @ 0x0208af30, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e20c8;

struct UnkStruct_0208af30 {
    int *p;
    int a;
    int b;
};

void func_0208af30(struct UnkStruct_0208af30 *s)
{
    s->p = &data_020e20c8;
    s->a = 0x80;
    s->b = 0x60;
}
