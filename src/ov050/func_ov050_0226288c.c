/* func_ov050_0226288c @ 0x0226288c, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(void *a, int b);
extern int func_0209b4d4(void *object);
extern void func_0209bb90(int a, int b);

typedef struct {
    char pad_00[0xb4];
    unsigned char *ptr;
} ObjA;

extern void func_ov050_02262910(ObjA *a, void *b);

void func_ov050_0226288c(ObjA *a, void *b)
{
    func_0209bb90(func_0209b4d4((void *) (func_0209ad9c(b, 0))), 0);
    a->ptr[0x73e] = 1;
    func_ov050_02262910(a, b);
}
