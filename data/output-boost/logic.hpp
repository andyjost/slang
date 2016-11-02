
    void nonnull() {};

  tribool() : value(false_value) {}

  tribool(bool initial_value) : value(initial_value? true_value : false_value) {}

  tribool(indeterminate_keyword_t) : value(indeterminate_value) {}

  operator safe_bool() const
  {
    return value == true_value? &dummy::nonnull : 0;
  }

inline bool indeterminate(tribool x, detail::indeterminate_t)
{
  return x.value == tribool::indeterminate_value;
}

inline tribool operator!(tribool x)
{
  return x.value == tribool::false_value? tribool(true)
        :x.value == tribool::true_value? tribool(false)
        :tribool(indeterminate);
}

inline tribool operator&&(tribool x, tribool y)
{
  if (static_cast<bool>(!x) || static_cast<bool>(!y))
    return false;
  else if (static_cast<bool>(x) && static_cast<bool>(y))
    return true;
  else
    return indeterminate;
}

inline tribool operator&&(tribool x, bool y)
{ return y? x : tribool(false); }

inline tribool operator&&(bool x, tribool y)
{ return x? y : tribool(false); }

inline tribool operator&&(indeterminate_keyword_t, tribool x)
{ return !x? tribool(false) : tribool(indeterminate); }

inline tribool operator&&(tribool x, indeterminate_keyword_t)
{ return !x? tribool(false) : tribool(indeterminate); }

inline tribool operator||(tribool x, tribool y)
{
  if (static_cast<bool>(!x) && static_cast<bool>(!y))
    return false;
  else if (static_cast<bool>(x) || static_cast<bool>(y))
    return true;
  else
    return indeterminate;
}

inline tribool operator||(tribool x, bool y)
{ return y? tribool(true) : x; }

inline tribool operator||(bool x, tribool y)
{ return x? tribool(true) : y; }

inline tribool operator||(indeterminate_keyword_t, tribool x)
{ return x? tribool(true) : tribool(indeterminate); }

inline tribool operator||(tribool x, indeterminate_keyword_t)
{ return x? tribool(true) : tribool(indeterminate); }

inline tribool operator==(tribool x, tribool y)
{
  if (indeterminate(x) || indeterminate(y))
    return indeterminate;
  else
    return (x && y) || (!x && !y);
}

inline tribool operator==(tribool x, bool y) { return x == tribool(y); }

inline tribool operator==(bool x, tribool y) { return tribool(x) == y; }

inline tribool operator==(indeterminate_keyword_t, tribool x)
{ return tribool(indeterminate) == x; }

inline tribool operator==(tribool x, indeterminate_keyword_t)
{ return tribool(indeterminate) == x; }

inline tribool operator!=(tribool x, tribool y)
{
  if (indeterminate(x) || indeterminate(y))
    return indeterminate;
  else
    return !((x && y) || (!x && !y));
}

inline tribool operator!=(tribool x, bool y) { return x != tribool(y); }

inline tribool operator!=(bool x, tribool y) { return tribool(x) != y; }

inline tribool operator!=(indeterminate_keyword_t, tribool x)
{ return tribool(indeterminate) != x; }

inline tribool operator!=(tribool x, indeterminate_keyword_t)
{ return x != tribool(indeterminate); }
