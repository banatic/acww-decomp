/* func_ov074_02278a34 @ 0x02278a34, 0x38 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov074_02278b1c(void *);
extern void *func_ov074_02278fe4(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

extern unsigned char data_ov074_02279c68[];

void *func_ov074_02278a34(void *obj)
{
    *(void **) obj = (void *) data_ov074_02279c68;
    func_ov074_02278b1c((char *) obj + 0x714);
    func_ov074_02278fe4((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
