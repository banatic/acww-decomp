/* func_0202edc8 @ 0x0202edc8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201bdb4(void);
extern int func_0202edfc(void *arg0, int arg1, int arg2);

int func_0202edc8(void *arg0)
{
    int result;
    void *r4;

    r4 = arg0;
    if (func_0201bdb4() == 0) {
        return 0;
    }
    func_0202edfc(r4, 0x1000, 0x2000);
    *(unsigned char *) ((char *) r4 + 0x650) = 0;
    return 1;
}
