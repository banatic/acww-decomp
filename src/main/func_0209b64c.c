/* func_0209b64c @ 0x0209b64c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b91c(void *);
extern int func_0209bd44(int);
extern int func_0209bc40(int);
extern int func_0209b914(int);
extern unsigned int func_0209b6b8(int);
extern unsigned char data_020d1a30[];

int func_0209b64c(int arg0)
{
    int a, i;

    a = func_0209b91c((void *) arg0);
    if (func_0209bd44(a) != 0 && func_0209bc40(a) == 4 && (i = func_0209b914(arg0)) < 6) {
        if (func_0209b6b8(arg0) >= data_020d1a30[i]) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
