/* func_ov096_0229e79c @ 0x0229e79c, 0x26 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f650(void *arg0, int arg1);
extern int func_ov096_0229f4ac(void *arg0, int arg1);

int func_ov096_0229e79c(void *arg0, int arg1)
{
    unsigned char type = *((unsigned char *) arg0 + 0xb1);

    switch (type) {
        case 2:
            return func_ov096_0229f650(arg0, arg1);
        case 1:
            return func_ov096_0229f4ac(arg0, arg1);
        default:
            return 0;
    }
}
