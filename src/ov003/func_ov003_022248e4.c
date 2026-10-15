/* func_ov003_022248e4 @ 0x022248e4, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cfe4[];
extern void *data_ov003_0223cf74;
extern void *data_ov003_0223cf78;
extern int data_ov003_0223cf70;

extern int func_020552b0(void *p);
extern void func_ov003_02223928(void *p);
extern void func_ov003_02221488(int *p);
extern void func_02045d44(void);
extern void func_020e9fd4(void *h);

int func_ov003_022248e4(char *self)
{
    func_020552b0(self + 0x4ae0);
    func_020552b0(self + 0x4af0);
    func_020552b0(self + 0x4b00);
    func_020552b0(self + 0x4b10);
    func_ov003_02223928(self + 0x4b20);
    func_ov003_02221488(data_ov003_0223cfe4);
    func_02045d44();
    if (data_ov003_0223cf74) {
        func_020e9fd4(data_ov003_0223cf74);
        data_ov003_0223cf74 = 0;
    }
    if (data_ov003_0223cf78) {
        func_020e9fd4(data_ov003_0223cf78);
        data_ov003_0223cf78 = 0;
    }
    data_ov003_0223cf70 = 0;
    return 1;
}
