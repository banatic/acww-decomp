/* func_020704c0 @ 0x020704c0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *a, void *b, int c);
extern int func_0206ea84(void *a, void *b);
extern void func_0206ea28(int a);
extern void func_0207a500(void *a);
extern char data_021cfbbc;
extern char data_021f3b68;
extern char data_021e5a2c;

void func_020704c0(void *arg)
{
    MI_CpuCopy8((char *) arg + 1, &data_021cfbbc, 0x10);
    func_0206ea28(func_0206ea84(&data_021f3b68, &data_021cfbbc));
    func_0207a500(&data_021e5a2c);
}
