/* npc_lookup: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082340 @ 0x02082340, 0x34 bytes, Thumb
 * func_02082308 @ 0x02082308, 0x36 bytes, Thumb
 */

extern int func_0200363c(int);
extern int func_020b4a20(void *, void *, void *);
extern char data_020e19a8[];
extern void *func_020821bc(char *buf);
extern int func_020a87e0(int a, char *buf);
extern void *func_020821a4(char *buf);

int func_02082340(void *a1, int a2)
{
    int result = 0;
    if (func_0200363c(a2) != 0) {
        char ch = (char) a2;
        func_020b4a20(a1, &ch, data_020e19a8);
        result = 1;
    }
    return result;
}

int func_02082308(int a, int b)
{
    char buf[0x20];
    int ret;

    func_020821bc(buf);
    ret = 0;
    if (func_02082340((void *) buf, b)) {
        func_020a87e0(a, buf);
        ret = 1;
    }
    func_020821a4(buf);
    return ret;
}
