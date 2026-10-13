/* func_ov004_02232934 @ 0x02232934, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_020b6804(void);
extern void *func_02060ee0(void *, int);
extern void func_020611bc(void *, int, int);
extern char data_021ebcd4;

void func_ov004_02232934(int a0, int a1, int a2)
{
    void *p;
    if (func_020b67d4() != 0) {
        p = func_02060ee0(&data_021ebcd4, func_020b6804());
        if (p != 0) {
            func_020611bc(p, a1, a2);
        }
    }
}
