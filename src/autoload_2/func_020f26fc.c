/* func_020f26fc @ 0x020f26fc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern int data_0213eee4;

void *func_020f26fc(void *obj)
{
    *(void **) obj = &data_0213eee4;
    func_020f4514(obj);
    return obj;
}
