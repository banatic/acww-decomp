/* func_ov139_02299a68 @ 0x02299a68, 0x16 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208aa60(void *, int parameter1, int parameter2);

class UnkStruct_02299a68 {
  public:
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov139_02299a68(UnkStruct_02299a68 *obj, int arg1, int arg2)
{
    func_0208aa60(obj, arg1, arg2);
    obj->f3();
}
