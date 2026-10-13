/* func_020a8c1c @ 0x020a8c1c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051ad8(void *);
extern void func_020a9b04(void *);

void func_020a8c1c(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02051ad8(r4);
    *(unsigned int *) ((char *) r4 + 4) = 0;
    func_020a9b04((char *) r4 + 8);
}
