/* func_ov071_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
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
