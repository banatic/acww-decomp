/* func_0209e474 @ 0x0209e474, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc744[3];
extern int data_021dc754[3];

void func_0209e474(unsigned char *p0)
{
    int *const b = data_021dc754;
    int *a = data_021dc744;
    p0[5] = a[0];
    p0[4] = a[1];
    p0[3] = a[2];
    p0[2] = b[0];
    p0[1] = b[1];
    p0[0] = b[2];
}
