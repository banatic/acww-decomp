/* func_ov131_0229b5b4 @ 0x0229b5b4, 0x5a bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

func_ov131_0229b5b4(void *r0)
{
    extern void func_ov131_0229b404(void);
    extern void func_ov131_0229b3f4(void *);
    extern void func_ov131_0229b3d4(void *);
    extern void func_02002708(int);
    extern void func_ov131_0229b504(void *);
    extern void func_ov131_0229ad34(void *, int);
    extern void func_ov002_0220ab38(void *, int);
    extern void func_ov002_02208090(void *, int);
    extern void func_ov002_02207f20(void *, int, int, int, int);

    void *r4 = r0;
    func_ov131_0229b404();
    func_ov131_0229b3f4(r4);
    func_ov131_0229b3d4(r4);
    func_ov002_02207f20(r4, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov131_0229b504(r4);
    func_ov131_0229ad34(r4, 1);
    func_ov002_0220ab38((char *) r4 + 0xf8, 0x65);
    func_ov002_02208090(r4, 1);
}
