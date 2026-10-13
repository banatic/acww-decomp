/* func_02030d48 @ 0x02030d48, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02031a08(void);
extern unsigned int func_02030d68(unsigned int a, unsigned int b, unsigned int c);

unsigned int func_02030d48(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int t = func_02031a08() & ~c;
    return func_02030d68(a, b, t);
}
