/* func_02032c8c @ 0x02032c8c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032d10(void *);

void func_02032c8c(void *p)
{
    func_02032d10((char *) p + 0xc);
    *(int *) ((char *) p + 8) = 0;
    *(int *) p = *(int *) ((char *) p + 4);
    *(int *) ((char *) p + 4) = 0;
    *(int *) ((char *) p + 0x24) = 0;
    *(int *) ((char *) p + 0x28) = 0;
    *(int *) ((char *) p + 0x2c) = 0;
}
