/* mailbox_scene_8: 8 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229e99c @ 0x0229e99c, 0x8 bytes, Thumb
 * func_ov106_0229e960 @ 0x0229e960, 0x3c bytes, Thumb
 * func_ov106_0229e928 @ 0x0229e928, 0x38 bytes, Thumb
 * func_ov106_0229e8f4 @ 0x0229e8f4, 0x32 bytes, Thumb
 * func_ov106_0229e8e0 @ 0x0229e8e0, 0x14 bytes, Thumb
 * func_ov106_0229e88c @ 0x0229e88c, 0x54 bytes, Thumb
 * func_ov106_0229e860 @ 0x0229e860, 0x2c bytes, Thumb
 * func_ov106_0229e7e0 @ 0x0229e7e0, 0x80 bytes, Thumb
 */

extern void func_ov106_0229d3b0(void *);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov002_0220af74(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov106_0229cf0c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);
extern int data_021fbe94;
extern int data_ov106_0229f740[];
extern int data_ov106_0229f760[];
extern int data_ov106_0229f784[];
extern int func_02002d14(int *p, int a, int b, int c, int d, int e);
extern int func_02002ca4(int *p, int a, int b);
extern int func_02002c6c(int *p, int a, int b, int c, int d, int e);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220ab84(char *addr, int value);
extern int func_ov002_02208054(void *self, int flag);
extern void func_ov106_0229d75c(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov106_0229d2e4(char *a, int b, int c, int d);
extern void func_ov106_0229d60c(void *p, int val);
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov106_0229c378(void *arg);

void func_ov106_0229e928(void *self);

void func_ov106_0229e99c(void *argument0)
{
    func_ov106_0229e928(argument0);
}

void func_ov106_0229e960(void *p)
{
    func_ov106_0229d3b0(p);
    func_ov094_0229a084((char *) p + 0xb80);
    func_ov094_0229af20((char *) p + 0xf8);
    func_ov094_0229bbc0((char *) p + 0xb58);
    func_ov002_0220af74((char *) p + 0x3fb4);
}

void func_ov106_0229e928(void *self)
{
    func_ov002_022091cc((char *) self + 0x2304);
    func_ov094_0229a05c((char *) self + 0xb80);
    if (func_ov002_02207d5c((char *) self + 0x21b8)) {
        func_ov106_0229cf0c(self);
    }
}

void func_ov106_0229e8f4(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov106_0229e8e0(int x)
{
    func_ov094_0229a29c(x + 0xB80, 0);
}

void func_ov106_0229e88c(void *self)
{
    int value = data_021fbe94;
    int local1 = 4;
    int local2 = 4;

    func_02002d14(data_ov106_0229f740, value, 4, 4, local1, local2);
    func_02002ca4(data_ov106_0229f760, value, 4);

    local1 = 0x1e2;
    local2 = 0x227;
    func_02002c6c(data_ov106_0229f784, value, 4, local1, local1, local2);
}

void func_ov106_0229e860(char *p)
{
    func_ov094_0229a098((void *) ((char *) p + 0xb80));
    func_ov002_0220af94((void *) ((char *) p + 0x3fb4));
    func_ov002_0220ab84(p + 0x3fb4, 0x88);
}

void func_ov106_0229e7e0(void *self)
{
    int result;
    int cond;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov106_0229d75c(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto isfalse;
    }
    if (data_021fbddc == 0) {
        goto isfalse;
    }
    cond = 1;
    goto done;
isfalse:
    cond = 0;
done:
    if (cond == 0) {
        return;
    }
    result = func_ov106_0229d2e4((char *) self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (result != 0x20) {
        func_ov106_0229d60c(self, result);
        return;
    }
    if (func_ov002_0220a784((char *) self + 0x3fb4, 9) != 0) {
        func_ov106_0229c378(self);
    }
}
