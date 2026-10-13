/* func_ov049_02262664 @ 0x02262664, 0x48 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_020ad8f0(int value);
extern void func_0203e020(void *ptr);
extern void func_ov049_02262a94(void *ptr, int value);

int func_ov049_02262664(char *p)
{
    if (func_02014868(p + 0x618)) {
        return 1;
    }
    if (*(unsigned char *) (p + 0x974) != 0 && func_020ad8f0(*(unsigned char *) (p + 0x974)) == 0) {
        return 1;
    }
    func_0203e020(p);
    func_ov049_02262a94(p, 6);
    return 1;
}
