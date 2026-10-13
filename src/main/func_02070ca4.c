/* func_02070ca4 @ 0x02070ca4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Copy33To43_(void *a, void *b);
extern void MTX_Concat43(void *a, void *b, void *c);
extern char data_021cfe68[];

void func_02070ca4(void *arg)
{
    char buf[0x34];

    MTX_Copy33To43_(arg, buf);
    MTX_Concat43(buf, data_021cfe68, data_021cfe68);
}
