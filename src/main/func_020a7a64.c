/* func_020a7a64 @ 0x020a7a64, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8754(void *);
extern void func_020a94a4(void *);

void func_020a7a64(void *arg0)
{
    unsigned char *p;
    void *r4 = arg0;

    *(int *) ((char *) r4 + 0x24) = 0;
    func_020a8754((char *) r4 + 0x28);
    *(int *) ((char *) r4 + 0x3c) = 0;
    *(int *) ((char *) r4 + 0x40) = -1;
    *(int *) ((char *) r4 + 0x44) = -1;
    *(int *) ((char *) r4 + 0x48) = 0;
    *(int *) ((char *) r4 + 0x4c) = 0;
    *(int *) ((char *) r4 + 0x50) = 0;
    *(int *) ((char *) r4 + 0x54) = 0;
    p = (unsigned char *) r4 + 0x58;
    *p = 0;
    func_020a94a4(r4);
}
