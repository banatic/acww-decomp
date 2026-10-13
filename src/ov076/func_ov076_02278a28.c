/* func_ov076_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov076_022797d4;
extern void func_ov076_02278e78(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov076_02278a28(void *obj)
{
    *(void **) obj = (void *) &data_ov076_022797d4;
    func_ov076_02278e78((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
