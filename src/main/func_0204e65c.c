/* func_0204e65c @ 0x0204e65c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c158(void);
extern void *func_020e9948(void *p, unsigned int size);
extern void func_0204e6a4(void);
extern int func_0204e52c(void *p, void *q);
extern void *data_021c80c0;

int func_0204e65c(void *arg0)
{
    int result = 1;
    func_0205c158();
    if (data_021c80c0 != 0) {
        goto done;
    }
    data_021c80c0 = func_020e9948(arg0, 0x20);
    if (data_021c80c0 == 0) {
        goto done;
    }
    if (data_021c80c0) {
        func_0204e6a4();
    }
    result = func_0204e52c(data_021c80c0, arg0);
done:
    return result;
}
