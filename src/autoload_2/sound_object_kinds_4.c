/* sound_object_kinds_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f7dcc @ 0x020f7dcc, 0x24 bytes, ARM
 * func_020f7d9c @ 0x020f7d9c, 0x30 bytes, ARM
 */

extern void func_020f7d4c(void *);

void func_020f7dcc(void *p)
{
    func_020f7d4c(p);
    *(unsigned short *) ((char *) p + 0xe) = 0;
    *(unsigned short *) ((char *) p + 0x10) = 0;
    *(unsigned short *) ((char *) p + 0x12) = 0;
}

void func_020f7d9c(unsigned short *r4)
{
    extern int func_020f7bc4(void *r0, int r1, void *r2);
    unsigned short r0;

    func_020f7bc4(r4, 0x526, (void *) (r4 + 2));
    r0 = 0;
    *(unsigned short *) ((char *) r4 + 0x10) = r0;
    r0 = *(unsigned short *) ((char *) r4 + 0x10);
    *(unsigned short *) ((char *) r4 + 0xe) = r0;
}
