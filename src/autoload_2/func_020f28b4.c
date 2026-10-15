/* func_020f28b4 @ 0x020f28b4, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern char data_0213ee7c[];

void *func_020f28b4(void *obj)
{
    *(void **) obj = data_0213ee7c;
    func_020f4514(obj);
    return obj;
}
