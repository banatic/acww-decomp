/* func_0208f608 @ 0x0208f608, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e2388;
extern void func_020a8c38(void *);
extern void *func_020edb3c(void *) __attribute__((arm));

void *func_0208f608(void *obj)
{
    *(void **) obj = &data_020e2388;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
