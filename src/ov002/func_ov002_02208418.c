/* func_ov002_02208418 @ 0x02208418, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220882c(void *);

void func_ov002_02208418(void *r0, int r1, unsigned char r2, int r3)
{
    *(unsigned char *) ((char *) r0 + 0x18) = r2;
    *(int *) ((char *) r0 + 0x14) = r3;
    func_ov002_0220882c(r0);
    *(int *) ((char *) r0 + 0xc) = 0;
    switch (*(unsigned char *) ((char *) r0 + 0x18)) {
        case 0:
        case 1:
            *(int *) ((char *) r0 + 0x10) = 0xc0;
            break;
        case 2:
        case 3:
            *(int *) ((char *) r0 + 0x10) = 0x100;
            break;
    }
}
