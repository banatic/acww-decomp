/* func_ov102_0229cd80 @ 0x0229cd80, 0x38 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov102_0229cd80(int *r0)
{
    int r2;
    int r1;

    r2 = *(int *) ((char *) r0 + 0x24d8);
    r1 = data_021f6c58;
    r2 += r1;
    *(int *) ((char *) r0 + 0x24e0) = r2;

    r2 = *(int *) ((char *) r0 + 0x24dc);
    r1 = data_021f6c54;
    r2 += r1;
    *(int *) ((char *) r0 + 0x24e4) = r2;
}
