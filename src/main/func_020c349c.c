/* func_020c349c @ 0x020c349c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, int, int);
extern void func_0201af1c(int, int);

int func_020c349c(char *p)
{
    func_02019d0c((int) p + 0x564, 3, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_0201af1c((int) p + 0x350, 2);
    return 1;
}
