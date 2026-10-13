/* func_ov104_0229c344 @ 0x0229c344, 0xe bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

void func_ov104_0229c344(void *param0, unsigned int param1)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) param0 + 0x94);
    val = *ptr;
    val &= ~param1;
    *((unsigned int *) ((char *) param0 + 0x94)) = val;
}
