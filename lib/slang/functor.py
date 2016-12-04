import numbers
__all__ = ['_', 'functor']

# Placeholder
_ = type('Arg', (), {})()

class functor(object):
  def __new__(cls, f):
    return f if isinstance(f, functor) else object.__new__(cls)
  def __init__(self, f):
    if f is not self:
      self.f = f
  def __call__(self, *args):
    f_ = object.__getattribute__(self, 'f')
    if any(callable(arg) or arg is _ for arg in args):
      def wrapped(x):
        deref = lambda y: y(x) if callable(y) else x if y is _ else y
        args_ = [deref(arg) for arg in args]
        return f_(*args_)
      wrapped.funtr = self
      wrapped.args = args
      return functor(wrapped)
    else:
      return f_(*args)
  @staticmethod
  def rebind(funtr, transformer):
    wrapped = object.__getattribute__(funtr, 'f')
    if hasattr(wrapped, 'args'):
      args = list(wrapped.args)
      if isinstance(transformer, numbers.Number):
        n = transformer
        transformer = lambda seq: tuple(
            n if isinstance(x, numbers.Number) else x for x in seq
          )
      return wrapped.funtr(*transformer(args))
    else:
      return funtr
  def __getattribute__(self, name):
    return getattr(object.__getattribute__(self, 'f'), name)
  def __or__(lhs, rhs): return functor(lambda l,r: l or r)(lhs, functor(rhs))
  def __ror__(rhs, lhs): return functor(lambda l,r: l or r)(functor(lhs), rhs)
  def __and__(lhs, rhs): return functor(lambda l,r: l and r)(lhs, functor(rhs))
  def __rand__(rhs, lhs): return functor(lambda l,r: l and r)(functor(lhs), rhs)
  def __invert__(self): return functor(lambda l: not l)(self)

