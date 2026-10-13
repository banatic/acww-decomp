/* func_0207ca08 @ 0x0207ca08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082500(unsigned char);
extern int func_0207caa0(unsigned char, void *);

int func_0207ca08(void *param)
{
    int i;
    void *res;
    for (i = 0; i < 150; i++) {
        res = func_02082500((unsigned char) i);
        if (res != 0) {
            if (*(unsigned char *) ((char *) res + 0x4b) < 2) {
                if (func_0207caa0((unsigned char) i, param) == 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
