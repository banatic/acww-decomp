/* func_0205f00c @ 0x0205f00c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565ec(void *ptr);
extern int data_020dd754;

void *func_0205f00c(void *obj)
{
    func_020565ec(obj);
    *(void **) obj = (void *) &data_020dd754;
    return obj;
}
