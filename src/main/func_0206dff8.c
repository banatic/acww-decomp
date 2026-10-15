/* func_0206dff8 @ 0x0206dff8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x60];
} Buffer;

extern void *func_020a88ec(void *p);
extern void func_020a8874(void *dst, const void *src, unsigned int len);
extern void func_0206db74(void *p);
extern void func_0206dbc0(void *p, void *q);
extern void *func_020a887c(void *p);
extern char data_020df270[];

void func_0206dff8(char *obj, const void *data)
{
    Buffer buf;
    func_020a88ec(&buf);
    buf.unk_00 = data_020df270;
    func_0206db74((char *) obj + 0x74);
    func_020a8874(&buf, data, 0x10);
    obj = (char *) obj + 0x74;
    func_0206dbc0(obj, &buf);
    buf.unk_00 = data_020df270;
    func_020a887c(&buf);
}
