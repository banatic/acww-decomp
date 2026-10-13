/* func_020b6d8c @ 0x020b6d8c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0abc(void *p, void *a, void *b, int c, int d);
extern void *data_021f6948;
extern int data_021f42dc;
extern int data_021f42e4;

void func_020b6d8c(int unused, int p2, int p3)
{
    func_020b0abc(data_021f6948, &data_021f42dc, &data_021f42e4, p2, p3);
}
