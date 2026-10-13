/* func_0201ad8c @ 0x0201ad8c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f7d0(void *);

int func_0201ad8c(void *r0, void *r1)
{
    int r4 = 0;
    int r3 = *(int *) ((char *) r0 + 0x50);
    if (r3 != 0) {
        goto label;
    }
    if (*(int *) ((char *) r0 + 0x54) != 0) {
        goto label;
    }
    if (*(int *) ((char *) r0 + 0x58) == 0) {
        goto end;
    }
label:
    *(int *) r1 = r3;
    *(int *) ((char *) r1 + 4) = *(int *) ((char *) r0 + 0x54);
    *(int *) ((char *) r1 + 8) = *(int *) ((char *) r0 + 0x58);
    func_0203f7d0(r1);
    r4 = 1;
end:
    return r4;
}
