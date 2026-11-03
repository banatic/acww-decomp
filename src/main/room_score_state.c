/* room_score_state: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205bfcc @ 0x0205bfcc, 0x2 bytes, Thumb
 * func_0205bfc8 @ 0x0205bfc8, 0x2 bytes, Thumb
 * func_0205bfc4 @ 0x0205bfc4, 0x2 bytes, Thumb
 * func_0205bfc0 @ 0x0205bfc0, 0x2 bytes, Thumb
 * func_0205bfbc @ 0x0205bfbc, 0x2 bytes, Thumb
 * func_0205bf90 @ 0x0205bf90, 0x2c bytes, Thumb
 * func_0205bf88 @ 0x0205bf88, 0x8 bytes, Thumb
 * func_0205be9c @ 0x0205be9c, 0xec bytes, Thumb
 * func_0205be64 @ 0x0205be64, 0x38 bytes, Thumb
 */

extern void func_0209e474(void *p);
extern void func_0209e140(void *, int);
extern int func_0209de88(int, int, int);
extern void func_0209e29c(void *, int);
extern int func_0209e3ac(void *, void *, int);

void func_0205bfcc(void *object) {}

void func_0205bfc8(void *object) {}

void func_0205bfc4(void *object) {}

void func_0205bfc0(void *self) {}

void func_0205bfbc(void *self) {}

void func_0205bf90(unsigned char *out)
{
    int t[2];
    t[0] = 0;
    t[1] = 0;
    func_0209e474(t);
    out[0] = ((unsigned char *) t)[3];
    out[1] = ((unsigned char *) t)[4];
    out[2] = ((unsigned char *) t)[5];
    out[3] = 0;
}

void func_0205bf88(unsigned char *argument0)
{
    func_0205bf90((unsigned char *) argument0);
}

int func_0205be9c(unsigned char *r4)
{
    unsigned int buf1[2];
    unsigned int buf2[2];
    unsigned int key[2];
    int r;

    buf1[0] = 0;
    buf1[1] = 0;
    func_0209e474(buf1);
    if (((unsigned char *) buf1)[2] < 6) {
        ((unsigned char *) buf1)[2] = 7;
        func_0209e140(buf1, 1);
    }

    buf2[0] = 0;
    buf2[1] = 0;
    func_0209e474(buf2);
    r = func_0209de88(((unsigned char *) buf2)[5], ((unsigned char *) buf2)[4], ((unsigned char *) buf2)[3]);
    func_0209e140(buf2, r);

    if (((unsigned char *) buf2)[5] > ((unsigned char *) buf1)[5]) {
        func_0209e29c(buf2, 7);
    }

    key[0] = 0;
    key[1] = 0;
    ((unsigned char *) key)[5] = r4[2];
    ((unsigned char *) key)[4] = r4[1];
    ((unsigned char *) key)[3] = r4[0];
    ((unsigned char *) key)[2] = 7;
    ((unsigned char *) key)[1] = 0;
    ((unsigned char *) key)[0] = 0;

    if (func_0209e3ac(buf1, key, 0x38) == -1) {
        r4[2] = ((unsigned char *) buf1)[5];
        r4[1] = ((unsigned char *) buf1)[4];
        r4[0] = ((unsigned char *) buf1)[3];
        ((unsigned char *) key)[5] = r4[2];
        ((unsigned char *) key)[4] = r4[1];
        ((unsigned char *) key)[3] = r4[0];
        ((unsigned char *) key)[2] = 7;
        ((unsigned char *) key)[1] = 0;
        ((unsigned char *) key)[0] = 0;
        return 0;
    }

    if (func_0209e3ac(key, buf2, 0x38) != -1) {
        goto ret0;
    }
    if (func_0209e3ac(buf2, buf1, 0x38) == -1) {
        goto ret1;
    }
    if (func_0209e3ac(buf2, buf1, 0x38) != 0) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

void func_0205be64(unsigned char *out)
{
    unsigned int buffer[2];
    buffer[0] = 0;
    buffer[1] = 0;
    func_0209e474(buffer);
    if (((unsigned char *) buffer)[2] < 6) {
        func_0209e140(buffer, 1);
    }
    out[0] = ((unsigned char *) buffer)[3];
    out[1] = ((unsigned char *) buffer)[4];
    out[2] = ((unsigned char *) buffer)[5];
}
