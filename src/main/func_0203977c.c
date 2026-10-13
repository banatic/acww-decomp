/* func_0203977c @ 0x0203977c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020da5d8;
extern void func_0203a1f8(void);
extern void func_02138c48(void *, unsigned int, unsigned int, void (*)(void));

void *func_0203977c(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_020da5d8;
    func_02138c48((char *) p + 4, 4, 0xb8, func_0203a1f8);
    return p;
}
