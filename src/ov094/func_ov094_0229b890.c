/* func_ov094_0229b890 @ 0x0229b890, 0x22 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov094_0229b8d8(void *parameter0, int parameter1);
extern void func_02066650(void *);
extern void func_ov094_0229b134(void *p, void *q);

void func_ov094_0229b890(void *a, void *b)
{
    func_02066650((void *) func_ov094_0229b8d8((void *) (a), (int) (b)));
    func_ov094_0229b134((char *) a + 8, b);
}
