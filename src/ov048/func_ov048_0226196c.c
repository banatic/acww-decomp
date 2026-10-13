/* func_ov048_0226196c @ 0x0226196c, 0x40 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_022616b8(void *self, int n);
extern void func_0206844c(unsigned int a, char *b, int c);
extern int data_ov048_02263d20;

void func_ov048_0226196c(void *self, int which)
{
    char local;

    switch (which) {
        case 0:
            func_ov048_022616b8(self, 20);
            break;
        case 1:
            local = 0x6c;
            func_0206844c(*(unsigned int *) ((char *) self + 0x40), &local, data_ov048_02263d20);
            break;
        case 2:
            func_ov048_022616b8(self, 20);
            break;
    }
}
