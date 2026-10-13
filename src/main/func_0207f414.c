/* func_0207f414 @ 0x0207f414, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207f5c8(void *);
extern int func_020644cc(int);

void func_0207f414(char *ptr, int flag, int other)
{
    if (flag == 2) {
        *(ptr + 0x7d8) = (char) func_020644cc(10);
        func_0207f5c8(ptr);
    } else {
        *(ptr + 0x7d8) = (char) func_020644cc(0x28);
        if (other != 0) {
            func_0207f5c8(ptr);
        }
    }
}
