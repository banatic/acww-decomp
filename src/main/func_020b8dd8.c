/* func_020b8dd8 @ 0x020b8dd8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f6ba0;
extern int data_021f6b20;
extern void func_020b889c(int);

void func_020b8dd8(void)
{
    *(int *) ((char *) ((int) &data_021f6ba0) + (124)) = 9;
    func_020b889c((int) &data_021f6b20);
}
