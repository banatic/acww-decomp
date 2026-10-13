/* func_02082164 @ 0x02082164, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *);

extern unsigned char data_020e1934[];

unsigned int *func_02082164(unsigned int *obj)
{
    func_020a88ec(obj);
    *obj = (unsigned int) data_020e1934;
    return obj;
}
