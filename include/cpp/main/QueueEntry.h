#ifndef CPP_MAIN_QUEUEENTRY_H
#define CPP_MAIN_QUEUEENTRY_H

// Head of a 0x1c-byte record that func_0200e894 copies into a 30-slot
// queue; built on the stack by its callers.
struct QueueEntry {
    int unk_00;
    int unk_04;
    short unk_08;
};

extern "C" {
// Constructor and destructor; both return the object.
QueueEntry *func_0200e92c(QueueEntry *self);
QueueEntry *func_0200e91c(QueueEntry *self);
void func_0200e90c(QueueEntry *self, int a, int b, int c);
}

#endif
