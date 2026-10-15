/* func_020115ec @ 0x020115ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5914(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020d8414[];

void *func_020115ec(void *param)
{
    *(void **) param = (void *) data_020d8414;
    func_020f5914(param);
    func_020edb3c(param);
    return param;
}
