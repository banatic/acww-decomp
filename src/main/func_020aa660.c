/* func_020aa660 @ 0x020aa660, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aa5d0(void *);

void func_020aa660(void *r0)
{
    if (*(unsigned char *) ((char *) r0 + 4) != 0) {
        *(unsigned char *) ((char *) r0 + 4) = 0;
        func_020aa5d0(r0);
    }
}
