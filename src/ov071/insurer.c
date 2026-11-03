/* insurer: 2 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov071_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

extern void *func_ov071_02278fa0(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov071_0227a278[];

void *func_ov071_02278a28(void *p)
{
    *(unsigned int *) p = (unsigned int) data_ov071_0227a278;
    func_ov071_02278fa0((void *) ((char *) p + 0x658));
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}

void *func_ov071_02278a00(void *obj)
{
    *(void **) obj = (void *) ((char *) data_ov071_0227a278);
    func_ov071_02278fa0((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
