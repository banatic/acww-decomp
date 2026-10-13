/* func_ov003_0220c184 @ 0x0220c184, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov003_0223c5f4[];
extern unsigned char data_ov003_0223c5a0;

int func_ov003_0220c184(void *self)
{
    unsigned int idx;
    unsigned char *p;
    int result;

    idx = *(unsigned int *) ((char *) self + 8);
    data_ov003_0223c5f4[idx] = 0;
    p = &data_ov003_0223c5a0;
    *p = *p - 1;
    return 1;
}
