/* anim_slots: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205cb94 @ 0x0205cb94, 0x14 bytes, Thumb
 * func_0205cb80 @ 0x0205cb80, 0x14 bytes, Thumb
 */

extern int func_0205cd58(void *, unsigned char);
extern unsigned char data_021c9b58[];
extern unsigned short func_0205cd4c(void *ptr, unsigned char cmd);

int func_0205cb94(unsigned char *param)
{
    return func_0205cd58(((unsigned char *) data_021c9b58), *param);
}

unsigned short func_0205cb80(unsigned char *p)
{
    return func_0205cd4c(data_021c9b58, *p);
}
