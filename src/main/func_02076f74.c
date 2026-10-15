/* func_02076f74 @ 0x02076f74, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int, char *, unsigned int);
extern void func_020b260c(char *, unsigned int);

void func_02076f74(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, a1);
    func_020b260c(buf, a4);
}
