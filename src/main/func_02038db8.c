/* func_02038db8 @ 0x02038db8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039064(void *);
extern int func_02011ec8(void);
extern void func_020393b4(void *);
extern void func_020392dc(void *);

int func_02038db8(void *param)
{
    void *r4 = param;
    func_02039064((char *) param + 0x50);
    if (func_02011ec8() != 0) {
        func_020393b4((char *) r4 + 0x54);
    }
    func_020392dc((char *) r4 + 0x358);
    return 1;
}
