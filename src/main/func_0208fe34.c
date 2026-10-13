/* func_0208fe34 @ 0x0208fe34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e246c[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

struct UnkStruct_0208fe34 {
    void *vtable;
    unsigned char pad_04[0x10];
    char unk_14;
};

void *func_0208fe34(void *arg)
{
    struct UnkStruct_0208fe34 *obj = (struct UnkStruct_0208fe34 *) arg;
    obj->vtable = data_020e246c;
    func_0208a1f4(&obj->unk_14);
    func_0208af00(obj);
    func_020edb3c(obj);
    return obj;
}
