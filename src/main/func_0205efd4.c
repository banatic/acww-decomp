/* func_0205efd4 @ 0x0205efd4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd754;
void *func_02056578(void *obj);
void func_020edb3c(void *obj);

void *func_0205efd4(void *obj)
{
    *(void **) obj = &data_020dd754;
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}
