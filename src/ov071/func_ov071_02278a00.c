/* func_ov071_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov071_02278fa0(void *p);
extern void *func_0202ee5c(void *p);
extern char data_ov071_0227a278;

void *func_ov071_02278a00(void *obj)
{
    *(void **) obj = (void *) &data_ov071_0227a278;
    func_ov071_02278fa0((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
