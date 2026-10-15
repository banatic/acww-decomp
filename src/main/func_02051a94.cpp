/* func_02051a94 @ 0x02051a94, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02051a94 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int m0();
    virtual int m1();
};

extern "C" void *memcpy(int a, int b, int c);

extern "C" int func_02051a94(UnkStruct_02051a94 *obj, int param2)
{
    int r7 = obj->m0();
    int r6 = obj->m1();
    int pos = r7 - 1;
    signed char *q = (signed char *) (r6 + pos);
    int flag;

    memcpy(r6, param2, r7);
    q[0] = 0;
    flag = (q[0] == 0);
    if (flag == 0) {
        q[0] = 0;
    }
    return flag;
}
