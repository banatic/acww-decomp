/* func_02094fd4 @ 0x02094fd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern unsigned char data_020e2f6c;

void *func_02094fd4(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = &data_020e2f6c;
    return obj;
}
