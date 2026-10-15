/* func_02054188 @ 0x02054188, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054a94(unsigned int, unsigned int);
extern void func_02054a64(int, unsigned int);
extern void func_02054580(int, unsigned int);

void func_02054188(int p1, unsigned int p2, unsigned int p3)
{
    unsigned int i;
    for (i = p2; i <= p3; i++) {
        func_02054a94(p1, i);
        func_02054a64(p1, i);
        func_02054580(p1, i);
    }
}
