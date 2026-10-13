/* func_02017590 @ 0x02017590, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(void *p, int b);
extern int func_02057d0c(int a, int b);
extern int func_02057b90(int a, int b);
extern void func_02019af0(void *p);
extern void func_02095380(int n);

int func_02017590(void *s, int v)
{
    if (func_02057bd4(s, v) && func_02057d0c(8, v)) {
        func_02057b90(8, v);
        ((char *) s)[0x98] = 0;
        func_02019af0(s);
        func_02095380(0x72);
    }
    return 1;
}
