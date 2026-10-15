/* func_02079f60 @ 0x02079f60, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207a2d8(void *, int, signed char);
extern void func_020794d4(char *, int);
extern void func_02079540(char *, int);
extern int func_0207a244(void *, int, signed char);

void func_02079f60(void *ptr, char *str, int *count, char *table, int n)
{
    char *elem;
    int zero1 = 0;
    int zero2 = 0;
    int i;

    for (i = 0; i < n; i++) {
        signed char c = str[zero2];
        if (func_0207a2d8(ptr, *count, c)) {
            (*count)++;
            elem = table + c * 44;
            func_020794d4(elem, zero1);
            func_02079540(elem, 1);
            func_0207a244(ptr, i, c);
        }
        str++;
    }
}
