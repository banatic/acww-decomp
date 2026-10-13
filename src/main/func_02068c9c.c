/* func_02068c9c @ 0x02068c9c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a234(void *);

int func_02068c9c(void *p)
{
    return (*(int *) ((char *) p + 0x7c) == 0) && (func_0208a234((char *) p + 0xc) == 1);
}
