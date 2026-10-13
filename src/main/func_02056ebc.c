/* func_02056ebc @ 0x02056ebc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(unsigned int *);

extern unsigned char data_020dd174[];

unsigned int *func_02056ebc(unsigned int *arg)
{
    *arg = (unsigned int) data_020dd174;
    func_020edb3c(arg);
    return arg;
}
