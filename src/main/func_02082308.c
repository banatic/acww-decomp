/* func_02082308 @ 0x02082308, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020821bc(char *buf);
extern int func_02082340(char *buf, int b);
extern int func_020a87e0(int a, char *buf);
extern void *func_020821a4(char *buf);

int func_02082308(int a, int b)
{
    char buf[0x20];
    int ret;

    func_020821bc(buf);
    ret = 0;
    if (func_02082340(buf, b)) {
        func_020a87e0(a, buf);
        ret = 1;
    }
    func_020821a4(buf);
    return ret;
}
