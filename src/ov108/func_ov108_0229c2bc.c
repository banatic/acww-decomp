/* func_ov108_0229c2bc @ 0x0229c2bc, 0xe bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

void func_ov108_0229c2bc(void *param0, unsigned int param1)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) param0 + 0x94);
    val = *ptr;
    val &= ~param1;
    *((unsigned int *) ((char *) param0 + 0x94)) = val;
}
