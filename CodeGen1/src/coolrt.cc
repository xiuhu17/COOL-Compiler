#include "coolrt.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This file provides the runtime library for cool. It implements
   the functions of the cool classes in C
   */

/* Class name strings */
const char Object_string[] = "Object";
const char Int_string[] = "Int";
const char Bool_string[] = "Bool";
const char String_string[] = "String";
const char IO_string[] = "IO";

const char default_string[] = "";

/* Class vtable prototypes */
/*
const Object_vtable _Object_vtable_prototype = {
        .tag = 0,
        .size = sizeof(struct Object),
        .name = Object_string,

        .abort_object     = Object_abort,
        .type_name_object = Object_type_name,
        .copy_object      = Object_copy
};

const Int_vtable _Int_vtable_prototype = {
        .tag = 1,
        .size = sizeof(struct Int),
        .name = Int_string,

        .abort_int     = Object_abort,
        .type_name_int = Object_type_name,
        .copy_int      = Object_copy
};

const Bool_vtable _Bool_vtable_prototype = {
        .tag = 2,
        .size = sizeof(struct Bool),
        .name = Bool_string,

        .abort_bool     = Object_abort,
        .type_name_bool = Object_type_name,
        .copy_bool      = Object_copy
};

const String_vtable _String_vtable_prototype = {
        .tag = 3,
        .size = sizeof(struct String),
        .name = String_string,

        .abort_string     = Object_abort,
        .type_name_string = Object_type_name,
        .copy_string      = Object_copy,
        .length_string    = String_length,
        .concat_string    = String_concat,
        .substr_string    = String_substr
};

const IO_vtable _IO_vtable_prototype = {
        .tag = 4,
        .size = sizeof(struct IO),
        .name = IO_string,

        .abort_io      = Object_abort,
        .type_name_io  = Object_type_name,
        .copy_io       = Object_copy,
        .out_string_io = IO_out_string,
        .out_int_io    = IO_out_int,
        .in_string_io  = IO_in_string,
        .in_int_io     = IO_in_int
};

*/

/*
// Methods in class object (only some are provided to you)
*/
Object *Object_new() {
  Object *o = (Object *)malloc(sizeof(Object));
  if (o == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  o->vtblptr = &_Object_vtable_prototype;
  return o;
}

Object *Object_abort(Object *self) {
  printf("Abort called from class %s\n",
         !self ? "Unknown" : self->vtblptr->name);
  exit(1);
  return self;
}

String *Object_type_name(Object *self) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }
  String *s = String_new();
  s->val = self->vtblptr->name;
  return s;
}

Object *Object_copy(Object *self) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }

  unsigned size = self->vtblptr->size;
  assert(size > 0);
  Object *obj = (Object *)malloc(size);
  if (obj == 0) {
    fprintf(stderr, "At %s(line %d): malloc failed in Object::copy()\n",
            __FILE__, __LINE__);
    abort();
  }
  memcpy(obj, self, size);
  return obj;
}

/*
// Methods in class IO (only some are provided to you)
*/
IO *IO_new() {
  IO *io = (IO *)malloc(sizeof(IO));
  if (io == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  io->vtblptr = &_IO_vtable_prototype;
  return io;
}

IO *IO_out_string(IO *self, String *s) {
  if (self == 0 || s == 0) {
    fprintf(stderr, "At %s(line %d): NULL object\n", __FILE__, __LINE__);
    abort();
  }
  printf("%s", s->val);
  return self;
}

IO *IO_out_int(IO *self, int x) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): NULL object\n", __FILE__, __LINE__);
    abort();
  }
  printf("%d", x);
  return self;
}

/*
 * Get one line from stream using get_line(), then discard newline character.
 * Allocate string *in_string_p and store result there.
 * Return number of chars read.
 */
static int get_one_line(char **in_string_p, FILE *stream) {
  /* Get one line worth of input */
  size_t len = 0;
  ssize_t num_chars_read;
  num_chars_read = getline(in_string_p, &len, stdin);
  if (*in_string_p == 0) {
    fprintf(stderr, "At %s(line %d): allocation failed in IO::in_string()\n",
            __FILE__, __LINE__);
    exit(1);
  }

  /* Discard the newline char, if any.  It may not exist if EOF reached. */
  if (num_chars_read > 0 && (*in_string_p)[num_chars_read - 1] == '\n') {
    (*in_string_p)[num_chars_read - 1] = '\0';
    --len;
  }

  return len;
}

/*
 * The method IO::in_string(): String reads a string from
 * the standard input, up to but not including a newline character.
 */
String *IO_in_string(IO *self) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }

  /* Get one line worth of input with the newline, if any, discarded */
  char *in_string = 0;
  ssize_t len = get_one_line(&in_string, stdin);
  assert(in_string);

  /* We can take advantage of knowing the internal layout of String objects */
  String *str = String_new();
  str->val = in_string;
  return str;
}

/*
 * The method IO::in_int(): Int reads a single integer, which may be preceded
 * by whitespace.
 * Any characters following the integer, up to and including the next newline,
 * are discarded by in_int.
 */
int IO_in_int(IO *self) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }

  /* Get one line worth of input with the newline, if any, discarded */
  char *in_string = 0;
  ssize_t len = get_one_line(&in_string, stdin);
  assert(in_string);

  /* Now extract initial int and ignore the rest of the line */
  int x;
  int num_ints = 0;
  if (len)
    /* Discards initial spaces*/
    num_ints = sscanf(in_string, " %d", &x);

  /* If no text found, abort. */
  if (num_ints == 0) {
    fprintf(stderr,
            "At %s(line %d): Invalid integer on input in IO::in_int()\n",
            __FILE__, __LINE__);
    Object_abort((Object *)self);
  }
  return x;
}

/*
// Methods in class Int
*/
Int *Int_new() {
  Int *x = (Int *)malloc(sizeof(Int));
  if (x == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  x->vtblptr = &_Int_vtable_prototype;
  x->val = 0;
  return x;
}

void Int_init(Int *self, int i) { self->val = i; }

/*
// Methods in class Bool
*/
Bool *Bool_new() {
  Bool *b = (Bool *)malloc(sizeof(Bool));
  if (b == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  b->vtblptr = &_Bool_vtable_prototype;
  b->val = false;
  return b;
}

void Bool_init(Bool *self, bool b) { self->val = b; }

/*
// Methods in class String
*/
String *String_new() {
  String *s = (String *)malloc(sizeof(String));
  if (s == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  s->vtblptr = &_String_vtable_prototype;
  s->val = "";
  return s;
}

int String_length(String *self) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }

  return strlen(self->val);
}

String *String_concat(String *self, String *s) {
  if (self == 0 || s == 0) {
    fprintf(stderr, "At %s(line %d): NULL object\n", __FILE__, __LINE__);
    abort();
  }

  String *s1 = (String *)malloc(sizeof(String));
  if (s1 == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  s1->vtblptr = &_String_vtable_prototype;

  char *cats = (char *)malloc(strlen(self->val) + strlen(s->val) + 1);
  if (cats == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  strcpy(cats, self->val);
  strcat(cats, s->val);
  s1->val = cats;

  return s1;
}

String *String_substr(String *self, int i, int l) {
  if (self == 0) {
    fprintf(stderr, "At %s(line %d): self is NULL\n", __FILE__, __LINE__);
    abort();
  }

  int len = strlen(self->val);
  if (i >= len || i + l - 1 >= len) {
    fprintf(stderr, "At %s(line %d): Substring out of range\n", __FILE__,
            __LINE__);
    Object_abort((Object *)0);
  }

  String *s1 = (String *)malloc(sizeof(String));
  if (s1 == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  s1->vtblptr = &_String_vtable_prototype;

  char *subs = (char *)malloc(l + 1);
  if (subs == 0) {
    fprintf(stderr, "At %s(line %d): Out of memory\n", __FILE__, __LINE__);
    Object_abort((Object *)0);
  }
  strncpy(subs, &(self->val[i]), l);
  subs[l] = '\0';
  s1->val = subs;

  return s1;
}
