/* func_020ea8c8 @ 0x020ea8c8, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_CrossProduct(unsigned int, unsigned int, const unsigned int *);

void func_020ea8c8(unsigned int *dst, const unsigned int *src, unsigned int a, unsigned int b)
{
    VEC_CrossProduct(a, b, src);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}
