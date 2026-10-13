/* func_0209782c @ 0x0209782c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f20fc;
extern unsigned char *func_02097ff0(unsigned char *addr, int val);
extern int func_02065ec0(unsigned char *ptr);

int func_0209782c(void)
{
    int i;
    unsigned char *p;

    p = func_02097ff0(&data_021f20fc, 0);
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            return 1;
        }
        p += 0x100;
    }
    return 0;
}
