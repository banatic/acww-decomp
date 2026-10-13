/* func_ov119_0229c1a0 @ 0x0229c1a0, 0x78 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void func_02002c6c(void *data, void *ptr, int size, int v1, int v2, int v3);
extern void func_02002d14(void *data, void *ptr, int size, int v1, int v2, int v3);
extern void func_02064af4(void *data, void *ptr, int size);
extern char data_ov119_0229cf00[];
extern char data_ov119_0229cf18[];
extern char data_ov119_0229cf30[];
extern char data_ov119_0229cf44[];

void func_ov119_0229c1a0(int a1)
{
    void *p;

    p = data_021fbe94;
    func_02002c6c((void *) data_ov119_0229cf00, p, 8, 0xc0, 0xc0, 0x15d);
    func_02002c6c((void *) data_ov119_0229cf18, p, 8, 0x1a0, 0x1a0, 0x1df);
    func_02002d14((void *) data_ov119_0229cf30, p, 8, 4, 4, 0xa);
    func_02064af4((void *) data_ov119_0229cf44, (void *) (a1 + 0x1e10), 0x20);
}
