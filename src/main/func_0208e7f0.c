/* func_0208e7f0 @ 0x0208e7f0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SubObject {
    char data[0x20];
} SubObject;

typedef struct MyObject {
    void *vtable;
    char pad_04[8];
    SubObject sub1;
    SubObject sub2;
} MyObject;

extern void func_0208a1f4(void *ptr);
extern void func_0208af00(MyObject *obj);

extern unsigned char data_020e2314[];

MyObject *func_0208e7f0(MyObject *obj)
{
    obj->vtable = (void *) data_020e2314;
    func_0208a1f4(&obj->sub2);
    func_0208a1f4(&obj->sub1);
    func_0208af00(obj);
    return obj;
}
