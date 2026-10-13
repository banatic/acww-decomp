/* func_0206d670 @ 0x0206d670, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a40(void *obj);
extern char data_020def64;

void *func_0206d670(void *obj)
{
    *(void **) obj = &data_020def64;
    func_020a9a40(obj);
    return obj;
}
