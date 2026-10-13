/* func_ov139_02299a68 @ 0x02299a68, 0x16 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208aa60(void *);

class UnkStruct_02299a68 {
  public:
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov139_02299a68(UnkStruct_02299a68 *obj)
{
    func_0208aa60(obj);
    obj->f3();
}
