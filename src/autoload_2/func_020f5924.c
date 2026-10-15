/* func_020f5924 @ 0x020f5924, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213f074;
extern void func_020edb3c(int argument0);

void *func_020f5924(void *p)
{
    *((void **) p) = (void *) &data_0213f074;
    func_020edb3c((int) p);
    return p;
}
