/* func_02031078 @ 0x02031078, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void *data_020da1a8; // at 0x020da1a8

struct UnkStruct_02031078 {
    unsigned char pad_00[0x120];
    void *obj;
};

class Object {
  public:
    virtual int f1();
    virtual int f2();
    virtual int method(int *a, int *b, int *c, int x, int y);
};

int func_02031078(int arg0, int arg1, int *out1, int *out2, int *out3)
{
    Object *obj = (Object *) ((UnkStruct_02031078 *) data_020da1a8)->obj;
    int a, b, c;
    if (obj != 0) {
        if (obj->method(&a, &b, &c, arg0, arg1) != 0) {
            *out1 = a;
            *out2 = b;
            *out3 = c;
            return 1;
        }
    }
    return 0;
}
}
