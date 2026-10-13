/* func_0204cf14 @ 0x0204cf14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern char data_020db898;
extern char data_020da13c;

void *func_0204cf14(void *p)
{
    *(int *) p = (int) &data_020db898;
    *(int *) p = (int) &data_020da13c;
    func_020ee62c(p);
    return p;
}
