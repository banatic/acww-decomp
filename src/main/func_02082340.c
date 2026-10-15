/* func_02082340 @ 0x02082340, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(int);
extern int func_020b4a20(void *, void *, void *);
extern char data_020e19a8[];

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
