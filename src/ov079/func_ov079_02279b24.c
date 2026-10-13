/* func_ov079_02279b24 @ 0x02279b24, 0x38 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern struct T12 {
    int a;
    int b;
    int c;
} data_021c67d0;
extern int func_ov079_02279b5c(char *arg, struct T12 *tmp, char *p);

int func_ov079_02279b24(char *arg)
{
    char *p = arg + 0x5c;
    int result = 0;
    if (data_021c67a4 != 0) {
        struct T12 tmp;
        tmp.a = data_021c67d0.a;
        tmp.b = data_021c67d0.b;
        tmp.c = data_021c67d0.c;
        result = func_ov079_02279b5c(arg, &tmp, p);
    }
    return result;
}
