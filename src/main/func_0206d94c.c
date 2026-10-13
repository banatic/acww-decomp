/* func_0206d94c @ 0x0206d94c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a887c(void *p);

extern unsigned char data_020df1e8[];

void *func_0206d94c(void *p)
{
    *((void **) p) = (void *) data_020df1e8;
    func_020a887c(p);
    return p;
}
