/* func_0209cfb8 @ 0x0209cfb8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e8b4(void *ptr);
extern void func_02138c48(void *obj, int a, int b, void (*cb)(void));
extern void func_0209d038(void);

void *func_0209cfb8(void *obj)
{
    func_0206e8b4((char *) obj + 0x120);
    func_02138c48(obj, 0x24, 8, func_0209d038);
    return obj;
}
