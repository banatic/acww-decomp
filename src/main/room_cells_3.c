/* room_cells_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020534cc @ 0x020534cc, 0x20 bytes, Thumb
 * func_020534ac @ 0x020534ac, 0x20 bytes, Thumb
 */

extern void *func_020530b0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char data_021c89fc[];
extern unsigned char data_021c884c[];

void func_020534cc(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021c89fc), 8, 0x48, (((void (*)(void *)) func_020530b0)));
}

void func_020534ac(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021c884c), 6, 0x48, (((void (*)(void *)) func_020530b0)));
}
