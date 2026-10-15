/* func_ov073_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov073_02278e9c(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern int data_ov073_02279b00;

void *func_ov073_02278a28(void *p)
{
    *(void **) p = &data_ov073_02279b00;
    func_ov073_02278e9c((char *) p + 0x658);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}
