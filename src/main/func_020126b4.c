/* func_020126b4 @ 0x020126b4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020126b4(void *r0, void *r1);

int func_020126b4(void *r0, void *r1)
{
    int r2, r3, r1_val;
    int *r0_ptr;

    r2 = *(int *) ((char *) r1 + 8);
    r3 = r2 >> 17;
    r1_val = *(int *) r1;
    r2 = r1_val >> 17;
    r0_ptr = (int *) ((char *) r0 + 0x14);
    if (r2 == *r0_ptr) {
        r0_ptr = (int *) ((char *) r0 + 0x18);
        if (r3 == *r0_ptr) {
            return 1;
        }
    }
    return 0;
}
