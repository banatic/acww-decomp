/* func_ov048_0226224c @ 0x0226224c, 0x4c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94; // 0x020ccf94
extern unsigned char func_020ec1e8(void);
extern void func_020732b4(void *p, int x);
extern void func_ov048_02262390(void *self, int x);
extern void func_ov048_02262618(void *self, int a, int b);
extern void func_ov048_022616b8(void *self, int x);

void func_ov048_0226224c(void *self)
{
    func_ov048_02262390(self, 1);
    if (func_020ec1e8() == 2) {
        func_020732b4(data_020ccf94, 1);
    } else {
        func_ov048_02262618(self, 2, 1);
    }
    *(unsigned short *) ((char *) *(void **) ((char *) self + 0xb8) + 0xe6e) = 0xc8;
    func_ov048_022616b8(self, 4);
}
