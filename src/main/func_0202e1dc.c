/* func_0202e1dc @ 0x0202e1dc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203efdc(char *);
extern int func_02082568(void *);

int func_0202e1dc(void *arg0)
{
    void *r4;
    int r0;

    r4 = arg0;
    r0 = func_0203efdc(arg0);
    if (r0 == 0) {
        return 0;
    }
    r4 = (char *) r4 + 0xea;
    func_02082568(r4);
    return 1;
}
