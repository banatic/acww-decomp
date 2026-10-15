/* func_020901a0 @ 0x020901a0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02088450(char *);
extern int func_02079904(char *);
extern void *func_020b1a54(char *);
extern void func_02066688(char *);

char *func_020901a0(char *p)
{
    func_02088450(p + 0x93A);
    func_02079904(p + 0x14C);
    func_020b1a54(p + 0x100);
    func_02066688(p);
    return p;
}
