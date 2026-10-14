/* func_020839d8 @ 0x020839d8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083a50(void);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02083c78(void *);

extern unsigned char data_020e1aac[];

void *func_020839d8(void *p)
{
    *((unsigned int *) p) = (unsigned int) data_020e1aac;
    __cxa_vec_cleanup((char *) p + 8, 8, 8, func_02083a50);
    func_02083c78(p);
    return p;
}
