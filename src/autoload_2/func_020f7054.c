/* func_020f7054 @ 0x020f7054, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f6f3c(void *list);
extern void func_020eed18(void *obj, int param);
extern void func_020eedb8(int param, unsigned short value, void *obj);

typedef struct {
    void *link;
    unsigned int data;
    unsigned short id;
    unsigned char flag;
} EnvObj;

void func_020f7054(EnvObj *self, unsigned short id, unsigned int data)
{
    unsigned int has_link;

    func_020f6f3c(&self->link);
    has_link = (self->link != 0) ? 1u : 0u;
    if (has_link > 0) {
        func_020eed18(self, 0);
    }
    self->id = id;
    self->data = data;
    self->flag = 1;
    func_020eedb8(0, self->id, self);
}
