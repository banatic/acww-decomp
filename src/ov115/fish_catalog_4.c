/* fish_catalog_4: 9 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229e34c @ 0x0229e34c, 0x8 bytes, Thumb
 * func_ov115_0229e334 @ 0x0229e334, 0x16 bytes, Thumb
 * func_ov115_0229e328 @ 0x0229e328, 0xc bytes, Thumb
 * func_ov115_0229e2e0 @ 0x0229e2e0, 0x46 bytes, Thumb
 * func_ov115_0229e2c8 @ 0x0229e2c8, 0x18 bytes, Thumb
 * func_ov115_0229e2b0 @ 0x0229e2b0, 0x18 bytes, Thumb
 * func_ov115_0229e228 @ 0x0229e228, 0x88 bytes, Thumb
 * func_ov115_0229e1f0 @ 0x0229e1f0, 0x38 bytes, Thumb
 * func_ov115_0229e168 @ 0x0229e168, 0x88 bytes, Thumb
 */

typedef struct {
    char pad_00[2];
    unsigned short flags;
} UnkStruct_0229e168;

typedef struct {
    char pad_00[0xf8];
    char unk_F8;
} UnkStruct_0229e168_2;

extern void func_ov114_0229d87c(void *);
extern void func_ov115_0229df50(void *);
extern void func_ov114_0229d824(int r0);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov114_0229d700(void *p);
extern void func_ov114_0229c8dc(void *p);
extern void func_ov114_0229d688(void *receiver);
extern void func_ov114_0229cadc(void *);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(char *self, int a);
extern void func_ov115_0229df8c(char *self);
extern int func_ov114_0229d564(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229d3f4(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229ca50(char *p, unsigned char a, unsigned char b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov114_0229d32c(void *ptr, unsigned char val);
extern void func_ov114_0229d304(void *ptr);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov114_0229c410(void *, int);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);
extern void func_ov115_0229dfa8(void *);
extern void func_ov115_0229de60(void *);
extern void func_ov115_0229ddf8(void *);
extern int func_ov115_0229e4cc(void *, int);
extern UnkStruct_0229e168 data_021fbe40;

void func_ov115_0229e328(int r0);

void func_ov115_0229e34c(int argument0)
{
    func_ov115_0229e328(argument0);
}

void func_ov115_0229e334(void *self)
{
    func_ov114_0229d87c((char *) self + 0xf8);
    func_ov115_0229df50(self);
}

void func_ov115_0229e328(int r0)
{
    func_ov114_0229d824(r0 + 0xf8);
}

void func_ov115_0229e2e0(void)
{
    func_020029e8(3, 1);
    func_020028bc(3, 0, 0, 0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov115_0229e2c8(void *self)
{
    func_ov114_0229d700((char *) self + 0xf8);
    func_ov114_0229c8dc((char *) self + 0xf8);
}

void func_ov115_0229e2b0(char *p)
{
    func_ov114_0229d688((void *) ((char *) p + 0xf8));
    p += 0xf8;
    func_ov114_0229cadc(p);
}

void func_ov115_0229e228(char *self)
{
    unsigned int cond;
    unsigned char b;
    unsigned char c;
    if (func_ov002_02208054(self, 1)) {
        func_ov115_0229df8c(self);
        return;
    }
    cond = ((data_021fbdd8 != 0) && (data_021fbddc != 0)) ? (1) : (0);
    if (cond > 0) {
        if (self) {
            b = data_021f6c58;
            c = data_021f6c54;
        } else {
            b = data_021f6c58;
            c = data_021f6c54;
        }
        if (func_ov114_0229d564(self + 0xf8, b, c) == 0) {
            if (func_ov114_0229d3f4(self + 0xf8, b, c) != 0) {
                func_ov002_02208098((void *) (self), 1);
                return;
            }
            self = self + (0xf8 & 0xFFFFFFFFFFFFFFFF);
            if (func_ov114_0229ca50(self, b, c)) {
                return;
            }
        }
    }
}

void func_ov115_0229e1f0(void *self)
{
    if (data_021fbdd8) {
        func_ov114_0229d32c((char *) self + 0xf8, data_021f6c58);
    } else {
        func_ov114_0229d304((char *) self + 0xf8);
        func_ov002_02208098((void *) (self), 0);
    }
}

void func_ov115_0229e168(UnkStruct_0229e168_2 *param)
{
    unsigned short flags;

    if (func_ov002_02208014(param) != 0) {
        func_ov115_0229dfa8(param);
        return;
    }
    if (func_ov114_0229c410(&param->unk_F8, func_ov002_02208008(param)) != 0) {
        func_ov115_0229de60(param);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov115_0229ddf8(param);
        return;
    }
    if (flags & 0x100) {
        func_ov115_0229e4cc(param, func_ov090_02299078(2));
        return;
    }
    if (flags & 0x200) {
        func_ov115_0229e4cc(param, func_ov090_02299098(2));
    }
}
