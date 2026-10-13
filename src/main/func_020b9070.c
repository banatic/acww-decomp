/* func_020b9070 @ 0x020b9070, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a784(void *);

void func_020b9070(void *arg0)
{
    func_0208a784(arg0);
    ((unsigned char *) arg0)[0xe4] = 0;
    ((unsigned char *) arg0)[0xe5] = 0;
    *(unsigned int *) ((unsigned char *) arg0 + 0xe0) = 0;
    ((unsigned char *) arg0)[0xe6] = 0;
    ((unsigned char *) arg0)[0xe7] = 0;
    ((unsigned char *) arg0)[0xe8] = 0;
}
