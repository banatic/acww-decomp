/* func_020a4c5c @ 0x020a4c5c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_020a1954(void *p, int *data, int count);
extern void func_0206f74c(void);
extern void func_02098fd0(int v, int count);
extern void func_0204cdc8(int *data);
extern int data_020e3c2c;
extern int data_021f39fc;

void func_020a4c5c(void *p)
{
    int v;
    v = func_020984e8();
    func_020a1954(p, &data_020e3c2c, 0x66);
    func_0206f74c();
    func_02098fd0(v, 2);
    func_0204cdc8(&data_021f39fc);
    *((char *) p + 0xa1) = 0;
}
