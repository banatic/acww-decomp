/* func_0204d08c @ 0x0204d08c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67ac(void);
extern unsigned short func_02060d7c(void *addr);
extern unsigned char data_021ebcd4[];

void func_0204d08c(void *self, int *out, int count)
{
    if (func_020b67ac()) {
        *out = func_02060d7c((void *) data_021ebcd4);
    }
}
