/* func_ov086_02279088 @ 0x02279088, 0x30 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov086_02278e6c(void *, void *);

int func_ov086_02279088(void *obj)
{
    if (func_0202edc8(obj) == 0) {
        return 0;
    }
    func_0201c280(obj, (char *) obj + 0x658);
    func_ov086_02278e6c((char *) obj + 0x658, obj);
    return 1;
}
