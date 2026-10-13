/* func_020b3afc @ 0x020b3afc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02031ec0(void *p);
extern char data_020e50e8;

void *func_020b3afc(void *p)
{
    func_02031ec0(p);
    *(unsigned int *) p = (unsigned int) &data_020e50e8;
    return p;
}
