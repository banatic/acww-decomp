/* func_0208212c @ 0x0208212c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *);
extern void func_020edb3c(void *);
extern int data_020e1934;

void *func_0208212c(void *obj)
{
    *(void **) obj = (void *) &data_020e1934;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}
