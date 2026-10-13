/* func_020f35d8 @ 0x020f35d8, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4514(void *obj);
extern char data_0213eb3c[];

void *func_020f35d8(void *obj)
{
    *(void **) obj = data_0213eb3c;
    func_020f4514(obj);
    return obj;
}
