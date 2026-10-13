/* func_0208f864 @ 0x0208f864, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void *(*func_ptr)(void *);

void *func_0208f864(void *obj)
{
    func_ptr *vtbl;
    vtbl = *(func_ptr **) obj;
    return vtbl[2](obj);
}
