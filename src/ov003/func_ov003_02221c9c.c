/* func_ov003_02221c9c @ 0x02221c9c, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cf88[3];

void func_ov003_02221c9c(int *out)
{
    int *p = out + 1;
    out[1] = data_ov003_0223cf88[0];
    p[1] = data_ov003_0223cf88[1];
    p[2] = data_ov003_0223cf88[2];
}
