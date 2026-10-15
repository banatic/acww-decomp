/* func_0209e974 @ 0x0209e974, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern unsigned short *func_02095040(void *);
extern void *func_02099308(void *);
extern void func_0209df64(void *);
extern void func_02095038(void *, void *);
extern void *func_020996b8(void *);
extern void func_02072be0(void *, void *, unsigned short *);
extern void func_02098fd0(void *, int);
extern int func_02099670(void *);
extern void func_02088ac0(unsigned char *);
extern void func_02088aa0(void *);
extern unsigned int func_02099688(void *);
extern void func_020882f0(void *);
extern void func_020993b4(void *);
extern void func_020642f8(unsigned short *);

struct UnkStruct_0209e974 {
    unsigned short a;
    struct {
        unsigned short v[6];
    } r;
};

void func_0209e974(void *arg)
{
    void *obj;
    void *ptr;
    unsigned short *src;
    struct UnkStruct_0209e974 buf;

    obj = func_020984e8();
    src = (func_02095040((void *) func_02099870(obj)));

    buf.a = ((struct UnkStruct_0209e974 *) src)->a;
    buf.r = ((struct UnkStruct_0209e974 *) src)->r;

    func_0209df64(func_02099308(obj));
    func_02095038(func_02099870(obj), (unsigned char *) arg + 2);
    ptr = func_020996b8(obj);
    func_02072be0(ptr, func_02099870(obj), (unsigned short *) &buf);

    func_02098fd0(obj, 0x24);
    func_02098fd0(obj, 0x25);
    func_02098fd0(obj, 0x26);
    func_02088ac0((unsigned char *) func_02099670(obj));

    func_02098fd0(obj, 0xf);
    func_02088aa0((void *) func_02099670(obj));

    func_020882f0((void *) func_02099688(obj));

    func_020993b4(obj);
    func_020642f8((unsigned short *) &buf);
}