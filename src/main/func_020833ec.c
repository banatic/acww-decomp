/* func_020833ec @ 0x020833ec, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083cb8(char *p);
extern void func_0205db70(char *p);
char *func_020833ec(char *p)
{
    func_02083cb8(p);
    func_0205db70(p + 1);
    return p;
}
