/* func_020ea41c @ 0x020ea41c, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea450(void *obj, unsigned int unused1, unsigned int unused2, unsigned int unused3);
extern void OS_InitMutex(void *mutex);
extern unsigned char data_0213e5b0;

void *func_020ea41c(void *obj, int a, int b, int c, int d)
{
    func_020ea450(obj, a, b, c);
    *(void **) obj = (void *) &data_0213e5b0;
    *((int *) ((char *) obj + 0x14)) = d;
    OS_InitMutex((char *) obj + 0x18);
    return obj;
}
