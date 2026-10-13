/* func_ov003_0222866c @ 0x0222866c, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0225f76c[];
void func_ov003_02228ae8(void *self, void *e, int i);
void func_ov003_02228618(void *self);

int func_ov003_0222866c(char *self)
{
    char *p = data_ov003_0225f76c;
    int i;
    for (i = 0; i < 6; i++) {
        func_ov003_02228ae8(self, p, i);
        p += 0x24c;
    }
    *(char *) (self + 0x84) = 0;
    func_ov003_02228618(self);
    return 1;
}
