/* func_ov009_02262f74 @ 0x02262f74, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5914(void *);

extern unsigned char data_0213f090[];

void *func_ov009_02262f74(void *obj)
{
    *(void **) obj = (void *) data_0213f090;
    func_020f5914(obj);
    return obj;
}
