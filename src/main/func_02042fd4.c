/* func_02042fd4 @ 0x02042fd4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204811c(void *dst, const void *src);

extern unsigned char data_021c779c[];

void func_02042fd4(void *src)
{
    struct {
        unsigned int a;
        unsigned int b;
        unsigned int c;
    } local;
    unsigned int *p = (unsigned int *) src;
    local.a = p[0];
    local.b = p[1];
    local.c = p[2];
    func_0204811c((void *) data_021c779c, &local);
}
