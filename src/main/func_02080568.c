/* func_02080568 @ 0x02080568, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080578(unsigned short *, unsigned short *, void *);
extern int func_020805bc(void *, int (*)(void *, void *, void *));

#define Compare_02080578 ((int (*)(void *, void *, void *)) func_02080578)

int func_02080568(int arg)
{
    return func_020805bc((void *) arg, Compare_02080578);
}
