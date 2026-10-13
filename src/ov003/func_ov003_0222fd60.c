/* func_ov003_0222fd60 @ 0x0222fd60, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222fd60;
extern UnkStruct_0222fd60 *data_020ccf94;

extern void func_0205c9c8(void);
extern void func_0205c9ac(void);
extern void func_0205ca30(void);
extern void func_0205ca14(void);
extern void func_0205c9fc(void);
extern void func_0205c9e0(void);

extern void func_0209d180(void *p, int a, int b, int c, int size, void (*f0)(void), void (*f1)(void), int z);
extern int func_02073dd4(void *a, int b);
extern void func_ov003_0222ff74(void *self, int a, int b);
extern void func_ov003_0222c758(void);

int func_ov003_0222fd60(char *self)
{
    func_0209d180(self + 0x50, 8, 0x400, 0x40, 0x9c4, func_0205c9c8, func_0205c9ac, 0);
    func_0209d180(self + 0x68, 2, 0x400, 0x40, 0x6e8, func_0205ca30, func_0205ca14, 0);
    func_0209d180(self + 0x80, 4, 0x400, 0x40, 0x9c4, func_0205c9fc, func_0205c9e0, 0);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        func_ov003_0222ff74(self, 0x3a, 0);
        func_ov003_0222ff74(self, 0x3b, 1);
    }
    func_ov003_0222c758();
    return 1;
}
