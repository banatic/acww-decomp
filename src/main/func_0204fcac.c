/* func_0204fcac @ 0x0204fcac, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_020ee62c(void *);
extern void func_02050704(void);

extern unsigned char data_020da13c[];
extern unsigned char data_020dce48[];

void *func_0204fcac(void *obj)
{
    *(unsigned int *) obj = (unsigned int) data_020dce48;
    func_0209d2b4((char *) obj + 0x600);
    __cxa_vec_cleanup((char *) obj + 0x50, 4, 0x16c, func_02050704);
    *(unsigned int *) obj = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
