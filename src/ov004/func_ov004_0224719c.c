/* func_ov004_0224719c @ 0x0224719c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long a, b, c;
} UnkStruct_0224719c;
extern unsigned char *data_021c67a4;
extern int func_0203c0ac(void *, int);
int func_ov004_0224719c(UnkStruct_0224719c *src)
{
    UnkStruct_0224719c *d;
    if (data_021c67a4 != 0) {
        d = (UnkStruct_0224719c *) (data_021c67a4 + 0x1cc);
        d->a = src->a;
        d->b = src->b;
        d->c = src->c;
        return func_0203c0ac(data_021c67a4, 0x10);
    }
    return 0;
}
