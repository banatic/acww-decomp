/* func_ov136_0229d00c @ 0x0229d00c, 0x38 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229bd38(void *p, int a, int b, int c, int d);

void func_ov136_0229d00c(void *p)
{
    func_ov134_0229bd38((char *) p + 0x2c4, 1, 6, 4, 3);
    ((char *) p)[0x2b77] = 0;
    *(unsigned short *) ((char *) p + 0x2b74) = 0;
}
