/* func_ov049_02262414 @ 0x02262414, 0x58 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(void *unused0);
extern int func_0201c040(void *self, int *a, int *b);
extern int func_020a7278(void);
extern void func_0201c054(void *self, int a, int b, int c);
extern void func_ov049_02262a94(void *self, int a);

typedef struct {
    unsigned char pad_00[0x64];
    int value;
} UnkStruct_02262414;
extern UnkStruct_02262414 *data_020ccf94;

int func_ov049_02262414(void *self)
{
    if (func_0201c0e0(self) != 0) {
        int a = 4;
        int b = 4;
        if (func_0201c040(self, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(self, 1, data_020ccf94->value, 4);
                    func_ov049_02262a94(self, 0xa);
                }
            }
        }
    }
    return 1;
}
