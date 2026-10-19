/* func_ov068_0226e76c @ 0x0226e76c, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209615c(int size);
extern int func_0201c2a4(void *self, int a);
extern void func_02016108(void *addr, int b);
extern void func_ov068_0226e878(void *self, int a);

typedef struct {
    char pad_00[0x658];
    void *vtable;
} UnkStruct_0226e76c;

int func_ov068_0226e76c(UnkStruct_0226e76c *self)
{
    int r;
    if (func_0209615c(4) == 0) {
        (*(void (**)(void *))(*(void ***) ((char *) self + 0x658) + 2))((char *) self + 0x658);
        r = func_0201c2a4(self, 4);
        func_02016108((char *) self + 0x658, r);
        func_ov068_0226e878(self, 1);
    }
    return 1;
}
