/* func_020705c0 @ 0x020705c0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *data_021fbe94;
extern char data_021ee418[];

extern void *func_020e9958(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_020e993c(void *, void *);
extern void *func_020900f0(void *);
extern void func_02066830(void *, void *);
extern void func_02090100(void *);
extern void func_02090140(void *, int);

void func_020705c0(char *s)
{
    void *heap;
    void *buf;
    char *obj;

    heap = data_021fbe94;
    buf = func_020e9958(heap, 0x100);
    MI_CpuCopy8(s + 1, buf, 0x100);
    obj = data_021ee418;
    func_02066830(func_020900f0(obj), buf);
    func_02090100(obj);
    func_02090140(obj, 0);
    func_020e993c(heap, buf);
}
