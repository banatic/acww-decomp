/* func_ov105_0229cebc @ 0x0229cebc, 0x54 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov105_0229cebc(void *p)
{
    int v1 = func_ov002_02208ae4((char *) ((unsigned int) p + 0x2508));
    int v2 = func_ov002_02208ad8((char *) p + 0x2508, ((unsigned char *) p)[0x2bf]);
    func_ov002_0220a08c((char *) p + 0x24a4, v1, v2, 2);
    ((unsigned char *) p)[0x2bd] = ((unsigned char *) p)[0x8d];
    func_ov002_02208098(p, 13);
}
