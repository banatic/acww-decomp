/* func_02015de4 @ 0x02015de4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02062f90(void *);
extern void func_020683b4(unsigned int, void *, void *, void *);
extern void func_02062f4c(void *);

void func_02015de4(void *arg0, int arg1, void *arg2, void *arg3)
{
    unsigned char local_28[0x28];

    func_02062f90(local_28);
    func_020683b4(*(unsigned int *) ((char *) arg0 + 0x40), arg2, local_28, arg3);
    func_02062f4c(local_28);
    return;
}
