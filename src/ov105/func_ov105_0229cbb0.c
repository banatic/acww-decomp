/* func_ov105_0229cbb0 @ 0x0229cbb0, 0x30 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229cdbc(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov105_0229cbb0(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;
    p[0x2be] = 4;
    func_ov105_0229cdbc(arg0);
    func_ov002_022096d8((char *) arg0 + 0x2508, 0);
    func_ov002_02208098(arg0, 0x18);
}
