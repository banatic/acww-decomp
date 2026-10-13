/* func_0206dcec @ 0x0206dcec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void);

void func_0206dcec(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x64) != 0) {
        func_020a8fb8();
        *(unsigned int *) ((char *) arg0 + 0x64) = 0;
    }
}
