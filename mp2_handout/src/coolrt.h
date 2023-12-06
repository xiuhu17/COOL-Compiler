/*
 * This file provides the runtime library for cool. It implements
 * the cool classes in C.  Feel free to change it to match the structure
 * of your code generator.
 */

#include <stdbool.h>

typedef struct Object Object;
typedef struct Int Int;
typedef struct Bool Bool;
typedef struct String String;
typedef struct IO IO;

typedef struct _Object_vtable Object_vtable;
typedef struct _Int_vtable Int_vtable;
typedef struct _Bool_vtable Bool_vtable;
typedef struct _String_vtable String_vtable;
typedef struct _IO_vtable IO_vtable;

/* class type definitions */
struct Object {
  const Object_vtable *vtblptr;
};

struct Int {
  const Int_vtable *vtblptr;
  int val;
};

struct Bool {
  const Bool_vtable *vtblptr;
  bool val;
};

struct String {
  const String_vtable *vtblptr;
  const char *val;
};

struct IO {
  const IO_vtable *vtblptr;
};

/* vtable type definitions */
struct _Object_vtable {
  int tag;
  int size;
  const char *name;

  Object *(*abort_object)(Object *self);
  String *(*type_name_object)(Object *self);
  Object *(*copy_object)(Object *self);
};

struct _Int_vtable {
  int tag;
  int size;
  const char *name;

  Object *(*abort_int)(Object *self);
  String *(*type_name_int)(Object *self);
  Object *(*copy_int)(Object *self);
};

struct _Bool_vtable {
  int tag;
  int size;
  const char *name;

  Object *(*abort_bool)(Object *self);
  String *(*type_name_bool)(Object *self);
  Object *(*copy_bool)(Object *self);
};

struct _String_vtable {
  int tag;
  int size;
  const char *name;

  Object *(*abort_string)(Object *self);
  String *(*type_name_string)(Object *self);
  Object *(*copy_string)(Object *self);
  int (*length_string)(String *self);
  String *(*concat_string)(String *self, String *s);
  String *(*substr_string)(String *self, int i, int l);
};

struct _IO_vtable {
  int tag;
  int size;
  const char *name;

  Object *(*abort_io)(Object *self);
  String *(*type_name_io)(Object *self);
  Object *(*copy_io)(Object *self);
  IO *(*out_string_io)(IO *self, String *s);
  IO *(*out_int_io)(IO *self, int x);
  String *(*in_string_io)(IO *self);
  int (*in_int_io)(IO *self);
};

/* Class vtable prototypes */
extern const Object_vtable _Object_vtable_prototype;
extern const Int_vtable _Int_vtable_prototype;
extern const Bool_vtable _Bool_vtable_prototype;
extern const String_vtable _String_vtable_prototype;
extern const IO_vtable _IO_vtable_prototype;

/* methods in class Object */
Object *Object_new(void);
Object *Object_abort(Object *self);
String *Object_type_name(Object *self);
Object *Object_copy(Object *self);

/* methods in class Int */
Int *Int_new(void);
void Int_init(Int *self, int i);

/* methods in class Bool */
Bool *Bool_new(void);
void Bool_init(Bool *self, bool b);

/* methods in class String */
String *String_new(void);
int String_length(String *self);
String *String_concat(String *self, String *s);
String *String_substr(String *self, int i, int l);

/* methods in class IO */
IO *IO_new(void);
IO *IO_out_string(IO *self, String *s);
IO *IO_out_int(IO *self, int x);
String *IO_in_string(IO *self);
int IO_in_int(IO *self);
