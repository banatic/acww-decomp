/* func_0208b0d8 @ 0x0208b0d8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern int func_02011ed4(char *obj);
extern int func_0208d01c(char *p);
extern void func_0208d04c(char *p);
extern int func_0208d03c(char *p);
extern void func_0208dd18(char *p);
extern void func_0208dd10(char *p);
extern int func_0208dd00(char *p);
extern void func_0208d054(char *p);

static __inline int check_flag(void)
{
    return (data_020e54a8 == 1) ? 1 : 0;
}

void func_0208b0d8(char *obj)
{
    if (func_02011ed4(obj) != 0) {
        if (check_flag() != 0) {
            if (func_0208d01c(obj + 0xe0) != 0) {
                func_0208d04c(obj + 0xe0);
                if (func_0208d03c(obj + 0xe0) != 0) {
                    func_0208dd18(obj + 8);
                }
            } else {
                func_0208dd10(obj + 8);
                if (func_0208dd00(obj + 8) != 0) {
                    func_0208d054(obj + 0xe0);
                }
            }
        }
    }
}
