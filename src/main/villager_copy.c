/* villager_copy: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02079914 @ 0x02079914, 0x10 bytes, Thumb
 * func_02079904 @ 0x02079904, 0x10 bytes, Thumb
 * func_02079900 @ 0x02079900, 0x2 bytes, Thumb
 */

extern int func_020817a8(int arg);
extern int func_02081710(int);

int func_02079914(int arg)
{
    func_020817a8(arg);
    return arg;
}

int func_02079904(int arg)
{
    func_02081710(arg);
    return arg;
}

int func_02079900(int address)
{
    return address;
}
