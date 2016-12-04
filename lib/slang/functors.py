from .functor import *
from .utility import *
from .data import cursorize, Cursor
import operator

not_ = functor(operator.not_)
is_ = functor(operator.is_)
lt = functor(operator.lt)
gt = functor(operator.gt)
ge = functor(operator.ge)
le = functor(operator.le)
eq = functor(operator.eq)
ne = functor(operator.ne)
and_ = functor(operator.and_)
or_ = functor(operator.or_)

@functor
def true(*args):
  return True

@functor
def false(*args):
  return False

@functor
def is_function(cursor):
  return cursor.kind in FUNCTION_KINDS

@functor
def function_body(cursor):
  assert is_function(cursor)
  return uselect(cursorize(cursor), [is_compound_stmt])

@functor
def is_definition(cursor):
  if not is_function(cursor): return False
  children = list(cursor.get_children())
  result = bool(children) and is_compound_stmt(children[-1])
  assert result == cursor.is_definition()
  return result

@functor
def function_has_empty_body(cursor):
  body = function_body(cursor)
  return empty(select(cursorize(body), [ne(body)]))

@functor
def function_body_stmts(cursor):
  body = function_body(cursor)
  return sum(1 for _ in body.children)

@functor
def is_compound_stmt(cursor):
  return cursor.kind == CursorKind.COMPOUND_STMT

@functor
def owned_by(cursor):
  return lambda obj: cursor == Cursor(obj)

@functor
def is_kind(cursor, kind):
  return cursor.kind == kind

@functor
def is_class_like(cursor):
  return cursor.kind in (
      CursorKind.CLASS_DECL
    , CursorKind.CLASS_TEMPLATE
    , CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION
    )

@functor
def is_constructor(cursor):
  if cursor.kind == CursorKind.CONSTRUCTOR:
    return True
  if cursor.kind == CursorKind.FUNCTION_TEMPLATE:
    parent = cursor.semantic_parent
    if parent and is_class_like(parent):
      # E.g., 'optional<T>' -> 'optional'
      basename = lambda s: s.split('<')[0]
      return basename(parent.spelling) == basename(cursor.spelling)
  return False

@functor
def is_spelled(obj, spelling):
  return obj.spelling == spelling

@functor
def contains_keyword(cursor, spelling):
  found = select(
      cursor.tokens, [is_kind(_, TokenKind.KEYWORD), is_spelled(_, spelling)]
    )
  return not empty(found)

@functor
def is_whitespace(token):
  try:
    return token.isWhitespace
  except AttributeError:
    return False

@functor
def is_space(token):
  try:
    return token.isSpace
  except AttributeError:
    return False

@functor
def is_line_end(token):
  try:
    return token.isLineEnding
  except AttributeError:
    return False

@functor
def length_as_single_line(cursor):
  counting = True # To skip strings of whitespace.
  length = 0
  for token in cursor.tokens:
    if is_whitespace(token):
      if counting:
        length += 1
        counting = False
    else:
      counting = True
      length += len(token.spelling)
  return length

@functor
def function_has_newline_before_body(cursor):
  body = function_body(cursor)
  p = uselect(cursor.tokens, [owned_by(body), is_spelled(_, '{')])
  prev = uselect(revfrom(p.prev()), [or_(not_(is_whitespace), is_line_end)])
  return is_line_end(prev)

@functor
def this(item):
  return item

@functor
def up(item):
  if item is None:
    return None
  else:
    return item.up()

@functor
def down(item, i):
  if item is None:
    return None
  else:
    return item.down(i)

@functor
def left(item):
  if item is None:
    return None
  else:
    return item.left()

@functor
def right(item):
  if item is None:
    return None
  else:
    return item.right()

@functor
def true(*args):
  return True

@functor
def false(*args):
  return False



# Add _ to the public names.
__all__ = ['_'] + filter(lambda s: not s.startswith('_'), globals().keys())
