/* func_020afcf4 @ 0x020afcf4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203d7b0(int, int);
extern int func_0203d79c(int, int);
extern void *func_020af028(void *);
extern int func_02077f14(void *, void *);
extern int data_021f395c;
extern int data_020e41b8;

int func_020afcf4(int a, int b)
{
    func_0203d7b0(2, a);
    func_0203d79c(3, b);
    return func_02077f14(func_020af028(&data_021f395c), &data_020e41b8);
}
