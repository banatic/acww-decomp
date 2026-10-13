/* func_02038de8 @ 0x02038de8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039080(void *);
extern void func_02039404(void *);
extern void func_020392e8(void *);

int func_02038de8(void *param)
{
    void *r4 = param;
    func_02039080((char *) r4 + 0x50);
    func_02039404((char *) r4 + 0x54);
    func_020392e8((char *) r4 + 0x358);
    return 1;
}
