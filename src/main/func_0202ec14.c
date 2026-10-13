/* func_0202ec14 @ 0x0202ec14, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b744(void);
extern int func_02083068(void *);

int func_0202ec14(void *arg0)
{
    int result;
    void *ptr;

    if (func_0201b744() == 0) {
        return 0;
    }
    ptr = (char *) arg0 + 0x640;
    func_02083068(ptr);
    return 1;
}
