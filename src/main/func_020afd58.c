/* func_020afd58 @ 0x020afd58, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b5630(char *p);
extern int func_020b45d0(char *p, void *arg, int n, int a, int b, int c);
extern int func_0203d7c4(int a, char *p);
extern int func_020644cc(int a);
extern void *func_02077f14(int a, int *p);
extern void *func_020b5618(char *p);
extern int data_020e41c4;

void func_020afd58(void *arg)
{
    char st[0x40];
    func_020b5630(st);
    func_020b45d0(st, arg, 10, 0, 0, 0);
    func_0203d7c4(2, st);
    func_02077f14(func_020644cc(2) + 2, &data_020e41c4);
    func_020b5618(st);
}
