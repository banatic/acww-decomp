/* func_020369d0 @ 0x020369d0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da304;
extern void func_02036f60(void *);
extern void func_020370e4(void *);
extern void func_020372ec(void *);

void *func_020369d0(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_020da304;
    func_02036f60((char *) p + 0x24);
    func_020370e4((char *) p + 0x18);
    func_020372ec((char *) p + 0x04);
    return p;
}
