/* func_02041788 @ 0x02041788, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020417ac(void);
extern int func_02073d90(unsigned int);
extern void func_02041644(void);

void func_02041788(void)
{
    func_020417ac();
    if (func_02073d90(data_020ccf94) == 0) {
        func_02041644();
    }
}
