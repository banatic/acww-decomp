/* func_ov052_02261424 @ 0x02261424, 0x48 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern int func_020ad888(void);
extern void func_0203e020(void *p);
extern void func_ov052_02261908(void *p, int n);

int func_ov052_02261424(void *obj)
{
    if (func_02014868((char *) obj + 0x618) != 0) {
        return 1;
    }
    if (*(unsigned char *) ((char *) obj + 0x730) != 0) {
        if (func_020ad888() == 0) {
            return 1;
        }
    }
    func_0203e020(obj);
    func_ov052_02261908(obj, 7);
    return 1;
}
