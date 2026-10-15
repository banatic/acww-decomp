/* func_020821bc @ 0x020821bc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *obj);
extern char data_020e1904;

void *func_020821bc(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) &data_020e1904;
    return obj;
}
