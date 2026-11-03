/* item_traits_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c520 @ 0x0204c520, 0xa4 bytes, Thumb
 * func_0204c4e8 @ 0x0204c4e8, 0x38 bytes, Thumb
 * func_0204c4c0 @ 0x0204c4c0, 0x26 bytes, Thumb
 * func_0204c4b8 @ 0x0204c4b8, 0x6 bytes, Thumb
 * func_0204c438 @ 0x0204c438, 0x80 bytes, Thumb
 * func_0204c3f0 @ 0x0204c3f0, 0x48 bytes, Thumb
 */

typedef struct UnkStruct_0204c3f0 UnkStruct_0204c3f0;

extern void func_02061e2c(void *dst, int src);
extern int func_0204bcf8(void *p);
extern unsigned int func_0204b42c(int arg);
extern void *func_02062870(void *p);
extern void func_020051b0(void *p);
extern int func_0204bcdc(void *p);
extern int func_0204c614(void *p);
extern int func_0204c5ec(void *p);
extern int func_0204c5c4(void *p);
extern void func_0204b3cc(void *buffer, int value);
extern int func_0206266c(void *buffer);
extern int func_0204b1d8(unsigned short *);
extern int func_0204c63c(int param);
extern int func_0204bd08(void *p);
extern int func_0204c358(void *p);
extern int func_0204c3c8(void *p);
extern int func_0204c3a0(UnkStruct_0204c3f0 *p);
extern int func_0204fa68(int);

int func_0204c520(int arg)
{
    struct {
        unsigned short head;
        unsigned char body[6];
    } local;
    void *result;

    func_02061e2c(&local, arg);
    if (func_0204bcf8(&local) == 1) {
        func_0204b3cc(&local.body[0], func_0204b42c(arg));
        result = func_02062870(&local.body[0]);
        func_020051b0(&local.body[0]);
        func_020051b0(&local);
        return (int) result;
    } else {
        if (func_0204bcdc(&local) != 0) {
            if (func_0204c614(&local) != 0) {
                func_020051b0(&local);
                return 0x39;
            }
            if (func_0204c5ec(&local) != 0) {
                func_020051b0(&local);
                return 0x3a;
            }
            if (func_0204c5c4(&local) != 0) {
                func_020051b0(&local);
                return 0x3a;
            }
            func_020051b0(&local);
            return 0x3b;
        } else {
            func_020051b0(&local);
            return 0;
        }
    }
}

int func_0204c4e8(void *param)
{
    if (func_0204bcf8(param) == 1) {
        int result;
        char buffer[8];
        func_0204b3cc(buffer, (int) func_0204b42c((int) param));
        result = func_0206266c(buffer);
        func_020051b0(buffer);
        return result;
    }
    return 0;
}

int func_0204c4c0(int param)
{
    int result;
    int r4;

    r4 = param;
    if (func_0204b1d8((unsigned short *) param) != 0) {
        if (func_0204c63c(r4) == 8) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}

void func_0204c4b8(unsigned short *d, unsigned short *s)
{
    d[0] = *s;
}

int func_0204c438(void *p0, void *p1)
{
    char local[8];
    int result;

    func_0204b3cc(local, 0x0000fff1);
    result = 0;
    func_02061e2c(local + 2, (int) p0);
    if (func_0204bd08(local + 2) || func_0204bcdc(local + 2)) {
        if (func_0204c358(local + 2) == 0 && func_0204c3c8(local + 2) == 0) {
            func_0204c4b8((unsigned short *) local, (unsigned short *) (local + 2));
            result = 1;
        }
    }
    if (p1) {
        func_0204c4b8((unsigned short *) p1, (unsigned short *) local);
    }
    func_020051b0(local + 2);
    func_020051b0(local);
    return result;
}

int func_0204c3f0(UnkStruct_0204c3f0 *p)
{
    if (func_0204c3c8((void *) p) != 0) {
        switch (func_0204fa68((int) func_0204c3a0(p))) {
            case 1:
                return 0;
            case 3:
                return 1;
            case 2:
                return 2;
            case 0:
                return 3;
        }
    }
    return 4;
}
