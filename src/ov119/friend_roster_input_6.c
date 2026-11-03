/* friend_roster_input_6: 3 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c13c @ 0x0229c13c, 0x64 bytes, Thumb
 * func_ov119_0229c090 @ 0x0229c090, 0xac bytes, Thumb
 * func_ov119_0229c008 @ 0x0229c008, 0x88 bytes, Thumb
 */

struct FlagsStruct {
    unsigned short unk_00;
    unsigned short flags;
};

extern int func_ov002_02208054(void *self, int a);
extern void func_ov119_0229bc14(void *self);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov119_0229b0f8(void *self, unsigned char a, unsigned char b);
extern int func_ov119_0229b188(void *self);
extern int func_0206f56c(void);
extern void func_ov119_0229a4e4(void *);
extern void func_ov119_0229b828(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_02208b00(void *, unsigned char, unsigned char);
extern int func_ov119_0229a420(void *, int);
extern void func_ov002_02209114(void *, int, int);
extern int func_ov119_0229a5cc(void *, int);
extern void func_ov119_0229bc30(void *p);
extern int func_ov119_0229b5a8(void *p, int v);
extern void func_ov119_0229b930(void *p);
extern void func_ov119_0229b808(void *p);
extern int func_ov119_0229c608(void *p, int v);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov090_02299078(int a);
extern int func_ov090_02299098(int a);
extern struct FlagsStruct data_021fbe40;

void func_ov119_0229c13c(void *self)
{
    unsigned int cond;
    if (func_ov002_02208054(self, 1)) {
        func_ov119_0229bc14(self);
        return;
    }
    if (data_021fbdd8 == 0) {
        goto zero;
    }
    if (data_021fbddc == 0) {
        goto zero;
    }
    cond = 1;
    goto done;
zero:
    cond = 0;
done:
    if (cond) {
        int r = func_ov119_0229b0f8(self, data_021f6c58, data_021f6c54);
        if (r != 0x17) {
            *((unsigned char *) self + 0xa0) = r;
            func_ov119_0229b188(self);
        }
    }
}

void func_ov119_0229c090(void *self)
{
    int r;
    int v;
    int w;

    if (func_0206f56c() != 0) {
        func_ov119_0229a4e4(self);
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov119_0229b828(self);
        func_ov002_02208098(self, 6);
        return;
    }

    r = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (r == 0) {
        return;
    }

    v = func_ov002_02208b00((char *) self + 0xdc, data_021f6c58, data_021f6c54);
    if (v < 0) {
        return;
    }

    w = func_ov119_0229a420(self, 0x10);
    if (w != 0 && v == 0) {
        return;
    }

    func_ov002_02209114((char *) self + 0xdc, v, 1);
    ((char *) self)[0xad] = (char) func_ov119_0229a5cc(self, v);
    func_ov002_02208098(self, 0xb);
}

void func_ov119_0229c008(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov119_0229bc30(p);
        return;
    } else {
        int v = func_ov002_02208008(p);
        if (func_ov119_0229b5a8(p, v)) {
            func_ov119_0229b930(p);
            return;
        } else {
            unsigned short flags = data_021fbe40.flags;
            if (flags & 1) {
                func_ov119_0229b808(p);
                return;
            } else if (flags & 0x100) {
                int r = func_ov090_02299078(6);
                func_ov119_0229c608(p, r);
                return;
            } else if (flags & 0x200) {
                int r = func_ov090_02299098(6);
                func_ov119_0229c608(p, r);
                return;
            }
        }
    }
}
