/* func_02082010 @ 0x02082010, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e191c[];
extern void *func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);

void *func_02082010(void *obj)
{
    *(void **) obj = (void *) data_020e191c;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
