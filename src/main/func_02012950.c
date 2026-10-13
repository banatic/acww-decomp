/* func_02012950 @ 0x02012950, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02013518(void *, int);
extern void func_02013440(void *);
extern void func_02012e58(void *, int);

int func_02012950(void *arg0, int arg1)
{
    if (func_02013518(arg0, arg1) == 0) {
        func_02013440(arg0);
        *((int *) ((char *) arg0 + 0x88)) = 0;
        *((int *) ((char *) arg0 + 0x8c)) = 2;
        func_02012e58(arg0, arg1);
        return 0;
    } else {
        return 1;
    }
}
