/* func_ov105_0229d0d4 @ 0x0229d0d4, 0x24 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d5dc(void *obj, void *arg1, void *ptr);

void func_ov105_0229d0d4(void *obj, void *arg1)
{
    if (*(unsigned char *) ((char *) obj + 0x2b4) == 1) {
        func_ov105_0229d5dc(obj, arg1, (char *) obj + 0xb4);
    }
    *(unsigned char *) ((char *) obj + 0x2b4) = 0;
}
