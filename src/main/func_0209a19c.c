/* func_0209a19c @ 0x0209a19c, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);

unsigned short func_0209a19c(void)
{
    unsigned short result;
    int obj[3];

    func_02063ccc(obj, 0, 3);
    func_020638d4(&result, obj, 0, 0, 1, 1, 0);
    func_02063cc8(obj);
    return result;
}
