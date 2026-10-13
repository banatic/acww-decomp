/* func_020ea88c @ 0x020ea88c, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Normalize(void *);

void func_020ea88c(void *dst, void *src)
{
    VEC_Normalize(src);
    *(unsigned int *) dst = *(unsigned int *) src;
    *(unsigned int *) ((char *) dst + 4) = *(unsigned int *) ((char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(unsigned int *) ((char *) src + 8);
}
