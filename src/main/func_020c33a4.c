/* func_020c33a4 @ 0x020c33a4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *obj);
extern unsigned char data_020e7e14[];

void *func_020c33a4(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = data_020e7e14;
    return obj;
}
