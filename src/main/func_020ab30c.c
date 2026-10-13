/* func_020ab30c @ 0x020ab30c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab58c(void *);
extern void func_020ab1a0(void *);
extern void func_020ab230(void *);
extern void func_020ab238(void *);

void func_020ab30c(void *param)
{
    void *r4 = param;
    func_020ab58c(*(void **) ((char *) r4 + 0x20));
    func_020ab1a0(r4);
    *(int *) r4 = 0;
    *(int *) ((char *) r4 + 0x24) = 0;
    func_020ab230(r4);
    func_020ab238(r4);
}
