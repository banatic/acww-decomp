/* func_020b8744 @ 0x020b8744, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a844(void *arg);
extern void func_020b884c(void *arg);
extern int func_020b8854(void *arg);
extern int func_020b8878(void *arg);
extern void *func_0208a9ac(void *arg);
extern void func_020b8a5c(void *arg);

typedef struct {
    unsigned char pad_00[0xf4];
    unsigned short *sub;
    unsigned short id;
} UnkStruct_020b8744;

void func_020b8744(void *p)
{
    UnkStruct_020b8744 *s = (UnkStruct_020b8744 *) p;

    if (func_0208a844((char *) p + 8) == 0) {
        func_020b884c(p);
        return;
    }

    if (s->sub == 0) {
        goto skip;
    }
    if (s->id == 0xfff1) {
        goto call8854;
    }
    if (s->id != *s->sub) {
        goto skip;
    }

call8854:
    if (func_020b8854(p) != 0) {
        goto skip;
    }
    if (func_020b8878(p) == 0) {
        goto a5c;
    }

skip:
    func_0208a9ac((char *) p + 8);
    return;

a5c:
    func_020b8a5c(p);
}
