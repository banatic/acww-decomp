/* func_02077be8 @ 0x02077be8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eb6e8(void *, unsigned int);
extern void func_020eb6a0(void *, int);
extern int func_02077d68(void *);

void func_02077be8(unsigned char *param)
{
    func_020eb6e8(param, 0x41444d4b);
    func_020eb6a0(param, func_02077d68(param + 0x40));
}
