/* actor_table: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082578 @ 0x02082578, 0x14 bytes, Thumb
 * func_02082568 @ 0x02082568, 0x10 bytes, Thumb
 * func_02082554 @ 0x02082554, 0x14 bytes, Thumb
 * func_02082544 @ 0x02082544, 0x10 bytes, Thumb
 */

extern int func_02082ab0(int, int, int);
extern unsigned char data_021d1d4c[];
extern int func_02082a84(void *a, void *b);
extern int func_02082808(int *p, int a, int b);
extern int func_020827dc(void *param1, void *param2);

int func_02082578(int a, int b)
{
    return func_02082ab0((unsigned int) data_021d1d4c, a, b);
}

int func_02082568(void *arg)
{
    return func_02082a84((void *) data_021d1d4c, arg);
}

int func_02082554(int a, int b)
{
    return func_02082808(((int *) data_021d1d4c), a, b);
}

void func_02082544(void *param)
{
    func_020827dc((void *) data_021d1d4c, param);
}
