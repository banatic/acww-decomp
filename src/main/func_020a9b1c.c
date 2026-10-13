/* func_020a9b1c @ 0x020a9b1c, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a9b1c(void *r0, const void *r1)
{
    *(unsigned int *) ((char *) r0 + 4) = *(const unsigned int *) ((const char *) r1 + 4);
    *(unsigned char *) ((char *) r0 + 8) = *(const unsigned char *) ((const char *) r1 + 8);
    *(unsigned char *) ((char *) r0 + 9) = *(const unsigned char *) ((const char *) r1 + 9);
}
