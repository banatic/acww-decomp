/* func_02094d48 @ 0x02094d48, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094d6c(unsigned int, void *, unsigned int, unsigned int);
extern void func_02090db0(unsigned int);
extern unsigned int data_021d5658;

void func_02094d48(unsigned int a, unsigned int b, unsigned int c)
{
    func_02094d6c(a, &data_021d5658, b, c);
    func_02090db0(a);
}
