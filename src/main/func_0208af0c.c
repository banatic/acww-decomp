/* func_0208af0c @ 0x0208af0c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e20c8;
extern void func_020edb3c(void *);

void *func_0208af0c(void *obj)
{
    *(void **) obj = &data_020e20c8;
    func_020edb3c(obj);
    return obj;
}
