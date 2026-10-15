/* func_02065d0c @ 0x02065d0c, 0xaa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070c08(void *);
extern int func_020707d0(void *);
extern int func_020b4980(void *, const char *, int);
extern int func_020a87e0(void *, void *);
extern int func_02051ce0(void *, int, int);
extern int func_02051c08(void *, const void *, int);
extern int func_02051c8c_unk(void *, int);
extern void *func_020707b8(void *);
extern int **func_02070be8(void *);
void func_02065d0c(const char *arg0, const unsigned short *arg1, unsigned char *out, void *dest)
{
    struct {
        char objA[0x6c];
        char objB[0x0c];
        char buf[0x54];
    } s;
    int val;
    unsigned int len;
    int offset;
    int len2;
    unsigned short *q;
    func_02070c08(s.objA);
    func_020707d0(s.objB);
    func_020b4980(s.objA, arg0, 0);
    func_020a87e0(s.objB, s.objA);
    len = func_02051ce0((unsigned short *) (&s.buf[2]), 0x29, 0);
    *out = (unsigned char) len;
    if (len != 0) {
        func_02051c08((unsigned short *) (&s.buf[2]), arg1, len);
    }
    offset = len;
    if (dest != 0) {
        offset = func_02051c8c_unk(dest, 6);
        func_02051c08(dest, arg1 + len, offset);
        offset = len + offset;
    }
    if (((unsigned short *) (&s.buf[2]))[len] == 0xa) {
        val = len + 1;
        q = ((unsigned short *) (&s.buf[2])) + val;
        len2 = func_02051ce0(q, 0x29 - val, 0);
        if (len2 != 0) {
            func_02051c08(q, arg1 + offset, len2);
        }
    }
    func_020707b8(s.objB);
    func_02070be8(s.objA);
}
