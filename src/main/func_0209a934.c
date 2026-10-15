/* func_0209a934 @ 0x0209a934, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209ad9c(void *, int);
extern char *func_02137550(void *, int);
extern int func_02003704(void *);
extern void *func_0207cb9c(void *, void **, int);
extern unsigned int func_0208150c(unsigned int);
extern int func_0209b4d8(unsigned int, int, int, unsigned int);
extern void func_02003728(void *, unsigned int);
extern int data_021e5a2c;

void func_0209a934(char *arg)
{
    unsigned int key;
    void *list[2];
    int count;
    int i;
    unsigned int res;
    void *elem;

    key = (unsigned int) func_0209ad9c(arg, 0);
    func_02137550(list, 8);
    count = 0;
    for (i = 0; i < 2; i++) {
        elem = arg + 0x60 + i * 0x10;
        if (func_02003704(elem)) {
            list[count] = elem;
            count++;
        }
    }
    res = (unsigned int) func_0207cb9c(&data_021e5a2c, list, count);
    func_0209b4d8(key, 0x10, 0, func_0208150c(res));
    func_02003728(arg + 0x80, func_0208150c(res));
}
