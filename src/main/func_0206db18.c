/* func_0206db18 @ 0x0206db18, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df270;
extern void func_020a887c(void *);

void *func_0206db18(void *obj)
{
    *(void **) obj = &data_020df270;
    func_020a887c(obj);
    return obj;
}
