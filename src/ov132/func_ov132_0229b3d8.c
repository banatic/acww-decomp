/* func_ov132_0229b3d8 @ 0x0229b3d8, 0xe8 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov130_0229a678(int);
extern int func_02064af4(const void *src, void *dst, unsigned int size);
extern void func_0206fdd4(void *addr, int a1, int a2, int a3, int a4, int a5);
extern int func_02002b40(void *addr, int a1, unsigned int size, int a3);
extern void *func_ov132_0229ad88(void *ctx);
extern int func_0207094c(void *obj, int id);
extern void func_02070adc(void *obj, int a1, unsigned int a2, int a3, int a4, int a5, int a6);
extern void func_02070a04(void *obj, int a1, int a2);
extern const unsigned char data_ov132_0229b9f0[];
extern const unsigned char data_ov132_0229ba04[];

void func_ov132_0229b3d8(void *ctx)
{
    void *obj1;
    void *obj2;

    func_ov130_0229a678(6);
    func_02064af4(data_ov132_0229b9f0, (char *) ctx + 0x500, 0x800);
    func_0206fdd4((char *) ctx + 0x500, 6, 7, 0x19, 0xf, 6);
    func_02002b40((char *) ctx + 0x500, 6, 0x800, 0);

    func_02064af4(data_ov132_0229ba04, (char *) ctx + 0xd00, 0x800);
    func_0206fdd4((char *) ctx + 0xd00, 6, 7, 0x19, 0xf, 6);
    func_02002b40((char *) ctx + 0xd00, 4, 0x800, 0);

    obj1 = func_ov132_0229ad88(ctx);
    func_0207094c(obj1, 0x5f);
    func_02070adc(obj1, 4, 0x114, 0xe, 0xf, 0, 0);
    func_02070a04(obj1, 1, 0);

    obj2 = func_ov132_0229ad88(ctx);
    func_0207094c(obj2, 0x60);
    func_02070adc(obj2, 4, 0x130, 0xe, 0xf, 0, 0);
    func_02070a04(obj2, 1, 0);
}
