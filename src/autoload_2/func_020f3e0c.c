/* func_020f3e0c @ 0x020f3e0c, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eec48(void);
extern void func_020eec60(int argument0);
extern int func_020f1d84(void *p, int line);
extern char data_021fd1bc;

void func_020f3e0c(int unused, int p2)
{

    func_020eec60(func_020eec48());
    if (p2 != 0) {
        if (p2 != 1) {
            return;
        }
        func_020f1d84(&data_021fd1bc, 0xb2);
    } else {
        func_020f1d84(&data_021fd1bc, 0x8f);
    }
}
