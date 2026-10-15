/* func_020534cc @ 0x020534cc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020530b0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

extern unsigned char data_021c89fc[];

void func_020534cc(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021c89fc), 8, 0x48, (((void (*)(void *)) func_020530b0)));
}
