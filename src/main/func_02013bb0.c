/* func_02013bb0 @ 0x02013bb0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200443c(int receiver, unsigned int value, unsigned int flag);
extern int func_020b1cb0(void *ptr);

void func_02013bb0(unsigned char *data, void *param)
{
    unsigned int flags = *(unsigned int *) ((char *) param + 0xb0);
    unsigned int cond;

    cond = (flags & 4) ? 1 : 0;
    if (cond > 0) {
        cond = (flags & 2) ? 1 : 0;
        if (cond > 0) {
            return;
        }
    }

    if (*data != 0) {
        int value = func_020b1cb0((char *) param + 0x5c);
        func_0200443c((int) ((char *) param + 0x514), value, 0);
    }
}
