/* func_ov045_02260d14 @ 0x02260d14, 0x20 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov045_02261460;
extern void *func_0201615c(void *);
extern void func_020edb3c(void *);

void *func_ov045_02260d14(void *obj)
{
    *(void **) obj = (void *) &data_ov045_02261460;
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
