/* func_0206d54c @ 0x0206d54c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8ecc(void *);

void func_0206d54c(void *param)
{
    if (*(int *) ((char *) param + 0x30) != 0) {
        *(int *) ((char *) param + 0x50) = 0;
        *(int *) ((char *) param + 0x48) = 0;
        *(int *) ((char *) param + 0x4c) = 0;
        func_020a8ecc(*(void **) ((char *) param + 0x30));
    }
}
