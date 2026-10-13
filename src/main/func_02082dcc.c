/* func_02082dcc @ 0x02082dcc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *obj);
extern void func_020edb3c(void *obj);
extern char data_020e1a68;

void *func_02082dcc(void *obj)
{
    *(void **) obj = (void *) &data_020e1a68;
    func_020830d0(obj);
    func_020edb3c(obj);
    return obj;
}
