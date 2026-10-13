/* func_0202d84c @ 0x0202d84c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Task Task;
typedef struct TaskFuncs TaskFuncs;

struct TaskFuncs {
    void (*funcs[42])(Task *, int, int);
};

struct Task {
    TaskFuncs *funcs;
};

extern Task *func_02015d90(Task *task, int param);

void func_0202d84c(Task *task, int param)
{
    Task *t = func_02015d90(task, param);
    if (t) {
        t->funcs->funcs[41](t, 4, param);
    }
}
