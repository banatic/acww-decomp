/* func_020c19fc @ 0x020c19fc, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *);
extern void *func_02099688(void *);
extern int func_020882ec(void *);
extern int func_02015e70(void *, int, int);

int func_020c19fc(void *param)
{
    void *a = func_02099688(func_020984e8(param));
    func_02015e70(param, func_020882ec(a), 0);
    return func_02015e70(param, func_020882ec(a), 1);
}
