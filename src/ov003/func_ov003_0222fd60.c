/* func_ov003_0222fd60 @ 0x0222fd60, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222fd60;
extern UnkStruct_0222fd60 *data_020ccf94;

extern int func_0205c9c8(int size, int heapword);
extern void func_0205c9ac(void);
extern int func_0205ca30(int size, int heapword);
extern void func_0205ca14(void);
extern int func_0205c9fc(int size, int heapword);
extern void func_0205c9e0(void);

extern int func_0209d180(void *self, unsigned int count, int a, int b, int size, int (*allocate)(int, int),
                         void (*cleanup)(void), void *context);
extern int func_02073dd4(void *a, int b);
extern int func_ov003_0222ff74(void *self, int a, int b);
extern void func_ov003_0222c758(void);

int func_ov003_0222fd60(char *self)
{
    UnkStruct_0222fd60 *context;
    func_0209d180(self + 0x50, 8, 0x400, 0x40, 0x9c4, func_0205c9c8, func_0205c9ac, 0);
    func_0209d180(self + 0x68, 2, 0x400, 0x40, 0x6e8, func_0205ca30, func_0205ca14, 0);
    func_0209d180(self + 0x80, 4, 0x400, 0x40, 0x9c4, func_0205c9fc, func_0205c9e0, 0);
    context = data_020ccf94;
    if (func_02073dd4(context, context->unk_64) == 0) {
        func_ov003_0222ff74(self, 0x3a, 0);
        func_ov003_0222ff74(self, 0x3b, 1);
    }
    func_ov003_0222c758();
    return 1;
}
