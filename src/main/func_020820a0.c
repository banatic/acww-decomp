/* func_020820a0 @ 0x020820a0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a88ec(void *obj);
extern int data_020e194c;

void *func_020820a0(void *obj)
{
    func_020a88ec(obj);
    *(void **) obj = (void *) &data_020e194c;
    return obj;
}
