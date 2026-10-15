/* func_ov075_022795dc @ 0x022795dc, 0x30 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *object);
extern void func_0201c280(void *object, int value);
extern void func_ov075_02278b64(void *object, int value);

int func_ov075_022795dc(void *this)
{
    if (!func_0202edc8(this)) {
        return 0;
    }
    func_0201c280(this, (int) ((char *) this + 0x658));
    func_ov075_02278b64(((char *) this + 0x658), (int) this);
    return 1;
}
