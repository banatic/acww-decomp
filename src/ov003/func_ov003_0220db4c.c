/* func_ov003_0220db4c @ 0x0220db4c, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Sub7d4 {
    int a;
    char b;
    char c;
};

extern void func_020109fc(void *, int, int, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_02073908(int, int);
extern void func_0203ae98(void);
extern void func_02036450(int);
extern int data_020ccf94;
extern int data_021c526c;

void func_ov003_0220db4c(void *arg)
{
    struct Sub7d4 *sub = (struct Sub7d4 *) ((char *) arg + 0x7d4);
    int zero = 0;
    sub->a = ~zero;
    sub->b = zero;
    sub->c = 0x14;
    func_020109fc(arg, 0x7c, 9, zero);
    func_0205eae0((char *) arg + 0x5a0, 0x28, 0, 1);
    if (func_02073908(data_020ccf94, *(int *) ((char *) arg + 0x800)) != 0) {
        func_0203ae98();
        func_02036450(data_021c526c + 0x1c4);
    }
}
