/* func_ov137_0229ca90 @ 0x0229ca90, 0x28 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov137_0229c668(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov137_0229ca90(void *p)
{
    if (func_0208e484((char *) p + 0x94)) {
        func_ov137_0229c668(p);
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0x2b76));
    }
}
