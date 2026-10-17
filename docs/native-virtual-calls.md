# Audited virtual calls in Native copies

The matching source for func_ov100_0229e3b0 gives CSub::f3 an empty inline
body. Both PC compilers eliminate self->sub.f3(), leaving only the call to
func_ov100_0229e374. The ROM performs both calls: after the first returns,
0229e3ba computes self+0x2274, 0229e3bc loads that subobject's vtable,
0229e3be loads slot 3 at offset 12, and 0229e3c0 calls it.

tools/native_virtual.py changes only that empty definition into a declaration
in the PC copy. An exact source digest requires a new audit after any source
change. The compiler's unresolved method call uses the existing virtual_calls
probe and generated thunk, which read the object's current vtable at slot 3.
The original source, other method bodies and Reference policy are unchanged.

tools/test_native_virtual.py compiles the actual game source through
native.compile_one and links the production-generated dispatch thunk. Its
fixture changes the vtable during the first call and checks call order, the
subobject this pointer, slot selection and two distinct dynamic targets.
Full Windows and Linux recording, scene and differential gates remain required.
