/* func_02094f9c @ 0x02094f9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);
extern int data_020e2f6c;

void *func_02094f9c(void *obj)
{
    *((void **) obj) = (void *) &data_020e2f6c;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
