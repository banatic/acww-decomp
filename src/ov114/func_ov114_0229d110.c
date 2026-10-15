/* func_ov114_0229d110 @ 0x0229d110, 0x20 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov114_0229daf0;
extern void *func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);

void *func_ov114_0229d110(void *obj)
{
    *(void **) obj = &data_ov114_0229daf0;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
