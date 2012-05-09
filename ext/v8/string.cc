#include "rr.h"

namespace rr {

VALUE String::Class;

void String::Init() {
  ClassBuilder("String", "Value").
    defineSingletonMethod("New", &New).
    defineSingletonMethod("Concat", &Concat).
    defineMethod("Utf8Value", &Utf8Value).
    store(&Class);
}

VALUE String::New(VALUE StringClass, VALUE string) {
  return String::convert(v8::String::New(RSTRING_PTR(string), (int)RSTRING_LEN(string)));
}

VALUE String::Utf8Value(VALUE self) {
  String str(self);
  return rb_str_new(*v8::String::Utf8Value(str.GetHandle()), str->Utf8Length());
}

VALUE String::Concat(VALUE self, VALUE left, VALUE right) {
  return Convert(v8::String::Concat(String(left), String(right)));
}

VALUE String::convert(v8::Handle<v8::String> string) {
  return String::create(string, Class);
}

} //namespace rr