/* func_020b18fc @ 0x020b18fc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *obj);
extern char data_020e4278;

void *func_020b18fc(void *obj)
{
    func_020a88ec(obj);
    *(void **) obj = (void *) &data_020e4278;
    return obj;
}
