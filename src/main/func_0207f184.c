/* func_0207f184 @ 0x0207f184, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b5ec(char *p);
extern unsigned int func_0209c304(int val);
extern int func_0209c330(int val);
extern void func_0209bff0(void *p, int val);

void func_0207f184(char *p0, void *p1)
{
    if (func_0209c304(func_0209b5ec(p0 + 0x734)) <= 1) {
        func_0209bff0(p1, func_0209c330(func_0209b5ec(p0 + 0x734)));
    } else {
        func_0209bff0(p1, 7);
    }
}
