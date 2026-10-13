/* func_02015bfc @ 0x02015bfc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015d44(int);
extern int func_02095794(int);
extern int func_0200322c(int, void *);
extern void func_02095518(int, int, int);
extern void func_02095a8c(int, int);
extern void func_02095eec(int, int);

void func_02015bfc(int arg0, void *arg1)
{
    int val = func_02015d44(arg0);
    int flag = func_02095794(val);
    if (flag) {
        void *p = (char *) arg1 + 0x5c;
        int res = func_0200322c(flag, p);
        func_02095518(0, 0, val);
        func_02095a8c(res, val);
        func_02095eec(1, val);
    }
}
