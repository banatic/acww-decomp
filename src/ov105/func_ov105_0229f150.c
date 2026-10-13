/* func_ov105_0229f150 @ 0x0229f150, 0x64 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229e9a4(void *);
extern void func_ov105_0229d49c(void *);
extern void func_ov105_0229c330(void *, int);
extern void func_ov105_0229ed98(void *);
extern void func_02002708(int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov002_02208090(void *, int);

void func_ov105_0229f150(void *r0)
{
    void *r4 = r0;
    int sp[2];

    func_ov105_0229e9a4(r4);
    func_ov094_0229ad20((char *) r4 + 0x2fc);
    func_ov094_0229b2b0((char *) r4 + 0xd5c);
    func_ov105_0229d49c(r4);
    func_ov002_02207f20(r4, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(r4, 2);
    func_ov105_0229c330(r4, 1);
    func_ov105_0229c330(r4, 2);
    func_ov105_0229ed98(r4);
}
