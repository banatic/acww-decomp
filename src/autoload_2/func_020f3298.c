/* func_020f3298 @ 0x020f3298, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ec0c;
extern void func_020f4514(void);

void *func_020f3298(void *obj)
{
    *(int **) obj = &data_0213ec0c;
    func_020f4514();
    return obj;
}
