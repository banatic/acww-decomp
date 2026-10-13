/* func_ov085_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov085_02278efc(void *p);
extern void func_0202ee5c(void *p);
extern int data_ov085_022794f0;

void *func_ov085_02278a00(void *obj)
{
    *(void **) obj = &data_ov085_022794f0;
    func_ov085_02278efc((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
