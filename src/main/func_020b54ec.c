/* func_020b54ec @ 0x020b54ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *obj);
extern void func_020edb3c(void *obj);

extern unsigned char data_020e51b8[];

void *func_020b54ec(void *obj)
{
    *(void **) obj = (void *) data_020e51b8;
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
