/* func_ov133_0229c2b0 @ 0x0229c2b0, 0x4c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

void func_ov133_0229c2b0(void *param)
{
    extern void func_ov133_0229ba10(void *);
    extern void func_ov002_02207f04(void *, int, int, int, int);
    extern void func_ov002_02207e80(void *, int, int, int);
    extern void func_ov002_02208090(void *, int);
    extern int func_ov002_02207f60(void *);

    void *r4 = param;
    int result;

    func_ov133_0229ba10(r4);
    func_ov002_02207f04(r4, 10, 0, 0, 0x30);
    func_ov002_02207e80(r4, 4, 0, 0);
    func_ov002_02207e80(r4, 6, 0, 0);
    func_ov002_02208090(r4, 4);
    result = func_ov002_02207f60(r4);
    r4 = (char *) r4 + 0x94;
    *(int *) r4 = result;
}
