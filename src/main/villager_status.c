/* villager_status: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207f2c4 @ 0x0207f2c4, 0x22 bytes, Thumb
 * func_0207f29c @ 0x0207f29c, 0x28 bytes, Thumb
 * func_0207f294 @ 0x0207f294, 0x8 bytes, Thumb
 * func_0207f270 @ 0x0207f270, 0x22 bytes, Thumb
 * func_0207f1d8 @ 0x0207f1d8, 0x98 bytes, Thumb
 * func_0207f1d4 @ 0x0207f1d4, 0x4 bytes, Thumb
 * func_0207f1c8 @ 0x0207f1c8, 0xc bytes, Thumb
 * func_0207f184 @ 0x0207f184, 0x44 bytes, Thumb
 * func_0207f150 @ 0x0207f150, 0x34 bytes, Thumb
 * func_0207f120 @ 0x0207f120, 0x2e bytes, Thumb
 * func_0207f0f0 @ 0x0207f0f0, 0x2e bytes, Thumb
 * func_0207f0c0 @ 0x0207f0c0, 0x2e bytes, Thumb
 * func_0207f074 @ 0x0207f074, 0x4c bytes, Thumb
 * func_0207ef54 @ 0x0207ef54, 0x11e bytes, Thumb
 * func_0207ef48 @ 0x0207ef48, 0xc bytes, Thumb
 * func_0207ef3c @ 0x0207ef3c, 0xc bytes, Thumb
 */

typedef struct UnkStruct_0207f1d8 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0207f1d8;

extern int func_02003648(unsigned char *);
extern int func_02082500(int);
extern int func_0208150c(int param);
extern int func_0207cf14(void *ptr, int value);
extern char data_021e5a2c;
extern int func_02079350(void);
extern int func_02079330(int, int);
extern UnkStruct_0207f1d8 *data_020ccf94;
extern int func_02073dd4(UnkStruct_0207f1d8 *, int);
extern int func_020794d8(int);
extern int func_02079544(int);
extern unsigned int func_0209c304(int val);
extern int func_0209c330(int val);
extern int func_0209bff0(void *p, int val);
extern int func_02003704(int);
extern int func_0209b5ec(void *);
extern int func_020984e8(void);
extern int func_02099640(int);
extern char *func_0209ad9c(void *p, int i);
extern void *func_0209b4d4(const void *p);
extern int func_0209bd44(void *p);
extern char *func_0209b4cc(const void *p, int data);
extern int memcmp(const void *a, const void *b, int n);
extern int func_0209a854(void *p, char *key);
extern int func_0209aebc(void *p, char *key);

int func_0207f120(int arg0);
int func_0207f0f0(int param);
int func_0207f0c0(int param);
int func_0207ef54(void *a0, char *obj);

int func_0207f2c4(int result)
{
    int temp;

    temp = func_02082500((int) func_02003648((unsigned char *) func_0208150c(result)));

    if (temp != 0) {
        result = *(unsigned char *) (temp + 0x4d);
    } else {
        result = 0;
    }

    return result;
}

int func_0207f29c(int param)
{
    void *p = (void *) &data_021e5a2c;
    int result = -1;
    if (p != 0) {
        int tmp = func_0208150c(param);
        result = func_0207cf14(p, tmp);
    }
    return result;
}

int func_0207f294(int argument0)
{
    return func_0207f29c((int) argument0);
}

int func_0207f270(int arg)
{
    return func_02079330(func_02079350(), func_0207f29c(arg));
}

int func_0207f1d8(void *a)
{
    int r = 0;

    if (func_02003704((int) ((void *) (unsigned int) func_0208150c((int) a)))) {
        r = func_0207f270((int) a);
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
            if (func_020794d8(r) == 2) {
                r = 2;
            } else {
                r = 1;
            }
        } else {
            switch (func_02079544(r)) {
                case 0:
                    if (func_020794d8(r) == 2) {
                        r = 2;
                    } else {
                        r = 1;
                    }
                    break;
                case 2:
                    r = 3;
                    break;
                case 3:
                    r = 4;
                    break;
                case 5:
                    r = 6;
                    break;
                case 6:
                    r = 7;
                    break;
                case 4:
                    r = 5;
                    break;
                case 1:
                default:
                    r = 0;
                    break;
            }
        }
    }
    return r;
}

int func_0207f1d4(void *handle)
{
    return 1;
}

unsigned int func_0207f1c8(unsigned int r0)
{
    return r0 + 0x734;
}

int func_0207f184(char *p0, void *p1)
{
    if (func_0209c304(func_0209b5ec((void *) (p0 + 0x734))) <= 1) {
        return func_0209bff0(p1, func_0209c330(func_0209b5ec((void *) (p0 + 0x734))));
    } else {
        return func_0209bff0(p1, 7);
    }
}

int func_0207f150(void *param)
{
    int result;

    if (func_0207f120((int) param) != 0) {
        result = 0;
    } else if (func_0207f0f0((int) param) != 0) {
        result = 1;
    } else if (func_0207f0c0((int) param) != 0) {
        result = 2;
    } else {
        result = 3;
    }
    return result;
}

int func_0207f120(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    result = func_02003704((int) ((void *) (unsigned int) func_0208150c(arg0)));
    if (result != 0) {
        if (func_0209c330((int) ((unsigned char *) (void *) func_0209b5ec((void *) (int) func_0207f1c8(r4)))) == 9) {
            return 1;
        }
    }
    return 0;
}

int func_0207f0f0(int param)
{
    if (func_02003704(func_0208150c(param)) != 0 &&
        func_0209c330((func_0209b5ec((void *) (int) func_0207f1c8(param)))) == 10) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207f0c0(int param)
{
    if (func_02003704(func_0208150c(param)) && func_0209c330((func_0209b5ec((void *) (int) func_0207f1c8(param)))) == 11) {
        return 1;
    }
    return 0;
}

int func_0207f074(int x)
{
    int temp;
    temp = func_02099640(func_020984e8());
    if (func_02003704(func_0208150c(x)) == 0) {
        goto fail;
    }
    if (func_0207f150((void *) x) != 3) {
        goto fail;
    }
    if (func_0207f1d8((void *) x) == 2) {
        goto fail;
    }
    if (func_0207ef54((void *) x, (char *) temp) != 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

static inline int eq(const char *t, const char *key)
{
    return *(const unsigned short *) t == *(const unsigned short *) key && memcmp(t + 2, key + 2, 12) == 0 &&
           *(const unsigned char *) (t + 0xf) == *(const unsigned char *) (key + 0xf);
}

int func_0207ef54(void *a0, char *obj)
{
    char *key;
    char *e0;
    char *e1;
    char *q;

    key = (char *) func_0208150c((int) a0);
    if (func_02003704((int) key) != 0) {
        e0 = func_0209ad9c(obj, 0);
        e1 = func_0209ad9c(obj, 1);
        q = obj;
        q = obj + 0xa4;
        if (func_0209bd44(func_0209b4d4(e0)) != 0) {
            if (eq(func_0209b4cc(e0, 0), key) || eq(func_0209b4cc(e0, 1), key)) {
                return 1;
            }
        }
        if (func_0209bd44(func_0209b4d4(e1)) != 0) {
            if (eq(func_0209b4cc(e1, 0), key) || eq(func_0209b4cc(e1, 1), key)) {
                return 1;
            }
        }
        if (func_0209a854(obj, key) != 0) {
            return 1;
        }
        if (func_0209aebc(q, key) != 0) {
            return 1;
        }
    }
    return 0;
}

unsigned char func_0207ef48(unsigned char *base)
{
    return base[0x7d6];
}

void func_0207ef3c(unsigned char *base, unsigned char val)
{
    base[0x7d6] = val;
}
