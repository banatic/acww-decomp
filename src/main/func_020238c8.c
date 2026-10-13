/* func_020238c8 @ 0x020238c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207b410(void *);
extern int func_0209a778(void);
extern int func_0209bd44(void);
extern void func_0209bb90(int, int);

extern unsigned char data_021e5a2c[];

void func_020238c8(void)
{
    int r4;
    void *addr;

    addr = (void *) data_021e5a2c;
    func_0207b410(addr);
    r4 = func_0209a778();
    if (func_0209bd44() != 0) {
        func_0209bb90(r4, 1);
    }
}
