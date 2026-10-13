/* func_020aae40 @ 0x020aae40, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab58c(void *);
extern void func_020aac8c(void *);
extern void func_020aa9c0(void *);
extern void func_020aad08(void *);

void func_020aae40(void *param)
{
    void *r4 = param;
    func_020ab58c(*(void **) ((char *) r4 + 0x34));
    func_020aac8c(r4);
    *(int *) ((char *) r4 + 4) = 0;
    *(int *) ((char *) r4 + 8) = 0x800;
    *(int *) ((char *) r4 + 0xc) = 0x800;
    func_020aa9c0(r4);
    func_020aad08(r4);
    *(char *) ((char *) r4 + 0x31) = 0;
}
