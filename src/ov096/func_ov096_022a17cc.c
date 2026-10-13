/* func_ov096_022a17cc @ 0x022a17cc, 0x6c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002708(int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov096_0229c2ec(void *, int);
extern void *func_ov002_02207f60(void *);

void func_ov096_022a17cc(void *obj)
{
    func_ov094_0229ad20((char *) obj + 0x358);
    func_ov094_0229b2b0((char *) obj + 0xDB8);
    func_ov002_02207f20(obj, 8, 3, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, 0);
    func_ov002_02208090(obj, 4);
    func_ov096_0229c2ec(obj, 1);
    func_ov096_0229c2ec(obj, 2);
    *(void **) ((char *) obj + 0x98) = func_ov002_02207f60(obj);
}
