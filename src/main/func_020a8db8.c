/* func_020a8db8 @ 0x020a8db8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9228(void *a, void *b);
extern void func_020a94a4(void *a);
extern void func_020a9354(void *a, int b);
extern int func_020a922c(void *a, int b);
extern void func_020a9220(void *a);

extern int data_021f44dc;

int func_020a8db8(void *self)
{
    void *ptr;

    ptr = *(void **) ((char *) self + 0x80);
    if (ptr == 0) {
        ptr = (void *) &data_021f44dc;
    }

    *(int *) ((char *) self + 0x7c) = 2;
    func_020a9228(ptr, self);
    func_020a94a4(ptr);
    func_020a9354(ptr, *(int *) ((char *) self + 0x10));
    func_020a922c(ptr, *(int *) ((char *) self + 0x14));
    func_020a9220(ptr);

    *(int *) ((char *) self + 0x7c) = 0;
    return *(int *) ((char *) self + 0x68);
}
