/* func_020aae8c @ 0x020aae8c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020ab51c(void *);

void func_020aae8c(void *arg0, void *arg1)
{
    void *r4;
    void *r5;

    r5 = arg0;
    r4 = arg1;
    func_020ab51c(r4);
    *(void **) ((char *) r5 + 0x34) = r4;
}
