/* func_0200f1ec @ 0x0200f1ec, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f7d0(void *, void *);

int func_0200f1ec(void *r0, void *r1)
{
    if (*(int *) ((char *) r0 + 0x6bc) == 0 && *(int *) ((char *) r0 + 0x6c0) == 0 && *(int *) ((char *) r0 + 0x6c4) == 0) {
        return 0;
    }
    *(int *) r1 = *(int *) ((char *) r0 + 0x6bc);
    *(int *) ((char *) r1 + 4) = *(int *) ((char *) r0 + 0x6c0);
    *(int *) ((char *) r1 + 8) = *(int *) ((char *) r0 + 0x6c4);
    func_0203f7d0(r1, r1);
    return 1;
}
