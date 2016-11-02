

  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  static point_type get(
      const segment_type& segment, direction_1d dir) {
    return segment.get(dir);
  }


  static void set(
      segment_type& segment, direction_1d dir, const point_type& point) {
    segment.set(dir, point);
  }


  static segment_type construct(const point_type& low, const point_type& high) {
    return segment_type(low, high);
  }


  static coordinate_type get(
      const point_type& point, orientation_2d orient) {
    return point.get(orient);
  }


  static void set(
      point_type& point, orientation_2d orient, coordinate_type value) {
    point.set(orient, value);
  }


  static point_type construct(coordinate_type x, coordinate_type y) {
    return point_type(x, y);
  }


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_get,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type get(const PointType& point, orientation_2d orient) {
  return point_traits<PointType>::get(point, orient);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_set,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  void
>::type set(PointType& point, orientation_2d orient,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  point_mutable_traits<PointType>::set(point, orient, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_construct,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type construct(
    typename point_mutable_traits<PointType>::coordinate_type x,
    typename point_mutable_traits<PointType>::coordinate_type y) {
  return point_mutable_traits<PointType>::construct(x, y);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_assign,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
>::type,
PointType1>::type& assign(PointType1& lvalue, const PointType2& rvalue) {
  set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
  set(lvalue, VERTICAL, get(rvalue, VERTICAL));
  return lvalue;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_x,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type x(const PointType& point) {
  return get(point, HORIZONTAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_y,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type y(const PointType& point) {
  return get(point, VERTICAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sx,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type x(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, HORIZONTAL, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sy,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type y(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, VERTICAL, value);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_equiv,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
bool>::type equivalence(
    const PointType1& point1, const PointType2& point2) {
  return (x(point1) == x(point2)) && (y(point1) == y(point2));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_man_dist,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
manhattan_distance(const PointType1& point1, const PointType2& point2) {
  return euclidean_distance(point1, point2, HORIZONTAL) +
         euclidean_distance(point1, point2, VERTICAL);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed1,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
euclidean_distance(
    const PointType1& point1,
    const PointType2& point2,
    orientation_2d orient) {
  typename point_difference_type<PointType1>::type dif =
      get(point1, orient) - get(point2, orient);
  return (dif < 0) ? -dif : dif;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_eds,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
distance_squared(const PointType1& point1, const PointType2& point2) {
  typename point_difference_type<PointType1>::type dx =
      euclidean_distance(point1, point2, HORIZONTAL);
  typename point_difference_type<PointType1>::type dy =
      euclidean_distance(point1, point2, VERTICAL);
  dx *= dx;
  dy *= dy;
  return dx + dy;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed2,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_distance_type<PointType1>::type>::type
euclidean_distance(const PointType1& point1, const PointType2& point2) {
  return (std::sqrt)(
      static_cast<double>(distance_squared(point1, point2)));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_convolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& convolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) + x(rvalue));
  y(lvalue, y(lvalue) + y(rvalue));
  return lvalue;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_deconvolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& deconvolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) - x(rvalue));
  y(lvalue, y(lvalue) - y(rvalue));
  return lvalue;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_up,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_up(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  x(point, x(point) * (Unit)factor);
  y(point, y(point) * (Unit)factor);
  return point;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_down,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_down(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  typedef typename coordinate_traits<Unit>::coordinate_distance dt;
  x(point, scaling_policy<Unit>::round((dt)(x(point)) / (dt)factor));
  y(point, scaling_policy<Unit>::round((dt)(y(point)) / (dt)factor));
  return point;
}


template <typename PointType, typename ScaleType>
typename enable_if<
  typename gtl_and<
    y_pt_scale,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale(PointType& point, const ScaleType& scaling) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  scaling.scale(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType, typename TransformType>
typename enable_if<
  typename gtl_and<
    y_pt_transform,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& transform(PointType& point, const TransformType& transform) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  transform.transform(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_move,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& move(PointType& point, orientation_2d orient,
    typename point_coordinate_type<PointType>::type displacement) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit coord = get(point, orient);
  set(point, orient, coord + displacement);
  return point;
}


  point_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  point_data(coordinate_type x, coordinate_type y) {
    coords_[HORIZONTAL] = x;
    coords_[VERTICAL] = y;
  }


  explicit point_data(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  point_data& operator=(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename PointType>
  explicit point_data(const PointType& that) {
    *this = that;
  }


  template <typename PointType>
  point_data& operator=(const PointType& that) {
    assign(*this, that);
    return *this;
  }

  template <typename CT>
  point_data(const point_data<CT>& that) {
    coords_[HORIZONTAL] = (coordinate_type)that.x();
    coords_[VERTICAL] = (coordinate_type)that.y();
  }


  coordinate_type get(orientation_2d orient) const {
    return coords_[orient.to_int()];
  }


  void set(orientation_2d orient, coordinate_type value) {
    coords_[orient.to_int()] = value;
  }


  coordinate_type x() const {
    return coords_[HORIZONTAL];
  }


  point_data& x(coordinate_type value) {
    coords_[HORIZONTAL] = value;
    return *this;
  }


  coordinate_type y() const {
    return coords_[VERTICAL];
  }


  point_data& y(coordinate_type value) {
    coords_[VERTICAL] = value;
    return *this;
  }


  bool operator==(const point_data& that) const {
    return (coords_[0] == that.coords_[0]) &&
      (coords_[1] == that.coords_[1]);
  }


  bool operator!=(const point_data& that) const {
    return !(*this == that);
  }


  bool operator<(const point_data& that) const {
    return (coords_[0] < that.coords_[0]) ||
      ((coords_[0] == that.coords_[0]) &&
       (coords_[1] < that.coords_[1]));
  }


  bool operator<=(const point_data& that) const {
    return !(that < *this);
  }


  bool operator>(const point_data& that) const {
    return that < *this;
  }


  bool operator>=(const point_data& that) const {
    return !(*this < that);
  }


  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }


  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }


  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}


  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }


  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }


  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }


  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }


  coordinate_type low() const {
    return coords_[0];
  }


  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }


  coordinate_type high() const {
    return coords_[1];
  }


  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }


  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }


  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }


  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }


  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }


  bool operator>(const interval_data& that) const {
    return that < *this;
  }


  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

  inline rectangle_data():ranges_() {}

  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }

  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }


  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }

  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }

  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }


  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }

  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }

  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }

    static inline interval_type get(const T& rectangle, orientation_2d orient) {
      return rectangle.get(orient); }

    template <typename T2>
    static inline void set(T& rectangle, orientation_2d orient, const T2& interval) {
      rectangle.set(orient, interval); }

    template <typename T2, typename T3>
    static inline T construct(const T2& interval_horizontal,
                              const T3& interval_vertical) {
      return T(interval_horizontal, interval_vertical); }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_get_interval, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                      typename rectangle_interval_type<T>::type>::type
  get(const T& rectangle, orientation_2d orient) {
    return rectangle_traits<T>::get(rectangle, orient);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_h, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  horizontal(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, HORIZONTAL);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_v, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  vertical(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, VERTICAL);
  }


  template <orientation_2d_enum orient, typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, orientation_2d orient, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_h2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  horizontal(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, HORIZONTAL, interval);
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_v2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                     typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type, void>::type
  vertical(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, VERTICAL, interval);
  }


  template <typename T, typename T2, typename T3>
  typename enable_if< typename gtl_and<y_r_construct, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(const T2& interval_horizontal,
            const T3& interval_vertical) {
    return rectangle_mutable_traits<T>::construct(interval_horizontal, interval_vertical); }


  template <typename T, typename coord_type>
  typename enable_if< typename gtl_and<y_r_construct2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(coord_type xl, coord_type yl, coord_type xh, coord_type yh) {
    return rectangle_mutable_traits<T>::construct(interval_data<coord_type>(xl, xh),
                                                  interval_data<coord_type>(yl, yh));
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_cconstruct,
      typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    T>::type
  copy_construct(const T2& rectangle) {
    return construct<T> (get(rectangle, HORIZONTAL), get(rectangle, VERTICAL));
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_assign,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  assign(rectangle_type_1& lvalue, const rectangle_type_2& rvalue) {
    set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
    set(lvalue, VERTICAL, get(rvalue, VERTICAL));
    return lvalue;
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3< y_r_equiv,
      typename is_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    bool>::type
  equivalence(const T& rect1, const T2& rect2) {
    return equivalence(get(rect1, HORIZONTAL), get(rect2, HORIZONTAL)) &&
      equivalence(get(rect1, VERTICAL), get(rect2, VERTICAL));
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_get, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  get(const rectangle_type& rectangle, orientation_2d orient, direction_1d dir) {
    return get(rectangle_traits<rectangle_type>::get(rectangle, orient), dir);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_set3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  set(rectangle_type& rectangle, orientation_2d orient, direction_1d dir,
      typename rectangle_coordinate_type<rectangle_type>::type value) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    set(ivl, dir, value);
    set(rectangle, orient, ivl);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xl(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      xl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xh(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  xh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yl(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yh(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ll,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ll(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_lr,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  lr(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ul,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ul(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yh(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ur,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ur(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yh(rectangle));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_contains, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  contains(const rectangle_type& rectangle, const rectangle_type_2 rectangle_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), horizontal(rectangle_contained), consider_touch) &&
      contains(vertical(rectangle), vertical(rectangle_contained), consider_touch);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_contains2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, bool>::type
  contains(const rectangle_type& rectangle, const point_type point_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), x(point_contained), consider_touch) &&
      contains(vertical(rectangle), y(point_contained), consider_touch);
  }

  template <typename rectangle_type, typename point_type_1, typename point_type_2>
  typename enable_if< typename gtl_and_4< y_r_set_points,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_1>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_2>::type>::type>::type,
                       rectangle_type>::type &
  set_points(rectangle_type& rectangle, const point_type_1& p1,
             const point_type_2& p2) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit x1(x(p1));
    Unit x2(x(p2));
    Unit y1(y(p1));
    Unit y2(y(p2));
    horizontal(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(x1, x2));
    vertical(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(y1, y2));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_move, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  move(rectangle_type& rectangle, orientation_2d orient,
       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference delta) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    move(ivl, delta);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_convolve,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  convolve(rectangle_type_1& rectangle,
           const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3< y_r_deconvolve,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_reconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_convolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_redeconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_convolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       rectangle_type>::type &
  convolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_deconvolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, rectangle_type>::type &
  deconvolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_delta, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  delta(const rectangle_type& rectangle, orientation_2d orient) {
    return delta(get(rectangle, orient));
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_area, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type>::type
  area(const rectangle_type& rectangle) {
    typedef typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type area_type;
    return (area_type)delta(rectangle, HORIZONTAL) * (area_type)delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_go, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      orientation_2d>::type
  guess_orientation(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) >= delta(rectangle, VERTICAL) ?
      HORIZONTAL : VERTICAL;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_half_p, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  half_perimeter(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) + delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_perimeter, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  perimeter(const rectangle_type& rectangle) {
    return 2 * half_perimeter(rectangle);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_intersects, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  intersects(const rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    return intersects(horizontal(rectangle), horizontal(b), consider_touch) &&
      intersects(vertical(rectangle), vertical(b), consider_touch);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  boundaries_intersect(const rectangle_type_1& rectangle, const rectangle_type_2& b,
                       bool consider_touch = true) {
    return (intersects(rectangle, b, consider_touch) &&
            !(contains(rectangle, b, !consider_touch)) &&
            !(contains(b, rectangle, !consider_touch)));
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        direction_2d dir) {
    return
      abuts(get(rectangle, orientation_2d(dir)),
            get(b, orientation_2d(dir)),
            direction_1d(dir)) &&
      intersects(get(rectangle, orientation_2d(dir).get_perpendicular()),
                 get(b, orientation_2d(dir).get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts2, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        orientation_2d orient) {
    return
      abuts(get(rectangle, orient), get(b, orient)) &&
      intersects(get(rectangle, orient.get_perpendicular()),
                 get(b, orient.get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts3, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b) {
    return abuts(rectangle, b, HORIZONTAL) || abuts(rectangle, b, VERTICAL);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
    bool>::type
  intersect(rectangle_type& rectangle, const interval_type& b,
            orientation_2d orient, bool consider_touch = true) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(intersect(ivl, b, consider_touch)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_intersect3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  intersect(rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    if(intersects(rectangle, b)) {
      intersect(rectangle, horizontal(b), HORIZONTAL, consider_touch);
      intersect(rectangle, vertical(b), VERTICAL, consider_touch);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_g_intersect,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  generalized_intersect(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = get(rectangle, HORIZONTAL);
    generalized_intersect(ivl, horizontal(b));
    horizontal(rectangle, ivl);
    ivl = vertical(rectangle);
    generalized_intersect(ivl, vertical(b));
    vertical(rectangle, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, orientation_2d orient,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    bloat(ivl, bloating);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    bloat(rectangle, HORIZONTAL, bloating);
    return bloat(rectangle, VERTICAL, bloating);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, direction_2d dir,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orientation_2d(dir));
    bloat(ivl, direction_1d(dir), bloating);
    set(rectangle, orientation_2d(dir), ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, orientation_2d orient,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, orient, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, direction_2d dir,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, dir, -shrinking);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
        typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type& rectangle, const interval_type& b, orientation_2d orient) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(encompass(ivl, b)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<
        y_r_encompass2,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type >::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    //note that operator | is intentional because both should be called regardless
    return encompass(rectangle, horizontal(b), HORIZONTAL) |
      encompass(rectangle, vertical(b), VERTICAL);
  }

  template <typename rectangle_type_1, typename point_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass3,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const point_type& b) {
    typename rectangle_interval_type<rectangle_type_1>::type hivl, vivl;
    hivl = horizontal(rectangle);
    vivl = vertical(rectangle);
    //note that operator | is intentional because both should be called regardless
    bool retval = encompass(hivl, x(b)) | encompass(vivl, y(b));
    if(retval) {
      horizontal(rectangle, hivl);
      vertical(rectangle, vivl);
    }
    return retval;
  }

  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_center, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  center(point_type& center_point, const rectangle_type& rectangle) {
    center_point = construct<point_type>(center(horizontal(rectangle)),
                                         center(vertical(rectangle)));
    return true;
  }


  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_get_corner, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  get_corner(point_type& corner_point, const rectangle_type& rectangle, direction_2d direction_facing, direction_1d direction_turning) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit u1 = get(rectangle, direction_facing);
    Unit u2 = get(rectangle, direction_facing.turn(direction_turning));
    if(orientation_2d(direction_facing).to_int()) std::swap(u1, u2);
    corner_point = construct<point_type>(u1, u2);
    return true;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_get_half, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type
  get_half(const rectangle_type& rectangle, direction_2d dir) {
    rectangle_type retval(rectangle);
    set(retval, orientation_2d(dir), get_half(get(rectangle, orientation_2d(dir)), direction_1d(dir)));
    return retval;
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_join_with, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  join_with(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typedef typename rectangle_interval_type<rectangle_type_1>::type Interval1;
    typedef typename rectangle_interval_type<rectangle_type_2>::type Interval2;
    Interval1 hi1 = get(rectangle, HORIZONTAL);
    Interval1 vi1 = get(rectangle, VERTICAL);
    Interval2 hi2 = get(b, HORIZONTAL), vi2 = get(b, VERTICAL);
    Interval1 temp;
    if (equivalence(hi1, hi2) && join_with(vi1, vi2)) {
      vertical(rectangle, vi1);
      return true;
    }
    if (equivalence(vi1, vi2) && join_with(hi1, hi2)) {
      horizontal(rectangle, hi1);
      return true;
    }
    return false;
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_eda2,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const point_type& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_eda,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_sed,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_sed2, typename is_rectangle_concept< typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept< typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_edist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    return std::sqrt((double)(square_euclidean_distance(lvalue, rvalue)));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_edist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    double val = (int)square_euclidean_distance(lvalue, rvalue);
    return std::sqrt(val);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_mdist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_mdist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_up, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_up(rectangle_type& rectangle,
           typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_up(horizontal(rectangle), factor));
    vertical(rectangle, scale_up(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_down, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_down(rectangle_type& rectangle,
             typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_down(horizontal(rectangle), factor));
    vertical(rectangle, scale_down(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type, typename scaling_type>
  typename enable_if<typename gtl_and<y_r_scale, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale(rectangle_type& rectangle, const scaling_type& scaling) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xl(rectangle), yl(rectangle));
    scale(llp, scaling);
    scale(urp, scaling);
    set_points(rectangle, llp, urp);
    return rectangle;
  }


  template <typename rectangle_type, typename transformation_type>
  typename enable_if<typename gtl_and<y_r_transform, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  transform(rectangle_type& rectangle, const transformation_type& transformation) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xh(rectangle), yh(rectangle));
    transform(llp, transformation);
    transform(urp, transformation);
    set_points(rectangle, llp, urp);
    return rectangle;
  }

    inline less_rectangle_concept(orientation_2d orient = VERTICAL) : orient_(orient) {}

    typename enable_if<
      typename gtl_and< typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
      bool>::type
    operator () (const rectangle_type_1& a,
                 const rectangle_type_2& b) const {
      typedef typename rectangle_coordinate_type<rectangle_type_1>::type Unit;
      Unit vl1 = get(get(a, orient_), LOW);
      Unit vl2 = get(get(b, orient_), LOW);
      if(vl1 > vl2) return false;
      if(vl1 == vl2) {
        orientation_2d perp = orient_.get_perpendicular();
        Unit hl1 = get(get(a, perp), LOW);
        Unit hl2 = get(get(b, perp), LOW);
        if(hl1 > hl2) return false;
        if(hl1 == hl2) {
          Unit vh1 = get(get(a, orient_), HIGH);
          Unit vh2 = get(get(b, orient_), HIGH);
          if(vh1 > vh2) return false;
          if(vh1 == vh2) {
            Unit hh1 = get(get(a, perp), HIGH);
            Unit hh2 = get(get(b, perp), HIGH);
            return hh1 < hh2;
          }
        }
      }
      return true;
    }

  template <typename interval_type_1>
  inline void rectangle_data<T>::set(orientation_2d orient, const interval_type_1& interval) {
    assign(ranges_[orient.to_int()], interval);
  }

  template <class T2>
  rectangle_data<T>& rectangle_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  bool rectangle_data<T>::operator==(const T2& rvalue) const {
    return equivalence(*this, rvalue);
  }


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_get,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
get(const Segment& segment, direction_1d dir) {
  return segment_traits<Segment>::get(segment, dir);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_set,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type set(Segment& segment, direction_1d dir, const Point& point) {
  segment_mutable_traits<Segment>::set(segment, dir, point);
}


template <typename Segment, typename Point1, typename Point2>
typename enable_if<
  typename gtl_and_4<
    y_s_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point2>::type
    >::type
  >::type,
Segment>::type construct(const Point1& low, const Point2& high) {
  return segment_mutable_traits<Segment>::construct(low, high);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_copy_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type copy_construct(const Segment2& segment) {
  return construct<Segment1>(get(segment, LOW), get(segment, HIGH));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_assign,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type& assign(Segment1& segment1, const Segment2& segment2) {
  return segment1 = copy_construct<Segment1>(segment2);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_equivalence,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type equivalence(const Segment1& segment1, const Segment2& segment2) {
  return get(segment1, LOW) == get(segment2, LOW) &&
         get(segment1, HIGH) == get(segment2, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_low,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type low(const Segment& segment) {
  return get(segment, LOW);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_high,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type high(const Segment& segment) {
  return get(segment, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_center,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
center(const Segment& segment) {
  return construct<typename segment_point_type<Segment>::type>(
      (x(high(segment)) + x(low(segment)))/2,
      (y(high(segment)) + y(low(segment)))/2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_low2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type low(Segment& segment, const Point& point) {
  set(segment, LOW, point);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_high2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type high(Segment& segment, const Point& point) {
  set(segment, HIGH, point);
}

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
int>::type orientation(const Segment1& segment1, const Segment2& segment2) {
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::manhattan_area_type int_x2;
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::unsigned_area_type uint_x2;
  int_x2 a1 = (int_x2)x(high(segment1)) - (int_x2)x(low(segment1));
  int_x2 b1 = (int_x2)y(high(segment1)) - (int_x2)y(low(segment1));
  int_x2 a2 = (int_x2)x(high(segment2)) - (int_x2)x(low(segment2));
  int_x2 b2 = (int_x2)y(high(segment2)) - (int_x2)y(low(segment2));

  int sign1 = 0;
  int sign2 = 0;
  if (a1 && b2)
    sign1 = ((a1 > 0) ^ (b2 > 0)) ? -1 : 1;
  if (a2 && b1)
    sign2 = ((a2 > 0) ^ (b1 > 0)) ? -1 : 1;

  if (sign1 != sign2)
    return (sign1 < sign2) ? -1 : 1;
  uint_x2 a3 = (uint_x2)(a1 < 0 ? -a1 : a1) * (uint_x2)(b2 < 0 ? -b2 : b2);
  uint_x2 b3 = (uint_x2)(b1 < 0 ? -b1 : b1) * (uint_x2)(a2 < 0 ? -a2 : a2);
  if (a3 == b3)
    return 0;
  return ((a3 < b3) ^ (sign1 == 1)) ? 1 : -1;
}

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation2,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
int>::type orientation(const Segment& segment, const Point& point) {
  Segment segment2 = construct<Segment>(high(segment), point);
  return orientation(segment, segment2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_contains,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
bool>::type contains(const Segment& segment,
    const Point& point, bool consider_touch = true ) {
  if (orientation(segment, point))
    return false;
  rectangle_data<typename segment_coordinate_type<Segment>::type> rect;
  set_points(rect, low(segment), high(segment));
  if (!contains(rect, point, true))
    return false;
  if (!consider_touch &&
      (equivalence(low(segment), point) ||
       equivalence(high(segment), point)))
    return false;
  return true;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_contains2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type contains(const Segment1& segment1,
    const Segment2& segment2, bool consider_touch = true) {
  return contains(segment1, get(segment2, LOW), consider_touch) &&
         contains(segment1, get(segment2, HIGH), consider_touch);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_length,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
length(const Segment& segment) {
  return euclidean_distance(low(segment), high(segment));
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_up,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_up(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_up(l, factor));
  high(segment, scale_up(h, factor));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_down,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_down(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_down(l, factor));
  high(segment, scale_down(h, factor));
  return segment;
}


template <typename Segment, typename Scale>
typename enable_if<
  typename gtl_and<
    y_s_scale,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale(Segment& segment, const Scale& sc) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale(l, sc));
  high(segment, scale(h, sc));
  return segment;
}


template <typename Segment, typename Transform>
typename enable_if<
  typename gtl_and<
    y_s_transform,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& transform(Segment& segment, const Transform& tr) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, transform(l, tr));
  high(segment, transform(h, tr));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_move,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& move(Segment& segment, orientation_2d orient,
    typename segment_coordinate_type<Segment>::type displacement) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, move(l, orient, displacement));
  high(segment, move(h, orient, displacement));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_convolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& convolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, convolve(l, point));
  high(segment, convolve(h, point));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_deconvolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& deconvolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, deconvolve(l, point));
  high(segment, deconvolve(h, point));
  return segment;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1,
    const Segment2& segment2, direction_1d dir) {
  return dir.to_int() ? equivalence(low(segment2) , high(segment1)) :
                        equivalence(low(segment1) , high(segment2));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1, const Segment2& segment2) {
  return abuts(segment1, segment2, HIGH) || abuts(segment1, segment2, LOW);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_intersects,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool
>::type intersects(const Segment1& segment1, const Segment2& segment2,
    bool consider_touch = true) {
  rectangle_data<typename segment_coordinate_type<Segment1>::type> rect1, rect2;
  set_points(rect1, low(segment1), high(segment1));
  set_points(rect2, low(segment2), high(segment2));
  // Check if axis-parallel rectangles containing segments intersect.
  if (!intersects(rect1, rect2, true))
    return false;
  int or1_1 = orientation(segment1, low(segment2));
  int or1_2 = orientation(segment1, high(segment2));
  if (or1_1 * or1_2 > 0)
    return false;
  int or2_1 = orientation(segment2, low(segment1));
  int or2_2 = orientation(segment2, high(segment1));
  if (or2_1 * or2_2 > 0)
    return false;
  if (consider_touch || (or1_1 && or1_2) || (or2_1 && or2_2))
    return true;
  if (or1_1 || or1_2)
    return false;
  return intersects(vertical(rect1), vertical(rect2), false) ||
         intersects(horizontal(rect1), horizontal(rect2), false);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
euclidean_distance(const Segment& segment, const Point& point) {
  typedef typename segment_distance_type<Segment>::type Unit;
  Unit x1 = x(low(segment));
  Unit y1 = y(low(segment));
  Unit x2 = x(high(segment));
  Unit y2 = y(high(segment));
  Unit X = x(point);
  Unit Y = y(point);
  Unit A = X - x1;
  Unit B = Y - y1;
  Unit C = x2 - x1;
  Unit D = y2 - y1;
  Unit param = (A * C + B * D);
  Unit length_sq = C * C + D * D;
  if (param > length_sq) {
    return euclidean_distance(high(segment), point);
  } else if (param < 0.0) {
    return euclidean_distance(low(segment), point);
  }
  if (length_sq == 0.0)
    return 0.0;
  Unit denom = std::sqrt(length_sq);
  Unit result = (A * D - C * B) / denom;
  return (result < 0.0) ? -result : result;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
typename segment_distance_type<Segment1>::type>::type
euclidean_distance(const Segment1& segment1, const Segment2& segment2) {
  if (intersects(segment1, segment2))
    return 0.0;
  typename segment_distance_type<Segment1>::type
      result1 = euclidean_distance(segment1, low(segment2)),
      result2 = euclidean_distance(segment1, high(segment2)),
      result3 = euclidean_distance(segment2, low(segment1)),
      result4 = euclidean_distance(segment2, high(segment1));
  if (result2 < result1)
    result1 = result2;
  if (result4 < result3)
    result3 = result4;
  return (result1 < result3) ? result1 : result3;
}


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  axis_transformation() : atr_(NULL_TRANSFORM) {}

  explicit axis_transformation(ATR atr) : atr_(atr) {}

  axis_transformation(const axis_transformation& atr) : atr_(atr.atr_) {}


  explicit axis_transformation(const orientation_2d& orient) {
    const ATR tmp[2] = {
      NORTH_EAST,  // sort x, then y
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[orient.to_int()];
  }


  explicit axis_transformation(const direction_2d& dir) {
    const ATR tmp[4] = {
      SOUTH_EAST,  // sort x, then y
      NORTH_EAST,  // sort x, then y
      EAST_SOUTH,  // sort y, then x
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[dir.to_int()];
  }

  axis_transformation& operator=(const axis_transformation& a) {
    atr_ = a.atr_;
    return *this;
  }

  axis_transformation& operator=(const ATR& atr) {
    atr_ = atr;
    return *this;
  }

  bool operator==(const axis_transformation& a) const {
    return atr_ == a.atr_;
  }

  bool operator!=(const axis_transformation& a) const {
    return !(*this == a);
  }

  bool operator<(const axis_transformation& a) const {
    return atr_ < a.atr_;
  }

  axis_transformation& operator+=(const axis_transformation& a) {
    bool abit2 = (a.atr_ & 4) != 0;
    bool abit1 = (a.atr_ & 2) != 0;
    bool abit0 = (a.atr_ & 1) != 0;
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    int indexes[2][2] = {
      { (int)bit2, (int)(!bit2) },
      { (int)abit2, (int)(!abit2) }
    };
    int zero_bits[2][2] = {
      {bit0, bit1}, {abit0, abit1}
    };
    int nbit1 = zero_bits[0][1] ^ zero_bits[1][indexes[0][1]];
    int nbit0 = zero_bits[0][0] ^ zero_bits[1][indexes[0][0]];
    indexes[0][0] = indexes[1][indexes[0][0]];
    indexes[0][1] = indexes[1][indexes[0][1]];
    int nbit2 = indexes[0][0] & 1;  // swap xy
    atr_ = (ATR)((nbit2 << 2) + (nbit1 << 1) + nbit0);
    return *this;
  }

  axis_transformation operator+(const axis_transformation& a) const {
    axis_transformation retval(*this);
    return retval+=a;
  }

  void populate_axis_array(INDIVIDUAL_AXIS axis_array[]) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    axis_array[1] = (INDIVIDUAL_AXIS)(((int)(!bit2) << 1) + bit1);
    axis_array[0] = (INDIVIDUAL_AXIS)(((int)(bit2) << 1) + bit0);
  }

  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    vertical_dir = direction_2d((direction_2d_enum)(((int)(!bit2) << 1) + !bit1));
    horizontal_dir = direction_2d((direction_2d_enum)(((int)(bit2) << 1) + !bit0));
  }

  static void combine_axis_arrays(INDIVIDUAL_AXIS this_array[],
                                  const INDIVIDUAL_AXIS that_array[]) {
    int indexes[2] = { this_array[0] >> 1, this_array[1] >> 1 };
    int zero_bits[2][2] = {
      { this_array[0] & 1, this_array[1] & 1 },
      { that_array[0] & 1, that_array[1] & 1 }
    };
    this_array[0] = (INDIVIDUAL_AXIS)((int)this_array[0] |
                                      ((int)zero_bits[0][0] ^
                                       (int)zero_bits[1][indexes[0]]));
    this_array[1] = (INDIVIDUAL_AXIS)((int)this_array[1] |
                                      ((int)zero_bits[0][1] ^
                                       (int)zero_bits[1][indexes[1]]));
  }

  void write_back_axis_array(const INDIVIDUAL_AXIS this_array[]) {
    int bit2 = ((int)this_array[0] & 2) != 0;  // swap xy
    int bit1 = ((int)this_array[1] & 1);
    int bit0 = ((int)this_array[0] & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
  }

  axis_transformation& set_directions(const direction_2d& horizontal_dir,
                                      const direction_2d& vertical_dir) {
    int bit2 = (static_cast<orientation_2d>(horizontal_dir).to_int()) != 0;
    int bit1 = !(vertical_dir.to_int() & 1);
    int bit0 = !(horizontal_dir.to_int() & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
    return *this;
  }

  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y) const {
    int bit2 = (atr_ & 4) != 0;
    int bit1 = (atr_ & 2) != 0;
    int bit0 = (atr_ & 1) != 0;
    x *= -((bit0 << 1) - 1);
    y *= -((bit1 << 1) - 1);
    predicated_swap(bit2 != 0, x, y);
  }

  axis_transformation& invert() {
    int bit2 = ((atr_ & 4) != 0);
    int bit1 = ((atr_ & 2) != 0);
    int bit0 = ((atr_ & 1) != 0);
    // swap bit 0 and bit 1 if bit2 is 1
    predicated_swap(bit2 != 0, bit0, bit1);
    bit1 = bit1 << 1;
    atr_ = (ATR)(atr_ & (32+16+8+4));  // mask away bit0 and bit1
    atr_ = (ATR)(atr_ | bit0 | bit1);
    return *this;
  }

  axis_transformation inverse() const {
    axis_transformation retval(*this);
    return retval.invert();
  }

  anisotropic_scale_factor() {
    scale_[0] = 1;
    scale_[1] = 1;
  }

  anisotropic_scale_factor(scale_factor_type xscale,
                           scale_factor_type yscale) {
    scale_[0] = xscale;
    scale_[1] = yscale;
  }

  scale_factor_type get(orientation_2d orient) const {
    return scale_[orient.to_int()];
  }

  void set(orientation_2d orient, scale_factor_type value) {
    scale_[orient.to_int()] = value;
  }


  scale_factor_type x() const {
    return scale_[HORIZONTAL];
  }


  scale_factor_type y() const {
    return scale_[VERTICAL];
  }


  void x(scale_factor_type value) {
    scale_[HORIZONTAL] = value;
  }


  void y(scale_factor_type value) {
    scale_[VERTICAL] = value;
  }

  anisotropic_scale_factor operator+(const anisotropic_scale_factor& s) const {
    anisotropic_scale_factor<scale_factor_type> retval(*this);
    return retval += s;
  }

  const anisotropic_scale_factor& operator+=(
      const anisotropic_scale_factor& s) {
    scale_[0] *= s.scale_[0];
    scale_[1] *= s.scale_[1];
    return *this;
  }

  anisotropic_scale_factor& transform(axis_transformation atr) {
    direction_2d dirs[2];
    atr.get_directions(dirs[0], dirs[1]);
    scale_factor_type tmp[2] = {scale_[0], scale_[1]};
    for (int i = 0; i < 2; ++i) {
      scale_[orientation_2d(dirs[i]).to_int()] = tmp[i];
    }
    return *this;
  }

  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y) const {
    x = scaling_policy<coordinate_type>::round(
        (scale_factor_type)x * get(HORIZONTAL));
    y = scaling_policy<coordinate_type>::round(
        (scale_factor_type)y * get(HORIZONTAL));
  }

  anisotropic_scale_factor& invert() {
    x(1/x());
    y(1/y());
    return *this;
  }

  transformation() : atr_(), p_(0, 0) {}

  explicit transformation(axis_transformation atr) : atr_(atr), p_(0, 0) {}

  explicit transformation(axis_transformation::ATR atr) : atr_(atr), p_(0, 0) {}

  transformation(const transformation& tr) : atr_(tr.atr_), p_(tr.p_) {}


  template <typename point_type>
  explicit transformation(const point_type& p) : atr_(), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& p) : atr_(atr), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& referencePt,
                 const point_type& destinationPt) : atr_(), p_(0, 0) {
    transformation<coordinate_type> tmp(referencePt);
    transformation<coordinate_type> rotRef(atr);
    transformation<coordinate_type> tmpInverse = tmp.inverse();
    point_type decon(referencePt);
    deconvolve(decon, destinationPt);
    transformation<coordinate_type> displacement(decon);
    tmp += rotRef;
    tmp += tmpInverse;
    tmp += displacement;
    (*this) = tmp;
  }

  bool operator==(const transformation& tr) const {
    return (atr_ == tr.atr_) && (p_ == tr.p_);
  }

  bool operator!=(const transformation& tr) const {
    return !(*this == tr);
  }

  bool operator<(const transformation& tr) const {
    return (atr_ < tr.atr_) || ((atr_ == tr.atr_) && (p_ < tr.p_));
  }

  transformation operator+(const transformation& tr) const {
    transformation<coordinate_type> retval(*this);
    return retval+=tr;
  }

  const transformation& operator+=(const transformation& tr) {
    coordinate_type x, y;
    transformation<coordinate_type> inv = inverse();
    inv.transform(x, y);
    p_.set(HORIZONTAL, p_.get(HORIZONTAL) + x);
    p_.set(VERTICAL, p_.get(VERTICAL) + y);
    // concatenate axis transforms
    atr_ += tr.atr_;
    return *this;
  }

  axis_transformation get_axis_transformation() const {
    return atr_;
  }

  void set_axis_transformation(const axis_transformation& atr) {
    atr_ = atr;
  }

  template <typename point_type>
  void get_translation(point_type& p) const {
    assign(p, p_);
  }

  template <typename point_type>
  void set_translation(const point_type& p) {
    assign(p_, p);
  }

  void transform(coordinate_type& x, coordinate_type& y) const {
    y -= p_.get(VERTICAL);
    x -= p_.get(HORIZONTAL);
    atr_.transform(x, y);
  }

  transformation& invert() {
    coordinate_type x = p_.get(HORIZONTAL), y = p_.get(VERTICAL);
    atr_.transform(x, y);
    x *= -1;
    y *= -1;
    p_ = point_data<coordinate_type>(x, y);
    atr_.invert();
    return *this;
  }

  transformation inverse() const {
    transformation<coordinate_type> ret_val(*this);
    return ret_val.invert();
  }


  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    return atr_.get_directions(horizontal_dir, vertical_dir);
  }


  Result operator()(fpt64 a, fpt64 b, unsigned int maxUlps) const {
    uint64 ll_a, ll_b;

    // Reinterpret double bits as 64-bit signed integer.
    std::memcpy(&ll_a, &a, sizeof(fpt64));
    std::memcpy(&ll_b, &b, sizeof(fpt64));

    // Positive 0.0 is integer zero. Negative 0.0 is 0x8000000000000000.
    // Map negative zero to an integer zero representation - making it
    // identical to positive zero - the smallest negative number is
    // represented by negative one, and downwards from there.
    if (ll_a < 0x8000000000000000ULL)
      ll_a = 0x8000000000000000ULL - ll_a;
    if (ll_b < 0x8000000000000000ULL)
      ll_b = 0x8000000000000000ULL - ll_b;

    // Compare 64-bit signed integer representations of input values.
    // Difference in 1 Ulp is equivalent to a relative error of between
    // 1/4,000,000,000,000,000 and 1/8,000,000,000,000,000.
    if (ll_a > ll_b)
      return (ll_a - ll_b <= maxUlps) ? EQUAL : LESS;
    return (ll_b - ll_a <= maxUlps) ? EQUAL : MORE;
  }


  explicit extended_exponent_fpt(fpt_type val) {
    val_ = std::frexp(val, &exp_);
  }


  extended_exponent_fpt(fpt_type val, exp_type exp) {
    val_ = std::frexp(val, &exp_);
    exp_ += exp;
  }


  bool is_pos() const {
    return val_ > 0;
  }


  bool is_neg() const {
    return val_ < 0;
  }


  bool is_zero() const {
    return val_ == 0;
  }


  extended_exponent_fpt operator-() const {
    return extended_exponent_fpt(-val_, exp_);
  }


  extended_exponent_fpt operator+(const extended_exponent_fpt& that) const {
    if (this->val_ == 0.0 ||
        that.exp_ > this->exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return that;
    }
    if (that.val_ == 0.0 ||
        this->exp_ > that.exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return *this;
    }
    if (this->exp_ >= that.exp_) {
      exp_type exp_dif = this->exp_ - that.exp_;
      fpt_type val = std::ldexp(this->val_, exp_dif) + that.val_;
      return extended_exponent_fpt(val, that.exp_);
    } else {
      exp_type exp_dif = that.exp_ - this->exp_;
      fpt_type val = std::ldexp(that.val_, exp_dif) + this->val_;
      return extended_exponent_fpt(val, this->exp_);
    }
  }


  extended_exponent_fpt operator-(const extended_exponent_fpt& that) const {
    if (this->val_ == 0.0 ||
        that.exp_ > this->exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return extended_exponent_fpt(-that.val_, that.exp_);
    }
    if (that.val_ == 0.0 ||
        this->exp_ > that.exp_ + _traits::MAX_SIGNIFICANT_EXP_DIF) {
      return *this;
    }
    if (this->exp_ >= that.exp_) {
      exp_type exp_dif = this->exp_ - that.exp_;
      fpt_type val = std::ldexp(this->val_, exp_dif) - that.val_;
      return extended_exponent_fpt(val, that.exp_);
    } else {
      exp_type exp_dif = that.exp_ - this->exp_;
      fpt_type val = std::ldexp(-that.val_, exp_dif) + this->val_;
      return extended_exponent_fpt(val, this->exp_);
    }
  }


  extended_exponent_fpt operator*(const extended_exponent_fpt& that) const {
    fpt_type val = this->val_ * that.val_;
    exp_type exp = this->exp_ + that.exp_;
    return extended_exponent_fpt(val, exp);
  }


  extended_exponent_fpt operator/(const extended_exponent_fpt& that) const {
    fpt_type val = this->val_ / that.val_;
    exp_type exp = this->exp_ - that.exp_;
    return extended_exponent_fpt(val, exp);
  }


  extended_exponent_fpt& operator+=(const extended_exponent_fpt& that) {
    return *this = *this + that;
  }


  extended_exponent_fpt& operator-=(const extended_exponent_fpt& that) {
    return *this = *this - that;
  }


  extended_exponent_fpt& operator*=(const extended_exponent_fpt& that) {
    return *this = *this * that;
  }


  extended_exponent_fpt& operator/=(const extended_exponent_fpt& that) {
    return *this = *this / that;
  }


  extended_exponent_fpt sqrt() const {
    fpt_type val = val_;
    exp_type exp = exp_;
    if (exp & 1) {
      val *= 2.0;
      --exp;
    }
    return extended_exponent_fpt(std::sqrt(val), exp >> 1);
  }


  fpt_type d() const {
    return std::ldexp(val_, exp_);
  }


template <typename _fpt>
extended_exponent_fpt<_fpt> get_sqrt(const extended_exponent_fpt<_fpt>& that) {
  return that.sqrt();
}


template <typename _fpt>
bool is_pos(const extended_exponent_fpt<_fpt>& that) {
  return that.is_pos();
}


template <typename _fpt>
bool is_neg(const extended_exponent_fpt<_fpt>& that) {
  return that.is_neg();
}


template <typename _fpt>
bool is_zero(const extended_exponent_fpt<_fpt>& that) {
  return that.is_zero();
}

  extended_int() {}


  extended_int(int32 that) {
    if (that > 0) {
      this->chunks_[0] = that;
      this->count_ = 1;
    } else if (that < 0) {
      this->chunks_[0] = -that;
      this->count_ = -1;
    } else {
      this->count_ = 0;
    }
  }


  template<std::size_t M>
  extended_int(const extended_int<M>& that) {
    this->count_ = that.count();
    std::memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
  }


  extended_int& operator=(int32 that) {
    if (that > 0) {
      this->chunks_[0] = that;
      this->count_ = 1;
    } else if (that < 0) {
      this->chunks_[0] = -that;
      this->count_ = -1;
    } else {
      this->count_ = 0;
    }
    return *this;
  }


  template<std::size_t M>
  extended_int& operator=(const extended_int<M>& that) {
    this->count_ = that.count();
    std::memcpy(this->chunks_, that.chunks(), that.size() * sizeof(uint32));
    return *this;
  }


  bool is_pos() const {
    return this->count_ > 0;
  }


  bool is_neg() const {
    return this->count_ < 0;
  }


  bool is_zero() const {
    return this->count_ == 0;
  }


  bool operator==(const extended_int& that) const {
    if (this->count_ != that.count())
      return false;
    for (std::size_t i = 0; i < this->size(); ++i)
      if (this->chunks_[i] != that.chunks()[i])
        return false;
    return true;
  }


  bool operator!=(const extended_int& that) const {
    return !(*this == that);
  }


  bool operator<(const extended_int& that) const {
    if (this->count_ != that.count())
      return this->count_ < that.count();
    std::size_t i = this->size();
    if (!i)
      return false;
    do {
      --i;
      if (this->chunks_[i] != that.chunks()[i])
        return (this->chunks_[i] < that.chunks()[i]) ^ (this->count_ < 0);
    } while (i);
    return false;
  }


  bool operator>(const extended_int& that) const {
    return that < *this;
  }


  bool operator<=(const extended_int& that) const {
    return !(that < *this);
  }


  bool operator>=(const extended_int& that) const {
    return !(*this < that);
  }


  extended_int operator-() const {
    extended_int ret_val = *this;
    ret_val.neg();
    return ret_val;
  }


  void neg() {
    this->count_ = -this->count_;
  }


  extended_int operator+(const extended_int& that) const {
    extended_int ret_val;
    ret_val.add(*this, that);
    return ret_val;
  }


  void add(const extended_int& e1, const extended_int& e2) {
    if (!e1.count()) {
      *this = e2;
      return;
    }
    if (!e2.count()) {
      *this = e1;
      return;
    }
    if ((e1.count() > 0) ^ (e2.count() > 0)) {
      dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    } else {
      add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    }
    if (e1.count() < 0)
      this->count_ = -this->count_;
  }


  extended_int operator-(const extended_int& that) const {
    extended_int ret_val;
    ret_val.dif(*this, that);
    return ret_val;
  }


  void dif(const extended_int& e1, const extended_int& e2) {
    if (!e1.count()) {
      *this = e2;
      this->count_ = -this->count_;
      return;
    }
    if (!e2.count()) {
      *this = e1;
      return;
    }
    if ((e1.count() > 0) ^ (e2.count() > 0)) {
      add(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    } else {
      dif(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    }
    if (e1.count() < 0)
      this->count_ = -this->count_;
  }


  extended_int operator*(int32 that) const {
    extended_int temp(that);
    return (*this) * temp;
  }


  extended_int operator*(const extended_int& that) const {
    extended_int ret_val;
    ret_val.mul(*this, that);
    return ret_val;
  }


  void mul(const extended_int& e1, const extended_int& e2) {
    if (!e1.count() || !e2.count()) {
      this->count_ = 0;
      return;
    }
    mul(e1.chunks(), e1.size(), e2.chunks(), e2.size());
    if ((e1.count() > 0) ^ (e2.count() > 0))
      this->count_ = -this->count_;
  }


  const uint32* chunks() const {
    return chunks_;
  }


  int32 count() const {
    return count_;
  }


  std::size_t size() const {
    return (std::abs)(count_);
  }


template <std::size_t N>
bool is_pos(const extended_int<N>& that) {
  return that.count() > 0;
}


template <std::size_t N>
bool is_neg(const extended_int<N>& that) {
  return that.count() < 0;
}


template <std::size_t N>
bool is_zero(const extended_int<N>& that) {
  return !that.count();
}

  template <typename T>
  fpt64 operator()(const T& that) const {
    return static_cast<fpt64>(that);
  }


  template <std::size_t N>
  fpt64 operator()(const extended_int<N>& that) const {
    return that.d();
  }

  template <std::size_t N>
  extended_exponent_fpt<fpt64> operator()(const extended_int<N>& that) const {
    std::pair<fpt64, int> p = that.p();
    return extended_exponent_fpt<fpt64>(p.first, p.second);
  }


template <typename T>
T get_sqrt(const T& that) {
  return (std::sqrt)(that);
}


template <typename T>
bool is_pos(const T& that) {
  return that > 0;
}


template <typename T>
bool is_neg(const T& that) {
  return that < 0;
}


template <typename T>
bool is_zero(const T& that) {
  return that == 0;
}


  robust_fpt() : fpv_(0.0), re_(0.0) {}

  explicit robust_fpt(floating_point_type fpv) :
      fpv_(fpv), re_(0.0) {}

  robust_fpt(floating_point_type fpv, relative_error_type error) :
      fpv_(fpv), re_(error) {}


  floating_point_type fpv() const { return fpv_; }

  relative_error_type re() const { return re_; }

  relative_error_type ulp() const { return re_; }


  robust_fpt& operator=(const robust_fpt& that) {
    this->fpv_ = that.fpv_;
    this->re_ = that.re_;
    return *this;
  }


  bool has_pos_value() const {
    return is_pos(fpv_);
  }


  bool has_neg_value() const {
    return is_neg(fpv_);
  }


  bool has_zero_value() const {
    return is_zero(fpv_);
  }


  robust_fpt operator-() const {
    return robust_fpt(-fpv_, re_);
  }


  robust_fpt& operator+=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }


  robust_fpt& operator-=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
       this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
         temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }


  robust_fpt& operator*=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ *= that.fpv_;
    return *this;
  }


  robust_fpt& operator/=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ /= that.fpv_;
    return *this;
  }


  robust_fpt operator+(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }


  robust_fpt operator-(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }


  robust_fpt operator*(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ * that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }


  robust_fpt operator/(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ / that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }


  robust_fpt sqrt() const {
    return robust_fpt(get_sqrt(fpv_),
                      re_ * static_cast<relative_error_type>(0.5) +
                      ROUNDING_ERROR);
  }


template <typename T>
robust_fpt<T> get_sqrt(const robust_fpt<T>& that) {
  return that.sqrt();
}


template <typename T>
bool is_pos(const robust_fpt<T>& that) {
  return that.has_pos_value();
}


template <typename T>
bool is_neg(const robust_fpt<T>& that) {
  return that.has_neg_value();
}


template <typename T>
bool is_zero(const robust_fpt<T>& that) {
  return that.has_zero_value();
}

  robust_dif() :
      positive_sum_(0),
      negative_sum_(0) {}


  explicit robust_dif(const T& value) :
      positive_sum_((value > 0)?value:0),
      negative_sum_((value < 0)?-value:0) {}


  robust_dif(const T& pos, const T& neg) :
      positive_sum_(pos),
      negative_sum_(neg) {}


  T dif() const {
    return positive_sum_ - negative_sum_;
  }


  T pos() const {
    return positive_sum_;
  }


  T neg() const {
    return negative_sum_;
  }


  robust_dif<T> operator-() const {
    return robust_dif(negative_sum_, positive_sum_);
  }


  robust_dif<T>& operator+=(const T& val) {
    if (!is_neg(val))
      positive_sum_ += val;
    else
      negative_sum_ -= val;
    return *this;
  }


  robust_dif<T>& operator+=(const robust_dif<T>& that) {
    positive_sum_ += that.positive_sum_;
    negative_sum_ += that.negative_sum_;
    return *this;
  }


  robust_dif<T>& operator-=(const T& val) {
    if (!is_neg(val))
      negative_sum_ += val;
    else
      positive_sum_ -= val;
    return *this;
  }


  robust_dif<T>& operator-=(const robust_dif<T>& that) {
    positive_sum_ += that.negative_sum_;
    negative_sum_ += that.positive_sum_;
    return *this;
  }


  robust_dif<T>& operator*=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ *= val;
      negative_sum_ *= val;
    } else {
      positive_sum_ *= -val;
      negative_sum_ *= -val;
      swap();
    }
    return *this;
  }


  robust_dif<T>& operator*=(const robust_dif<T>& that) {
    T positive_sum = this->positive_sum_ * that.positive_sum_ +
                     this->negative_sum_ * that.negative_sum_;
    T negative_sum = this->positive_sum_ * that.negative_sum_ +
                     this->negative_sum_ * that.positive_sum_;
    positive_sum_ = positive_sum;
    negative_sum_ = negative_sum;
    return *this;
  }


  robust_dif<T>& operator/=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ /= val;
      negative_sum_ /= val;
    } else {
      positive_sum_ /= -val;
      negative_sum_ /= -val;
      swap();
    }
    return *this;
  }

  void swap() {
    (std::swap)(positive_sum_, negative_sum_);
  }


template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.pos(), lhs.neg() + rhs.neg());
}


template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
  } else {
    return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
  }
}


template<typename T>
robust_dif<T> operator+(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.pos(), rhs.neg());
  } else {
    return robust_dif<T>(rhs.pos(), rhs.neg() - lhs);
  }
}


template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.neg(), lhs.neg() + rhs.pos());
}


template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
  } else {
    return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
  }
}


template<typename T>
robust_dif<T> operator-(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.neg(), rhs.pos());
  } else {
    return robust_dif<T>(rhs.neg(), rhs.pos() - lhs);
  }
}


template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  T res_pos = lhs.pos() * rhs.pos() + lhs.neg() * rhs.neg();
  T res_neg = lhs.pos() * rhs.neg() + lhs.neg() * rhs.pos();
  return robust_dif<T>(res_pos, res_neg);
}


template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
  } else {
    return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
  }
}


template<typename T>
robust_dif<T> operator*(const T& val, const robust_dif<T>& rhs) {
  if (!is_neg(val)) {
    return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
  } else {
    return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
  }
}


template<typename T>
robust_dif<T> operator/(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
  } else {
    return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
  }
}

  _fpt eval1(_int* A, _int* B) {
    _fpt a = convert(A[0]);
    _fpt b = convert(B[0]);
    return a * get_sqrt(b);
  }

  _fpt eval2(_int* A, _int* B) {
    _fpt a = eval1(A, B);
    _fpt b = eval1(A + 1, B + 1);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    return convert(A[0] * A[0] * B[0] - A[1] * A[1] * B[1]) / (a - b);
  }

  _fpt eval3(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval1(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[3] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] - A[2] * A[2] * B[2];
    tB[3] = 1;
    tA[4] = A[0] * A[1] * 2;
    tB[4] = B[0] * B[1];
    return eval2(tA + 3, tB + 3) / (a - b);
  }

  _fpt eval4(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval2(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
            A[2] * A[2] * B[2] - A[3] * A[3] * B[3];
    tB[0] = 1;
    tA[1] = A[0] * A[1] * 2;
    tB[1] = B[0] * B[1];
    tA[2] = A[2] * A[3] * -2;
    tB[2] = B[2] * B[3];
    return eval3(tA, tB) / (a - b);
  }


  template <typename Point>
  static bool is_vertical(const Point& point1, const Point& point2) {
    return point1.x() == point2.x();
  }


  template <typename Site>
  static bool is_vertical(const Site& site) {
    return is_vertical(site.point0(), site.point1());
  }

  static fpt_type robust_cross_product(int_x2_type a1_,
                                       int_x2_type b1_,
                                       int_x2_type a2_,
                                       int_x2_type b2_) {
    static to_fpt_converter to_fpt;
    uint_x2_type a1 = static_cast<uint_x2_type>(is_neg(a1_) ? -a1_ : a1_);
    uint_x2_type b1 = static_cast<uint_x2_type>(is_neg(b1_) ? -b1_ : b1_);
    uint_x2_type a2 = static_cast<uint_x2_type>(is_neg(a2_) ? -a2_ : a2_);
    uint_x2_type b2 = static_cast<uint_x2_type>(is_neg(b2_) ? -b2_ : b2_);

    uint_x2_type l = a1 * b2;
    uint_x2_type r = b1 * a2;

    if (is_neg(a1_) ^ is_neg(b2_)) {
      if (is_neg(a2_) ^ is_neg(b1_))
        return (l > r) ? -to_fpt(l - r) : to_fpt(r - l);
      else
        return -to_fpt(l + r);
    } else {
      if (is_neg(a2_) ^ is_neg(b1_))
        return to_fpt(l + r);
      else
        return (l < r) ? -to_fpt(r - l) : to_fpt(l - r);
    }
  }

    template <typename T>
    static Orientation eval(T value) {
      if (is_zero(value)) return COLLINEAR;
      return (is_neg(value)) ? RIGHT : LEFT;
    }


    static Orientation eval(int_x2_type dif_x1_,
                            int_x2_type dif_y1_,
                            int_x2_type dif_x2_,
                            int_x2_type dif_y2_) {
      return eval(robust_cross_product(dif_x1_, dif_y1_, dif_x2_, dif_y2_));
    }


    template <typename Point>
    static Orientation eval(const Point& point1,
                            const Point& point2,
                            const Point& point3) {
      int_x2_type dx1 = static_cast<int_x2_type>(point1.x()) -
                        static_cast<int_x2_type>(point2.x());
      int_x2_type dx2 = static_cast<int_x2_type>(point2.x()) -
                        static_cast<int_x2_type>(point3.x());
      int_x2_type dy1 = static_cast<int_x2_type>(point1.y()) -
                        static_cast<int_x2_type>(point2.y());
      int_x2_type dy2 = static_cast<int_x2_type>(point2.y()) -
                        static_cast<int_x2_type>(point3.y());
      return eval(robust_cross_product(dx1, dy1, dx2, dy2));
    }

    template <typename T>
    static Orientation eval(T value) {
      if (is_zero(value)) return COLLINEAR;
      return (is_neg(value)) ? RIGHT : LEFT;
    }


    static Orientation eval(int_x2_type dif_x1_,
                            int_x2_type dif_y1_,
                            int_x2_type dif_x2_,
                            int_x2_type dif_y2_) {
      return eval(robust_cross_product(dif_x1_, dif_y1_, dif_x2_, dif_y2_));
    }


    template <typename Point>
    static Orientation eval(const Point& point1,
                            const Point& point2,
                            const Point& point3) {
      int_x2_type dx1 = static_cast<int_x2_type>(point1.x()) -
                        static_cast<int_x2_type>(point2.x());
      int_x2_type dx2 = static_cast<int_x2_type>(point2.x()) -
                        static_cast<int_x2_type>(point3.x());
      int_x2_type dy1 = static_cast<int_x2_type>(point1.y()) -
                        static_cast<int_x2_type>(point2.y());
      int_x2_type dy2 = static_cast<int_x2_type>(point2.y()) -
                        static_cast<int_x2_type>(point3.y());
      return eval(robust_cross_product(dx1, dy1, dx2, dy2));
    }


    bool operator()(const point_type& lhs, const point_type& rhs) const {
      if (lhs.x() == rhs.x())
        return lhs.y() < rhs.y();
      return lhs.x() < rhs.x();
    }


    bool operator()(const site_type& lhs, const site_type& rhs) const {
      if (lhs.x0() != rhs.x0())
        return lhs.x0() < rhs.x0();
      if (!lhs.is_segment()) {
        if (!rhs.is_segment())
          return lhs.y0() < rhs.y0();
        if (is_vertical(rhs))
          return lhs.y0() <= rhs.y0();
        return true;
      } else {
        if (is_vertical(rhs)) {
          if (is_vertical(lhs))
            return lhs.y0() < rhs.y0();
          return false;
        }
        if (is_vertical(lhs))
          return true;
        if (lhs.y0() != rhs.y0())
          return lhs.y0() < rhs.y0();
        return ot::eval(lhs.point1(), lhs.point0(), rhs.point1()) == ot::LEFT;
      }
    }


    bool operator()(const site_type& lhs, const circle_type& rhs) const {
      typename ulp_cmp_type::Result xCmp =
          ulp_cmp(to_fpt(lhs.x()), to_fpt(rhs.lower_x()), ULPSx5);
      if (xCmp != ulp_cmp_type::EQUAL)
        return xCmp == ulp_cmp_type::LESS;
      typename ulp_cmp_type::Result yCmp =
          ulp_cmp(to_fpt(lhs.y()), to_fpt(rhs.lower_y()), ULPSx5);
      return yCmp == ulp_cmp_type::LESS;
    }


    bool operator()(const circle_type& lhs, const site_type& rhs) const {
      typename ulp_cmp_type::Result xCmp =
          ulp_cmp(to_fpt(lhs.lower_x()), to_fpt(rhs.x()), ULPSx5);
      if (xCmp != ulp_cmp_type::EQUAL)
        return xCmp == ulp_cmp_type::LESS;
      typename ulp_cmp_type::Result yCmp =
          ulp_cmp(to_fpt(lhs.lower_y()), to_fpt(rhs.y()), ULPSx5);
      return yCmp == ulp_cmp_type::LESS;
    }


    bool operator()(const circle_type& lhs, const circle_type& rhs) const {
      typename ulp_cmp_type::Result xCmp =
          ulp_cmp(to_fpt(lhs.lower_x()), to_fpt(rhs.lower_x()), ULPSx2);
      if (xCmp != ulp_cmp_type::EQUAL)
        return xCmp == ulp_cmp_type::LESS;
      typename ulp_cmp_type::Result yCmp =
          ulp_cmp(to_fpt(lhs.lower_y()), to_fpt(rhs.lower_y()), ULPSx2);
      return yCmp == ulp_cmp_type::LESS;
    }

    bool operator()(const site_type& left_site,
                    const site_type& right_site,
                    const site_type& new_site) const {
      if (!left_site.is_segment()) {
        if (!right_site.is_segment()) {
          return pp(left_site, right_site, new_site);
        } else {
          return ps(left_site, right_site, new_site, false);
        }
      } else {
        if (!right_site.is_segment()) {
          return ps(right_site, left_site, new_site, true);
        } else {
          return ss(left_site, right_site, new_site);
        }
      }
    }

    bool pp(const site_type& left_site,
            const site_type& right_site,
            const site_type& new_site) const {
      const point_type& left_point = left_site.point0();
      const point_type& right_point = right_site.point0();
      const point_type& new_point = new_site.point0();
      if (left_point.x() > right_point.x()) {
        if (new_point.y() <= left_point.y())
          return false;
      } else if (left_point.x() < right_point.x()) {
        if (new_point.y() >= right_point.y())
          return true;
      } else {
        return static_cast<int_x2_type>(left_point.y()) +
               static_cast<int_x2_type>(right_point.y()) <
               static_cast<int_x2_type>(new_point.y()) * 2;
      }

      fpt_type dist1 = find_distance_to_point_arc(left_site, new_point);
      fpt_type dist2 = find_distance_to_point_arc(right_site, new_point);

      // The undefined ulp range is equal to 3EPS + 3EPS <= 6ULP.
      return dist1 < dist2;
    }


    bool ps(const site_type& left_site, const site_type& right_site,
            const site_type& new_site, bool reverse_order) const {
      kPredicateResult fast_res = fast_ps(
        left_site, right_site, new_site, reverse_order);
      if (fast_res != UNDEFINED)
        return (fast_res == LESS);

      fpt_type dist1 = find_distance_to_point_arc(
          left_site, new_site.point0());
      fpt_type dist2 = find_distance_to_segment_arc(
          right_site, new_site.point0());

      // The undefined ulp range is equal to 3EPS + 7EPS <= 10ULP.
      return reverse_order ^ (dist1 < dist2);
    }


    bool ss(const site_type& left_site,
            const site_type& right_site,
            const site_type& new_site) const {
      // Handle temporary segment sites.
      if (left_site.point0() == right_site.point0() &&
          left_site.point1() == right_site.point1()) {
        return ot::eval(left_site.point0(),
                        left_site.point1(),
                        new_site.point0()) == ot::LEFT;
      }

      fpt_type dist1 = find_distance_to_segment_arc(
          left_site, new_site.point0());
      fpt_type dist2 = find_distance_to_segment_arc(
          right_site, new_site.point0());

      // The undefined ulp range is equal to 7EPS + 7EPS <= 14ULP.
      return dist1 < dist2;
    }


    fpt_type find_distance_to_point_arc(
        const site_type& site, const point_type& point) const {
      fpt_type dx = to_fpt(site.x()) - to_fpt(point.x());
      fpt_type dy = to_fpt(site.y()) - to_fpt(point.y());
      // The relative error is at most 3EPS.
      return (dx * dx + dy * dy) / (to_fpt(2.0) * dx);
    }


    fpt_type find_distance_to_segment_arc(
        const site_type& site, const point_type& point) const {
      if (is_vertical(site)) {
        return (to_fpt(site.x()) - to_fpt(point.x())) * to_fpt(0.5);
      } else {
        const point_type& segment0 = site.point0(true);
        const point_type& segment1 = site.point1(true);
        fpt_type a1 = to_fpt(segment1.x()) - to_fpt(segment0.x());
        fpt_type b1 = to_fpt(segment1.y()) - to_fpt(segment0.y());
        fpt_type k = get_sqrt(a1 * a1 + b1 * b1);
        // Avoid subtraction while computing k.
        if (!is_neg(b1)) {
          k = to_fpt(1.0) / (b1 + k);
        } else {
          k = (k - b1) / (a1 * a1);
        }
        // The relative error is at most 7EPS.
        return k * robust_cross_product(
            static_cast<int_x2_type>(segment1.x()) -
            static_cast<int_x2_type>(segment0.x()),
            static_cast<int_x2_type>(segment1.y()) -
            static_cast<int_x2_type>(segment0.y()),
            static_cast<int_x2_type>(point.x()) -
            static_cast<int_x2_type>(segment0.x()),
            static_cast<int_x2_type>(point.y()) -
            static_cast<int_x2_type>(segment0.y()));
      }
    }


    kPredicateResult fast_ps(
        const site_type& left_site, const site_type& right_site,
        const site_type& new_site, bool reverse_order) const {
      const point_type& site_point = left_site.point0();
      const point_type& segment_start = right_site.point0(true);
      const point_type& segment_end = right_site.point1(true);
      const point_type& new_point = new_site.point0();

      if (ot::eval(segment_start, segment_end, new_point) != ot::RIGHT)
        return (!right_site.is_inverse()) ? LESS : MORE;

      fpt_type dif_x = to_fpt(new_point.x()) - to_fpt(site_point.x());
      fpt_type dif_y = to_fpt(new_point.y()) - to_fpt(site_point.y());
      fpt_type a = to_fpt(segment_end.x()) - to_fpt(segment_start.x());
      fpt_type b = to_fpt(segment_end.y()) - to_fpt(segment_start.y());

      if (is_vertical(right_site)) {
        if (new_point.y() < site_point.y() && !reverse_order)
          return MORE;
        else if (new_point.y() > site_point.y() && reverse_order)
          return LESS;
        return UNDEFINED;
      } else {
        typename ot::Orientation orientation = ot::eval(
            static_cast<int_x2_type>(segment_end.x()) -
            static_cast<int_x2_type>(segment_start.x()),
            static_cast<int_x2_type>(segment_end.y()) -
            static_cast<int_x2_type>(segment_start.y()),
            static_cast<int_x2_type>(new_point.x()) -
            static_cast<int_x2_type>(site_point.x()),
            static_cast<int_x2_type>(new_point.y()) -
            static_cast<int_x2_type>(site_point.y()));
        if (orientation == ot::LEFT) {
          if (!right_site.is_inverse())
            return reverse_order ? LESS : UNDEFINED;
          return reverse_order ? UNDEFINED : MORE;
        }
      }

      fpt_type fast_left_expr = a * (dif_y + dif_x) * (dif_y - dif_x);
      fpt_type fast_right_expr = (to_fpt(2.0) * b) * dif_x * dif_y;
      typename ulp_cmp_type::Result expr_cmp =
          ulp_cmp(fast_left_expr, fast_right_expr, 4);
      if (expr_cmp != ulp_cmp_type::EQUAL) {
        if ((expr_cmp == ulp_cmp_type::MORE) ^ reverse_order)
          return reverse_order ? LESS : MORE;
        return UNDEFINED;
      }
      return UNDEFINED;
    }

    bool operator() (const node_type& node1,
                     const node_type& node2) const {
      // Get x coordinate of the rightmost site from both nodes.
      const site_type& site1 = get_comparison_site(node1);
      const site_type& site2 = get_comparison_site(node2);

      if (site1.x() < site2.x()) {
        // The second node contains a new site.
        return predicate_(node1.left_site(), node1.right_site(), site2);
      } else if (site1.x() > site2.x()) {
        // The first node contains a new site.
        return !predicate_(node2.left_site(), node2.right_site(), site1);
      } else {
        // This checks were evaluated experimentally.
        if (site1.sorted_index() == site2.sorted_index()) {
          // Both nodes are new (inserted during same site event processing).
          return get_comparison_y(node1) < get_comparison_y(node2);
        } else if (site1.sorted_index() < site2.sorted_index()) {
          std::pair<coordinate_type, int> y1 = get_comparison_y(node1, false);
          std::pair<coordinate_type, int> y2 = get_comparison_y(node2, true);
          if (y1.first != y2.first) return y1.first < y2.first;
          return (!site1.is_segment()) ? (y1.second < 0) : false;
        } else {
          std::pair<coordinate_type, int> y1 = get_comparison_y(node1, true);
          std::pair<coordinate_type, int> y2 = get_comparison_y(node2, false);
          if (y1.first != y2.first) return y1.first < y2.first;
          return (!site2.is_segment()) ? (y2.second > 0) : true;
        }
      }
    }

    const site_type& get_comparison_site(const node_type& node) const {
      if (node.left_site().sorted_index() > node.right_site().sorted_index()) {
        return node.left_site();
      }
      return node.right_site();
    }


    bool ppp(const site_type& site1,
             const site_type& site2,
             const site_type& site3) const {
      return ot::eval(site1.point0(), site2.point0(), site3.point0()) ==
             ot::RIGHT;
    }


    bool pps(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int segment_index) const {
      if (segment_index != 2) {
        typename ot::Orientation orient1 = ot::eval(site1.point0(),
            site2.point0(), site3.point0(true));
        typename ot::Orientation orient2 = ot::eval(site1.point0(),
            site2.point0(), site3.point1(true));
        if (segment_index == 1 && site1.x0() >= site2.x0()) {
          if (orient1 != ot::RIGHT)
            return false;
        } else if (segment_index == 3 && site2.x0() >= site1.x0()) {
          if (orient2 != ot::RIGHT)
            return false;
        } else if (orient1 != ot::RIGHT && orient2 != ot::RIGHT) {
          return false;
        }
      } else {
        if (site3.point0(true) == site1.point0() &&
            site3.point1(true) == site2.point0())
          return false;
      }
      return true;
    }


    bool pss(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int point_index) const {
      if (site2.point0() == site3.point0() &&
          site2.point1() == site3.point1()) {
        return false;
      }
      if (point_index == 2) {
        if (!site2.is_inverse() && site3.is_inverse())
          return false;
        if (site2.is_inverse() == site3.is_inverse() &&
            ot::eval(site2.point0(true),
                     site1.point0(),
                     site3.point1(true)) != ot::RIGHT)
          return false;
      }
      return true;
    }


    bool sss(const site_type& site1,
             const site_type& site2,
             const site_type& site3) const {
      if (site1.point0() == site2.point0() && site1.point1() == site2.point1())
        return false;
      if (site2.point0() == site3.point0() && site2.point1() == site3.point1())
        return false;
      return true;
    }


    void ppp(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             circle_type& circle,
             bool recompute_c_x = true,
             bool recompute_c_y = true,
             bool recompute_lower_x = true) {
      big_int_type dif_x[3], dif_y[3], sum_x[2], sum_y[2];
      dif_x[0] = static_cast<int_x2_type>(site1.x()) -
                 static_cast<int_x2_type>(site2.x());
      dif_x[1] = static_cast<int_x2_type>(site2.x()) -
                 static_cast<int_x2_type>(site3.x());
      dif_x[2] = static_cast<int_x2_type>(site1.x()) -
                 static_cast<int_x2_type>(site3.x());
      dif_y[0] = static_cast<int_x2_type>(site1.y()) -
                 static_cast<int_x2_type>(site2.y());
      dif_y[1] = static_cast<int_x2_type>(site2.y()) -
                 static_cast<int_x2_type>(site3.y());
      dif_y[2] = static_cast<int_x2_type>(site1.y()) -
                 static_cast<int_x2_type>(site3.y());
      sum_x[0] = static_cast<int_x2_type>(site1.x()) +
                 static_cast<int_x2_type>(site2.x());
      sum_x[1] = static_cast<int_x2_type>(site2.x()) +
                 static_cast<int_x2_type>(site3.x());
      sum_y[0] = static_cast<int_x2_type>(site1.y()) +
                 static_cast<int_x2_type>(site2.y());
      sum_y[1] = static_cast<int_x2_type>(site2.y()) +
                 static_cast<int_x2_type>(site3.y());
      fpt_type inv_denom = to_fpt(0.5) / to_fpt(static_cast<big_int_type>(
          dif_x[0] * dif_y[1] - dif_x[1] * dif_y[0]));
      big_int_type numer1 = dif_x[0] * sum_x[0] + dif_y[0] * sum_y[0];
      big_int_type numer2 = dif_x[1] * sum_x[1] + dif_y[1] * sum_y[1];

      if (recompute_c_x || recompute_lower_x) {
        big_int_type c_x = numer1 * dif_y[1] - numer2 * dif_y[0];
        circle.x(to_fpt(c_x) * inv_denom);

        if (recompute_lower_x) {
          // Evaluate radius of the circle.
          big_int_type sqr_r = (dif_x[0] * dif_x[0] + dif_y[0] * dif_y[0]) *
                               (dif_x[1] * dif_x[1] + dif_y[1] * dif_y[1]) *
                               (dif_x[2] * dif_x[2] + dif_y[2] * dif_y[2]);
          fpt_type r = get_sqrt(to_fpt(sqr_r));

          // If c_x >= 0 then lower_x = c_x + r,
          // else lower_x = (c_x * c_x - r * r) / (c_x - r).
          // To guarantee epsilon relative error.
          if (!is_neg(circle.x())) {
            if (!is_neg(inv_denom)) {
              circle.lower_x(circle.x() + r * inv_denom);
            } else {
              circle.lower_x(circle.x() - r * inv_denom);
            }
          } else {
            big_int_type numer = c_x * c_x - sqr_r;
            fpt_type lower_x = to_fpt(numer) * inv_denom / (to_fpt(c_x) + r);
            circle.lower_x(lower_x);
          }
        }
      }

      if (recompute_c_y) {
        big_int_type c_y = numer2 * dif_x[0] - numer1 * dif_x[1];
        circle.y(to_fpt(c_y) * inv_denom);
      }
    }

    void pps(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int segment_index,
             circle_type& c_event,
             bool recompute_c_x = true,
             bool recompute_c_y = true,
             bool recompute_lower_x = true) {
      big_int_type cA[4], cB[4];
      big_int_type line_a = static_cast<int_x2_type>(site3.point1(true).y()) -
                            static_cast<int_x2_type>(site3.point0(true).y());
      big_int_type line_b = static_cast<int_x2_type>(site3.point0(true).x()) -
                            static_cast<int_x2_type>(site3.point1(true).x());
      big_int_type segm_len = line_a * line_a + line_b * line_b;
      big_int_type vec_x = static_cast<int_x2_type>(site2.y()) -
                           static_cast<int_x2_type>(site1.y());
      big_int_type vec_y = static_cast<int_x2_type>(site1.x()) -
                           static_cast<int_x2_type>(site2.x());
      big_int_type sum_x = static_cast<int_x2_type>(site1.x()) +
                           static_cast<int_x2_type>(site2.x());
      big_int_type sum_y = static_cast<int_x2_type>(site1.y()) +
                           static_cast<int_x2_type>(site2.y());
      big_int_type teta = line_a * vec_x + line_b * vec_y;
      big_int_type denom = vec_x * line_b - vec_y * line_a;

      big_int_type dif0 = static_cast<int_x2_type>(site3.point1().y()) -
                          static_cast<int_x2_type>(site1.y());
      big_int_type dif1 = static_cast<int_x2_type>(site1.x()) -
                          static_cast<int_x2_type>(site3.point1().x());
      big_int_type A = line_a * dif1 - line_b * dif0;
      dif0 = static_cast<int_x2_type>(site3.point1().y()) -
             static_cast<int_x2_type>(site2.y());
      dif1 = static_cast<int_x2_type>(site2.x()) -
             static_cast<int_x2_type>(site3.point1().x());
      big_int_type B = line_a * dif1 - line_b * dif0;
      big_int_type sum_AB = A + B;

      if (is_zero(denom)) {
        big_int_type numer = teta * teta - sum_AB * sum_AB;
        big_int_type denom = teta * sum_AB;
        cA[0] = denom * sum_x * 2 + numer * vec_x;
        cB[0] = segm_len;
        cA[1] = denom * sum_AB * 2 + numer * teta;
        cB[1] = 1;
        cA[2] = denom * sum_y * 2 + numer * vec_y;
        fpt_type inv_denom = to_fpt(1.0) / to_fpt(denom);
        if (recompute_c_x)
          c_event.x(to_fpt(0.25) * to_fpt(cA[0]) * inv_denom);
        if (recompute_c_y)
          c_event.y(to_fpt(0.25) * to_fpt(cA[2]) * inv_denom);
        if (recompute_lower_x) {
          c_event.lower_x(to_fpt(0.25) * to_fpt(sqrt_expr_.eval2(cA, cB)) *
              inv_denom / get_sqrt(to_fpt(segm_len)));
        }
        return;
      }

      big_int_type det = (teta * teta + denom * denom) * A * B * 4;
      fpt_type inv_denom_sqr = to_fpt(1.0) / to_fpt(denom);
      inv_denom_sqr *= inv_denom_sqr;

      if (recompute_c_x || recompute_lower_x) {
        cA[0] = sum_x * denom * denom + teta * sum_AB * vec_x;
        cB[0] = 1;
        cA[1] = (segment_index == 2) ? -vec_x : vec_x;
        cB[1] = det;
        if (recompute_c_x) {
          c_event.x(to_fpt(0.5) * to_fpt(sqrt_expr_.eval2(cA, cB)) *
              inv_denom_sqr);
        }
      }

      if (recompute_c_y || recompute_lower_x) {
        cA[2] = sum_y * denom * denom + teta * sum_AB * vec_y;
        cB[2] = 1;
        cA[3] = (segment_index == 2) ? -vec_y : vec_y;
        cB[3] = det;
        if (recompute_c_y) {
          c_event.y(to_fpt(0.5) * to_fpt(sqrt_expr_.eval2(&cA[2], &cB[2])) *
                    inv_denom_sqr);
        }
      }

      if (recompute_lower_x) {
        cB[0] = cB[0] * segm_len;
        cB[1] = cB[1] * segm_len;
        cA[2] = sum_AB * (denom * denom + teta * teta);
        cB[2] = 1;
        cA[3] = (segment_index == 2) ? -teta : teta;
        cB[3] = det;
        c_event.lower_x(to_fpt(0.5) * to_fpt(sqrt_expr_.eval4(cA, cB)) *
            inv_denom_sqr / get_sqrt(to_fpt(segm_len)));
      }
    }

    void pss(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int point_index,
             circle_type& c_event,
             bool recompute_c_x = true,
             bool recompute_c_y = true,
             bool recompute_lower_x = true) {
      big_int_type a[2], b[2], c[2], cA[4], cB[4];
      const point_type& segm_start1 = site2.point1(true);
      const point_type& segm_end1 = site2.point0(true);
      const point_type& segm_start2 = site3.point0(true);
      const point_type& segm_end2 = site3.point1(true);
      a[0] = static_cast<int_x2_type>(segm_end1.x()) -
             static_cast<int_x2_type>(segm_start1.x());
      b[0] = static_cast<int_x2_type>(segm_end1.y()) -
             static_cast<int_x2_type>(segm_start1.y());
      a[1] = static_cast<int_x2_type>(segm_end2.x()) -
             static_cast<int_x2_type>(segm_start2.x());
      b[1] = static_cast<int_x2_type>(segm_end2.y()) -
             static_cast<int_x2_type>(segm_start2.y());
      big_int_type orientation = a[1] * b[0] - a[0] * b[1];
      if (is_zero(orientation)) {
        fpt_type denom = to_fpt(2.0) * to_fpt(
            static_cast<big_int_type>(a[0] * a[0] + b[0] * b[0]));
        c[0] = b[0] * (static_cast<int_x2_type>(segm_start2.x()) -
                       static_cast<int_x2_type>(segm_start1.x())) -
               a[0] * (static_cast<int_x2_type>(segm_start2.y()) -
                       static_cast<int_x2_type>(segm_start1.y()));
        big_int_type dx = a[0] * (static_cast<int_x2_type>(site1.y()) -
                                  static_cast<int_x2_type>(segm_start1.y())) -
                          b[0] * (static_cast<int_x2_type>(site1.x()) -
                                  static_cast<int_x2_type>(segm_start1.x()));
        big_int_type dy = b[0] * (static_cast<int_x2_type>(site1.x()) -
                                  static_cast<int_x2_type>(segm_start2.x())) -
                          a[0] * (static_cast<int_x2_type>(site1.y()) -
                                  static_cast<int_x2_type>(segm_start2.y()));
        cB[0] = dx * dy;
        cB[1] = 1;

        if (recompute_c_y) {
          cA[0] = b[0] * ((point_index == 2) ? 2 : -2);
          cA[1] = a[0] * a[0] * (static_cast<int_x2_type>(segm_start1.y()) +
                                 static_cast<int_x2_type>(segm_start2.y())) -
                  a[0] * b[0] * (static_cast<int_x2_type>(segm_start1.x()) +
                                 static_cast<int_x2_type>(segm_start2.x()) -
                                 static_cast<int_x2_type>(site1.x()) * 2) +
                  b[0] * b[0] * (static_cast<int_x2_type>(site1.y()) * 2);
          fpt_type c_y = to_fpt(sqrt_expr_.eval2(cA, cB));
          c_event.y(c_y / denom);
        }

        if (recompute_c_x || recompute_lower_x) {
          cA[0] = a[0] * ((point_index == 2) ? 2 : -2);
          cA[1] = b[0] * b[0] * (static_cast<int_x2_type>(segm_start1.x()) +
                                 static_cast<int_x2_type>(segm_start2.x())) -
                  a[0] * b[0] * (static_cast<int_x2_type>(segm_start1.y()) +
                                 static_cast<int_x2_type>(segm_start2.y()) -
                                 static_cast<int_x2_type>(site1.y()) * 2) +
                  a[0] * a[0] * (static_cast<int_x2_type>(site1.x()) * 2);

          if (recompute_c_x) {
            fpt_type c_x = to_fpt(sqrt_expr_.eval2(cA, cB));
            c_event.x(c_x / denom);
          }

          if (recompute_lower_x) {
            cA[2] = is_neg(c[0]) ? -c[0] : c[0];
            cB[2] = a[0] * a[0] + b[0] * b[0];
            fpt_type lower_x = to_fpt(sqrt_expr_.eval3(cA, cB));
            c_event.lower_x(lower_x / denom);
          }
        }
        return;
      }
      c[0] = b[0] * segm_end1.x() - a[0] * segm_end1.y();
      c[1] = a[1] * segm_end2.y() - b[1] * segm_end2.x();
      big_int_type ix = a[0] * c[1] + a[1] * c[0];
      big_int_type iy = b[0] * c[1] + b[1] * c[0];
      big_int_type dx = ix - orientation * site1.x();
      big_int_type dy = iy - orientation * site1.y();
      if (is_zero(dx) && is_zero(dy)) {
        fpt_type denom = to_fpt(orientation);
        fpt_type c_x = to_fpt(ix) / denom;
        fpt_type c_y = to_fpt(iy) / denom;
        c_event = circle_type(c_x, c_y, c_x);
        return;
      }

      big_int_type sign = ((point_index == 2) ? 1 : -1) *
                          (is_neg(orientation) ? 1 : -1);
      cA[0] = a[1] * -dx + b[1] * -dy;
      cA[1] = a[0] * -dx + b[0] * -dy;
      cA[2] = sign;
      cA[3] = 0;
      cB[0] = a[0] * a[0] + b[0] * b[0];
      cB[1] = a[1] * a[1] + b[1] * b[1];
      cB[2] = a[0] * a[1] + b[0] * b[1];
      cB[3] = (a[0] * dy - b[0] * dx) * (a[1] * dy - b[1] * dx) * -2;
      fpt_type temp = to_fpt(
          sqrt_expr_evaluator_pss4<big_int_type, efpt_type>(cA, cB));
      fpt_type denom = temp * to_fpt(orientation);

      if (recompute_c_y) {
        cA[0] = b[1] * (dx * dx + dy * dy) - iy * (dx * a[1] + dy * b[1]);
        cA[1] = b[0] * (dx * dx + dy * dy) - iy * (dx * a[0] + dy * b[0]);
        cA[2] = iy * sign;
        fpt_type cy = to_fpt(
            sqrt_expr_evaluator_pss4<big_int_type, efpt_type>(cA, cB));
        c_event.y(cy / denom);
      }

      if (recompute_c_x || recompute_lower_x) {
        cA[0] = a[1] * (dx * dx + dy * dy) - ix * (dx * a[1] + dy * b[1]);
        cA[1] = a[0] * (dx * dx + dy * dy) - ix * (dx * a[0] + dy * b[0]);
        cA[2] = ix * sign;

        if (recompute_c_x) {
          fpt_type cx = to_fpt(
              sqrt_expr_evaluator_pss4<big_int_type, efpt_type>(cA, cB));
          c_event.x(cx / denom);
        }

        if (recompute_lower_x) {
          cA[3] = orientation * (dx * dx + dy * dy) * (is_neg(temp) ? -1 : 1);
          fpt_type lower_x = to_fpt(
              sqrt_expr_evaluator_pss4<big_int_type, efpt_type>(cA, cB));
          c_event.lower_x(lower_x / denom);
        }
      }
    }

    void sss(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             circle_type& c_event,
             bool recompute_c_x = true,
             bool recompute_c_y = true,
             bool recompute_lower_x = true) {
      big_int_type a[3], b[3], c[3], cA[4], cB[4];
      // cA - corresponds to the cross product.
      // cB - corresponds to the squared length.
      a[0] = static_cast<int_x2_type>(site1.x1(true)) -
             static_cast<int_x2_type>(site1.x0(true));
      a[1] = static_cast<int_x2_type>(site2.x1(true)) -
             static_cast<int_x2_type>(site2.x0(true));
      a[2] = static_cast<int_x2_type>(site3.x1(true)) -
             static_cast<int_x2_type>(site3.x0(true));

      b[0] = static_cast<int_x2_type>(site1.y1(true)) -
             static_cast<int_x2_type>(site1.y0(true));
      b[1] = static_cast<int_x2_type>(site2.y1(true)) -
             static_cast<int_x2_type>(site2.y0(true));
      b[2] = static_cast<int_x2_type>(site3.y1(true)) -
             static_cast<int_x2_type>(site3.y0(true));

      c[0] = static_cast<int_x2_type>(site1.x0(true)) *
             static_cast<int_x2_type>(site1.y1(true)) -
             static_cast<int_x2_type>(site1.y0(true)) *
             static_cast<int_x2_type>(site1.x1(true));
      c[1] = static_cast<int_x2_type>(site2.x0(true)) *
             static_cast<int_x2_type>(site2.y1(true)) -
             static_cast<int_x2_type>(site2.y0(true)) *
             static_cast<int_x2_type>(site2.x1(true));
      c[2] = static_cast<int_x2_type>(site3.x0(true)) *
             static_cast<int_x2_type>(site3.y1(true)) -
             static_cast<int_x2_type>(site3.y0(true)) *
             static_cast<int_x2_type>(site3.x1(true));

      for (int i = 0; i < 3; ++i)
        cB[i] = a[i] * a[i] + b[i] * b[i];

      for (int i = 0; i < 3; ++i) {
        int j = (i+1) % 3;
        int k = (i+2) % 3;
        cA[i] = a[j] * b[k] - a[k] * b[j];
      }
      fpt_type denom = to_fpt(sqrt_expr_.eval3(cA, cB));

      if (recompute_c_y) {
        for (int i = 0; i < 3; ++i) {
          int j = (i+1) % 3;
          int k = (i+2) % 3;
          cA[i] = b[j] * c[k] - b[k] * c[j];
        }
        fpt_type c_y = to_fpt(sqrt_expr_.eval3(cA, cB));
        c_event.y(c_y / denom);
      }

      if (recompute_c_x || recompute_lower_x) {
        cA[3] = 0;
        for (int i = 0; i < 3; ++i) {
          int j = (i+1) % 3;
          int k = (i+2) % 3;
          cA[i] = a[j] * c[k] - a[k] * c[j];
          if (recompute_lower_x) {
            cA[3] = cA[3] + cA[i] * b[i];
          }
        }

        if (recompute_c_x) {
          fpt_type c_x = to_fpt(sqrt_expr_.eval3(cA, cB));
          c_event.x(c_x / denom);
        }

        if (recompute_lower_x) {
          cB[3] = 1;
          fpt_type lower_x = to_fpt(sqrt_expr_.eval4(cA, cB));
          c_event.lower_x(lower_x / denom);
        }
      }
    }

    template <typename _int, typename _fpt>
    _fpt sqrt_expr_evaluator_pss4(_int *A, _int *B) {
      _int cA[4], cB[4];
      if (is_zero(A[3])) {
        _fpt lh = sqrt_expr_.eval2(A, B);
        cA[0] = 1;
        cB[0] = B[0] * B[1];
        cA[1] = B[2];
        cB[1] = 1;
        _fpt rh = sqrt_expr_.eval1(A+2, B+3) *
            get_sqrt(sqrt_expr_.eval2(cA, cB));
        if ((!is_neg(lh) && !is_neg(rh)) || (!is_pos(lh) && !is_pos(rh)))
          return lh + rh;
        cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
                A[2] * A[2] * B[3] * B[2];
        cB[0] = 1;
        cA[1] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
        cB[1] = B[0] * B[1];
        _fpt numer = sqrt_expr_.eval2(cA, cB);
        return numer / (lh - rh);
      }
      cA[0] = 1;
      cB[0] = B[0] * B[1];
      cA[1] = B[2];
      cB[1] = 1;
      _fpt rh = sqrt_expr_.eval1(A+2, B+3) * get_sqrt(sqrt_expr_.eval2(cA, cB));
      cA[0] = A[0];
      cB[0] = B[0];
      cA[1] = A[1];
      cB[1] = B[1];
      cA[2] = A[3];
      cB[2] = 1;
      _fpt lh = sqrt_expr_.eval3(cA, cB);
      if ((!is_neg(lh) && !is_neg(rh)) || (!is_pos(lh) && !is_pos(rh)))
        return lh + rh;
      cA[0] = A[3] * A[0] * 2;
      cA[1] = A[3] * A[1] * 2;
      cA[2] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] +
              A[3] * A[3] - A[2] * A[2] * B[2] * B[3];
      cA[3] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
      cB[3] = B[0] * B[1];
      _fpt numer = sqrt_expr_evaluator_pss3<_int, _fpt>(cA, cB);
      return numer / (lh - rh);
    }


    template <typename _int, typename _fpt>
    // Evaluates A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
    //           A[2] + A[3] * sqrt(B[0] * B[1]).
    // B[3] = B[0] * B[1].
    _fpt sqrt_expr_evaluator_pss3(_int *A, _int *B) {
      _int cA[2], cB[2];
      _fpt lh = sqrt_expr_.eval2(A, B);
      _fpt rh = sqrt_expr_.eval2(A+2, B+2);
      if ((!is_neg(lh) && !is_neg(rh)) || (!is_pos(lh) && !is_pos(rh)))
        return lh + rh;
      cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
              A[2] * A[2] - A[3] * A[3] * B[0] * B[1];
      cB[0] = 1;
      cA[1] = (A[0] * A[1] - A[2] * A[3]) * 2;
      cB[1] = B[3];
      _fpt numer = sqrt_expr_.eval2(cA, cB);
      return numer / (lh - rh);
    }


    void ppp(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             circle_type& c_event) {
      fpt_type dif_x1 = to_fpt(site1.x()) - to_fpt(site2.x());
      fpt_type dif_x2 = to_fpt(site2.x()) - to_fpt(site3.x());
      fpt_type dif_y1 = to_fpt(site1.y()) - to_fpt(site2.y());
      fpt_type dif_y2 = to_fpt(site2.y()) - to_fpt(site3.y());
      fpt_type orientation = robust_cross_product(
          static_cast<int_x2_type>(site1.x()) -
          static_cast<int_x2_type>(site2.x()),
          static_cast<int_x2_type>(site2.x()) -
          static_cast<int_x2_type>(site3.x()),
          static_cast<int_x2_type>(site1.y()) -
          static_cast<int_x2_type>(site2.y()),
          static_cast<int_x2_type>(site2.y()) -
          static_cast<int_x2_type>(site3.y()));
      robust_fpt_type inv_orientation(to_fpt(0.5) / orientation, to_fpt(2.0));
      fpt_type sum_x1 = to_fpt(site1.x()) + to_fpt(site2.x());
      fpt_type sum_x2 = to_fpt(site2.x()) + to_fpt(site3.x());
      fpt_type sum_y1 = to_fpt(site1.y()) + to_fpt(site2.y());
      fpt_type sum_y2 = to_fpt(site2.y()) + to_fpt(site3.y());
      fpt_type dif_x3 = to_fpt(site1.x()) - to_fpt(site3.x());
      fpt_type dif_y3 = to_fpt(site1.y()) - to_fpt(site3.y());
      robust_dif_type c_x, c_y;
      c_x += robust_fpt_type(dif_x1 * sum_x1 * dif_y2, to_fpt(2.0));
      c_x += robust_fpt_type(dif_y1 * sum_y1 * dif_y2, to_fpt(2.0));
      c_x -= robust_fpt_type(dif_x2 * sum_x2 * dif_y1, to_fpt(2.0));
      c_x -= robust_fpt_type(dif_y2 * sum_y2 * dif_y1, to_fpt(2.0));
      c_y += robust_fpt_type(dif_x2 * sum_x2 * dif_x1, to_fpt(2.0));
      c_y += robust_fpt_type(dif_y2 * sum_y2 * dif_x1, to_fpt(2.0));
      c_y -= robust_fpt_type(dif_x1 * sum_x1 * dif_x2, to_fpt(2.0));
      c_y -= robust_fpt_type(dif_y1 * sum_y1 * dif_x2, to_fpt(2.0));
      robust_dif_type lower_x(c_x);
      lower_x -= robust_fpt_type(get_sqrt(
          (dif_x1 * dif_x1 + dif_y1 * dif_y1) *
          (dif_x2 * dif_x2 + dif_y2 * dif_y2) *
          (dif_x3 * dif_x3 + dif_y3 * dif_y3)), to_fpt(5.0));
      c_event = circle_type(
          c_x.dif().fpv() * inv_orientation.fpv(),
          c_y.dif().fpv() * inv_orientation.fpv(),
          lower_x.dif().fpv() * inv_orientation.fpv());
      bool recompute_c_x = c_x.dif().ulp() > ULPS;
      bool recompute_c_y = c_y.dif().ulp() > ULPS;
      bool recompute_lower_x = lower_x.dif().ulp() > ULPS;
      if (recompute_c_x || recompute_c_y || recompute_lower_x) {
        exact_circle_formation_functor_.ppp(
            site1, site2, site3, c_event,
            recompute_c_x, recompute_c_y, recompute_lower_x);
      }
    }


    void pps(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int segment_index,
             circle_type& c_event) {
      fpt_type line_a = to_fpt(site3.point1(true).y()) -
                        to_fpt(site3.point0(true).y());
      fpt_type line_b = to_fpt(site3.point0(true).x()) -
                        to_fpt(site3.point1(true).x());
      fpt_type vec_x = to_fpt(site2.y()) - to_fpt(site1.y());
      fpt_type vec_y = to_fpt(site1.x()) - to_fpt(site2.x());
      robust_fpt_type teta(robust_cross_product(
          static_cast<int_x2_type>(site3.point1(true).y()) -
          static_cast<int_x2_type>(site3.point0(true).y()),
          static_cast<int_x2_type>(site3.point0(true).x()) -
          static_cast<int_x2_type>(site3.point1(true).x()),
          static_cast<int_x2_type>(site2.x()) -
          static_cast<int_x2_type>(site1.x()),
          static_cast<int_x2_type>(site2.y()) -
          static_cast<int_x2_type>(site1.y())), to_fpt(1.0));
      robust_fpt_type A(robust_cross_product(
          static_cast<int_x2_type>(site3.point1(true).y()) -
          static_cast<int_x2_type>(site3.point0(true).y()),
          static_cast<int_x2_type>(site3.point0(true).x()) -
          static_cast<int_x2_type>(site3.point1(true).x()),
          static_cast<int_x2_type>(site3.point1().y()) -
          static_cast<int_x2_type>(site1.y()),
          static_cast<int_x2_type>(site1.x()) -
          static_cast<int_x2_type>(site3.point1().x())), to_fpt(1.0));
      robust_fpt_type B(robust_cross_product(
          static_cast<int_x2_type>(site3.point1(true).y()) -
          static_cast<int_x2_type>(site3.point0(true).y()),
          static_cast<int_x2_type>(site3.point0(true).x()) -
          static_cast<int_x2_type>(site3.point1(true).x()),
          static_cast<int_x2_type>(site3.point1().y()) -
          static_cast<int_x2_type>(site2.y()),
          static_cast<int_x2_type>(site2.x()) -
          static_cast<int_x2_type>(site3.point1().x())), to_fpt(1.0));
      robust_fpt_type denom(robust_cross_product(
          static_cast<int_x2_type>(site2.y()) -
          static_cast<int_x2_type>(site1.y()),
          static_cast<int_x2_type>(site1.x()) -
          static_cast<int_x2_type>(site2.x()),
          static_cast<int_x2_type>(site3.point1(true).y()) -
          static_cast<int_x2_type>(site3.point0(true).y()),
          static_cast<int_x2_type>(site3.point0(true).x()) -
          static_cast<int_x2_type>(site3.point1(true).x())), to_fpt(1.0));
      robust_fpt_type inv_segm_len(to_fpt(1.0) /
          get_sqrt(line_a * line_a + line_b * line_b), to_fpt(3.0));
      robust_dif_type t;
      if (ot::eval(denom) == ot::COLLINEAR) {
        t += teta / (robust_fpt_type(to_fpt(8.0)) * A);
        t -= A / (robust_fpt_type(to_fpt(2.0)) * teta);
      } else {
        robust_fpt_type det = ((teta * teta + denom * denom) * A * B).sqrt();
        if (segment_index == 2) {
          t -= det / (denom * denom);
        } else {
          t += det / (denom * denom);
        }
        t += teta * (A + B) / (robust_fpt_type(to_fpt(2.0)) * denom * denom);
      }
      robust_dif_type c_x, c_y;
      c_x += robust_fpt_type(to_fpt(0.5) * (to_fpt(site1.x()) +
                                            to_fpt(site2.x())));
      c_x += robust_fpt_type(vec_x) * t;
      c_y += robust_fpt_type(to_fpt(0.5) * (to_fpt(site1.y()) +
                                            to_fpt(site2.y())));
      c_y += robust_fpt_type(vec_y) * t;
      robust_dif_type r, lower_x(c_x);
      r -= robust_fpt_type(line_a) * robust_fpt_type(site3.x0());
      r -= robust_fpt_type(line_b) * robust_fpt_type(site3.y0());
      r += robust_fpt_type(line_a) * c_x;
      r += robust_fpt_type(line_b) * c_y;
      if (r.pos().fpv() < r.neg().fpv())
        r = -r;
      lower_x += r * inv_segm_len;
      c_event = circle_type(
          c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
      bool recompute_c_x = c_x.dif().ulp() > ULPS;
      bool recompute_c_y = c_y.dif().ulp() > ULPS;
      bool recompute_lower_x = lower_x.dif().ulp() > ULPS;
      if (recompute_c_x || recompute_c_y || recompute_lower_x) {
        exact_circle_formation_functor_.pps(
            site1, site2, site3, segment_index, c_event,
            recompute_c_x, recompute_c_y, recompute_lower_x);
      }
    }


    void pss(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             int point_index,
             circle_type& c_event) {
      const point_type& segm_start1 = site2.point1(true);
      const point_type& segm_end1 = site2.point0(true);
      const point_type& segm_start2 = site3.point0(true);
      const point_type& segm_end2 = site3.point1(true);
      fpt_type a1 = to_fpt(segm_end1.x()) - to_fpt(segm_start1.x());
      fpt_type b1 = to_fpt(segm_end1.y()) - to_fpt(segm_start1.y());
      fpt_type a2 = to_fpt(segm_end2.x()) - to_fpt(segm_start2.x());
      fpt_type b2 = to_fpt(segm_end2.y()) - to_fpt(segm_start2.y());
      bool recompute_c_x, recompute_c_y, recompute_lower_x;
      robust_fpt_type orientation(robust_cross_product(
        static_cast<int_x2_type>(segm_end1.y()) -
        static_cast<int_x2_type>(segm_start1.y()),
        static_cast<int_x2_type>(segm_end1.x()) -
        static_cast<int_x2_type>(segm_start1.x()),
        static_cast<int_x2_type>(segm_end2.y()) -
        static_cast<int_x2_type>(segm_start2.y()),
        static_cast<int_x2_type>(segm_end2.x()) -
        static_cast<int_x2_type>(segm_start2.x())), to_fpt(1.0));
      if (ot::eval(orientation) == ot::COLLINEAR) {
        robust_fpt_type a(a1 * a1 + b1 * b1, to_fpt(2.0));
        robust_fpt_type c(robust_cross_product(
            static_cast<int_x2_type>(segm_end1.y()) -
            static_cast<int_x2_type>(segm_start1.y()),
            static_cast<int_x2_type>(segm_end1.x()) -
            static_cast<int_x2_type>(segm_start1.x()),
            static_cast<int_x2_type>(segm_start2.y()) -
            static_cast<int_x2_type>(segm_start1.y()),
            static_cast<int_x2_type>(segm_start2.x()) -
            static_cast<int_x2_type>(segm_start1.x())), to_fpt(1.0));
        robust_fpt_type det(
            robust_cross_product(
                static_cast<int_x2_type>(segm_end1.x()) -
                static_cast<int_x2_type>(segm_start1.x()),
                static_cast<int_x2_type>(segm_end1.y()) -
                static_cast<int_x2_type>(segm_start1.y()),
                static_cast<int_x2_type>(site1.x()) -
                static_cast<int_x2_type>(segm_start1.x()),
                static_cast<int_x2_type>(site1.y()) -
                static_cast<int_x2_type>(segm_start1.y())) *
            robust_cross_product(
                static_cast<int_x2_type>(segm_end1.y()) -
                static_cast<int_x2_type>(segm_start1.y()),
                static_cast<int_x2_type>(segm_end1.x()) -
                static_cast<int_x2_type>(segm_start1.x()),
                static_cast<int_x2_type>(site1.y()) -
                static_cast<int_x2_type>(segm_start2.y()),
                static_cast<int_x2_type>(site1.x()) -
                static_cast<int_x2_type>(segm_start2.x())),
            to_fpt(3.0));
        robust_dif_type t;
        t -= robust_fpt_type(a1) * robust_fpt_type((
             to_fpt(segm_start1.x()) + to_fpt(segm_start2.x())) * to_fpt(0.5) -
             to_fpt(site1.x()));
        t -= robust_fpt_type(b1) * robust_fpt_type((
             to_fpt(segm_start1.y()) + to_fpt(segm_start2.y())) * to_fpt(0.5) -
             to_fpt(site1.y()));
        if (point_index == 2) {
          t += det.sqrt();
        } else {
          t -= det.sqrt();
        }
        t /= a;
        robust_dif_type c_x, c_y;
        c_x += robust_fpt_type(to_fpt(0.5) * (
            to_fpt(segm_start1.x()) + to_fpt(segm_start2.x())));
        c_x += robust_fpt_type(a1) * t;
        c_y += robust_fpt_type(to_fpt(0.5) * (
            to_fpt(segm_start1.y()) + to_fpt(segm_start2.y())));
        c_y += robust_fpt_type(b1) * t;
        robust_dif_type lower_x(c_x);
        if (is_neg(c)) {
          lower_x -= robust_fpt_type(to_fpt(0.5)) * c / a.sqrt();
        } else {
          lower_x += robust_fpt_type(to_fpt(0.5)) * c / a.sqrt();
        }
        recompute_c_x = c_x.dif().ulp() > ULPS;
        recompute_c_y = c_y.dif().ulp() > ULPS;
        recompute_lower_x = lower_x.dif().ulp() > ULPS;
        c_event =
            circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
      } else {
        robust_fpt_type sqr_sum1(get_sqrt(a1 * a1 + b1 * b1), to_fpt(2.0));
        robust_fpt_type sqr_sum2(get_sqrt(a2 * a2 + b2 * b2), to_fpt(2.0));
        robust_fpt_type a(robust_cross_product(
          static_cast<int_x2_type>(segm_end1.x()) -
          static_cast<int_x2_type>(segm_start1.x()),
          static_cast<int_x2_type>(segm_end1.y()) -
          static_cast<int_x2_type>(segm_start1.y()),
          static_cast<int_x2_type>(segm_start2.y()) -
          static_cast<int_x2_type>(segm_end2.y()),
          static_cast<int_x2_type>(segm_end2.x()) -
          static_cast<int_x2_type>(segm_start2.x())), to_fpt(1.0));
        if (!is_neg(a)) {
          a += sqr_sum1 * sqr_sum2;
        } else {
          a = (orientation * orientation) / (sqr_sum1 * sqr_sum2 - a);
        }
        robust_fpt_type or1(robust_cross_product(
            static_cast<int_x2_type>(segm_end1.y()) -
            static_cast<int_x2_type>(segm_start1.y()),
            static_cast<int_x2_type>(segm_end1.x()) -
            static_cast<int_x2_type>(segm_start1.x()),
            static_cast<int_x2_type>(segm_end1.y()) -
            static_cast<int_x2_type>(site1.y()),
            static_cast<int_x2_type>(segm_end1.x()) -
            static_cast<int_x2_type>(site1.x())), to_fpt(1.0));
        robust_fpt_type or2(robust_cross_product(
            static_cast<int_x2_type>(segm_end2.x()) -
            static_cast<int_x2_type>(segm_start2.x()),
            static_cast<int_x2_type>(segm_end2.y()) -
            static_cast<int_x2_type>(segm_start2.y()),
            static_cast<int_x2_type>(segm_end2.x()) -
            static_cast<int_x2_type>(site1.x()),
            static_cast<int_x2_type>(segm_end2.y()) -
            static_cast<int_x2_type>(site1.y())), to_fpt(1.0));
        robust_fpt_type det = robust_fpt_type(to_fpt(2.0)) * a * or1 * or2;
        robust_fpt_type c1(robust_cross_product(
            static_cast<int_x2_type>(segm_end1.y()) -
            static_cast<int_x2_type>(segm_start1.y()),
            static_cast<int_x2_type>(segm_end1.x()) -
            static_cast<int_x2_type>(segm_start1.x()),
            static_cast<int_x2_type>(segm_end1.y()),
            static_cast<int_x2_type>(segm_end1.x())), to_fpt(1.0));
        robust_fpt_type c2(robust_cross_product(
            static_cast<int_x2_type>(segm_end2.x()) -
            static_cast<int_x2_type>(segm_start2.x()),
            static_cast<int_x2_type>(segm_end2.y()) -
            static_cast<int_x2_type>(segm_start2.y()),
            static_cast<int_x2_type>(segm_end2.x()),
            static_cast<int_x2_type>(segm_end2.y())), to_fpt(1.0));
        robust_fpt_type inv_orientation =
            robust_fpt_type(to_fpt(1.0)) / orientation;
        robust_dif_type t, b, ix, iy;
        ix += robust_fpt_type(a2) * c1 * inv_orientation;
        ix += robust_fpt_type(a1) * c2 * inv_orientation;
        iy += robust_fpt_type(b1) * c2 * inv_orientation;
        iy += robust_fpt_type(b2) * c1 * inv_orientation;

        b += ix * (robust_fpt_type(a1) * sqr_sum2);
        b += ix * (robust_fpt_type(a2) * sqr_sum1);
        b += iy * (robust_fpt_type(b1) * sqr_sum2);
        b += iy * (robust_fpt_type(b2) * sqr_sum1);
        b -= sqr_sum1 * robust_fpt_type(robust_cross_product(
            static_cast<int_x2_type>(segm_end2.x()) -
            static_cast<int_x2_type>(segm_start2.x()),
            static_cast<int_x2_type>(segm_end2.y()) -
            static_cast<int_x2_type>(segm_start2.y()),
            static_cast<int_x2_type>(-site1.y()),
            static_cast<int_x2_type>(site1.x())), to_fpt(1.0));
        b -= sqr_sum2 * robust_fpt_type(robust_cross_product(
            static_cast<int_x2_type>(segm_end1.x()) -
            static_cast<int_x2_type>(segm_start1.x()),
            static_cast<int_x2_type>(segm_end1.y()) -
            static_cast<int_x2_type>(segm_start1.y()),
            static_cast<int_x2_type>(-site1.y()),
            static_cast<int_x2_type>(site1.x())), to_fpt(1.0));
        t -= b;
        if (point_index == 2) {
          t += det.sqrt();
        } else {
          t -= det.sqrt();
        }
        t /= (a * a);
        robust_dif_type c_x(ix), c_y(iy);
        c_x += t * (robust_fpt_type(a1) * sqr_sum2);
        c_x += t * (robust_fpt_type(a2) * sqr_sum1);
        c_y += t * (robust_fpt_type(b1) * sqr_sum2);
        c_y += t * (robust_fpt_type(b2) * sqr_sum1);
        if (t.pos().fpv() < t.neg().fpv()) {
          t = -t;
        }
        robust_dif_type lower_x(c_x);
        if (is_neg(orientation)) {
          lower_x -= t * orientation;
        } else {
          lower_x += t * orientation;
        }
        recompute_c_x = c_x.dif().ulp() > ULPS;
        recompute_c_y = c_y.dif().ulp() > ULPS;
        recompute_lower_x = lower_x.dif().ulp() > ULPS;
        c_event = circle_type(
            c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
      }
      if (recompute_c_x || recompute_c_y || recompute_lower_x) {
          exact_circle_formation_functor_.pss(
              site1, site2, site3, point_index, c_event,
        recompute_c_x, recompute_c_y, recompute_lower_x);
      }
    }


    void sss(const site_type& site1,
             const site_type& site2,
             const site_type& site3,
             circle_type& c_event) {
      robust_fpt_type a1(to_fpt(site1.x1(true)) - to_fpt(site1.x0(true)));
      robust_fpt_type b1(to_fpt(site1.y1(true)) - to_fpt(site1.y0(true)));
      robust_fpt_type c1(robust_cross_product(
          site1.x0(true), site1.y0(true),
          site1.x1(true), site1.y1(true)), to_fpt(1.0));

      robust_fpt_type a2(to_fpt(site2.x1(true)) - to_fpt(site2.x0(true)));
      robust_fpt_type b2(to_fpt(site2.y1(true)) - to_fpt(site2.y0(true)));
      robust_fpt_type c2(robust_cross_product(
          site2.x0(true), site2.y0(true),
          site2.x1(true), site2.y1(true)), to_fpt(1.0));

      robust_fpt_type a3(to_fpt(site3.x1(true)) - to_fpt(site3.x0(true)));
      robust_fpt_type b3(to_fpt(site3.y1(true)) - to_fpt(site3.y0(true)));
      robust_fpt_type c3(robust_cross_product(
          site3.x0(true), site3.y0(true),
          site3.x1(true), site3.y1(true)), to_fpt(1.0));

      robust_fpt_type len1 = (a1 * a1 + b1 * b1).sqrt();
      robust_fpt_type len2 = (a2 * a2 + b2 * b2).sqrt();
      robust_fpt_type len3 = (a3 * a3 + b3 * b3).sqrt();
      robust_fpt_type cross_12(robust_cross_product(
          static_cast<int_x2_type>(site1.x1(true)) -
          static_cast<int_x2_type>(site1.x0(true)),
          static_cast<int_x2_type>(site1.y1(true)) -
          static_cast<int_x2_type>(site1.y0(true)),
          static_cast<int_x2_type>(site2.x1(true)) -
          static_cast<int_x2_type>(site2.x0(true)),
          static_cast<int_x2_type>(site2.y1(true)) -
          static_cast<int_x2_type>(site2.y0(true))), to_fpt(1.0));
      robust_fpt_type cross_23(robust_cross_product(
          static_cast<int_x2_type>(site2.x1(true)) -
          static_cast<int_x2_type>(site2.x0(true)),
          static_cast<int_x2_type>(site2.y1(true)) -
          static_cast<int_x2_type>(site2.y0(true)),
          static_cast<int_x2_type>(site3.x1(true)) -
          static_cast<int_x2_type>(site3.x0(true)),
          static_cast<int_x2_type>(site3.y1(true)) -
          static_cast<int_x2_type>(site3.y0(true))), to_fpt(1.0));
      robust_fpt_type cross_31(robust_cross_product(
          static_cast<int_x2_type>(site3.x1(true)) -
          static_cast<int_x2_type>(site3.x0(true)),
          static_cast<int_x2_type>(site3.y1(true)) -
          static_cast<int_x2_type>(site3.y0(true)),
          static_cast<int_x2_type>(site1.x1(true)) -
          static_cast<int_x2_type>(site1.x0(true)),
          static_cast<int_x2_type>(site1.y1(true)) -
          static_cast<int_x2_type>(site1.y0(true))), to_fpt(1.0));

      // denom = cross_12 * len3 + cross_23 * len1 + cross_31 * len2.
      robust_dif_type denom;
      denom += cross_12 * len3;
      denom += cross_23 * len1;
      denom += cross_31 * len2;

      // denom * r = (b2 * c_x - a2 * c_y - c2 * denom) / len2.
      robust_dif_type r;
      r -= cross_12 * c3;
      r -= cross_23 * c1;
      r -= cross_31 * c2;

      robust_dif_type c_x;
      c_x += a1 * c2 * len3;
      c_x -= a2 * c1 * len3;
      c_x += a2 * c3 * len1;
      c_x -= a3 * c2 * len1;
      c_x += a3 * c1 * len2;
      c_x -= a1 * c3 * len2;

      robust_dif_type c_y;
      c_y += b1 * c2 * len3;
      c_y -= b2 * c1 * len3;
      c_y += b2 * c3 * len1;
      c_y -= b3 * c2 * len1;
      c_y += b3 * c1 * len2;
      c_y -= b1 * c3 * len2;

      robust_dif_type lower_x = c_x + r;

      robust_fpt_type denom_dif = denom.dif();
      robust_fpt_type c_x_dif = c_x.dif() / denom_dif;
      robust_fpt_type c_y_dif = c_y.dif() / denom_dif;
      robust_fpt_type lower_x_dif = lower_x.dif() / denom_dif;

      bool recompute_c_x = c_x_dif.ulp() > ULPS;
      bool recompute_c_y = c_y_dif.ulp() > ULPS;
      bool recompute_lower_x = lower_x_dif.ulp() > ULPS;
      c_event = circle_type(c_x_dif.fpv(), c_y_dif.fpv(), lower_x_dif.fpv());
      if (recompute_c_x || recompute_c_y || recompute_lower_x) {
        exact_circle_formation_functor_.sss(
            site1, site2, site3, c_event,
            recompute_c_x, recompute_c_y, recompute_lower_x);
      }
    }

    bool operator()(const site_type& site1, const site_type& site2,
                    const site_type& site3, circle_type& circle) {
      if (!site1.is_segment()) {
        if (!site2.is_segment()) {
          if (!site3.is_segment()) {
            // (point, point, point) sites.
            if (!circle_existence_predicate_.ppp(site1, site2, site3))
              return false;
            circle_formation_functor_.ppp(site1, site2, site3, circle);
          } else {
            // (point, point, segment) sites.
            if (!circle_existence_predicate_.pps(site1, site2, site3, 3))
              return false;
            circle_formation_functor_.pps(site1, site2, site3, 3, circle);
          }
        } else {
          if (!site3.is_segment()) {
            // (point, segment, point) sites.
            if (!circle_existence_predicate_.pps(site1, site3, site2, 2))
              return false;
            circle_formation_functor_.pps(site1, site3, site2, 2, circle);
          } else {
            // (point, segment, segment) sites.
            if (!circle_existence_predicate_.pss(site1, site2, site3, 1))
              return false;
            circle_formation_functor_.pss(site1, site2, site3, 1, circle);
          }
        }
      } else {
        if (!site2.is_segment()) {
          if (!site3.is_segment()) {
            // (segment, point, point) sites.
            if (!circle_existence_predicate_.pps(site2, site3, site1, 1))
              return false;
            circle_formation_functor_.pps(site2, site3, site1, 1, circle);
          } else {
            // (segment, point, segment) sites.
            if (!circle_existence_predicate_.pss(site2, site1, site3, 2))
              return false;
            circle_formation_functor_.pss(site2, site1, site3, 2, circle);
          }
        } else {
          if (!site3.is_segment()) {
            // (segment, segment, point) sites.
            if (!circle_existence_predicate_.pss(site3, site1, site2, 3))
              return false;
            circle_formation_functor_.pss(site3, site1, site2, 3, circle);
          } else {
            // (segment, segment, segment) sites.
            if (!circle_existence_predicate_.sss(site1, site2, site3))
              return false;
            circle_formation_functor_.sss(site1, site2, site3, circle);
          }
        }
      }
      return true;
    }


inline bool belongs(
    SourceCategory source_category,
    GeometryCategory geometry_category) {
  return (static_cast<std::size_t>(source_category) >>
              SOURCE_CATEGORY_GEOMETRY_SHIFT) ==
         static_cast<std::size_t>(geometry_category);
}


  point_2d() {}


  point_2d(coordinate_type x, coordinate_type y) :
      x_(x),
      y_(y) {}


  bool operator==(const point_2d& that) const {
    return (this->x_ == that.x()) && (this->y_ == that.y());
  }


  bool operator!=(const point_2d& that) const {
    return (this->x_ != that.x()) || (this->y_ != that.y());
  }


  coordinate_type x() const {
    return x_;
  }


  coordinate_type y() const {
    return y_;
  }


  point_2d& x(coordinate_type x) {
    x_ = x;
    return *this;
  }


  point_2d& y(coordinate_type y) {
    y_ = y;
    return *this;
  }


  site_event() :
      point0_(0, 0),
      point1_(0, 0),
      sorted_index_(0),
      flags_(0) {}


  site_event(coordinate_type x, coordinate_type y) :
      point0_(x, y),
      point1_(x, y),
      sorted_index_(0),
      flags_(0) {}


  explicit site_event(const point_type& point) :
      point0_(point),
      point1_(point),
      sorted_index_(0),
      flags_(0) {}


  site_event(coordinate_type x1, coordinate_type y1,
             coordinate_type x2, coordinate_type y2):
      point0_(x1, y1),
      point1_(x2, y2),
      sorted_index_(0),
      flags_(0) {}


  site_event(const point_type& point1, const point_type& point2) :
      point0_(point1),
      point1_(point2),
      sorted_index_(0),
      flags_(0) {}


  bool operator==(const site_event& that) const {
    return (this->point0_ == that.point0_) &&
           (this->point1_ == that.point1_);
  }


  bool operator!=(const site_event& that) const {
    return (this->point0_ != that.point0_) ||
           (this->point1_ != that.point1_);
  }


  coordinate_type x(bool oriented = false) const {
    return x0(oriented);
  }


  coordinate_type y(bool oriented = false) const {
    return y0(oriented);
  }


  coordinate_type x0(bool oriented = false) const {
    if (!oriented)
      return point0_.x();
    return is_inverse() ? point1_.x() : point0_.x();
  }


  coordinate_type y0(bool oriented = false) const {
    if (!oriented)
      return point0_.y();
    return is_inverse() ? point1_.y() : point0_.y();
  }


  coordinate_type x1(bool oriented = false) const {
    if (!oriented)
      return point1_.x();
    return is_inverse() ? point0_.x() : point1_.x();
  }


  coordinate_type y1(bool oriented = false) const {
    if (!oriented)
      return point1_.y();
    return is_inverse() ? point0_.y() : point1_.y();
  }


  const point_type& point0(bool oriented = false) const {
    if (!oriented)
      return point0_;
    return is_inverse() ? point1_ : point0_;
  }


  const point_type& point1(bool oriented = false) const {
    if (!oriented)
      return point1_;
    return is_inverse() ? point0_ : point1_;
  }


  std::size_t sorted_index() const {
    return sorted_index_;
  }


  std::size_t initial_index() const {
    return initial_index_;
  }


  bool is_inverse() const {
    return (flags_ & IS_INVERSE) ? true : false;
  }


  site_event& inverse() {
    flags_ ^= IS_INVERSE;
    return *this;
  }


  SourceCategory source_category() const {
    return static_cast<SourceCategory>(flags_ & SOURCE_CATEGORY_BITMASK);
  }


  site_event& source_category(SourceCategory source_category) {
    flags_ |= source_category;
    return *this;
  }


  bool is_point() const {
    return (point0_.x() == point1_.x()) && (point0_.y() == point1_.y());
  }


  bool is_segment() const {
    return (point0_.x() != point1_.x()) || (point0_.y() != point1_.y());
  }


  circle_event() : is_active_(true) {}


  circle_event(coordinate_type c_x,
               coordinate_type c_y,
               coordinate_type lower_x) :
      center_x_(c_x),
      center_y_(c_y),
      lower_x_(lower_x),
      is_active_(true) {}


  coordinate_type x() const {
    return center_x_;
  }


  circle_event& x(coordinate_type center_x) {
    center_x_ = center_x;
    return *this;
  }


  coordinate_type y() const {
    return center_y_;
  }


  circle_event& y(coordinate_type center_y) {
    center_y_ = center_y;
    return *this;
  }


  coordinate_type lower_x() const {
    return lower_x_;
  }


  circle_event& lower_x(coordinate_type lower_x) {
    lower_x_ = lower_x;
    return *this;
  }


  coordinate_type lower_y() const {
    return center_y_;
  }


  bool is_active() const {
    return is_active_;
  }


  circle_event& deactivate() {
    is_active_ = false;
    return *this;
  }

  ordered_queue() {}


  bool empty() const {
    return c_.empty();
  }


  const T &top() const {
    return *c_.top();
  }


  void pop() {
    list_iterator_type it = c_.top();
    c_.pop();
    c_list_.erase(it);
  }


  T &push(const T &e) {
    c_list_.push_front(e);
    c_.push(c_list_.begin());
    return c_list_.front();
  }


  void clear() {
    while (!c_.empty())
        c_.pop();
    c_list_.clear();
  }

    bool operator() (const list_iterator_type &it1,
                     const list_iterator_type &it2) const {
      return cmp_(*it1, *it2);
    }

  explicit beach_line_node_key(const site_type &new_site) :
      left_site_(new_site),
      right_site_(new_site) {}

  beach_line_node_key(const site_type &left_site,
                      const site_type &right_site) :
      left_site_(left_site),
      right_site_(right_site) {}


  const site_type &left_site() const {
    return left_site_;
  }


  site_type &left_site() {
    return left_site_;
  }


  beach_line_node_key& left_site(const site_type &site) {
    left_site_ = site;
    return *this;
  }


  const site_type &right_site() const {
    return right_site_;
  }


  site_type &right_site() {
    return right_site_;
  }


  beach_line_node_key& right_site(const site_type &site) {
    right_site_ = site;
    return *this;
  }

  explicit beach_line_node_data(Edge* new_edge) :
      circle_event_(NULL),
      edge_(new_edge) {}


  Circle* circle_event() const {
    return circle_event_;
  }


  beach_line_node_data& circle_event(Circle* circle_event) {
    circle_event_ = circle_event;
    return *this;
  }


  Edge* edge() const {
    return edge_;
  }


  beach_line_node_data& edge(Edge* new_edge) {
    edge_ = new_edge;
    return *this;
  }


  voronoi_builder() : index_(0) {}

  std::size_t insert_point(const int_type& x, const int_type& y) {
    site_events_.push_back(site_event_type(x, y));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SINGLE_POINT);
    return index_++;
  }

  std::size_t insert_segment(
      const int_type& x1, const int_type& y1,
      const int_type& x2, const int_type& y2) {
    // Set up start point site.
    point_type p1(x1, y1);
    site_events_.push_back(site_event_type(p1));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SEGMENT_START_POINT);

    // Set up end point site.
    point_type p2(x2, y2);
    site_events_.push_back(site_event_type(p2));
    site_events_.back().initial_index(index_);
    site_events_.back().source_category(SOURCE_CATEGORY_SEGMENT_END_POINT);

    // Set up segment site.
    if (point_comparison_(p1, p2)) {
      site_events_.push_back(site_event_type(p1, p2));
      site_events_.back().source_category(SOURCE_CATEGORY_INITIAL_SEGMENT);
    } else {
      site_events_.push_back(site_event_type(p2, p1));
      site_events_.back().source_category(SOURCE_CATEGORY_REVERSE_SEGMENT);
    }
    site_events_.back().initial_index(index_);
    return index_++;
  }

  template <typename OUTPUT>
  void construct(OUTPUT* output) {
    // Init structures.
    output->_reserve(site_events_.size());
    init_sites_queue();
    init_beach_line(output);

    // The algorithm stops when there are no events to process.
    event_comparison_predicate event_comparison;
    while (!circle_events_.empty() ||
           !(site_event_iterator_ == site_events_.end())) {
      if (circle_events_.empty()) {
        process_site_event(output);
      } else if (site_event_iterator_ == site_events_.end()) {
        process_circle_event(output);
      } else {
        if (event_comparison(*site_event_iterator_,
                             circle_events_.top().first)) {
          process_site_event(output);
        } else {
          process_circle_event(output);
        }
      }
      while (!circle_events_.empty() &&
             !circle_events_.top().first.is_active()) {
        circle_events_.pop();
      }
    }
    beach_line_.clear();

    // Finish construction.
    output->_build();
  }


  void clear() {
    index_ = 0;
    site_events_.clear();
  }

    bool operator()(const event_type& lhs, const event_type& rhs) const {
      return predicate(rhs.first, lhs.first);
    }

    bool operator()(const event_type& lhs, const event_type& rhs) const {
      return predicate(rhs.first, lhs.first);
    }


  void init_sites_queue() {
    // Sort site events.
    std::sort(site_events_.begin(), site_events_.end(),
        event_comparison_predicate());

    // Remove duplicates.
    site_events_.erase(std::unique(
        site_events_.begin(), site_events_.end()), site_events_.end());

    // Index sites.
    for (std::size_t cur = 0; cur < site_events_.size(); ++cur) {
      site_events_[cur].sorted_index(cur);
    }

    // Init site iterator.
    site_event_iterator_ = site_events_.begin();
  }


  template <typename OUTPUT>
  void init_beach_line(OUTPUT* output) {
    if (site_events_.empty())
      return;
    if (site_events_.size() == 1) {
      // Handle single site event case.
      output->_process_single_site(site_events_[0]);
      ++site_event_iterator_;
    } else {
      int skip = 0;

      while (site_event_iterator_ != site_events_.end() &&
             VP::is_vertical(site_event_iterator_->point0(),
                             site_events_.begin()->point0()) &&
             VP::is_vertical(*site_event_iterator_)) {
        ++site_event_iterator_;
        ++skip;
      }

      if (skip == 1) {
        // Init beach line with the first two sites.
        init_beach_line_default(output);
      } else {
        // Init beach line with collinear vertical sites.
        init_beach_line_collinear_sites(output);
      }
    }
  }

  template <typename OUTPUT>
  void init_beach_line_default(OUTPUT* output) {
    // Get the first and the second site event.
    site_event_iterator_type it_first = site_events_.begin();
    site_event_iterator_type it_second = site_events_.begin();
    ++it_second;
    insert_new_arc(
        *it_first, *it_first, *it_second, beach_line_.end(), output);
    // The second site was already processed. Move the iterator.
    ++site_event_iterator_;
  }

  template <typename OUTPUT>
  void init_beach_line_collinear_sites(OUTPUT* output) {
    site_event_iterator_type it_first = site_events_.begin();
    site_event_iterator_type it_second = site_events_.begin();
    ++it_second;
    while (it_second != site_event_iterator_) {
      // Create a new beach line node.
      key_type new_node(*it_first, *it_second);

      // Update the output.
      edge_type* edge = output->_insert_new_edge(*it_first, *it_second).first;

      // Insert a new bisector into the beach line.
      beach_line_.insert(beach_line_.end(),
          std::pair<key_type, value_type>(new_node, value_type(edge)));

      // Update iterators.
      ++it_first;
      ++it_second;
    }
  }


  void deactivate_circle_event(value_type* value) {
    if (value->circle_event()) {
      value->circle_event()->deactivate();
      value->circle_event(NULL);
    }
  }


  template <typename OUTPUT>
  void process_site_event(OUTPUT* output) {
    // Get next site event to process.
    site_event_type site_event = *site_event_iterator_;

    // Move site iterator.
    site_event_iterator_type last = site_event_iterator_ + 1;

    // If a new site is an end point of some segment,
    // remove temporary nodes from the beach line data structure.
    if (!site_event.is_segment()) {
      while (!end_points_.empty() &&
             end_points_.top().first == site_event.point0()) {
        beach_line_iterator b_it = end_points_.top().second;
        end_points_.pop();
        beach_line_.erase(b_it);
      }
    } else {
      while (last != site_events_.end() &&
             last->is_segment() && last->point0() == site_event.point0())
        ++last;
    }

    // Find the node in the binary search tree with left arc
    // lying above the new site point.
    key_type new_key(*site_event_iterator_);
    beach_line_iterator right_it = beach_line_.lower_bound(new_key);

    for (; site_event_iterator_ != last; ++site_event_iterator_) {
      site_event = *site_event_iterator_;
      beach_line_iterator left_it = right_it;

      // Do further processing depending on the above node position.
      // For any two neighboring nodes the second site of the first node
      // is the same as the first site of the second node.
      if (right_it == beach_line_.end()) {
        // The above arc corresponds to the second arc of the last node.
        // Move the iterator to the last node.
        --left_it;

        // Get the second site of the last node
        const site_event_type& site_arc = left_it->first.right_site();

        // Insert new nodes into the beach line. Update the output.
        right_it = insert_new_arc(
            site_arc, site_arc, site_event, right_it, output);

        // Add a candidate circle to the circle event queue.
        // There could be only one new circle event formed by
        // a new bisector and the one on the left.
        activate_circle_event(left_it->first.left_site(),
                              left_it->first.right_site(),
                              site_event, right_it);
      } else if (right_it == beach_line_.begin()) {
        // The above arc corresponds to the first site of the first node.
        const site_event_type& site_arc = right_it->first.left_site();

        // Insert new nodes into the beach line. Update the output.
        left_it = insert_new_arc(
            site_arc, site_arc, site_event, right_it, output);

        // If the site event is a segment, update its direction.
        if (site_event.is_segment()) {
          site_event.inverse();
        }

        // Add a candidate circle to the circle event queue.
        // There could be only one new circle event formed by
        // a new bisector and the one on the right.
        activate_circle_event(site_event, right_it->first.left_site(),
            right_it->first.right_site(), right_it);
        right_it = left_it;
      } else {
        // The above arc corresponds neither to the first,
        // nor to the last site in the beach line.
        const site_event_type& site_arc2 = right_it->first.left_site();
        const site_event_type& site3 = right_it->first.right_site();

        // Remove the candidate circle from the event queue.
        deactivate_circle_event(&right_it->second);
        --left_it;
        const site_event_type& site_arc1 = left_it->first.right_site();
        const site_event_type& site1 = left_it->first.left_site();

        // Insert new nodes into the beach line. Update the output.
        beach_line_iterator new_node_it =
            insert_new_arc(site_arc1, site_arc2, site_event, right_it, output);

        // Add candidate circles to the circle event queue.
        // There could be up to two circle events formed by
        // a new bisector and the one on the left or right.
        activate_circle_event(site1, site_arc1, site_event, new_node_it);

        // If the site event is a segment, update its direction.
        if (site_event.is_segment()) {
          site_event.inverse();
        }
        activate_circle_event(site_event, site_arc2, site3, right_it);
        right_it = new_node_it;
      }
    }
  }

  template <typename OUTPUT>
  void process_circle_event(OUTPUT* output) {
    // Get the topmost circle event.
    const event_type& e = circle_events_.top();
    const circle_event_type& circle_event = e.first;
    beach_line_iterator it_first = e.second;
    beach_line_iterator it_last = it_first;

    // Get the C site.
    site_event_type site3 = it_first->first.right_site();

    // Get the half-edge corresponding to the second bisector - (B, C).
    edge_type* bisector2 = it_first->second.edge();

    // Get the half-edge corresponding to the first bisector - (A, B).
    --it_first;
    edge_type* bisector1 = it_first->second.edge();

    // Get the A site.
    site_event_type site1 = it_first->first.left_site();

    if (!site1.is_segment() && site3.is_segment() &&
        site3.point1(true) == site1.point0()) {
      site3.inverse();
    }

    // Change the (A, B) bisector node to the (A, C) bisector node.
    const_cast<key_type&>(it_first->first).right_site(site3);

    // Insert the new bisector into the beach line.
    it_first->second.edge(output->_insert_new_edge(
        site1, site3, circle_event, bisector1, bisector2).first);

    // Remove the (B, C) bisector node from the beach line.
    beach_line_.erase(it_last);
    it_last = it_first;

    // Pop the topmost circle event from the event queue.
    circle_events_.pop();

    // Check new triplets formed by the neighboring arcs
    // to the left for potential circle events.
    if (it_first != beach_line_.begin()) {
      deactivate_circle_event(&it_first->second);
      --it_first;
      const site_event_type& site_l1 = it_first->first.left_site();
      activate_circle_event(site_l1, site1, site3, it_last);
    }

    // Check the new triplet formed by the neighboring arcs
    // to the right for potential circle events.
    ++it_last;
    if (it_last != beach_line_.end()) {
      deactivate_circle_event(&it_last->second);
      const site_event_type& site_r1 = it_last->first.right_site();
      activate_circle_event(site1, site3, site_r1, it_last);
    }
  }

  template <typename OUTPUT>
  beach_line_iterator insert_new_arc(
      const site_event_type& site_arc1, const site_event_type &site_arc2,
      const site_event_type& site_event, beach_line_iterator position,
      OUTPUT* output) {
    // Create two new bisectors with opposite directions.
    key_type new_left_node(site_arc1, site_event);
    key_type new_right_node(site_event, site_arc2);

    // Set correct orientation for the first site of the second node.
    if (site_event.is_segment()) {
      new_right_node.left_site().inverse();
    }

    // Update the output.
    std::pair<edge_type*, edge_type*> edges =
        output->_insert_new_edge(site_arc2, site_event);
    position = beach_line_.insert(position,
        typename beach_line_type::value_type(
            new_right_node, value_type(edges.second)));

    if (site_event.is_segment()) {
      // Update the beach line with temporary bisector, that will
      // disappear after processing site event corresponding to the
      // second endpoint of the segment site.
      key_type new_node(site_event, site_event);
      new_node.right_site().inverse();
      position = beach_line_.insert(position,
          typename beach_line_type::value_type(new_node, value_type(NULL)));

      // Update the data structure that holds temporary bisectors.
      end_points_.push(std::make_pair(site_event.point1(), position));
    }

    position = beach_line_.insert(position,
        typename beach_line_type::value_type(
            new_left_node, value_type(edges.first)));

    return position;
  }

  void activate_circle_event(const site_event_type& site1,
                             const site_event_type& site2,
                             const site_event_type& site3,
                             beach_line_iterator bisector_node) {
    circle_event_type c_event;
    // Check if the three input sites create a circle event.
    if (circle_formation_predicate_(site1, site2, site3, c_event)) {
      // Add the new circle event to the circle events queue.
      // Update bisector's circle event iterator to point to the
      // new circle event in the circle event queue.
      event_type& e = circle_events_.push(
          std::pair<circle_event_type, beach_line_iterator>(
              c_event, bisector_node));
      bisector_node->second.circle_event(&e.first);
    }
  }

    bool operator() (const end_point_type& end1,
                     const end_point_type& end2) const {
      return point_comparison(end2.first, end1.first);
    }


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  inline polygon_90_data() : coords_() {}

  template<class iT>
  inline polygon_90_data& set(iT begin_point, iT end_point) {
    return set_compact(iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(begin_point, end_point),
                       iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(end_point, end_point));
  }


  template<class iT>
  inline polygon_90_data& set_compact(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    while(input_begin != input_end) {
       coords_.insert(coords_.end(), *input_begin);
       ++input_begin;
    }
    return *this;
  }

  inline polygon_90_data(const polygon_90_data& that) : coords_(that.coords_) {}

  inline polygon_90_data& operator=(const polygon_90_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  inline bool operator==(const polygon_90_data& that) const {
    return coords_ == that.coords_;
  }

  inline iterator_type begin() const { return iterator_type(coords_.begin(), coords_.end()); }

  inline iterator_type end() const { return iterator_type(coords_.end(), coords_.end()); }

  inline compact_iterator_type begin_compact() const { return coords_.begin(); }

  inline compact_iterator_type end_compact() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }

  inline polygon_90_with_holes_data() : self_(), holes_() {}

  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }

  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }


  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }


  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}


  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }


  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }


  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }


  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }


  coordinate_type low() const {
    return coords_[0];
  }


  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }


  coordinate_type high() const {
    return coords_[1];
  }


  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }


  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }


  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }


  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }


  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }


  bool operator>(const interval_data& that) const {
    return that < *this;
  }


  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  static coordinate_type get(
      const point_type& point, orientation_2d orient) {
    return point.get(orient);
  }


  static void set(
      point_type& point, orientation_2d orient, coordinate_type value) {
    point.set(orient, value);
  }


  static point_type construct(coordinate_type x, coordinate_type y) {
    return point_type(x, y);
  }


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_get,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type get(const PointType& point, orientation_2d orient) {
  return point_traits<PointType>::get(point, orient);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_set,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  void
>::type set(PointType& point, orientation_2d orient,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  point_mutable_traits<PointType>::set(point, orient, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_construct,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type construct(
    typename point_mutable_traits<PointType>::coordinate_type x,
    typename point_mutable_traits<PointType>::coordinate_type y) {
  return point_mutable_traits<PointType>::construct(x, y);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_assign,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
>::type,
PointType1>::type& assign(PointType1& lvalue, const PointType2& rvalue) {
  set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
  set(lvalue, VERTICAL, get(rvalue, VERTICAL));
  return lvalue;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_x,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type x(const PointType& point) {
  return get(point, HORIZONTAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_y,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type y(const PointType& point) {
  return get(point, VERTICAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sx,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type x(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, HORIZONTAL, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sy,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type y(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, VERTICAL, value);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_equiv,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
bool>::type equivalence(
    const PointType1& point1, const PointType2& point2) {
  return (x(point1) == x(point2)) && (y(point1) == y(point2));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_man_dist,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
manhattan_distance(const PointType1& point1, const PointType2& point2) {
  return euclidean_distance(point1, point2, HORIZONTAL) +
         euclidean_distance(point1, point2, VERTICAL);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed1,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
euclidean_distance(
    const PointType1& point1,
    const PointType2& point2,
    orientation_2d orient) {
  typename point_difference_type<PointType1>::type dif =
      get(point1, orient) - get(point2, orient);
  return (dif < 0) ? -dif : dif;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_eds,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
distance_squared(const PointType1& point1, const PointType2& point2) {
  typename point_difference_type<PointType1>::type dx =
      euclidean_distance(point1, point2, HORIZONTAL);
  typename point_difference_type<PointType1>::type dy =
      euclidean_distance(point1, point2, VERTICAL);
  dx *= dx;
  dy *= dy;
  return dx + dy;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed2,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_distance_type<PointType1>::type>::type
euclidean_distance(const PointType1& point1, const PointType2& point2) {
  return (std::sqrt)(
      static_cast<double>(distance_squared(point1, point2)));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_convolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& convolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) + x(rvalue));
  y(lvalue, y(lvalue) + y(rvalue));
  return lvalue;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_deconvolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& deconvolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) - x(rvalue));
  y(lvalue, y(lvalue) - y(rvalue));
  return lvalue;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_up,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_up(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  x(point, x(point) * (Unit)factor);
  y(point, y(point) * (Unit)factor);
  return point;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_down,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_down(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  typedef typename coordinate_traits<Unit>::coordinate_distance dt;
  x(point, scaling_policy<Unit>::round((dt)(x(point)) / (dt)factor));
  y(point, scaling_policy<Unit>::round((dt)(y(point)) / (dt)factor));
  return point;
}


template <typename PointType, typename ScaleType>
typename enable_if<
  typename gtl_and<
    y_pt_scale,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale(PointType& point, const ScaleType& scaling) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  scaling.scale(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType, typename TransformType>
typename enable_if<
  typename gtl_and<
    y_pt_transform,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& transform(PointType& point, const TransformType& transform) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  transform.transform(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_move,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& move(PointType& point, orientation_2d orient,
    typename point_coordinate_type<PointType>::type displacement) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit coord = get(point, orient);
  set(point, orient, coord + displacement);
  return point;
}


  axis_transformation() : atr_(NULL_TRANSFORM) {}

  explicit axis_transformation(ATR atr) : atr_(atr) {}

  axis_transformation(const axis_transformation& atr) : atr_(atr.atr_) {}


  explicit axis_transformation(const orientation_2d& orient) {
    const ATR tmp[2] = {
      NORTH_EAST,  // sort x, then y
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[orient.to_int()];
  }


  explicit axis_transformation(const direction_2d& dir) {
    const ATR tmp[4] = {
      SOUTH_EAST,  // sort x, then y
      NORTH_EAST,  // sort x, then y
      EAST_SOUTH,  // sort y, then x
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[dir.to_int()];
  }

  axis_transformation& operator=(const axis_transformation& a) {
    atr_ = a.atr_;
    return *this;
  }

  axis_transformation& operator=(const ATR& atr) {
    atr_ = atr;
    return *this;
  }

  bool operator==(const axis_transformation& a) const {
    return atr_ == a.atr_;
  }

  bool operator!=(const axis_transformation& a) const {
    return !(*this == a);
  }

  bool operator<(const axis_transformation& a) const {
    return atr_ < a.atr_;
  }

  axis_transformation& operator+=(const axis_transformation& a) {
    bool abit2 = (a.atr_ & 4) != 0;
    bool abit1 = (a.atr_ & 2) != 0;
    bool abit0 = (a.atr_ & 1) != 0;
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    int indexes[2][2] = {
      { (int)bit2, (int)(!bit2) },
      { (int)abit2, (int)(!abit2) }
    };
    int zero_bits[2][2] = {
      {bit0, bit1}, {abit0, abit1}
    };
    int nbit1 = zero_bits[0][1] ^ zero_bits[1][indexes[0][1]];
    int nbit0 = zero_bits[0][0] ^ zero_bits[1][indexes[0][0]];
    indexes[0][0] = indexes[1][indexes[0][0]];
    indexes[0][1] = indexes[1][indexes[0][1]];
    int nbit2 = indexes[0][0] & 1;  // swap xy
    atr_ = (ATR)((nbit2 << 2) + (nbit1 << 1) + nbit0);
    return *this;
  }

  axis_transformation operator+(const axis_transformation& a) const {
    axis_transformation retval(*this);
    return retval+=a;
  }

  void populate_axis_array(INDIVIDUAL_AXIS axis_array[]) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    axis_array[1] = (INDIVIDUAL_AXIS)(((int)(!bit2) << 1) + bit1);
    axis_array[0] = (INDIVIDUAL_AXIS)(((int)(bit2) << 1) + bit0);
  }

  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    vertical_dir = direction_2d((direction_2d_enum)(((int)(!bit2) << 1) + !bit1));
    horizontal_dir = direction_2d((direction_2d_enum)(((int)(bit2) << 1) + !bit0));
  }

  static void combine_axis_arrays(INDIVIDUAL_AXIS this_array[],
                                  const INDIVIDUAL_AXIS that_array[]) {
    int indexes[2] = { this_array[0] >> 1, this_array[1] >> 1 };
    int zero_bits[2][2] = {
      { this_array[0] & 1, this_array[1] & 1 },
      { that_array[0] & 1, that_array[1] & 1 }
    };
    this_array[0] = (INDIVIDUAL_AXIS)((int)this_array[0] |
                                      ((int)zero_bits[0][0] ^
                                       (int)zero_bits[1][indexes[0]]));
    this_array[1] = (INDIVIDUAL_AXIS)((int)this_array[1] |
                                      ((int)zero_bits[0][1] ^
                                       (int)zero_bits[1][indexes[1]]));
  }

  void write_back_axis_array(const INDIVIDUAL_AXIS this_array[]) {
    int bit2 = ((int)this_array[0] & 2) != 0;  // swap xy
    int bit1 = ((int)this_array[1] & 1);
    int bit0 = ((int)this_array[0] & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
  }

  axis_transformation& set_directions(const direction_2d& horizontal_dir,
                                      const direction_2d& vertical_dir) {
    int bit2 = (static_cast<orientation_2d>(horizontal_dir).to_int()) != 0;
    int bit1 = !(vertical_dir.to_int() & 1);
    int bit0 = !(horizontal_dir.to_int() & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
    return *this;
  }

  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y) const {
    int bit2 = (atr_ & 4) != 0;
    int bit1 = (atr_ & 2) != 0;
    int bit0 = (atr_ & 1) != 0;
    x *= -((bit0 << 1) - 1);
    y *= -((bit1 << 1) - 1);
    predicated_swap(bit2 != 0, x, y);
  }

  axis_transformation& invert() {
    int bit2 = ((atr_ & 4) != 0);
    int bit1 = ((atr_ & 2) != 0);
    int bit0 = ((atr_ & 1) != 0);
    // swap bit 0 and bit 1 if bit2 is 1
    predicated_swap(bit2 != 0, bit0, bit1);
    bit1 = bit1 << 1;
    atr_ = (ATR)(atr_ & (32+16+8+4));  // mask away bit0 and bit1
    atr_ = (ATR)(atr_ | bit0 | bit1);
    return *this;
  }

  axis_transformation inverse() const {
    axis_transformation retval(*this);
    return retval.invert();
  }

  anisotropic_scale_factor() {
    scale_[0] = 1;
    scale_[1] = 1;
  }

  anisotropic_scale_factor(scale_factor_type xscale,
                           scale_factor_type yscale) {
    scale_[0] = xscale;
    scale_[1] = yscale;
  }

  scale_factor_type get(orientation_2d orient) const {
    return scale_[orient.to_int()];
  }

  void set(orientation_2d orient, scale_factor_type value) {
    scale_[orient.to_int()] = value;
  }


  scale_factor_type x() const {
    return scale_[HORIZONTAL];
  }


  scale_factor_type y() const {
    return scale_[VERTICAL];
  }


  void x(scale_factor_type value) {
    scale_[HORIZONTAL] = value;
  }


  void y(scale_factor_type value) {
    scale_[VERTICAL] = value;
  }

  anisotropic_scale_factor operator+(const anisotropic_scale_factor& s) const {
    anisotropic_scale_factor<scale_factor_type> retval(*this);
    return retval += s;
  }

  const anisotropic_scale_factor& operator+=(
      const anisotropic_scale_factor& s) {
    scale_[0] *= s.scale_[0];
    scale_[1] *= s.scale_[1];
    return *this;
  }

  anisotropic_scale_factor& transform(axis_transformation atr) {
    direction_2d dirs[2];
    atr.get_directions(dirs[0], dirs[1]);
    scale_factor_type tmp[2] = {scale_[0], scale_[1]};
    for (int i = 0; i < 2; ++i) {
      scale_[orientation_2d(dirs[i]).to_int()] = tmp[i];
    }
    return *this;
  }

  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y) const {
    x = scaling_policy<coordinate_type>::round(
        (scale_factor_type)x * get(HORIZONTAL));
    y = scaling_policy<coordinate_type>::round(
        (scale_factor_type)y * get(HORIZONTAL));
  }

  anisotropic_scale_factor& invert() {
    x(1/x());
    y(1/y());
    return *this;
  }

  transformation() : atr_(), p_(0, 0) {}

  explicit transformation(axis_transformation atr) : atr_(atr), p_(0, 0) {}

  explicit transformation(axis_transformation::ATR atr) : atr_(atr), p_(0, 0) {}

  transformation(const transformation& tr) : atr_(tr.atr_), p_(tr.p_) {}


  template <typename point_type>
  explicit transformation(const point_type& p) : atr_(), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& p) : atr_(atr), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& referencePt,
                 const point_type& destinationPt) : atr_(), p_(0, 0) {
    transformation<coordinate_type> tmp(referencePt);
    transformation<coordinate_type> rotRef(atr);
    transformation<coordinate_type> tmpInverse = tmp.inverse();
    point_type decon(referencePt);
    deconvolve(decon, destinationPt);
    transformation<coordinate_type> displacement(decon);
    tmp += rotRef;
    tmp += tmpInverse;
    tmp += displacement;
    (*this) = tmp;
  }

  bool operator==(const transformation& tr) const {
    return (atr_ == tr.atr_) && (p_ == tr.p_);
  }

  bool operator!=(const transformation& tr) const {
    return !(*this == tr);
  }

  bool operator<(const transformation& tr) const {
    return (atr_ < tr.atr_) || ((atr_ == tr.atr_) && (p_ < tr.p_));
  }

  transformation operator+(const transformation& tr) const {
    transformation<coordinate_type> retval(*this);
    return retval+=tr;
  }

  const transformation& operator+=(const transformation& tr) {
    coordinate_type x, y;
    transformation<coordinate_type> inv = inverse();
    inv.transform(x, y);
    p_.set(HORIZONTAL, p_.get(HORIZONTAL) + x);
    p_.set(VERTICAL, p_.get(VERTICAL) + y);
    // concatenate axis transforms
    atr_ += tr.atr_;
    return *this;
  }

  axis_transformation get_axis_transformation() const {
    return atr_;
  }

  void set_axis_transformation(const axis_transformation& atr) {
    atr_ = atr;
  }

  template <typename point_type>
  void get_translation(point_type& p) const {
    assign(p, p_);
  }

  template <typename point_type>
  void set_translation(const point_type& p) {
    assign(p_, p);
  }

  void transform(coordinate_type& x, coordinate_type& y) const {
    y -= p_.get(VERTICAL);
    x -= p_.get(HORIZONTAL);
    atr_.transform(x, y);
  }

  transformation& invert() {
    coordinate_type x = p_.get(HORIZONTAL), y = p_.get(VERTICAL);
    atr_.transform(x, y);
    x *= -1;
    y *= -1;
    p_ = point_data<coordinate_type>(x, y);
    atr_.invert();
    return *this;
  }

  transformation inverse() const {
    transformation<coordinate_type> ret_val(*this);
    return ret_val.invert();
  }


  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    return atr_.get_directions(horizontal_dir, vertical_dir);
  }


  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }


  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }


  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}


  point_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  point_data(coordinate_type x, coordinate_type y) {
    coords_[HORIZONTAL] = x;
    coords_[VERTICAL] = y;
  }


  explicit point_data(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  point_data& operator=(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename PointType>
  explicit point_data(const PointType& that) {
    *this = that;
  }


  template <typename PointType>
  point_data& operator=(const PointType& that) {
    assign(*this, that);
    return *this;
  }

  template <typename CT>
  point_data(const point_data<CT>& that) {
    coords_[HORIZONTAL] = (coordinate_type)that.x();
    coords_[VERTICAL] = (coordinate_type)that.y();
  }


  coordinate_type get(orientation_2d orient) const {
    return coords_[orient.to_int()];
  }


  void set(orientation_2d orient, coordinate_type value) {
    coords_[orient.to_int()] = value;
  }


  coordinate_type x() const {
    return coords_[HORIZONTAL];
  }


  point_data& x(coordinate_type value) {
    coords_[HORIZONTAL] = value;
    return *this;
  }


  coordinate_type y() const {
    return coords_[VERTICAL];
  }


  point_data& y(coordinate_type value) {
    coords_[VERTICAL] = value;
    return *this;
  }


  bool operator==(const point_data& that) const {
    return (coords_[0] == that.coords_[0]) &&
      (coords_[1] == that.coords_[1]);
  }


  bool operator!=(const point_data& that) const {
    return !(*this == that);
  }


  bool operator<(const point_data& that) const {
    return (coords_[0] < that.coords_[0]) ||
      ((coords_[0] == that.coords_[0]) &&
       (coords_[1] < that.coords_[1]));
  }


  bool operator<=(const point_data& that) const {
    return !(that < *this);
  }


  bool operator>(const point_data& that) const {
    return that < *this;
  }


  bool operator>=(const point_data& that) const {
    return !(*this < that);
  }


  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }


  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }


  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }


  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }


  coordinate_type low() const {
    return coords_[0];
  }


  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }


  coordinate_type high() const {
    return coords_[1];
  }


  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }


  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }


  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }


  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }


  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }


  bool operator>(const interval_data& that) const {
    return that < *this;
  }


  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

  inline rectangle_data():ranges_() {}

  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }

  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }


  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }

  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }

  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }


  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }

  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }

  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }

    static inline interval_type get(const T& rectangle, orientation_2d orient) {
      return rectangle.get(orient); }

    template <typename T2>
    static inline void set(T& rectangle, orientation_2d orient, const T2& interval) {
      rectangle.set(orient, interval); }

    template <typename T2, typename T3>
    static inline T construct(const T2& interval_horizontal,
                              const T3& interval_vertical) {
      return T(interval_horizontal, interval_vertical); }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_get_interval, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                      typename rectangle_interval_type<T>::type>::type
  get(const T& rectangle, orientation_2d orient) {
    return rectangle_traits<T>::get(rectangle, orient);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_h, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  horizontal(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, HORIZONTAL);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_v, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  vertical(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, VERTICAL);
  }


  template <orientation_2d_enum orient, typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, orientation_2d orient, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_h2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  horizontal(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, HORIZONTAL, interval);
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_v2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                     typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type, void>::type
  vertical(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, VERTICAL, interval);
  }


  template <typename T, typename T2, typename T3>
  typename enable_if< typename gtl_and<y_r_construct, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(const T2& interval_horizontal,
            const T3& interval_vertical) {
    return rectangle_mutable_traits<T>::construct(interval_horizontal, interval_vertical); }


  template <typename T, typename coord_type>
  typename enable_if< typename gtl_and<y_r_construct2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(coord_type xl, coord_type yl, coord_type xh, coord_type yh) {
    return rectangle_mutable_traits<T>::construct(interval_data<coord_type>(xl, xh),
                                                  interval_data<coord_type>(yl, yh));
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_cconstruct,
      typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    T>::type
  copy_construct(const T2& rectangle) {
    return construct<T> (get(rectangle, HORIZONTAL), get(rectangle, VERTICAL));
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_assign,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  assign(rectangle_type_1& lvalue, const rectangle_type_2& rvalue) {
    set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
    set(lvalue, VERTICAL, get(rvalue, VERTICAL));
    return lvalue;
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3< y_r_equiv,
      typename is_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    bool>::type
  equivalence(const T& rect1, const T2& rect2) {
    return equivalence(get(rect1, HORIZONTAL), get(rect2, HORIZONTAL)) &&
      equivalence(get(rect1, VERTICAL), get(rect2, VERTICAL));
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_get, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  get(const rectangle_type& rectangle, orientation_2d orient, direction_1d dir) {
    return get(rectangle_traits<rectangle_type>::get(rectangle, orient), dir);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_set3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  set(rectangle_type& rectangle, orientation_2d orient, direction_1d dir,
      typename rectangle_coordinate_type<rectangle_type>::type value) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    set(ivl, dir, value);
    set(rectangle, orient, ivl);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xl(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      xl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xh(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  xh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yl(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yh(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ll,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ll(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_lr,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  lr(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ul,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ul(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yh(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ur,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ur(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yh(rectangle));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_contains, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  contains(const rectangle_type& rectangle, const rectangle_type_2 rectangle_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), horizontal(rectangle_contained), consider_touch) &&
      contains(vertical(rectangle), vertical(rectangle_contained), consider_touch);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_contains2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, bool>::type
  contains(const rectangle_type& rectangle, const point_type point_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), x(point_contained), consider_touch) &&
      contains(vertical(rectangle), y(point_contained), consider_touch);
  }

  template <typename rectangle_type, typename point_type_1, typename point_type_2>
  typename enable_if< typename gtl_and_4< y_r_set_points,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_1>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_2>::type>::type>::type,
                       rectangle_type>::type &
  set_points(rectangle_type& rectangle, const point_type_1& p1,
             const point_type_2& p2) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit x1(x(p1));
    Unit x2(x(p2));
    Unit y1(y(p1));
    Unit y2(y(p2));
    horizontal(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(x1, x2));
    vertical(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(y1, y2));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_move, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  move(rectangle_type& rectangle, orientation_2d orient,
       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference delta) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    move(ivl, delta);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_convolve,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  convolve(rectangle_type_1& rectangle,
           const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3< y_r_deconvolve,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_reconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_convolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_redeconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_convolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       rectangle_type>::type &
  convolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_deconvolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, rectangle_type>::type &
  deconvolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_delta, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  delta(const rectangle_type& rectangle, orientation_2d orient) {
    return delta(get(rectangle, orient));
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_area, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type>::type
  area(const rectangle_type& rectangle) {
    typedef typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type area_type;
    return (area_type)delta(rectangle, HORIZONTAL) * (area_type)delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_go, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      orientation_2d>::type
  guess_orientation(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) >= delta(rectangle, VERTICAL) ?
      HORIZONTAL : VERTICAL;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_half_p, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  half_perimeter(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) + delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_perimeter, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  perimeter(const rectangle_type& rectangle) {
    return 2 * half_perimeter(rectangle);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_intersects, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  intersects(const rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    return intersects(horizontal(rectangle), horizontal(b), consider_touch) &&
      intersects(vertical(rectangle), vertical(b), consider_touch);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  boundaries_intersect(const rectangle_type_1& rectangle, const rectangle_type_2& b,
                       bool consider_touch = true) {
    return (intersects(rectangle, b, consider_touch) &&
            !(contains(rectangle, b, !consider_touch)) &&
            !(contains(b, rectangle, !consider_touch)));
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        direction_2d dir) {
    return
      abuts(get(rectangle, orientation_2d(dir)),
            get(b, orientation_2d(dir)),
            direction_1d(dir)) &&
      intersects(get(rectangle, orientation_2d(dir).get_perpendicular()),
                 get(b, orientation_2d(dir).get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts2, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        orientation_2d orient) {
    return
      abuts(get(rectangle, orient), get(b, orient)) &&
      intersects(get(rectangle, orient.get_perpendicular()),
                 get(b, orient.get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts3, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b) {
    return abuts(rectangle, b, HORIZONTAL) || abuts(rectangle, b, VERTICAL);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
    bool>::type
  intersect(rectangle_type& rectangle, const interval_type& b,
            orientation_2d orient, bool consider_touch = true) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(intersect(ivl, b, consider_touch)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_intersect3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  intersect(rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    if(intersects(rectangle, b)) {
      intersect(rectangle, horizontal(b), HORIZONTAL, consider_touch);
      intersect(rectangle, vertical(b), VERTICAL, consider_touch);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_g_intersect,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  generalized_intersect(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = get(rectangle, HORIZONTAL);
    generalized_intersect(ivl, horizontal(b));
    horizontal(rectangle, ivl);
    ivl = vertical(rectangle);
    generalized_intersect(ivl, vertical(b));
    vertical(rectangle, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, orientation_2d orient,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    bloat(ivl, bloating);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    bloat(rectangle, HORIZONTAL, bloating);
    return bloat(rectangle, VERTICAL, bloating);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, direction_2d dir,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orientation_2d(dir));
    bloat(ivl, direction_1d(dir), bloating);
    set(rectangle, orientation_2d(dir), ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, orientation_2d orient,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, orient, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, direction_2d dir,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, dir, -shrinking);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
        typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type& rectangle, const interval_type& b, orientation_2d orient) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(encompass(ivl, b)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<
        y_r_encompass2,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type >::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    //note that operator | is intentional because both should be called regardless
    return encompass(rectangle, horizontal(b), HORIZONTAL) |
      encompass(rectangle, vertical(b), VERTICAL);
  }

  template <typename rectangle_type_1, typename point_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass3,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const point_type& b) {
    typename rectangle_interval_type<rectangle_type_1>::type hivl, vivl;
    hivl = horizontal(rectangle);
    vivl = vertical(rectangle);
    //note that operator | is intentional because both should be called regardless
    bool retval = encompass(hivl, x(b)) | encompass(vivl, y(b));
    if(retval) {
      horizontal(rectangle, hivl);
      vertical(rectangle, vivl);
    }
    return retval;
  }

  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_center, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  center(point_type& center_point, const rectangle_type& rectangle) {
    center_point = construct<point_type>(center(horizontal(rectangle)),
                                         center(vertical(rectangle)));
    return true;
  }


  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_get_corner, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  get_corner(point_type& corner_point, const rectangle_type& rectangle, direction_2d direction_facing, direction_1d direction_turning) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit u1 = get(rectangle, direction_facing);
    Unit u2 = get(rectangle, direction_facing.turn(direction_turning));
    if(orientation_2d(direction_facing).to_int()) std::swap(u1, u2);
    corner_point = construct<point_type>(u1, u2);
    return true;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_get_half, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type
  get_half(const rectangle_type& rectangle, direction_2d dir) {
    rectangle_type retval(rectangle);
    set(retval, orientation_2d(dir), get_half(get(rectangle, orientation_2d(dir)), direction_1d(dir)));
    return retval;
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_join_with, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  join_with(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typedef typename rectangle_interval_type<rectangle_type_1>::type Interval1;
    typedef typename rectangle_interval_type<rectangle_type_2>::type Interval2;
    Interval1 hi1 = get(rectangle, HORIZONTAL);
    Interval1 vi1 = get(rectangle, VERTICAL);
    Interval2 hi2 = get(b, HORIZONTAL), vi2 = get(b, VERTICAL);
    Interval1 temp;
    if (equivalence(hi1, hi2) && join_with(vi1, vi2)) {
      vertical(rectangle, vi1);
      return true;
    }
    if (equivalence(vi1, vi2) && join_with(hi1, hi2)) {
      horizontal(rectangle, hi1);
      return true;
    }
    return false;
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_eda2,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const point_type& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_eda,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_sed,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_sed2, typename is_rectangle_concept< typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept< typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_edist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    return std::sqrt((double)(square_euclidean_distance(lvalue, rvalue)));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_edist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    double val = (int)square_euclidean_distance(lvalue, rvalue);
    return std::sqrt(val);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_mdist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_mdist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_up, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_up(rectangle_type& rectangle,
           typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_up(horizontal(rectangle), factor));
    vertical(rectangle, scale_up(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_down, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_down(rectangle_type& rectangle,
             typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_down(horizontal(rectangle), factor));
    vertical(rectangle, scale_down(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type, typename scaling_type>
  typename enable_if<typename gtl_and<y_r_scale, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale(rectangle_type& rectangle, const scaling_type& scaling) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xl(rectangle), yl(rectangle));
    scale(llp, scaling);
    scale(urp, scaling);
    set_points(rectangle, llp, urp);
    return rectangle;
  }


  template <typename rectangle_type, typename transformation_type>
  typename enable_if<typename gtl_and<y_r_transform, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  transform(rectangle_type& rectangle, const transformation_type& transformation) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xh(rectangle), yh(rectangle));
    transform(llp, transformation);
    transform(urp, transformation);
    set_points(rectangle, llp, urp);
    return rectangle;
  }

    inline less_rectangle_concept(orientation_2d orient = VERTICAL) : orient_(orient) {}

    typename enable_if<
      typename gtl_and< typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
      bool>::type
    operator () (const rectangle_type_1& a,
                 const rectangle_type_2& b) const {
      typedef typename rectangle_coordinate_type<rectangle_type_1>::type Unit;
      Unit vl1 = get(get(a, orient_), LOW);
      Unit vl2 = get(get(b, orient_), LOW);
      if(vl1 > vl2) return false;
      if(vl1 == vl2) {
        orientation_2d perp = orient_.get_perpendicular();
        Unit hl1 = get(get(a, perp), LOW);
        Unit hl2 = get(get(b, perp), LOW);
        if(hl1 > hl2) return false;
        if(hl1 == hl2) {
          Unit vh1 = get(get(a, orient_), HIGH);
          Unit vh2 = get(get(b, orient_), HIGH);
          if(vh1 > vh2) return false;
          if(vh1 == vh2) {
            Unit hh1 = get(get(a, perp), HIGH);
            Unit hh2 = get(get(b, perp), HIGH);
            return hh1 < hh2;
          }
        }
      }
      return true;
    }

  template <typename interval_type_1>
  inline void rectangle_data<T>::set(orientation_2d orient, const interval_type_1& interval) {
    assign(ranges_[orient.to_int()], interval);
  }

  template <class T2>
  rectangle_data<T>& rectangle_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  bool rectangle_data<T>::operator==(const T2& rvalue) const {
    return equivalence(*this, rvalue);
  }


  static point_type get(
      const segment_type& segment, direction_1d dir) {
    return segment.get(dir);
  }


  static void set(
      segment_type& segment, direction_1d dir, const point_type& point) {
    segment.set(dir, point);
  }


  static segment_type construct(const point_type& low, const point_type& high) {
    return segment_type(low, high);
  }


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_get,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
get(const Segment& segment, direction_1d dir) {
  return segment_traits<Segment>::get(segment, dir);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_set,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type set(Segment& segment, direction_1d dir, const Point& point) {
  segment_mutable_traits<Segment>::set(segment, dir, point);
}


template <typename Segment, typename Point1, typename Point2>
typename enable_if<
  typename gtl_and_4<
    y_s_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point2>::type
    >::type
  >::type,
Segment>::type construct(const Point1& low, const Point2& high) {
  return segment_mutable_traits<Segment>::construct(low, high);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_copy_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type copy_construct(const Segment2& segment) {
  return construct<Segment1>(get(segment, LOW), get(segment, HIGH));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_assign,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type& assign(Segment1& segment1, const Segment2& segment2) {
  return segment1 = copy_construct<Segment1>(segment2);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_equivalence,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type equivalence(const Segment1& segment1, const Segment2& segment2) {
  return get(segment1, LOW) == get(segment2, LOW) &&
         get(segment1, HIGH) == get(segment2, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_low,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type low(const Segment& segment) {
  return get(segment, LOW);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_high,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type high(const Segment& segment) {
  return get(segment, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_center,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
center(const Segment& segment) {
  return construct<typename segment_point_type<Segment>::type>(
      (x(high(segment)) + x(low(segment)))/2,
      (y(high(segment)) + y(low(segment)))/2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_low2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type low(Segment& segment, const Point& point) {
  set(segment, LOW, point);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_high2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type high(Segment& segment, const Point& point) {
  set(segment, HIGH, point);
}

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
int>::type orientation(const Segment1& segment1, const Segment2& segment2) {
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::manhattan_area_type int_x2;
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::unsigned_area_type uint_x2;
  int_x2 a1 = (int_x2)x(high(segment1)) - (int_x2)x(low(segment1));
  int_x2 b1 = (int_x2)y(high(segment1)) - (int_x2)y(low(segment1));
  int_x2 a2 = (int_x2)x(high(segment2)) - (int_x2)x(low(segment2));
  int_x2 b2 = (int_x2)y(high(segment2)) - (int_x2)y(low(segment2));

  int sign1 = 0;
  int sign2 = 0;
  if (a1 && b2)
    sign1 = ((a1 > 0) ^ (b2 > 0)) ? -1 : 1;
  if (a2 && b1)
    sign2 = ((a2 > 0) ^ (b1 > 0)) ? -1 : 1;

  if (sign1 != sign2)
    return (sign1 < sign2) ? -1 : 1;
  uint_x2 a3 = (uint_x2)(a1 < 0 ? -a1 : a1) * (uint_x2)(b2 < 0 ? -b2 : b2);
  uint_x2 b3 = (uint_x2)(b1 < 0 ? -b1 : b1) * (uint_x2)(a2 < 0 ? -a2 : a2);
  if (a3 == b3)
    return 0;
  return ((a3 < b3) ^ (sign1 == 1)) ? 1 : -1;
}

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation2,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
int>::type orientation(const Segment& segment, const Point& point) {
  Segment segment2 = construct<Segment>(high(segment), point);
  return orientation(segment, segment2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_contains,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
bool>::type contains(const Segment& segment,
    const Point& point, bool consider_touch = true ) {
  if (orientation(segment, point))
    return false;
  rectangle_data<typename segment_coordinate_type<Segment>::type> rect;
  set_points(rect, low(segment), high(segment));
  if (!contains(rect, point, true))
    return false;
  if (!consider_touch &&
      (equivalence(low(segment), point) ||
       equivalence(high(segment), point)))
    return false;
  return true;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_contains2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type contains(const Segment1& segment1,
    const Segment2& segment2, bool consider_touch = true) {
  return contains(segment1, get(segment2, LOW), consider_touch) &&
         contains(segment1, get(segment2, HIGH), consider_touch);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_length,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
length(const Segment& segment) {
  return euclidean_distance(low(segment), high(segment));
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_up,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_up(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_up(l, factor));
  high(segment, scale_up(h, factor));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_down,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_down(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_down(l, factor));
  high(segment, scale_down(h, factor));
  return segment;
}


template <typename Segment, typename Scale>
typename enable_if<
  typename gtl_and<
    y_s_scale,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale(Segment& segment, const Scale& sc) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale(l, sc));
  high(segment, scale(h, sc));
  return segment;
}


template <typename Segment, typename Transform>
typename enable_if<
  typename gtl_and<
    y_s_transform,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& transform(Segment& segment, const Transform& tr) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, transform(l, tr));
  high(segment, transform(h, tr));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_move,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& move(Segment& segment, orientation_2d orient,
    typename segment_coordinate_type<Segment>::type displacement) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, move(l, orient, displacement));
  high(segment, move(h, orient, displacement));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_convolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& convolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, convolve(l, point));
  high(segment, convolve(h, point));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_deconvolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& deconvolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, deconvolve(l, point));
  high(segment, deconvolve(h, point));
  return segment;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1,
    const Segment2& segment2, direction_1d dir) {
  return dir.to_int() ? equivalence(low(segment2) , high(segment1)) :
                        equivalence(low(segment1) , high(segment2));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1, const Segment2& segment2) {
  return abuts(segment1, segment2, HIGH) || abuts(segment1, segment2, LOW);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_intersects,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool
>::type intersects(const Segment1& segment1, const Segment2& segment2,
    bool consider_touch = true) {
  rectangle_data<typename segment_coordinate_type<Segment1>::type> rect1, rect2;
  set_points(rect1, low(segment1), high(segment1));
  set_points(rect2, low(segment2), high(segment2));
  // Check if axis-parallel rectangles containing segments intersect.
  if (!intersects(rect1, rect2, true))
    return false;
  int or1_1 = orientation(segment1, low(segment2));
  int or1_2 = orientation(segment1, high(segment2));
  if (or1_1 * or1_2 > 0)
    return false;
  int or2_1 = orientation(segment2, low(segment1));
  int or2_2 = orientation(segment2, high(segment1));
  if (or2_1 * or2_2 > 0)
    return false;
  if (consider_touch || (or1_1 && or1_2) || (or2_1 && or2_2))
    return true;
  if (or1_1 || or1_2)
    return false;
  return intersects(vertical(rect1), vertical(rect2), false) ||
         intersects(horizontal(rect1), horizontal(rect2), false);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
euclidean_distance(const Segment& segment, const Point& point) {
  typedef typename segment_distance_type<Segment>::type Unit;
  Unit x1 = x(low(segment));
  Unit y1 = y(low(segment));
  Unit x2 = x(high(segment));
  Unit y2 = y(high(segment));
  Unit X = x(point);
  Unit Y = y(point);
  Unit A = X - x1;
  Unit B = Y - y1;
  Unit C = x2 - x1;
  Unit D = y2 - y1;
  Unit param = (A * C + B * D);
  Unit length_sq = C * C + D * D;
  if (param > length_sq) {
    return euclidean_distance(high(segment), point);
  } else if (param < 0.0) {
    return euclidean_distance(low(segment), point);
  }
  if (length_sq == 0.0)
    return 0.0;
  Unit denom = std::sqrt(length_sq);
  Unit result = (A * D - C * B) / denom;
  return (result < 0.0) ? -result : result;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
typename segment_distance_type<Segment1>::type>::type
euclidean_distance(const Segment1& segment1, const Segment2& segment2) {
  if (intersects(segment1, segment2))
    return 0.0;
  typename segment_distance_type<Segment1>::type
      result1 = euclidean_distance(segment1, low(segment2)),
      result2 = euclidean_distance(segment1, high(segment2)),
      result3 = euclidean_distance(segment2, low(segment1)),
      result4 = euclidean_distance(segment2, high(segment1));
  if (result2 < result1)
    result1 = result2;
  if (result4 < result3)
    result3 = result4;
  return (result1 < result3) ? result1 : result3;
}


  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}

  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}

  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}

  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }

  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }

  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }

  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }


  inline iterator_compact_to_points() : iter_(), iter_end_(), pt_(), firstX_(), orient_() {}

  inline iterator_compact_to_points(iterator_type iter, iterator_type iter_end) :
    iter_(iter), iter_end_(iter_end), pt_(), firstX_(), orient_(HORIZONTAL) {
    if(iter_ != iter_end_) {
      firstX_ = *iter_;
      x(pt_, firstX_);
      ++iter_;
      if(iter_ != iter_end_) {
        y(pt_, *iter_);
      }
    }
  }

  inline iterator_compact_to_points& operator++() {
    iterator_type prev_iter = iter_;
    ++iter_;
    if(iter_ == iter_end_) {
      if(x(pt_) != firstX_) {
        iter_ = prev_iter;
        x(pt_, firstX_);
      }
    } else {
      set(pt_, orient_, *iter_);
      orient_.turn_90();
    }
    return *this;
  }

  inline const iterator_compact_to_points operator++(int) {
    iterator_compact_to_points tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_compact_to_points& that) const {
    return (iter_ == that.iter_);
  }

  inline bool operator!=(const iterator_compact_to_points& that) const {
    return (iter_ != that.iter_);
  }

  inline reference operator*() const { return pt_; }

    static inline compact_iterator_type begin_compact(const T& t) {
      return t.begin_compact();
    }

    static inline compact_iterator_type end_compact(const T& t) {
      return t.end_compact();
    }

    static inline std::size_t size(const T& t) {
      return t.size();
    }

    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }

    static inline iterator_type begin_points(const T& t) {
      return t.begin();
    }

    static inline iterator_type end_points(const T& t) {
      return t.end();
    }

    static inline std::size_t size(const T& t) {
      return t.size();
    }

    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }

    static inline iterator_type begin_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::begin_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    static inline iterator_type end_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::end_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    static inline std::size_t size(const T& t) {
      return polygon_90_traits<T>::size(t);
    }

    static inline winding_direction winding(const T& t) {
      return polygon_90_traits<T>::winding(t);
    }

    static inline iterator_holes_type begin_holes(const T& t) {
      return t.begin_holes();
    }

    static inline iterator_holes_type end_holes(const T& t) {
      return t.end_holes();
    }

    static inline std::size_t size_holes(const T& t) {
      return t.size_holes();
    }

    template <typename iT>
    static inline T& set_compact(T& t, iT input_begin, iT input_end) {
      t.set_compact(input_begin, input_end);
      return t;
    }

    template <typename iT>
    static inline T& set_points(T& t, iT input_begin, iT input_end) {
      t.set(input_begin, input_end);
      return t;
    }

    template <typename iT>
    static inline T& set_holes(T& t, iT inputBegin, iT inputEnd) {
      t.set_holes(inputBegin, inputEnd);
      return t;
    }


  inline polygon_45_data() : coords_() {}


  template<class iT>
  inline polygon_45_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}


  template<class iT>
  inline polygon_45_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  inline polygon_45_data(const polygon_45_data& that) : coords_(that.coords_) {}

  inline polygon_45_data& operator=(const polygon_45_data& that) {
    coords_ = that.coords_;
    return *this;
  }


  inline bool operator==(const polygon_45_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }


  inline bool operator!=(const polygon_45_data& that) const { return !((*this) == that); }

  inline iterator_type begin() const { return coords_.begin(); }

  inline iterator_type end() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }


  inline polygon_data() : coords_() {}


  template<class iT>
  inline polygon_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}


  template<class iT>
  inline polygon_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  inline polygon_data(const polygon_data& that) : coords_(that.coords_) {}

  inline polygon_data& operator=(const polygon_data& that) {
    coords_ = that.coords_;
    return *this;
  }


  inline bool operator==(const polygon_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }


  inline bool operator!=(const polygon_data& that) const { return !((*this) == that); }

  inline iterator_type begin() const { return coords_.begin(); }

  inline iterator_type end() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }


  inline polygon_90_data() : coords_() {}

  template<class iT>
  inline polygon_90_data& set(iT begin_point, iT end_point) {
    return set_compact(iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(begin_point, end_point),
                       iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(end_point, end_point));
  }


  template<class iT>
  inline polygon_90_data& set_compact(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    while(input_begin != input_end) {
       coords_.insert(coords_.end(), *input_begin);
       ++input_begin;
    }
    return *this;
  }

  inline polygon_90_data(const polygon_90_data& that) : coords_(that.coords_) {}

  inline polygon_90_data& operator=(const polygon_90_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  inline bool operator==(const polygon_90_data& that) const {
    return coords_ == that.coords_;
  }

  inline iterator_type begin() const { return iterator_type(coords_.begin(), coords_.end()); }

  inline iterator_type end() const { return iterator_type(coords_.end(), coords_.end()); }

  inline compact_iterator_type begin_compact() const { return coords_.begin(); }

  inline compact_iterator_type end_compact() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }

  inline polygon_90_with_holes_data() : self_(), holes_() {}

  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }

  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  inline polygon_45_with_holes_data() : self_(), holes_() {}


  template<class iT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }


  template<class iT, typename hiT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }


  template<class iT>
  inline polygon_45_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_45_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  inline polygon_45_with_holes_data(const polygon_45_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_45_with_holes_data& operator=(const polygon_45_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  inline polygon_with_holes_data() : self_(), holes_() {}


  template<class iT>
  inline polygon_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }


  template<class iT, typename hiT>
  inline polygon_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }


  template<class iT>
  inline polygon_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  inline polygon_with_holes_data(const polygon_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_with_holes_data& operator=(const polygon_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_type<T>::type, T>::type &
  set_points(T& t, iT begin_points, iT end_points) {
    polygon_mutable_traits<T>::set_points(t, begin_points, end_points);
    return t;
  }

  template <typename T, typename iT>
  typename enable_if <typename gtl_or<
    typename is_mutable_polygon_90_type<T>::type,
    typename is_mutable_polygon_90_with_holes_type<T>::type>::type, T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    polygon_90_mutable_traits<T>::set_compact(t, begin_compact_coordinates, end_compact_coordinates);
    return t;
  }

  template <typename T, typename iT>
  typename enable_if< typename gtl_and <
    typename is_any_mutable_polygon_with_holes_type<T>::type,
    typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                                manhattan_domain>::type>::type,
                       T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    iterator_compact_to_points<iT, point_data<typename polygon_traits<T>::coordinate_type> >
      itrb(begin_compact_coordinates, end_compact_coordinates),
      itre(end_compact_coordinates, end_compact_coordinates);
    return set_points(t, itrb, itre);
  }

  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  set_holes(T& t, iT begin_holes, iT end_holes) {
    polygon_with_holes_mutable_traits<T>::set_holes(t, begin_holes, end_holes);
    return t;
  }

  begin_compact(const T& polygon,
    typename enable_if<
      typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                        typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::begin_compact(polygon);
  }

  end_compact(const T& polygon,
    typename enable_if<
    typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
              manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::end_compact(polygon);
  }

  begin_points(const T& polygon) {
    return polygon_traits<T>::begin_points(polygon);
  }

  end_points(const T& polygon) {
    return polygon_traits<T>::end_points(polygon);
  }

  size(const T& polygon) {
    return polygon_traits<T>::size(polygon);
  }

  begin_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::begin_holes(polygon);
  }

  end_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::end_holes(polygon);
  }

  size_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::size_holes(polygon);
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_type<T1>::type,
                      typename is_polygon_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_with_holes_type<T1>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_45_type<T1>::type, typename is_polygon_45_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_45_with_holes_type<T1>::type,
                      typename is_polygon_45_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_type<T1>::type,
                      typename is_polygon_90_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_with_holes_type<T1>::type,
                      typename is_polygon_90_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_type<T1>::type,
                      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type, T1>::type &
  assign(T1& polygon, const T2& rect) {
    typedef point_data<typename polygon_traits<T1>::coordinate_type> PT;
    PT points[4] = {PT(xl(rect), yl(rect)), PT(xh(rect), yl(rect)), PT(xh(rect), yh(rect)), PT(xl(rect), yh(rect))};
    set_points(polygon, points, points+4);
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_90_type<polygon_type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename polygon_90_traits<polygon_type>::coordinate_type> coords;
    coords.reserve(size(polygon));
    bool pingpong = true;
    for(typename polygon_90_traits<polygon_type>::compact_iterator_type iter = begin_compact(polygon);
        iter != end_compact(polygon); ++iter) {
      coords.push_back((*iter) + (pingpong ? x(point) : y(point)));
      pingpong = !pingpong;
    }
    polygon_90_mutable_traits<polygon_type>::set_compact(polygon, coords.begin(), coords.end());
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename gtl_or<
    typename is_mutable_polygon_45_type<polygon_type>::type,
    typename is_mutable_polygon_type<polygon_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      convolve(points.back(), point);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    convolve(h, point);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      convolve(holes.back(), point);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename polygon_type, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  transform(polygon_type& polygon, const transform_type& tr) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      transform(points.back(), tr);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename T, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  transform(T& polygon, const transform_type& tr) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    transform(h, tr);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      transform(holes.back(), tr);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }


  template <typename Unit>
  Unit local_abs(Unit value) { return value < 0 ? (Unit)-value : value; }


  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
    }
    snap_point_vector_to_45(points);
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }


  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    snap_to_45(h);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      snap_to_45(holes.back());
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename polygon_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_not<typename gtl_same_type
                                       < forty_five_domain,
                                         typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type>::type,
    polygon_type>::type &
  scale(polygon_type& polygon, double factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale(points.back(), anisotropic_scale_factor<double>(factor, factor));
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }


  template <typename iterator_type, typename area_type>
  static area_type
  point_sequence_area(iterator_type begin_range, iterator_type end_range) {
    typedef typename std::iterator_traits<iterator_type>::value_type point_type;
    typedef typename point_traits<point_type>::coordinate_type Unit;
    if(begin_range == end_range) return area_type(0);
    point_type first = *begin_range;
    point_type previous = first;
    ++begin_range;
    // Initialize trapezoid base line
    area_type y_base = (area_type)y(first);
    // Initialize area accumulator

    area_type area(0);
    while (begin_range != end_range) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(*begin_range);
#ifdef BOOST_POLYGON_ICC
#pragma warning (push)
#pragma warning (disable:1572)
#endif
      if(x1 != x2) {
#ifdef BOOST_POLYGON_ICC
#pragma warning (pop)
#endif
        // do trapezoid area accumulation
        area += (x2 - x1) * (((area_type)y(*begin_range) - y_base) +
                             ((area_type)y(previous) - y_base)) / 2;
      }
      previous = *begin_range;
      // go to next point
      ++begin_range;
    }
    //wrap around to evaluate the edge between first and last if not closed
    if(!equivalence(first, previous)) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(first);
      area += (x2 - x1) * (((area_type)y(first) - y_base) +
                           ((area_type)y(previous) - y_base)) / 2;
    }
    return area;
  }


  template <typename iT>
  bool point_sequence_is_45(iT itr, iT itr_end) {
    typedef typename std::iterator_traits<iT>::value_type Point;
    typedef typename point_traits<Point>::coordinate_type Unit;
    if(itr == itr_end) return true;
    Point firstPt = *itr;
    Point prevPt = firstPt;
    ++itr;
    while(itr != itr_end) {
      Point pt = *itr;
      Unit deltax = x(pt) - x(prevPt);
      Unit deltay = y(pt) - y(prevPt);
      if(deltax && deltay &&
         local_abs(deltax) != local_abs(deltay))
        return false;
      prevPt = pt;
      ++itr;
    }
    Unit deltax = x(firstPt) - x(prevPt);
    Unit deltay = y(firstPt) - y(prevPt);
    if(deltax && deltay &&
       local_abs(deltax) != local_abs(deltay))
      return false;
    return true;
  }


  template <typename polygon_type>
  typename enable_if< typename is_polygon_with_holes_type<polygon_type>::type, bool>::type
  is_45(const polygon_type& polygon) {
    typename polygon_traits<polygon_type>::iterator_type itr = begin_points(polygon), itr_end = end_points(polygon);
    if(!point_sequence_is_45(itr, itr_end)) return false;
    typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itrh = begin_holes(polygon), itrh_end = end_holes(polygon);
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    for(; itrh != itrh_end; ++ itrh) {
      typename polygon_traits<hole_type>::iterator_type itr1 = begin_points(polygon), itr1_end = end_points(polygon);
      if(!point_sequence_is_45(itr1, itr1_end)) return false;
    }
    return true;
  }


  template <typename distance_type, typename iterator_type>
  distance_type point_sequence_distance(iterator_type itr, iterator_type itr_end) {
    typedef distance_type Unit;
    typedef iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    Unit return_value = Unit(0);
    point_type previous_point, first_point;
    if(itr == itr_end) return return_value;
    previous_point = first_point = *itr;
    ++itr;
    for( ; itr != itr_end; ++itr) {
      point_type current_point = *itr;
      return_value += (Unit)euclidean_distance(current_point, previous_point);
      previous_point = current_point;
    }
    return_value += (Unit)euclidean_distance(previous_point, first_point);
    return return_value;
  }


  template <typename T>
  typename enable_if <typename is_polygon_with_holes_type<T>::type,
                       direction_1d>::type
  winding(const T& polygon) {
    winding_direction wd = polygon_traits<T>::winding(polygon);
    if(wd != unknown_winding) {
      return wd == clockwise_winding ? CLOCKWISE: COUNTERCLOCKWISE;
    }
    typedef typename area_type_by_domain< typename geometry_domain<typename geometry_concept<T>::type>::type,
      typename polygon_traits<T>::coordinate_type>::type area_type;
    return point_sequence_area<typename polygon_traits<T>::iterator_type, area_type>(begin_points(polygon), end_points(polygon)) < 0 ?
      COUNTERCLOCKWISE : CLOCKWISE;
  }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and< typename is_polygon_90_type<T>::type,
                      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef T polygon_type;
    typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
    typedef typename polygon_traits<polygon_type>::iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    coordinate_type point_x = x(point);
    coordinate_type point_y = y(point);
    bool inside = false;
    for (iterator iter = begin_points(polygon); iter != end_points(polygon);) {
      point_type curr_point = *iter;
      ++iter;
      point_type next_point = (iter == end_points(polygon)) ? *begin_points(polygon) : *iter;
      if (x(curr_point) == x(next_point)) {
        if (x(curr_point) > point_x) {
          continue;
        }
        coordinate_type min_y = (std::min)(y(curr_point), y(next_point));
        coordinate_type max_y = (std::max)(y(curr_point), y(next_point));
        if (point_y > min_y && point_y < max_y) {
          if (x(curr_point) == point_x) {
            return consider_touch;
          }
          inside ^= true;
        }
      } else {
        coordinate_type min_x = (std::min)(x(curr_point), x(next_point));
        coordinate_type max_x = (std::max)(x(curr_point), x(next_point));
        if (point_x >= min_x && point_x <= max_x) {
          if (y(curr_point) == point_y) {
            return consider_touch;
          }
        }
      }
    }
    return inside;
  }

      inline less_point() {}

      inline bool operator () (const Point& pt1, const Point& pt2) const {
        if(pt1.get(HORIZONTAL) < pt2.get(HORIZONTAL)) return true;
        if(pt1.get(HORIZONTAL) == pt2.get(HORIZONTAL)) {
          if(pt1.get(VERTICAL) < pt2.get(VERTICAL)) return true;
        }
        return false;
      }


    static inline bool between(Point pt, Point pt1, Point pt2) {
      less_point lp;
      if(lp(pt1, pt2))
        return lp(pt, pt2) && lp(pt1, pt);
      return lp(pt, pt1) && lp(pt2, pt);
    }


    template <typename area_type>
    static inline bool equal_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      return cross_1 == cross_2 && (cross_1_sign == cross_2_sign || cross_1 == 0);
    }


    static inline bool equal_slope(const Unit& x, const Unit& y,
                                   const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return equal_slope(dx1, dy1, dx2, dy2);
    }


    template <typename area_type>
    static inline bool less_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      //reflext x and y slopes to right hand side half plane
      if(dx1 < 0) {
        dy1 *= -1;
        dx1 *= -1;
      } else if(dx1 == 0) {
        //if the first slope is vertical the first cannot be less
        return false;
      }
      if(dx2 < 0) {
        dy2 *= -1;
        dx2 *= -1;
      } else if(dx2 == 0) {
        //if the second slope is vertical the first is always less unless it is also vertical, in which case they are equal
        return dx1 != 0;
      }
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      if(cross_1_sign < cross_2_sign) return true;
      if(cross_2_sign < cross_1_sign) return false;
      if(cross_1_sign == -1) return cross_2 < cross_1;
      return cross_1 < cross_2;
    }


    static inline bool less_slope(const Unit& x, const Unit& y,
                                  const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      //compute y value on edge from pt_ to pts[1] at the x value of pts[0]
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return less_slope(dx1, dy1, dx2, dy2);
    }

    static inline int on_above_or_below(Point pt, const half_edge& he) {
      if(pt == he.first || pt == he.second) return 0;
      if(equal_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second)) return 0;
      bool less_result = less_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second);
      int retval = less_result ? -1 : 1;
      less_point lp;
      if(lp(he.second, he.first)) retval *= -1;
      if(!between(pt, he.first, he.second)) retval *= -1;
      return retval;
    }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename polygon_with_holes_traits<T>::iterator_holes_type holes_iterator;
    bool isInside = contains( view_as< typename polygon_from_polygon_with_holes_type<
                              typename geometry_concept<T>::type>::type>( polygon ), point, consider_touch );
    if(!isInside) return false; //no need to check holes
    holes_iterator itH = begin_holes( polygon );
    while( itH != end_holes( polygon ) ) {
      if(  contains( *itH, point, !consider_touch )  ) {
        isInside = false;
        break;
      }
      ++itH;
    }
    return isInside;
  }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and_3<
      typename is_polygon_type<T>::type,
      typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type, manhattan_domain>::type,
      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename point_traits<input_point_type>::coordinate_type Unit;
    typedef point_data<Unit> Point;
    typedef std::pair<Point, Point> half_edge;
    typedef typename polygon_traits<T>::iterator_type iterator;
    iterator itr = begin_points(polygon);
    iterator itrEnd = end_points(polygon);
    half_edge he;
    if(itr == itrEnd) return false;
    assign(he.first, *itr);
    Point firstPt;
    assign(firstPt, *itr);
    ++itr;
    if(itr == itrEnd) return false;
    bool done = false;
    int above = 0;
    while(!done) {
      Point currentPt;
      if(itr == itrEnd) {
        done = true;
        currentPt = firstPt;
      } else {
        assign(currentPt, *itr);
        ++itr;
      }
      if(currentPt == he.first) {
        continue;
      } else {
        he.second = currentPt;
        if(equivalence(point, currentPt)) return consider_touch;
        Unit xmin = (std::min)(x(he.first), x(he.second));
        Unit xmax = (std::max)(x(he.first), x(he.second));
        if(x(point) >= xmin && x(point) < xmax) { //double counts if <= xmax
          Point tmppt;
          assign(tmppt, point);
          int oabedge = edge_utils<Unit>::on_above_or_below(tmppt, he);
          if(oabedge == 0) return consider_touch;
          if(oabedge == 1) ++above;
        } else if(x(point) == xmax) {
          if(x(point) == xmin) {
            Unit ymin = (std::min)(y(he.first), y(he.second));
            Unit ymax = (std::max)(y(he.first), y(he.second));
            Unit ypt = y(point);
            if(ypt <= ymax && ypt >= ymin)
              return consider_touch;
          } else {
            Point tmppt;
            assign(tmppt, point);
            if( edge_utils<Unit>::on_above_or_below(tmppt, he) == 0 ) {
              return consider_touch;
            }
          }
        }
      }
      he.first = he.second;
    }
    return above % 2 != 0; //if the point is above an odd number of edges is must be inside polygon
  }


  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_point_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  center(T1& center_point, const T2& polygon) {
    typedef typename polygon_traits<T2>::coordinate_type coordinate_type;
    rectangle_data<coordinate_type> bbox;
    extents(bbox, polygon);
    return center(center_point, bbox);
  }


  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_rectangle_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  extents(T1& bounding_box, const T2& polygon) {
    typedef typename polygon_traits<T2>::iterator_type iterator;
    bool first_iteration = true;
    iterator itr_end = end_points(polygon);
    for(iterator itr = begin_points(polygon); itr != itr_end; ++itr) {
      if(first_iteration) {
        set_points(bounding_box, *itr, *itr);
        first_iteration = false;
      } else {
        encompass(bounding_box, *itr);
      }
    }
    if(first_iteration) return false;
    return true;
  }

  template <class T2>
  polygon_90_data<T>& polygon_90_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  polygon_45_data<T>& polygon_45_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  polygon_data<T>& polygon_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  polygon_90_with_holes_data<T>& polygon_90_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  polygon_45_with_holes_data<T>& polygon_45_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  polygon_with_holes_data<T>& polygon_with_holes_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

    static inline iterator_holes_type begin_holes(const hole_type& t) { return &t; }

    static inline iterator_holes_type end_holes(const hole_type& t) { return &t; }

    static inline std::size_t size_holes(const hole_type& t) { return 0; }

    view_of(const T& obj) : rect() {
      point_data<coordinate_type> pts[2];
      typename polygon_traits<T>::iterator_type itr =
        begin_points(obj), itre = end_points(obj);
      if(itr == itre) return;
      assign(pts[0], *itr);
      ++itr;
      if(itr == itre) return;
      ++itr;
      if(itr == itre) return;
      assign(pts[1], *itr);
      set_points(rect, pts[0], pts[1]);
    }

    inline interval_type get(orientation_2d orient) const {
      return rect.get(orient); }

    view_of(const T& obj) : t(&obj) {}

    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    view_of(const T& obj) : t(&obj) {}

    inline compact_iterator_type begin_compact() const {
      return compact_iterator_type(polygon_traits<T>::begin_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    inline compact_iterator_type end_compact() const {
      return compact_iterator_type(polygon_traits<T>::end_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    view_of(const T& obj) : t(&obj) {}

      iterator_holes_type() : internal_itr() {}

      iterator_holes_type(iht iht_in) : internal_itr(iht_in) {}

      inline iterator_holes_type& operator++() {
        ++internal_itr;
        return *this;
      }

      inline const iterator_holes_type operator++(int) {
        iterator_holes_type tmp(*this);
        ++(*this);
        return tmp;
      }

      inline bool operator==(const iterator_holes_type& that) const {
        return (internal_itr == that.internal_itr);
      }

      inline bool operator!=(const iterator_holes_type& that) const {
        return (internal_itr != that.internal_itr);
      }

      inline value_type operator*() const {
        return view_as<polygon_45_concept>(*internal_itr);
      }

    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    inline iterator_holes_type begin_holes() const {
      return polygon_with_holes_traits<T>::begin_holes(*t);
    }

    inline iterator_holes_type end_holes() const {
      return polygon_with_holes_traits<T>::end_holes(*t);
    }

    inline std::size_t size_holes() const {
      return polygon_with_holes_traits<T>::size_holes(*t);
    }

    view_of(const T& obj) : t(&obj) {}

      iterator_holes_type() : internal_itr() {}

      iterator_holes_type(iht iht_in) : internal_itr(iht_in) {}

      inline iterator_holes_type& operator++() {
        ++internal_itr;
        return *this;
      }

      inline const iterator_holes_type operator++(int) {
        iterator_holes_type tmp(*this);
        ++(*this);
        return tmp;
      }

      inline bool operator==(const iterator_holes_type& that) const {
        return (internal_itr == that.internal_itr);
      }

      inline bool operator!=(const iterator_holes_type& that) const {
        return (internal_itr != that.internal_itr);
      }

      inline value_type operator*() const {
        return view_as<polygon_90_concept>(*internal_itr);
      }

    inline compact_iterator_type begin_compact() const {
      return compact_iterator_type(polygon_traits<T>::begin_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    inline compact_iterator_type end_compact() const {
      return compact_iterator_type(polygon_traits<T>::end_points(*t),
                                   polygon_traits<T>::end_points(*t));
    }

    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    inline iterator_holes_type begin_holes() const {
      return polygon_with_holes_traits<T>::begin_holes(*t);
    }

    inline iterator_holes_type end_holes() const {
      return polygon_with_holes_traits<T>::end_holes(*t);
    }

    inline std::size_t size_holes() const {
      return polygon_with_holes_traits<T>::size_holes(*t);
    }

    view_of(const T& obj) : t(&obj) {}

    inline iterator_type begin() const {
      return polygon_traits<T>::begin_points(*t);
    }

    inline iterator_type end() const {
      return polygon_traits<T>::end_points(*t);
    }

    inline std::size_t size() const {
      return polygon_traits<T>::size(*t);
    }

    inline winding_direction winding() const {
      return polygon_traits<T>::winding(*t);
    }

    inline BooleanOp () : scanData_(), nextItr_(), nullT_() { nextItr_ = scanData_.end(); nullT_ = 0; }

    inline BooleanOp (T nullT) : scanData_(), nextItr_(), nullT_(nullT) { nextItr_ = scanData_.end(); }

    inline BooleanOp (const BooleanOp& that) : scanData_(that.scanData_), nextItr_(),
                                               nullT_(that.nullT_) { nextItr_ = scanData_.begin(); }

    inline void advanceScan() { nextItr_ = scanData_.begin(); }

    inline BinaryAnd() {}

    inline bool operator()(int a, int b) { return (a > 0) & (b > 0); }

    inline BinaryOr() {}

    inline bool operator()(int a, int b) { return (a > 0) | (b > 0); }

    inline BinaryNot() {}

    inline bool operator()(int a, int b) { return (a > 0) & !(b > 0); }

    inline BinaryXor() {}

    inline bool operator()(int a, int b) { return (a > 0) ^ (b > 0); }

    inline BinaryCount()
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { counts_[0] = counts_[1] = 0; }

    inline BinaryCount(int countL, int countR)
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { counts_[0] = countL, counts_[1] = countR; }

    inline BinaryCount& operator=(int count) { counts_[0] = count, counts_[1] = count; return *this; }

    inline BinaryCount(const BinaryCount& that)
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { *this = that; }

    inline bool operator!=(const BinaryCount& that) const { return !((*this) == that);}

    inline int& operator[](bool index) { return counts_[index]; }

    inline operator int() const { return T()(counts_[0], counts_[1]); }

    inline UnaryCount() : count_(0) {}

    inline explicit UnaryCount(int count) : count_(count) {}

    inline UnaryCount& operator=(int count) { count_ = count; return *this; }

    inline UnaryCount& operator=(const UnaryCount& that) { count_ = that.count_; return *this; }

    inline UnaryCount(const UnaryCount& that) : count_(that.count_) {}

    inline bool operator==(const UnaryCount& that) const { return count_ == that.count_; }

    inline bool operator!=(const UnaryCount& that) const { return !((*this) == that);}

    inline UnaryCount& operator+=(const UnaryCount& that) { count_ += that.count_; return *this; }

    inline UnaryCount& operator-=(const UnaryCount& that) { count_ -= that.count_; return *this; }

    inline UnaryCount operator+(const UnaryCount& that) const { UnaryCount tmp(*this); tmp += that; return tmp; }

    inline UnaryCount operator-(const UnaryCount& that) const { UnaryCount tmp(*this); tmp -= that; return tmp; }

    inline UnaryCount operator-() const { UnaryCount tmp; return tmp - *this; }

    inline operator int() const { return count_ % 2; }


  template <class T, typename Unit>
  inline BooleanOp<T, Unit>& BooleanOp<T, Unit>::operator=(const BooleanOp& that) {
    scanData_ = that.scanData_;
    nextItr_ = scanData_.begin();
    nullT_ = that.nullT_;
    return *this;
  }

  template <class cT>
  inline void BooleanOp<T, Unit>::processInterval(cT& outputContainer, interval_data<Unit> ivl, T deltaCount) {
    typename ScanData::iterator lowItr = lookup_(ivl.low());
    typename ScanData::iterator highItr = lookup_(ivl.high());
    //add interval to scan data if it is past the end
    if(lowItr == scanData_.end()) {
      lowItr = insert_(ivl.low(), deltaCount);
      highItr = insert_(ivl.high(), nullT_);
      evaluateInterval_(outputContainer, ivl, nullT_, deltaCount);
      return;
    }
    //ensure that highItr points to the end of the ivl
    if(highItr == scanData_.end() || (*highItr).first > ivl.high()) {
      T value = nullT_;
      if(highItr != scanData_.begin()) {
        --highItr;
        value = highItr->second;
      }
      nextItr_ = highItr;
      highItr = insert_(ivl.high(), value);
    }
    //split the low interval if needed
    if(lowItr->first > ivl.low()) {
      if(lowItr != scanData_.begin()) {
        --lowItr;
        nextItr_ = lowItr;
        lowItr = insert_(ivl.low(), lowItr->second);
      } else {
        nextItr_ = lowItr;
        lowItr = insert_(ivl.low(), nullT_);
      }
    }
    //process scan data intersecting interval
    for(typename ScanData::iterator itr = lowItr; itr != highItr; ){
      T beforeCount = itr->second;
      T afterCount = itr->second += deltaCount;
      Unit low = itr->first;
      ++itr;
      Unit high = itr->first;
      evaluateInterval_(outputContainer, interval_data<Unit>(low, high), beforeCount, afterCount);
    }
    //merge the bottom interval with the one below if they have the same count
    if(lowItr != scanData_.begin()){
      typename ScanData::iterator belowLowItr = lowItr;
      --belowLowItr;
      if(belowLowItr->second == lowItr->second) {
        scanData_.erase(lowItr);
      }
    }
    //merge the top interval with the one above if they have the same count
    if(highItr != scanData_.begin()) {
      typename ScanData::iterator beforeHighItr = highItr;
      --beforeHighItr;
      if(beforeHighItr->second == highItr->second) {
        scanData_.erase(highItr);
        highItr = beforeHighItr;
        ++highItr;
      }
    }
    nextItr_ = highItr;
  }

  template <class cT>
  inline void BooleanOp<T, Unit>::evaluateInterval_(cT& outputContainer, interval_data<Unit> ivl,
                                              T beforeCount, T afterCount) {
    bool before = (int)beforeCount > 0;
    bool after = (int)afterCount > 0;
    int value =  (!before & after) - (before & !after);
    if(value) {
      outputContainer.insert(outputContainer.end(), std::pair<interval_data<Unit>, int>(ivl, value));
    }
  }


  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator=(const BinaryCount<T>& that) {
    counts_[0] = that.counts_[0];
    counts_[1] = that.counts_[1];
    return *this;
  }

  template <class T>
  inline bool BinaryCount<T>::operator==(const BinaryCount<T>& that) const {
    return counts_[0] == that.counts_[0] &&
      counts_[1] == that.counts_[1];
  }

  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator+=(const BinaryCount<T>& that) {
    counts_[0] += that.counts_[0];
    counts_[1] += that.counts_[1];
    return *this;
  }

  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator-=(const BinaryCount<T>& that) {
    counts_[0] += that.counts_[0];
    counts_[1] += that.counts_[1];
    return *this;
  }

  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator+(const BinaryCount<T>& that) const {
    BinaryCount retVal(*this);
    retVal += that;
    return retVal;
  }

  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator-(const BinaryCount<T>& that) const {
    BinaryCount retVal(*this);
    retVal -= that;
    return retVal;
  }

  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator-() const {
    return BinaryCount<T>() - *this;
  }

    template <typename Unit>
    static inline void applyBooleanOr(std::vector<std::pair<Unit, std::pair<Unit, int> > >& input) {
      BooleanOp<count_type, Unit> booleanOr;
      std::vector<std::pair<interval_data<Unit>, int> > container;
      std::vector<std::pair<Unit, std::pair<Unit, int> > > output;
      output.reserve(input.size());
      //consider eliminating dependecy on limits with bool flag for initial state
      Unit UnitMax = (std::numeric_limits<Unit>::max)();
      Unit prevPos = UnitMax;
      Unit prevY = UnitMax;
      int count = 0;
      for(typename std::vector<std::pair<Unit, std::pair<Unit, int> > >::iterator itr = input.begin();
          itr != input.end(); ++itr) {
        Unit pos = (*itr).first;
        Unit y = (*itr).second.first;
        if(pos != prevPos) {
          booleanOr.advanceScan();
          prevPos = pos;
          prevY = y;
          count = (*itr).second.second;
          continue;
        }
        if(y != prevY && count != 0) {
          interval_data<Unit> ivl(prevY, y);
          container.clear();
          booleanOr.processInterval(container, ivl, count_type(count));
          for(std::size_t i = 0; i < container.size(); ++i) {
            std::pair<interval_data<Unit>, int>& element = container[i];
            if(!output.empty() && output.back().first == prevPos &&
               output.back().second.first == element.first.low() &&
               output.back().second.second == element.second * -1) {
              output.pop_back();
            } else {
              output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevPos, std::pair<Unit, int>(element.first.low(),
                                                                                                    element.second)));
            }
            output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevPos, std::pair<Unit, int>(element.first.high(),
                                                                                                  element.second * -1)));
          }
        }
        prevY = y;
        count += (*itr).second.second;
      }
      if(output.size() < input.size() / 2) {
        input = std::vector<std::pair<Unit, std::pair<Unit, int> > >();
      } else {
      input.clear();
      }
      input.insert(input.end(), output.begin(), output.end());
    }

      inline iterator() : pLine_(), pLineEnd_(), index_(), indexEnd_(), startEnd_() {}

      inline iterator(const ActiveTail* at, bool isHole, orientation_2d orient) :
        pLine_(), pLineEnd_(), index_(), indexEnd_(), startEnd_() {
        //if it is a hole and orientation is vertical or it is not a hole and orientation is horizontal
        //we want to use this active tail, otherwise we want to use the other active tail
        startEnd_ = TAIL;
        if(!isHole ^ (orient == HORIZONTAL)) {
          //switch winding direction
          at = at->getOtherActiveTail();
        }
        //now we have the right winding direction
        //if it is horizontal we need to skip the first element
        pLine_ = at->getTail();
        index_ = at->getTail()->numSegments() - 1;
        if((at->getOrient() == HORIZONTAL) ^ (orient == HORIZONTAL)) {
          pLineEnd_ = at->getTail();
          indexEnd_ = pLineEnd_->numSegments() - 1;
          if(index_ == 0) {
            pLine_ = at->getTail()->next(HEAD);
            if(at->getTail()->endConnectivity(HEAD) == TAIL) {
              index_ = pLine_->numSegments() -1;
            } else {
              startEnd_ = HEAD;
              index_ = 0;
            }
          } else { --index_; }
        } else {
          pLineEnd_ = at->getOtherActiveTail()->getTail();
          indexEnd_ = pLineEnd_->numSegments() - 1;
        }
        at->getTail()->joinTailToTail(*(at->getOtherActiveTail()->getTail()));
      }

      inline iterator& operator++() {
        if(pLine_ == pLineEnd_ && index_ == indexEnd_) {
          pLine_ = 0;
          index_ = 0;
          return *this;
        }
        if(startEnd_ == HEAD) {
          ++index_;
          if(index_ == pLine_->numSegments()) {
            End end = pLine_->endConnectivity(TAIL);
            pLine_ = pLine_->next(TAIL);
            if(end == TAIL) {
              startEnd_ = TAIL;
              index_ = pLine_->numSegments() -1;
            } else {
              index_ = 0;
            }
          }
        } else {
          if(index_ == 0) {
            End end = pLine_->endConnectivity(HEAD);
            pLine_ = pLine_->next(HEAD);
            if(end == TAIL) {
              index_ = pLine_->numSegments() -1;
            } else {
              startEnd_ = HEAD;
              index_ = 0;
            }
          } else {
            --index_;
          }
        }
        return *this;
      }

      inline const iterator operator++(int) {
        iterator tmp(*this);
        ++(*this);
        return tmp;
      }

      inline bool operator==(const iterator& that) const {
        return pLine_ == that.pLine_ && index_ == that.index_;
      }

      inline bool operator!=(const iterator& that) const {
        return pLine_ != that.pLine_ || index_ != that.index_;
      }

      inline Unit operator*() { return (*pLine_)[index_]; }

    inline PolyLineHoleData() : p_(0) {}

    inline PolyLineHoleData(ActiveTail<Unit>* p) : p_(p) {}

    inline compact_iterator_type begin_compact() const { return p_->begin(true, (orientT ? VERTICAL : HORIZONTAL)); }

    inline compact_iterator_type end_compact() const { return p_->end(); }

    inline iterator_type begin() const { return iterator_type(begin_compact(), end_compact()); }

    inline iterator_type end() const { return iterator_type(end_compact(), end_compact()); }

    inline std::size_t size() const { return 0; }

    inline ActiveTail<Unit>* yield() { return p_; }

    template<class iT>
    inline PolyLineHoleData& set(iT inputBegin, iT inputEnd) {
      return *this;
    }

    template<class iT>
    inline PolyLineHoleData& set_compact(iT inputBegin, iT inputEnd) {
      return *this;
    }

      inline iteratorHoles() : itr_() {}

      inline iteratorHoles(typename ActiveTail<Unit>::iteratorHoles itr) : itr_(itr) {}

      inline iteratorHoles& operator++() {
        ++itr_;
        return *this;
      }

      inline const iteratorHoles operator++(int) {
        iteratorHoles tmp(*this);
        ++(*this);
        return tmp;
      }

      inline bool operator==(const iteratorHoles& that) const {
        return itr_ == that.itr_;
      }

      inline bool operator!=(const iteratorHoles& that) const {
        return itr_ != that.itr_;
      }

      inline PolyLineHoleData<orientT, Unit> operator*() { return PolyLineHoleData<orientT, Unit>(*itr_);}


    inline PolyLinePolygonWithHolesData() : p_(0) {}

    inline PolyLinePolygonWithHolesData(ActiveTail<Unit>* p) : p_(p) {}

    inline compact_iterator_type begin_compact() const { return p_->begin(false, (orientT ? VERTICAL : HORIZONTAL)); }

    inline compact_iterator_type end_compact() const { return p_->end(); }

    inline iterator_type begin() const { return iterator_type(begin_compact(), end_compact()); }

    inline iterator_type end() const { return iterator_type(end_compact(), end_compact()); }

    inline iteratorHoles begin_holes() const { return iteratorHoles(p_->beginHoles()); }

    inline iteratorHoles end_holes() const { return iteratorHoles(p_->endHoles()); }

    inline ActiveTail<Unit>* yield() { return p_; }

    inline std::size_t size_holes() const { return 0; }

    inline std::size_t size() const { return 0; }

    template<class iT>
    inline PolyLinePolygonWithHolesData& set(iT inputBegin, iT inputEnd) {
      return *this;
    }

    template<class iT>
    inline PolyLinePolygonWithHolesData& set_compact(iT inputBegin, iT inputEnd) {
      return *this;
    }

    template<class iT>
    inline PolyLinePolygonWithHolesData& set_holes(iT inputBegin, iT inputEnd) {
      return *this;
    }

    inline ScanLineToPolygonItrs() : tailMap_(), outputPolygons_(), fractureHoles_(false)  {}

    inline ScanLineToPolygonItrs(bool fractureHoles) : tailMap_(), outputPolygons_(), fractureHoles_(fractureHoles) {}


    ~ScanLineToPolygonItrs() { clearOutput_(); }

  template <class T>
  inline bool to_bool(const T& val) { return val != 0; }

  template <typename Unit>
  inline PolyLine<Unit>::PolyLine() : ptdata_() ,headp_(0), tailp_(0), state_(-1) {}

  template <typename Unit>
  inline PolyLine<Unit>::PolyLine(orientation_2d orient, Unit coord, Side side) :
    ptdata_(1, coord),
    headp_(0),
    tailp_(0),
    state_(orient.to_int() +
           (side << 3)) {}

  template <typename Unit>
  inline PolyLine<Unit>::PolyLine(const PolyLine<Unit>& pline) : ptdata_(pline.ptdata_),
                                                     headp_(pline.headp_),
                                                     tailp_(pline.tailp_),
                                                     state_(pline.state_) {}

  template <typename Unit>
  inline PolyLine<Unit>::~PolyLine() {
    //clear out data just in case it is read later
    headp_ = tailp_ = 0;
    state_ = 0;
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::operator=(const PolyLine<Unit>& that) {
    if(!(this == &that)) {
      headp_ = that.headp_;
      tailp_ = that.tailp_;
      ptdata_ = that.ptdata_;
      state_ = that.state_;
    }
    return *this;
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::operator==(const PolyLine<Unit>& b) const {
    return this == &b || (state_ == b.state_ &&
                          headp_ == b.headp_ &&
                          tailp_ == b.tailp_);
  }

  template <typename Unit>
  inline bool PolyLine<Unit>::isValid() const {
    return state_ > -1; }

  template <typename Unit>
  inline bool PolyLine<Unit>::verticalHead() const {
    return state_ & VERTICAL_HEAD;
  }

  template <typename Unit>
  inline bool PolyLine<Unit>::oddLength() const {
    return to_bool((ptdata_.size()-1) % 2);
  }

  template <typename Unit>
  inline bool PolyLine<Unit>::verticalTail() const {
    return to_bool(verticalHead() ^ oddLength());
  }


  template <typename Unit>
  inline orientation_2d PolyLine<Unit>::tailOrient() const {
    return (verticalTail() ? VERTICAL : HORIZONTAL);
  }


  template <typename Unit>
  inline orientation_2d PolyLine<Unit>::headOrient() const {
    return (verticalHead() ? VERTICAL : HORIZONTAL);
  }


  template <typename Unit>
  inline End PolyLine<Unit>::endConnectivity(End end) const {
    //Tail should be defined as true
    if(end) { return tailToTail(); }
    return headToTail();
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::headToTail() const {
    return to_bool(state_ & HEAD_TO_TAIL);
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::headToHead() const {
    return to_bool(!headToTail());
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::tailToHead() const {
    return to_bool(!tailToTail());
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::tailToTail() const {
    return to_bool(state_ & TAIL_TO_TAIL);
  }


  template <typename Unit>
  inline Side PolyLine<Unit>::solidSide() const {
    return solidToRight(); }


  template <typename Unit>
  inline bool PolyLine<Unit>::solidToRight() const {
    return to_bool(state_ & SOLID_TO_RIGHT) != 0;
  }


  template <typename Unit>
  inline bool PolyLine<Unit>::active() const {
    return !to_bool(tailp_);
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::pushCoordinate(Unit coord) {
    ptdata_.push_back(coord);
    return *this;
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::popCoordinate() {
    ptdata_.pop_back();
    return *this;
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::pushPoint(const point_data<Unit>& point) {
    point_data<Unit> endPt = getEndPoint();
    //vertical is true, horizontal is false
    if((tailOrient().to_int() ? point.get(VERTICAL) == endPt.get(VERTICAL) : point.get(HORIZONTAL) == endPt.get(HORIZONTAL))) {
      //we were pushing a colinear segment
      return popCoordinate();
    }
    return pushCoordinate(tailOrient().to_int() ? point.get(VERTICAL) : point.get(HORIZONTAL));
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::extendTail(Unit delta) {
    ptdata_.back() += delta;
    return *this;
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinTo_(End thisEnd, PolyLine<Unit>& that, End end) {
    if(thisEnd){
      tailp_ = &that;
      state_ &= ~TAIL_TO_TAIL; //clear any previous state_ of bit (for safety)
      state_ |= (end << 2); //place bit into mask
    } else {
      headp_ = &that;
      state_ &= ~HEAD_TO_TAIL; //clear any previous state_ of bit (for safety)
      state_ |= (end << 1); //place bit into mask
    }
    return *this;
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinTo(End thisEnd, PolyLine<Unit>& that, End end) {
    joinTo_(thisEnd, that, end);
    that.joinTo_(end, *this, thisEnd);
    return *this;
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinToTail(PolyLine<Unit>& that, End end) {
    return joinTo(TAIL, that, end);
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinToHead(PolyLine<Unit>& that, End end) {
    return joinTo(HEAD, that, end);
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinHeadToHead(PolyLine<Unit>& that) {
    return joinToHead(that, HEAD);
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinHeadToTail(PolyLine<Unit>& that) {
    return joinToHead(that, TAIL);
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinTailToHead(PolyLine<Unit>& that) {
    return joinToTail(that, HEAD);
  }

  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::joinTailToTail(PolyLine<Unit>& that) {
    return joinToTail(that, TAIL);
  }


  template <typename Unit>
  inline PolyLine<Unit>& PolyLine<Unit>::disconnectTails() {
    next(TAIL)->state_ &= !TAIL_TO_TAIL;
    next(TAIL)->tailp_ = 0;
    state_ &= !TAIL_TO_TAIL;
    tailp_ = 0;
    return *this;
  }


  template <typename Unit>
  inline Unit PolyLine<Unit>::getEndCoord(End end) const {
    if(end)
      return ptdata_.back();
    return ptdata_.front();
  }


  template <typename Unit>
  inline orientation_2d PolyLine<Unit>::segmentOrient(unsigned int index) const {
    return (to_bool((unsigned int)verticalHead() ^ (index % 2)) ? VERTICAL : HORIZONTAL);
  }


  template <typename Unit>
  inline point_data<Unit> PolyLine<Unit>::getPoint(unsigned int index) const {
    //assert(isValid() && headp_->isValid()) ("PolyLine: headp_ must be valid");
    point_data<Unit> pt;
    pt.set(HORIZONTAL, ptdata_[index]);
    pt.set(VERTICAL, ptdata_[index]);
    Unit prevCoord;
    if(index == 0) {
      prevCoord = headp_->getEndCoord(headToTail());
    } else {
      prevCoord = ptdata_[index-1];
    }
    pt.set(segmentOrient(index), prevCoord);
    return pt;
  }


  template <typename Unit>
  inline point_data<Unit> PolyLine<Unit>::getEndPoint(End end) const {
    return getPoint((end ? numSegments() - 1 : (unsigned int)0));
  }


  template <typename Unit>
  inline Unit PolyLine<Unit>::operator[] (unsigned int index) const {
    //assert(ptdata_.size() > index) ("PolyLine: out of bounds index");
    return ptdata_[index];
  }


  template <typename Unit>
  inline unsigned int PolyLine<Unit>::numSegments() const {
    return ptdata_.size();
  }


  template <typename Unit>
  inline PolyLine<Unit>* PolyLine<Unit>::next(End end) const {
    return (end ? tailp_ : headp_);
  }


  template <typename Unit>
  inline ActiveTail<Unit>::ActiveTail() : tailp_(0), otherTailp_(0), holesList_() {}


  template <typename Unit>
  inline ActiveTail<Unit>::ActiveTail(orientation_2d orient, Unit coord, Side solidToRight, ActiveTail* otherTailp) :
    tailp_(0), otherTailp_(0), holesList_() {
    tailp_ = createPolyLine(orient, coord, solidToRight);
    otherTailp_ = otherTailp;
  }


  template <typename Unit>
  inline ActiveTail<Unit>::ActiveTail(PolyLine<Unit>* active, ActiveTail<Unit>* otherTailp) :
    tailp_(active), otherTailp_(otherTailp), holesList_() {}

  template <typename Unit>
  inline ActiveTail<Unit>::ActiveTail(const ActiveTail<Unit>& that) : tailp_(that.tailp_), otherTailp_(that.otherTailp_), holesList_() {}

  template <typename Unit>
  inline ActiveTail<Unit>::~ActiveTail() {
    //clear them in case the memory is read later
    tailp_ = 0; otherTailp_ = 0;
  }


  template <typename Unit>
  inline ActiveTail<Unit>& ActiveTail<Unit>::operator=(const ActiveTail<Unit>& that) {
    //self assignment is safe in this case
    tailp_ = that.tailp_;
    otherTailp_ = that.otherTailp_;
    return *this;
  }


  template <typename Unit>
  inline bool ActiveTail<Unit>::operator==(const ActiveTail<Unit>& b) const {
    return tailp_ == b.tailp_ && otherTailp_ == b.otherTailp_;
  }


  template <typename Unit>
  inline bool ActiveTail<Unit>::operator<(const ActiveTail<Unit>& b) const {
    return tailp_->getEndPoint().get(VERTICAL) < b.tailp_->getEndPoint().get(VERTICAL);
  }


  template <typename Unit>
  inline bool ActiveTail<Unit>::operator<=(const ActiveTail<Unit>& b) const {
    return !(*this > b); }


  template <typename Unit>
  inline bool ActiveTail<Unit>::operator>(const ActiveTail<Unit>& b) const {
    return b < (*this); }


  template <typename Unit>
  inline bool ActiveTail<Unit>::operator>=(const ActiveTail<Unit>& b) const {
    return !(*this < b); }


  template <typename Unit>
  inline PolyLine<Unit>* ActiveTail<Unit>::getTail() const {
    return tailp_; }


  template <typename Unit>
  inline PolyLine<Unit>* ActiveTail<Unit>::getOtherTail() const {
    return otherTailp_->tailp_; }


  template <typename Unit>
  inline ActiveTail<Unit>* ActiveTail<Unit>::getOtherActiveTail() const {
    return otherTailp_; }


  template <typename Unit>
  inline bool ActiveTail<Unit>::isOtherTail(const ActiveTail<Unit>& b) {
    //       assert( (tailp_ == b.getOtherTail() && getOtherTail() == b.tailp_) ||
    //                     (tailp_ != b.getOtherTail() && getOtherTail() != b.tailp_))
    //         ("ActiveTail: Active tails out of sync");
    return otherTailp_ == &b;
  }


  template <typename Unit>
  inline ActiveTail<Unit>& ActiveTail<Unit>::updateTail(PolyLine<Unit>* newTail) {
    tailp_ = newTail;
    return *this;
  }


  template <typename Unit>
  inline ActiveTail<Unit>* ActiveTail<Unit>::addHole(ActiveTail<Unit>* hole, bool fractureHoles) {
    if(!fractureHoles){
      holesList_.push_back(hole);
      copyHoles(*hole);
      copyHoles(*(hole->getOtherActiveTail()));
      return this;
    }
    ActiveTail<Unit>* h, *v;
    ActiveTail<Unit>* other = hole->getOtherActiveTail();
    if(other->getOrient() == VERTICAL) {
      //assert that hole.getOrient() == HORIZONTAL
      //this case should never happen
      h = hole;
      v = other;
    } else {
      //assert that hole.getOrient() == VERTICAL
      h = other;
      v = hole;
    }
    h->pushCoordinate(v->getCoordinate());
    //assert that h->getOrient() == VERTICAL
    //v->pushCoordinate(getCoordinate());
    //assert that v->getOrient() == VERTICAL
    //I can't close a figure by adding a hole, so pass zero for xMin and yMin
    std::vector<Unit> tmpVec;
    ActiveTail<Unit>::joinChains(this, h, false, tmpVec);
    return v;
  }

  template <typename output_container, typename iterator_type, typename concept_type>
  unsigned int get_polygons(output_container& container, iterator_type begin, iterator_type end,
                    orientation_2d orient, bool fracture_holes, concept_type ) {
    typedef typename output_container::value_type polygon_type;
    typedef typename std::iterator_traits<iterator_type>::value_type::first_type coordinate_type;
    polygon_type poly;
    unsigned int countPolygons = 0;
    typedef typename geometry_concept<polygon_type>::type polygon_concept_type;
    polygon_formation::ScanLineToPolygonItrs<true, coordinate_type, polygon_concept_type> scanlineToPolygonItrsV(fracture_holes);
    polygon_formation::ScanLineToPolygonItrs<false, coordinate_type, polygon_concept_type> scanlineToPolygonItrsH(fracture_holes);
    std::vector<interval_data<coordinate_type> > leftEdges;
    std::vector<interval_data<coordinate_type> > rightEdges;
    coordinate_type prevPos = (std::numeric_limits<coordinate_type>::max)();
    coordinate_type prevY = (std::numeric_limits<coordinate_type>::max)();
    int count = 0;
    for(iterator_type itr = begin;
        itr != end; ++ itr) {
      coordinate_type pos = (*itr).first;
      if(pos != prevPos) {
        if(orient == VERTICAL) {
          typename polygon_formation::ScanLineToPolygonItrs<true, coordinate_type, polygon_concept_type>::iterator itrPoly, itrPolyEnd;
          scanlineToPolygonItrsV.processEdges(itrPoly, itrPolyEnd, prevPos, leftEdges, rightEdges);
          for( ; itrPoly != itrPolyEnd; ++ itrPoly) {
            ++countPolygons;
            assign(poly, *itrPoly);
            container.insert(container.end(), poly);
          }
        } else {
          typename polygon_formation::ScanLineToPolygonItrs<false, coordinate_type, polygon_concept_type>::iterator itrPoly, itrPolyEnd;
          scanlineToPolygonItrsH.processEdges(itrPoly, itrPolyEnd, prevPos, leftEdges, rightEdges);
          for( ; itrPoly != itrPolyEnd; ++ itrPoly) {
            ++countPolygons;
            assign(poly, *itrPoly);
            container.insert(container.end(), poly);
          }
        }
        leftEdges.clear();
        rightEdges.clear();
        prevPos = pos;
        prevY = (*itr).second.first;
        count = (*itr).second.second;
        continue;
      }
      coordinate_type y = (*itr).second.first;
      if(count != 0 && y != prevY) {
        std::pair<interval_data<coordinate_type>, int> element(interval_data<coordinate_type>(prevY, y), count);
        if(element.second == 1) {
          if(leftEdges.size() && leftEdges.back().high() == element.first.low()) {
            encompass(leftEdges.back(), element.first);
          } else {
            leftEdges.push_back(element.first);
          }
        } else {
          if(rightEdges.size() && rightEdges.back().high() == element.first.low()) {
            encompass(rightEdges.back(), element.first);
          } else {
            rightEdges.push_back(element.first);
          }
        }

      }
      prevY = y;
      count += (*itr).second.second;
    }
    if(orient == VERTICAL) {
      typename polygon_formation::ScanLineToPolygonItrs<true, coordinate_type, polygon_concept_type>::iterator itrPoly, itrPolyEnd;
      scanlineToPolygonItrsV.processEdges(itrPoly, itrPolyEnd, prevPos, leftEdges, rightEdges);
      for( ; itrPoly != itrPolyEnd; ++ itrPoly) {
        ++countPolygons;
        assign(poly, *itrPoly);
        container.insert(container.end(), poly);
      }
    } else {
      typename polygon_formation::ScanLineToPolygonItrs<false, coordinate_type, polygon_concept_type>::iterator itrPoly, itrPolyEnd;
      scanlineToPolygonItrsH.processEdges(itrPoly, itrPolyEnd, prevPos, leftEdges, rightEdges);
      for( ; itrPoly != itrPolyEnd; ++ itrPoly) {
        ++countPolygons;
        assign(poly, *itrPoly);
        container.insert(container.end(), poly);
      }
    }
    return countPolygons;
  }

    inline ScanLineToRects() : scanData_(), haveCurrentRect_(), currentRect_(), orient_(), currentCoordinate_() {}


    inline ScanLineToRects(orientation_2d orient, rectangle_type model) :
      scanData_(orientation_2d(orient.to_int() ? VERTICAL : HORIZONTAL)),
      haveCurrentRect_(false), currentRect_(), orient_(orient), currentCoordinate_() {
      assign(currentRect_, model);
      currentCoordinate_ = (std::numeric_limits<coordinate_type>::max)();
    }


    inline ScanLineToRects& nextMajorCoordinate(coordinate_type currentCoordinate) {
      if(haveCurrentRect_) {
        scanData_.insert(scanData_.end(), currentRect_);
        haveCurrentRect_ = false;
      }
      currentCoordinate_ = currentCoordinate;
      return *this;
    }


  template <class CT, class ST, class rectangle_type, typename interval_type, typename coordinate_type> inline CT&
  processEdge_(CT& rectangles, ST& scanData, const interval_type& edge,
               bool& haveCurrentRect, rectangle_type& currentRect, coordinate_type currentCoordinate, orientation_2d orient)
  {
    typedef typename CT::value_type result_type;
    bool edgeProcessed = false;
    if(!scanData.empty()) {

      //process all rectangles in the scanData that touch the edge
      typename ST::iterator dataIter = scanData.lower_bound(rectangle_type(edge, edge));
      //decrement beginIter until its low is less than edge's low
      while((dataIter == scanData.end() || (*dataIter).get(orient).get(LOW) > edge.get(LOW)) &&
            dataIter != scanData.begin())
        {
          --dataIter;
        }
      //process each rectangle until the low end of the rectangle
      //is greater than the high end of the edge
      while(dataIter != scanData.end() &&
            (*dataIter).get(orient).get(LOW) <= edge.get(HIGH))
        {
          const rectangle_type& rect = *dataIter;
          //if the rectangle data intersects the edge at all
          if(rect.get(orient).get(HIGH) >= edge.get(LOW)) {
            if(contains(rect.get(orient), edge, true)) {
              //this is a closing edge
              //we need to write out the intersecting rectangle and
              //insert between 0 and 2 rectangles into the scanData
              //write out rectangle
              rectangle_type tmpRect = rect;

              if(rect.get(orient.get_perpendicular()).get(LOW) < currentCoordinate) {
                //set the high coordinate perpedicular to slicing orientation
                //to the current coordinate of the scan event
                tmpRect.set(orient.get_perpendicular().get_direction(HIGH),
                            currentCoordinate);
                result_type result;
                assign(result, tmpRect);
                rectangles.insert(rectangles.end(), result);
              }
              //erase the rectangle from the scan data
              typename ST::iterator nextIter = dataIter;
              ++nextIter;
              scanData.erase(dataIter);
              if(tmpRect.get(orient).get(LOW) < edge.get(LOW)) {
                //insert a rectangle for the overhang of the bottom
                //of the rectangle back into scan data
                rectangle_type lowRect(tmpRect);
                lowRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                currentCoordinate));
                lowRect.set(orient.get_direction(HIGH), edge.get(LOW));
                scanData.insert(nextIter, lowRect);
              }
              if(tmpRect.get(orient).get(HIGH) > edge.get(HIGH)) {
                //insert a rectangle for the overhang of the top
                //of the rectangle back into scan data
                rectangle_type highRect(tmpRect);
                highRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                 currentCoordinate));
                highRect.set(orient.get_direction(LOW), edge.get(HIGH));
                scanData.insert(nextIter, highRect);
              }
              //we are done with this edge
              edgeProcessed = true;
              break;
            } else {
              //it must be an opening edge
              //assert that rect does not overlap the edge but only touches
              //write out rectangle
              rectangle_type tmpRect = rect;
              //set the high coordinate perpedicular to slicing orientation
              //to the current coordinate of the scan event
              if(tmpRect.get(orient.get_perpendicular().get_direction(LOW)) < currentCoordinate) {
                tmpRect.set(orient.get_perpendicular().get_direction(HIGH),
                            currentCoordinate);
                result_type result;
                assign(result, tmpRect);
                rectangles.insert(rectangles.end(), result);
              }
              //erase the rectangle from the scan data
              typename ST::iterator nextIter = dataIter;
              ++nextIter;
              scanData.erase(dataIter);
              dataIter = nextIter;
              if(haveCurrentRect) {
                if(currentRect.get(orient).get(HIGH) >= edge.get(LOW)){
                  if(!edgeProcessed && currentRect.get(orient.get_direction(HIGH)) > edge.get(LOW)){
                    rectangle_type tmpRect2(currentRect);
                    tmpRect2.set(orient.get_direction(HIGH), edge.get(LOW));
                    scanData.insert(nextIter, tmpRect2);
                    if(currentRect.get(orient.get_direction(HIGH)) > edge.get(HIGH)) {
                      currentRect.set(orient, interval_data<coordinate_type>(edge.get(HIGH), currentRect.get(orient.get_direction(HIGH))));
                    } else {
                      haveCurrentRect = false;
                    }
                  } else {
                    //extend the top of current rect
                    currentRect.set(orient.get_direction(HIGH),
                                    (std::max)(edge.get(HIGH),
                                               tmpRect.get(orient.get_direction(HIGH))));
                  }
                } else {
                  //insert current rect into the scanData
                  scanData.insert(nextIter, currentRect);
                  //create a new current rect
                  currentRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                      currentCoordinate));
                  currentRect.set(orient, interval_data<coordinate_type>((std::min)(tmpRect.get(orient).get(LOW),
                                                       edge.get(LOW)),
                                                                         (std::max)(tmpRect.get(orient).get(HIGH),
                                                       edge.get(HIGH))));
                }
              } else {
                haveCurrentRect = true;
                currentRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                    currentCoordinate));
                currentRect.set(orient, interval_data<coordinate_type>((std::min)(tmpRect.get(orient).get(LOW),
                                                     edge.get(LOW)),
                                                                       (std::max)(tmpRect.get(orient).get(HIGH),
                                                     edge.get(HIGH))));
              }
              //skip to nextIter position
              edgeProcessed = true;
              continue;
            }
            //edgeProcessed = true;
          }
          ++dataIter;
        } //end while edge intersects rectangle data

    }
    if(!edgeProcessed) {
      if(haveCurrentRect) {
        if(currentRect.get(orient.get_perpendicular().get_direction(HIGH))
           == currentCoordinate &&
           currentRect.get(orient.get_direction(HIGH)) >= edge.get(LOW))
          {
            if(currentRect.get(orient.get_direction(HIGH)) > edge.get(LOW)){
              rectangle_type tmpRect(currentRect);
              tmpRect.set(orient.get_direction(HIGH), edge.get(LOW));
              scanData.insert(scanData.end(), tmpRect);
              if(currentRect.get(orient.get_direction(HIGH)) > edge.get(HIGH)) {
                currentRect.set(orient,
                                interval_data<coordinate_type>(edge.get(HIGH),
                                         currentRect.get(orient.get_direction(HIGH))));
                return rectangles;
              } else {
                haveCurrentRect = false;
                return rectangles;
              }
            }
            //extend current rect
            currentRect.set(orient.get_direction(HIGH), edge.get(HIGH));
            return rectangles;
          }
        scanData.insert(scanData.end(), currentRect);
        haveCurrentRect = false;
      }
      rectangle_type tmpRect(currentRect);
      tmpRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                      currentCoordinate));
      tmpRect.set(orient, edge);
      scanData.insert(tmpRect);
      return rectangles;
    }
    return rectangles;

  }

  template <class CT>
  inline
  ScanLineToRects<T>& ScanLineToRects<T>::processEdge(CT& rectangles, const interval_data<coordinate_type>& edge)
  {
    processEdge_(rectangles, scanData_, edge, haveCurrentRect_, currentRect_, currentCoordinate_, orient_);
    return *this;
  }


  template <typename output_container, typename iterator_type, typename rectangle_concept>
  void form_rectangles(output_container& output, iterator_type begin, iterator_type end,
                       orientation_2d orient, rectangle_concept ) {
    typedef typename output_container::value_type rectangle_type;
    typedef typename get_coordinate_type_for_rectangles<rectangle_type, typename geometry_concept<rectangle_type>::type>::type Unit;
    rectangle_data<Unit> model;
    Unit prevPos = (std::numeric_limits<Unit>::max)();
    rectangle_formation::ScanLineToRects<rectangle_data<Unit> > scanlineToRects(orient, model);
    for(iterator_type itr = begin;
        itr != end; ++ itr) {
      Unit pos = (*itr).first;
      if(pos != prevPos) {
        scanlineToRects.nextMajorCoordinate(pos);
        prevPos = pos;
      }
      Unit lowy = (*itr).second.first;
      iterator_type tmp_itr = itr;
      ++itr;
      Unit highy = (*itr).second.first;
      scanlineToRects.processEdge(output, interval_data<Unit>(lowy, highy));
      if(abs((*itr).second.second) > 1) itr = tmp_itr; //next edge begins from this vertex
    }
  }

      Node() : children_(), tracedPaths_(), rect() {}

      Node(const Rectangle rectIn) : children_(), tracedPaths_(), rect(rectIn) {}

      inline iterator begin() { return children_.begin(); }

      inline iterator end() { return children_.end(); }

      inline void add(Node* child) { children_.push_back(child); }

      inline bool tracedPath(const Interval& ivl) const {
        return tracedPaths_.find(ivl) != tracedPaths_.end();
      }

      inline void addPath(const Interval& ivl) {
        tracedPaths_.insert(tracedPaths_.end(), ivl);
      }

      inline lessEdgeAssociation() {}

      inline bool operator () (const EdgeAssociation& elem1, const EdgeAssociation& elem2) const {
        if(elem1.first.first < elem2.first.first) return true;
        if(elem1.first.first > elem2.first.first) return false;
        return elem1.first.second < elem2.first.second;
      }


    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient) {
      Interval rectIvl = node->rect.get(orient);
      if(node->tracedPath(rectIvl)) {
        return;
      }
      node->addPath(rectIvl);
      if(node->begin() == node->end()) {
        //std::cout << "WRITE OUT 3: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
        return;
      }
      bool writeOut = true;
      for(typename Node::iterator itr = node->begin(); itr != node->end(); ++itr) {
        getMaxCover(outputContainer, *itr, orient, node->rect); //get rectangles down path
        Interval nodeIvl = (*itr)->rect.get(orient);
        if(contains(nodeIvl, rectIvl, true)) writeOut = false;
      }
      if(writeOut) {
        //std::cout << "WRITE OUT 2: " << node->rect << std::endl;
        outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(node->rect));
      }
    }

      inline stack_element() :
        node(), rect(), itr() {}

      inline stack_element(Node* n,
                           const Rectangle& r,
                           typename Node::iterator i) :
        node(n), rect(r), itr(i) {}


    template <class cT>
    static inline void getMaxCover(cT& outputContainer, Node* node, orientation_2d orient,
                                   Rectangle rect) {
      //std::cout << "New Root\n";
      std::vector<stack_element> stack;
      typename Node::iterator itr = node->begin();
      do {
        //std::cout << "LOOP\n";
        //std::cout << node->rect << std::endl;
        Interval rectIvl = rect.get(orient);
        Interval nodeIvl = node->rect.get(orient);
        bool iresult = intersect(rectIvl, nodeIvl, false);
        bool tresult = !node->tracedPath(rectIvl);
        //std::cout << (itr != node->end()) << " " << iresult << " " << tresult << std::endl;
        Rectangle nextRect1 = Rectangle(rectIvl, rectIvl);
        Unit low = rect.get(orient.get_perpendicular()).low();
        Unit high = node->rect.get(orient.get_perpendicular()).high();
        nextRect1.set(orient.get_perpendicular(), Interval(low, high));
        if(iresult && tresult) {
          node->addPath(rectIvl);
          bool writeOut = true;
          //check further visibility beyond this node
          for(typename Node::iterator itr2 = node->begin(); itr2 != node->end(); ++itr2) {
            Interval nodeIvl3 = (*itr2)->rect.get(orient);
            //if a child of this node can contain the interval then we can extend through
            if(contains(nodeIvl3, rectIvl, true)) writeOut = false;
            //std::cout << "child " << (*itr2)->rect << std::endl;
          }
          Rectangle nextRect2 = Rectangle(rectIvl, rectIvl);
          Unit low2 = rect.get(orient.get_perpendicular()).low();
          Unit high2 = node->rect.get(orient.get_perpendicular()).high();
          nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
          if(writeOut) {
            //std::cout << "write out " << nextRect << std::endl;
            outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect2));
          } else {
            //std::cout << "supress " << nextRect << std::endl;
          }
        }
        if(itr != node->end() && iresult && tresult) {
          //std::cout << "recurse into child\n";
          stack.push_back(stack_element(node, rect, itr));
          rect = nextRect1;
          node = *itr;
          itr = node->begin();
        } else {
          if(!stack.empty()) {
            //std::cout << "recurse out of child\n";
            node = stack.back().node;
            rect = stack.back().rect;
            itr = stack.back().itr;
            stack.pop_back();
          } else {
            //std::cout << "empty stack\n";
            //if there were no children of the root node
//             Rectangle nextRect = Rectangle(rectIvl, rectIvl);
//             Unit low = rect.get(orient.get_perpendicular()).low();
//             Unit high = node->rect.get(orient.get_perpendicular()).high();
//             nextRect.set(orient.get_perpendicular(), Interval(low, high));
//             outputContainer.push_back(copy_construct<typename cT::value_type, Rectangle>(nextRect));
          }
          //std::cout << "increment " << (itr != node->end()) << std::endl;
          if(itr != node->end()) {
            ++itr;
            if(itr != node->end()) {
              //std::cout << "recurse into next child.\n";
              stack.push_back(stack_element(node, rect, itr));
              Interval rectIvl2 = rect.get(orient);
              Interval nodeIvl2 = node->rect.get(orient);
              /*bool iresult =*/ intersect(rectIvl2, nodeIvl2, false);
              Rectangle nextRect2 = Rectangle(rectIvl2, rectIvl2);
              Unit low2 = rect.get(orient.get_perpendicular()).low();
              Unit high2 = node->rect.get(orient.get_perpendicular()).high();
              nextRect2.set(orient.get_perpendicular(), Interval(low2, high2));
              rect = nextRect2;
              //std::cout << "rect for next child" << rect << std::endl;
              node = *itr;
              itr = node->begin();
            }
          }
        }
      } while(!stack.empty() || itr != node->end());
    }

    template <class iT>
    static inline void computeDag(iT beginNode, iT endNode, orientation_2d orient,
                                  std::size_t size) {
      std::vector<EdgeAssociation> leadingEdges;
      leadingEdges.reserve(size);
      for(iT iter = beginNode; iter != endNode; ++iter) {
        Node* nodep = &(*iter);
        Unit leading = nodep->rect.get(orient.get_perpendicular()).low();
        Interval rectIvl = nodep->rect.get(orient);
        leadingEdges.push_back(EdgeAssociation(std::pair<Unit, Interval>(leading, rectIvl), nodep));
      }
      polygon_sort(leadingEdges.begin(), leadingEdges.end(), lessEdgeAssociation());
      typename std::vector<EdgeAssociation>::iterator leadingBegin = leadingEdges.begin();
      iT trailingBegin = beginNode;
      while(leadingBegin != leadingEdges.end()) {
        EdgeAssociation& leadingSegment = (*leadingBegin);
        Unit trailing = (*trailingBegin).rect.get(orient.get_perpendicular()).high();
        Interval ivl = (*trailingBegin).rect.get(orient);
        std::pair<Unit, Interval> trailingSegment(trailing, ivl);
        if(leadingSegment.first.first < trailingSegment.first) {
          ++leadingBegin;
          continue;
        }
        if(leadingSegment.first.first > trailingSegment.first) {
          ++trailingBegin;
          continue;
        }
        if(leadingSegment.first.second.high() <= trailingSegment.second.low()) {
          ++leadingBegin;
          continue;
        }
        if(trailingSegment.second.high() <= leadingSegment.first.second.low()) {
          ++trailingBegin;
          continue;
        }
        //leading segment intersects trailing segment
        (*trailingBegin).add((*leadingBegin).second);
        if(leadingSegment.first.second.high() > trailingSegment.second.high()) {
          ++trailingBegin;
          continue;
        }
        if(trailingSegment.second.high() > leadingSegment.first.second.high()) {
          ++leadingBegin;
          continue;
        }
        ++leadingBegin;
        ++trailingBegin;
      }
    }

  inline property_merge_point() : x_(), y_() {}

  inline property_merge_point(coordinate_type x, coordinate_type y) : x_(x), y_(y) {}

  inline bool operator==(const property_merge_point& that) const { return x_ == that.x_ && y_ == that.y_; }

  inline bool operator!=(const property_merge_point& that) const { return !((*this) == that); }

  inline bool operator<(const property_merge_point& that) const {
    if(x_ < that.x_) return true;
    if(x_ > that.x_) return false;
    return y_ < that.y_;
  }

  inline coordinate_type x() const { return x_; }

  inline coordinate_type y() const { return y_; }

  inline void x(coordinate_type value) { x_ = value; }

  inline void y(coordinate_type value) { y_ = value; }

  inline property_merge_interval() : low_(), high_() {}

  inline property_merge_interval(coordinate_type low, coordinate_type high) : low_(low), high_(high) {}

  inline bool operator==(const property_merge_interval& that) const { return low_ == that.low_ && high_ == that.high_; }

  inline bool operator!=(const property_merge_interval& that) const { return !((*this) == that); }

  inline bool operator<(const property_merge_interval& that) const {
    if(low_ < that.low_) return true;
    if(low_ > that.low_) return false;
    return high_ < that.high_;
  }

  inline coordinate_type low() const { return low_; }

  inline coordinate_type high() const { return high_; }

  inline void low(coordinate_type value) { low_ = value; }

  inline void high(coordinate_type value) { high_ = value; }


  template <typename iT, typename orientation_2d_type>
  static inline void
  populate_property_merge_data(property_merge_data& pmd, iT input_begin, iT input_end,
                               const property_type& property, orientation_2d_type orient) {
    for( ; input_begin != input_end; ++input_begin) {
      std::pair<property_merge_point<coordinate_type>, std::pair<property_type, int> > element;
      if(orient == HORIZONTAL)
        element.first = property_merge_point<coordinate_type>((*input_begin).second.first, (*input_begin).first);
      else
        element.first = property_merge_point<coordinate_type>((*input_begin).first, (*input_begin).second.first);
      element.second.first = property;
      element.second.second = (*input_begin).second.second;
      pmd.push_back(element);
    }
  }


  merge_scanline() : output(), scanline(), currentVertex(), tmpVector(), previousY(), countFromBelow(), scanlinePosition() {}

  merge_scanline(const merge_scanline& that) :
    output(that.output),
    scanline(that.scanline),
    currentVertex(that.currentVertex),
    tmpVector(that.tmpVector),
    previousY(that.previousY),
    countFromBelow(that.countFromBelow),
    scanlinePosition(that.scanlinePosition)
  {}

  merge_scanline& operator=(const merge_scanline& that) {
    output = that.output;
    scanline = that.scanline;
    currentVertex = that.currentVertex;
    tmpVector = that.tmpVector;
    previousY = that.previousY;
    countFromBelow = that.countFromBelow;
    scanlinePosition = that.scanlinePosition;
    return *this;
  }


  template <typename result_type>
  inline void perform_merge(result_type& result, property_merge_data& data) {
    if(data.empty()) return;
    //sort
    polygon_sort(data.begin(), data.end(), less_vertex_data<vertex_property>());
    //scanline
    bool firstIteration = true;
    scanlinePosition = scanline.end();
    for(std::size_t i = 0; i < data.size(); ++i) {
      if(firstIteration) {
        mergeProperty(currentVertex.second, data[i].second);
        currentVertex.first = data[i].first;
        firstIteration = false;
      } else {
        if(data[i].first != currentVertex.first) {
          if(data[i].first.x() != currentVertex.first.x()) {
            processVertex(output);
            //std::cout << scanline.size() << " ";
            countFromBelow.clear(); //should already be clear
            writeOutput(currentVertex.first.x(), result, output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
            //std::cout << assertRedundant(scanline) << "/" << scanline.size() << " ";
          } else {
            processVertex(output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          }
        } else {
          mergeProperty(currentVertex.second, data[i].second);
        }
      }
    }
    processVertex(output);
    writeOutput(currentVertex.first.x(), result, output);
    //std::cout << assertRedundant(scanline) << "/" << scanline.size() << "\n";
    //std::cout << scanline.size() << "\n";
  }

    less_vertex_data() {}

    bool operator()(const T& lvalue, const T& rvalue) const {
      if(lvalue.first.x() < rvalue.first.x()) return true;
      if(lvalue.first.x() > rvalue.first.x()) return false;
      if(lvalue.first.y() < rvalue.first.y()) return true;
      return false;
    }

    lessPropertyCount() {}

    bool operator()(const T& a, const T& b) {
      return a.first < b.first;
    }


  static inline void mergeProperty(property_map& lvalue, std::pair<property_type, int>& rvalue) {
    typename property_map::iterator itr = std::lower_bound(lvalue.begin(), lvalue.end(), rvalue,
                                                          lessPropertyCount<std::pair<property_type, int> >());
    if(itr == lvalue.end() ||
       (*itr).first != rvalue.first) {
      lvalue.insert(itr, rvalue);
    } else {
      (*itr).second += rvalue.second;
      if((*itr).second == 0)
        lvalue.erase(itr);
    }
//     if(assertSorted(lvalue)) {
//       std::cout << "in mergeProperty\n";
//       exit(0);
//     }
  }


  static inline void setProperty(property_set& pset, property_map& pmap) {
    for(typename property_map::iterator itr = pmap.begin(); itr != pmap.end(); ++itr) {
      if((*itr).second > 0) {
        pset.insert(pset.end(), (*itr).first);
      }
    }
  }


  inline void mergeCount(property_map& lvalue, property_map& rvalue) {
    typename property_map::iterator litr = lvalue.begin();
    typename property_map::iterator ritr = rvalue.begin();
    tmpVector.clear();
    while(litr != lvalue.end() && ritr != rvalue.end()) {
      if((*litr).first <= (*ritr).first) {
        if(!tmpVector.empty() &&
           (*litr).first == tmpVector.back().first) {
          tmpVector.back().second += (*litr).second;
        } else {
          tmpVector.push_back(*litr);
        }
        ++litr;
      } else if((*ritr).first <= (*litr).first) {
        if(!tmpVector.empty() &&
           (*ritr).first == tmpVector.back().first) {
          tmpVector.back().second += (*ritr).second;
        } else {
          tmpVector.push_back(*ritr);
        }
        ++ritr;
      }
    }
    while(litr != lvalue.end()) {
      if(!tmpVector.empty() &&
         (*litr).first == tmpVector.back().first) {
        tmpVector.back().second += (*litr).second;
      } else {
        tmpVector.push_back(*litr);
      }
      ++litr;
    }
    while(ritr != rvalue.end()) {
      if(!tmpVector.empty() &&
         (*ritr).first == tmpVector.back().first) {
        tmpVector.back().second += (*ritr).second;
      } else {
        tmpVector.push_back(*ritr);
      }
      ++ritr;
    }
    lvalue.clear();
    for(std::size_t i = 0; i < tmpVector.size(); ++i) {
      if(tmpVector[i].second != 0) {
        lvalue.push_back(tmpVector[i]);
      }
    }
//     if(assertSorted(lvalue)) {
//       std::cout << "in mergeCount\n";
//       exit(0);
//     }
  }


  inline void processVertex(edge_property_vector& output) {
    if(!countFromBelow.empty()) {
      //we are processing an interval of change in scanline state between
      //previous vertex position and current vertex position where
      //count from below represents the change on the interval
      //foreach scanline element from previous to current we
      //write the interval on the scanline that is changing
      //the old value and the new value to output
      property_merge_interval<coordinate_type> currentInterval(previousY, currentVertex.first.y());
      coordinate_type currentY = currentInterval.low();
      if(scanlinePosition == scanline.end() ||
         (*scanlinePosition).first != previousY) {
        scanlinePosition = scanline.lower_bound(previousY);
      }
      scanline_iterator previousScanlinePosition = scanlinePosition;
      ++scanlinePosition;
      while(scanlinePosition != scanline.end()) {
        coordinate_type elementY = (*scanlinePosition).first;
        if(elementY <= currentInterval.high()) {
          property_map& countOnLeft = (*previousScanlinePosition).second;
          edge_property element;
          output.push_back(element);
          output.back().first = property_merge_interval<coordinate_type>((*previousScanlinePosition).first, elementY);
          setProperty(output.back().second.first, countOnLeft);
          mergeCount(countOnLeft, countFromBelow);
          setProperty(output.back().second.second, countOnLeft);
          if(output.back().second.first == output.back().second.second) {
            output.pop_back(); //it was an internal vertical edge, not to be output
          }
          else if(output.size() > 1) {
            edge_property& secondToLast = output[output.size()-2];
            if(secondToLast.first.high() == output.back().first.low() &&
               secondToLast.second.first == output.back().second.first &&
               secondToLast.second.second == output.back().second.second) {
              //merge output onto previous output because properties are
              //identical on both sides implying an internal horizontal edge
              secondToLast.first.high(output.back().first.high());
              output.pop_back();
            }
          }
          if(previousScanlinePosition == scanline.begin()) {
            if(countOnLeft.empty()) {
              scanline.erase(previousScanlinePosition);
            }
          } else {
            scanline_iterator tmpitr = previousScanlinePosition;
            --tmpitr;
            if((*tmpitr).second == (*previousScanlinePosition).second)
              scanline.erase(previousScanlinePosition);
          }

        } else if(currentY < currentInterval.high()){
          //elementY > currentInterval.high()
          //split the interval between previous and current scanline elements
          std::pair<coordinate_type, property_map> elementScan;
          elementScan.first = currentInterval.high();
          elementScan.second = (*previousScanlinePosition).second;
          scanlinePosition = scanline.insert(scanlinePosition, elementScan);
          continue;
        } else {
          break;
        }
        previousScanlinePosition = scanlinePosition;
        currentY = previousY = elementY;
        ++scanlinePosition;
        if(scanlinePosition == scanline.end() &&
           currentY < currentInterval.high()) {
          //insert a new element for top of range
          std::pair<coordinate_type, property_map> elementScan;
          elementScan.first = currentInterval.high();
          scanlinePosition = scanline.insert(scanline.end(), elementScan);
        }
      }
      if(scanlinePosition == scanline.end() &&
         currentY < currentInterval.high()) {
        //handle case where we iterated to end of the scanline
        //we need to insert an element into the scanline at currentY
        //with property value coming from below
        //and another one at currentInterval.high() with empty property value
        mergeCount(scanline[currentY], countFromBelow);
        std::pair<coordinate_type, property_map> elementScan;
        elementScan.first = currentInterval.high();
        scanline.insert(scanline.end(), elementScan);

        edge_property element;
        output.push_back(element);
        output.back().first = property_merge_interval<coordinate_type>(currentY, currentInterval.high());
        setProperty(output.back().second.second, countFromBelow);
        mergeCount(countFromBelow, currentVertex.second);
      } else {
        mergeCount(countFromBelow, currentVertex.second);
        if(countFromBelow.empty()) {
          if(previousScanlinePosition == scanline.begin()) {
            if((*previousScanlinePosition).second.empty()) {
              scanline.erase(previousScanlinePosition);
              //previousScanlinePosition = scanline.end();
              //std::cout << "ERASE_A ";
            }
          } else {
            scanline_iterator tmpitr = previousScanlinePosition;
            --tmpitr;
            if((*tmpitr).second == (*previousScanlinePosition).second) {
              scanline.erase(previousScanlinePosition);
              //previousScanlinePosition = scanline.end();
              //std::cout << "ERASE_B ";
            }
          }
        }
      }
    } else {
      //count from below is empty, we are starting a new interval of change
      countFromBelow = currentVertex.second;
      scanlinePosition = scanline.lower_bound(currentVertex.first.y());
      if(scanlinePosition != scanline.end()) {
        if((*scanlinePosition).first != currentVertex.first.y()) {
          if(scanlinePosition != scanline.begin()) {
            //decrement to get the lower position of the first interval this vertex intersects
            --scanlinePosition;
            //insert a new element into the scanline for the incoming vertex
            property_map& countOnLeft = (*scanlinePosition).second;
            std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
            scanlinePosition = scanline.insert(scanlinePosition, element);
          } else {
            property_map countOnLeft;
            std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
            scanlinePosition = scanline.insert(scanlinePosition, element);
          }
        }
      } else {
        property_map countOnLeft;
        std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
        scanlinePosition = scanline.insert(scanlinePosition, element);
      }
    }
    previousY = currentVertex.first.y();
  }


  template <typename T>
  inline int assertRedundant(T& t) {
    if(t.empty()) return 0;
    int count = 0;
    typename T::iterator itr = t.begin();
    if((*itr).second.empty())
      ++count;
    typename T::iterator itr2 = itr;
    ++itr2;
    while(itr2 != t.end()) {
      if((*itr).second == (*itr2).second)
        ++count;
      itr = itr2;
      ++itr2;
    }
    return count;
  }


  template <typename T>
  inline void performExtract(T& result, property_merge_data& data) {
    if(data.empty()) return;
    //sort
    polygon_sort(data.begin(), data.end(), less_vertex_data<vertex_property>());

    //scanline
    bool firstIteration = true;
    scanlinePosition = scanline.end();
    for(std::size_t i = 0; i < data.size(); ++i) {
      if(firstIteration) {
        mergeProperty(currentVertex.second, data[i].second);
        currentVertex.first = data[i].first;
        firstIteration = false;
      } else {
        if(data[i].first != currentVertex.first) {
          if(data[i].first.x() != currentVertex.first.x()) {
            processVertex(output);
            //std::cout << scanline.size() << " ";
            countFromBelow.clear(); //should already be clear
            writeGraph(currentVertex.first.x(), result, output, scanline);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          } else {
            processVertex(output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          }
        } else {
          mergeProperty(currentVertex.second, data[i].second);
        }
      }
    }
    processVertex(output);
    writeGraph(currentVertex.first.x(), result, output, scanline);
    //std::cout << scanline.size() << "\n";
  }


  template <typename T>
  inline void insertEdges(T& graph, property_set& p1, property_set& p2) {
    for(typename property_set::iterator itr = p1.begin(); itr != p1.end(); ++itr) {
      for(typename property_set::iterator itr2 = p2.begin(); itr2 != p2.end(); ++itr2) {
        if(*itr != *itr2) {
          graph[*itr].insert(*itr2);
          graph[*itr2].insert(*itr);
        }
      }
    }
  }


  template <typename T>
  inline void propertySetAbove(coordinate_type y, property_set& ps, T& scanline) {
    ps.clear();
    typename T::iterator itr = scanline.find(y);
    if(itr != scanline.end())
      setProperty(ps, (*itr).second);
  }


  template <typename T>
  inline void propertySetBelow(coordinate_type y, property_set& ps, T& scanline) {
    ps.clear();
    typename T::iterator itr = scanline.find(y);
    if(itr != scanline.begin()) {
      --itr;
      setProperty(ps, (*itr).second);
    }
  }


  template <typename T, typename T2>
  inline void writeGraph(coordinate_type x, T& graph, edge_property_vector& output, T2& scanline) {
    if(output.empty()) return;
    edge_property* previousEdgeP = &(output[0]);
    bool firstIteration = true;
    property_set ps;
    for(std::size_t i = 0; i < output.size(); ++i) {
      edge_property& previousEdge = *previousEdgeP;
      edge_property& edge = output[i];
      if(previousEdge.first.high() == edge.first.low()) {
        //horizontal edge
        insertEdges(graph, edge.second.first, previousEdge.second.first);
        //corner 1
        insertEdges(graph, edge.second.first, previousEdge.second.second);
        //other horizontal edge
        insertEdges(graph, edge.second.second, previousEdge.second.second);
        //corner 2
        insertEdges(graph, edge.second.second, previousEdge.second.first);
      } else {
        if(!firstIteration){
          //look up regions above previous edge
          propertySetAbove(previousEdge.first.high(), ps, scanline);
          insertEdges(graph, ps, previousEdge.second.first);
          insertEdges(graph, ps, previousEdge.second.second);
        }
        //look up regions below current edge in the scanline
        propertySetBelow(edge.first.high(), ps, scanline);
        insertEdges(graph, ps, edge.second.first);
        insertEdges(graph, ps, edge.second.second);
      }
      firstIteration = false;
      //vertical edge
      insertEdges(graph, edge.second.second, edge.second.first);
      //shared region to left
      insertEdges(graph, edge.second.second, edge.second.second);
      //shared region to right
      insertEdges(graph, edge.second.first, edge.second.first);
      previousEdgeP = &(output[i]);
    }
    edge_property& previousEdge = *previousEdgeP;
    propertySetAbove(previousEdge.first.high(), ps, scanline);
    insertEdges(graph, ps, previousEdge.second.first);
    insertEdges(graph, ps, previousEdge.second.second);
    output.clear();
  }


  template <typename Result>
  inline void writeOutput(coordinate_type x, Result& result, edge_property_vector& output) {
    for(std::size_t i = 0; i < output.size(); ++i) {
      edge_property& edge = output[i];
      //edge.second.first is the property set on the left of the edge
      if(!edge.second.first.empty()) {
        typename Result::iterator itr = result.find(edge.second.first);
        if(itr == result.end()) {
          std::pair<property_set, polygon_set_type> element(edge.second.first, polygon_set_type(VERTICAL));
          itr = result.insert(result.end(), element);
        }
        std::pair<interval_data<coordinate_type>, int> element2(interval_data<coordinate_type>(edge.first.low(), edge.first.high()), -1); //right edge of figure
        (*itr).second.insert(x, element2);
      }
      if(!edge.second.second.empty()) {
        //edge.second.second is the property set on the right of the edge
        typename Result::iterator itr = result.find(edge.second.second);
        if(itr == result.end()) {
          std::pair<property_set, polygon_set_type> element(edge.second.second, polygon_set_type(VERTICAL));
          itr = result.insert(result.end(), element);
        }
        std::pair<interval_data<coordinate_type>, int> element3(interval_data<coordinate_type>(edge.first.low(), edge.first.high()), 1); //left edge of figure
        (*itr).second.insert(x, element3);
      }
    }
    output.clear();
  }

        inline iterator() : itr_(), ivlIds_(), incremented_(false) {}

        inline iterator(const iterator& that) : itr_(), ivlIds_(), incremented_(false) { (*this) = that; }

        inline iterator& operator=(const iterator& that) {
          itr_ = that.itr_;
          ivlIds_.first = that.ivlIds_.first;
          ivlIds_.second = that.ivlIds_.second;
          incremented_ = that.incremented_;
          return *this;
        }

        inline bool operator==(const iterator& that) { return itr_ == that.itr_; }

        inline bool operator!=(const iterator& that) { return itr_ != that.itr_; }

        inline iterator& operator++() {
          //std::cout << "increment\n";
          //std::cout << "state\n";
          //for(std::set<int>::iterator itr = ivlIds_.second.begin(); itr != ivlIds_.second.end(); ++itr) {
          //   std::cout << (*itr) << " ";
          //} std::cout << std::endl;
          //std::cout << "update\n";
          for(std::set<int>::const_iterator itr = (*itr_).second.begin();
              itr != (*itr_).second.end(); ++itr) {
            //std::cout << (*itr) <<  " ";
            std::set<int>::iterator lb = ivlIds_.second.find(*itr);
            if(lb != ivlIds_.second.end()) {
              ivlIds_.second.erase(lb);
            } else {
              ivlIds_.second.insert(*itr);
            }
          }
          //std::cout << std::endl;
          //std::cout << "new state\n";
          //for(std::set<int>::iterator itr = ivlIds_.second.begin(); itr != ivlIds_.second.end(); ++itr) {
          //   std::cout << (*itr) << " ";
          //} std::cout << std::endl;
          ++itr_;
          //ivlIds_.first = Interval(ivlIds_.first.get(HIGH), itr_->first);
          incremented_ = true;
          return *this;
        }

        inline const iterator operator++(int){
          iterator tmpItr(*this);
          ++(*this);
          return tmpItr;
        }


      inline TouchScanEvent() : eventData_() {}

      template<class iT>
      inline TouchScanEvent(iT begin, iT end) : eventData_() {
        for( ; begin != end; ++begin){
          insert(*begin);
        }
      }

      inline TouchScanEvent(const TouchScanEvent& that) : eventData_(that.eventData_) {}

      inline TouchScanEvent& operator=(const TouchScanEvent& that){
        eventData_ = that.eventData_;
        return *this;
      }

      inline void insert(const std::pair<Interval, int>& intervalId){
        insert(intervalId.first.low(), intervalId.second);
        insert(intervalId.first.high(), intervalId.second);
      }

      inline void insert(Unit pos, int id) {
        typename EventData::iterator lb = eventData_.lower_bound(pos);
        if(lb != eventData_.end() && lb->first == pos) {
          std::set<int>& mr (lb->second);
          std::set<int>::iterator mri = mr.find(id);
          if(mri == mr.end()) {
            mr.insert(id);
          } else {
            mr.erase(id);
          }
        } else {
          lb = eventData_.insert(lb, std::pair<Unit, std::set<int> >(pos, std::set<int>()));
          (*lb).second.insert(id);
        }
      }

      inline void insert(const TouchScanEvent& that){
        typename EventData::const_iterator itr;
        for(itr = that.eventData_.begin(); itr != that.eventData_.end(); ++itr) {
          eventData_[(*itr).first].insert(itr->second.begin(), itr->second.end());
        }
      }

      inline iterator begin() const {
        //std::cout << "begin\n";
        if(eventData_.empty()) return end();
        typename EventData::const_iterator itr = eventData_.begin();
        Unit pos = itr->first;
        const std::set<int>& idr = itr->second;
        ++itr;
        return iterator(itr, pos, itr->first, idr);
      }

      inline iterator end() const { return iterator(eventData_.end(), 0, 0, std::set<int>()); }


      inline void clear() { eventData_.clear(); }


      inline Interval extents() const {
        if(eventData_.empty()) return Interval();
        return Interval((*(eventData_.begin())).first, (*(eventData_.rbegin())).first);
      }

      inline TouchOp () : scanData_(), nextItr_() { nextItr_ = scanData_.end(); }

      inline TouchOp (const TouchOp& that) : scanData_(that.scanData_), nextItr_() { nextItr_ = scanData_.begin(); }

      inline void advanceScan() { nextItr_ = scanData_.begin(); }

      template <typename graphT>
      inline void processInterval(graphT& outputContainer, Interval ivl, const std::set<int>& ids, bool leadingEdge) {
        //print();
        typename ScanData::iterator lowItr = lookup_(ivl.low());
        typename ScanData::iterator highItr = lookup_(ivl.high());
        //std::cout << "Interval: " << ivl << std::endl;
        //for(std::set<int>::const_iterator itr = ids.begin(); itr != ids.end(); ++itr)
        //   std::cout << (*itr) << " ";
        //std::cout << std::endl;
        //add interval to scan data if it is past the end
        if(lowItr == scanData_.end()) {
          //std::cout << "case0" << std::endl;
          lowItr = insert_(ivl.low(), ids);
          evaluateBorder_(outputContainer, ids, ids);
          highItr = insert_(ivl.high(), std::set<int>());
          return;
        }
        //ensure that highItr points to the end of the ivl
        if(highItr == scanData_.end() || (*highItr).first > ivl.high()) {
          //std::cout << "case1" << std::endl;
          //std::cout << highItr->first << std::endl;
          std::set<int> value = std::set<int>();
          if(highItr != scanData_.begin()) {
            --highItr;
            //std::cout << highItr->first << std::endl;
            //std::cout << "high set size " << highItr->second.size() << std::endl;
            value = highItr->second;
          }
          nextItr_ = highItr;
          highItr = insert_(ivl.high(), value);
        } else {
          //evaluate border with next higher interval
          //std::cout << "case1a" << std::endl;
          if(leadingEdge)evaluateBorder_(outputContainer, highItr->second, ids);
        }
        //split the low interval if needed
        if(lowItr->first > ivl.low()) {
          //std::cout << "case2" << std::endl;
          if(lowItr != scanData_.begin()) {
            //std::cout << "case3" << std::endl;
            --lowItr;
            nextItr_ = lowItr;
            //std::cout << lowItr->first << " " << lowItr->second.size() << std::endl;
            lowItr = insert_(ivl.low(), lowItr->second);
          } else {
            //std::cout << "case4" << std::endl;
            nextItr_ = lowItr;
            lowItr = insert_(ivl.low(), std::set<int>());
          }
        } else {
          //evaluate border with next higher interval
          //std::cout << "case2a" << std::endl;
          typename ScanData::iterator nextLowerItr = lowItr;
          if(leadingEdge && nextLowerItr != scanData_.begin()){
            --nextLowerItr;
            evaluateBorder_(outputContainer, nextLowerItr->second, ids);
          }
        }
        //std::cout << "low: " << lowItr->first << " high: " << highItr->first << std::endl;
        //print();
        //process scan data intersecting interval
        for(typename ScanData::iterator itr = lowItr; itr != highItr; ){
          //std::cout << "case5" << std::endl;
          //std::cout << itr->first << std::endl;
          std::set<int>& beforeIds = itr->second;
          ++itr;
          evaluateInterval_(outputContainer, beforeIds, ids, leadingEdge);
        }
        //print();
        //merge the bottom interval with the one below if they have the same count
        if(lowItr != scanData_.begin()){
          //std::cout << "case6" << std::endl;
          typename ScanData::iterator belowLowItr = lowItr;
          --belowLowItr;
          if(belowLowItr->second == lowItr->second) {
            //std::cout << "case7" << std::endl;
            scanData_.erase(lowItr);
          }
        }
        //merge the top interval with the one above if they have the same count
        if(highItr != scanData_.begin()) {
          //std::cout << "case8" << std::endl;
          typename ScanData::iterator beforeHighItr = highItr;
          --beforeHighItr;
          if(beforeHighItr->second == highItr->second) {
            //std::cout << "case9" << std::endl;
            scanData_.erase(highItr);
            highItr = beforeHighItr;
            ++highItr;
          }
        }
        //print();
        nextItr_ = highItr;
      }


    template <typename graphT>
    static inline void processEvent(graphT& outputContainer, TouchOp& op, const TouchScanEvent& data, bool leadingEdge) {
      for(typename TouchScanEvent::iterator itr = data.begin(); itr != data.end(); ++itr) {
        //std::cout << "processInterval" << std::endl;
        op.processInterval(outputContainer, (*itr).first, (*itr).second, leadingEdge);
      }
    }


    template <typename graphT>
    static inline void performTouch(graphT& outputContainer, const TouchSetData& data) {
      typename std::map<Unit, TouchScanEvent>::const_iterator leftItr = data.first.begin();
      typename std::map<Unit, TouchScanEvent>::const_iterator rightItr = data.second.begin();
      typename std::map<Unit, TouchScanEvent>::const_iterator leftEnd = data.first.end();
      typename std::map<Unit, TouchScanEvent>::const_iterator rightEnd = data.second.end();
      TouchOp op;
      while(leftItr != leftEnd || rightItr != rightEnd) {
        //std::cout << "loop" << std::endl;
        op.advanceScan();
        //rightItr cannont be at end if leftItr is not at end
        if(leftItr != leftEnd && rightItr != rightEnd &&
           leftItr->first <= rightItr->first) {
          //std::cout << "case1" << std::endl;
          //std::cout << leftItr ->first << std::endl;
          processEvent(outputContainer, op, leftItr->second, true);
          ++leftItr;
        } else {
          //std::cout << "case2" << std::endl;
          //std::cout << rightItr ->first << std::endl;
          processEvent(outputContainer, op, rightItr->second, false);
          ++rightItr;
        }
      }
    }


    template <class iT>
    static inline void populateTouchSetData(TouchSetData& data, iT beginData, iT endData, int id) {
      Unit prevPos = ((std::numeric_limits<Unit>::max)());
      Unit prevY = prevPos;
      int count = 0;
      for(iT itr = beginData; itr != endData; ++itr) {
        Unit pos = (*itr).first;
        if(pos != prevPos) {
          prevPos = pos;
          prevY = (*itr).second.first;
          count = (*itr).second.second;
          continue;
        }
        Unit y = (*itr).second.first;
        if(count != 0 && y != prevY) {
          std::pair<Interval, int> element(Interval(prevY, y), id);
          if(count > 0) {
            data.first[pos].insert(element);
          } else {
            data.second[pos].insert(element);
          }
        }
        prevY = y;
        count += (*itr).second.second;
      }
    }

  iterator_geometry_to_set() : rectangle_(), vertex_(), corner_(4), orient_(), is_hole_() {}

  iterator_geometry_to_set(const rectangle_type& rectangle, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    rectangle_(), vertex_(), corner_(0), orient_(orient), is_hole_(is_hole) {
    assign(rectangle_, rectangle);
    if(dir == HIGH) corner_ = 4;
  }

  inline iterator_geometry_to_set& operator++() {
    ++corner_;
    return *this;
  }

  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_geometry_to_set& that) const {
    return corner_ == that.corner_;
  }

  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }

  inline reference operator*() const {
    if(corner_ == 0) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), LOW);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 1) {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = -1;
      if(is_hole_) vertex_.second.second *= -1;
    } else if(corner_ == 2) {
      vertex_.first = get(get(rectangle_, orient_.get_perpendicular()), HIGH);
      vertex_.second.first = get(get(rectangle_, orient_), LOW);
    } else {
      vertex_.second.first = get(get(rectangle_, orient_), HIGH);
      vertex_.second.second = 1;
      if(is_hole_) vertex_.second.second *= -1;
    }
    return vertex_;
  }

  iterator_geometry_to_set() : vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {}

  iterator_geometry_to_set(const polygon_type& polygon, direction_1d dir, orientation_2d orient = HORIZONTAL, bool is_hole = false, bool winding_override = false, direction_1d w = CLOCKWISE) :
    vertex_(), itrb(), itre(), last_vertex_(),
    is_hole_(is_hole), multiplier_(), first_pt(), second_pt(), pts(), use_wrap(),
    orient_(orient), polygon_index(0) {
    itrb = begin_points(polygon);
    itre = end_points(polygon);
    use_wrap = false;
    if(itrb == itre || dir == HIGH || size(polygon) < 4) {
      polygon_index = -1;
    } else {
      direction_1d wdir = w;
      if(!winding_override)
        wdir = winding(polygon);
      multiplier_ = wdir == LOW ? -1 : 1;
      if(is_hole_) multiplier_ *= -1;
      first_pt = pts[0] = *itrb;
      ++itrb;
      second_pt = pts[1] = *itrb;
      ++itrb;
      pts[2] = *itrb;
      evaluate_();
    }
  }

  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    vertex_(), itrb(), itre(), last_vertex_(), is_hole_(), multiplier_(), first_pt(),
    second_pt(), pts(), use_wrap(), orient_(), polygon_index(-1) {
    vertex_ = that.vertex_;
    itrb = that.itrb;
    itre = that.itre;
    last_vertex_ = that.last_vertex_;
    is_hole_ = that.is_hole_;
    multiplier_ = that.multiplier_;
    first_pt = that.first_pt;
    second_pt = that.second_pt;
    pts[0] = that.pts[0];
    pts[1] = that.pts[1];
    pts[2] = that.pts[2];
    use_wrap = that.use_wrap;
    orient_ = that.orient_;
    polygon_index = that.polygon_index;
  }

  inline iterator_geometry_to_set& operator++() {
    ++polygon_index;
    if(itrb == itre) {
      if(first_pt == pts[1]) polygon_index = -1;
      else {
        pts[0] = pts[1];
        pts[1] = pts[2];
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      }
    } else {
      ++itrb;
      pts[0] = pts[1];
      pts[1] = pts[2];
      if(itrb == itre) {
        if(first_pt == pts[2]) {
          pts[2] = second_pt;
        } else {
          pts[2] = first_pt;
        }
      } else {
        pts[2] = *itrb;
      }
    }
    evaluate_();
    return *this;
  }

  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_geometry_to_set& that) const {
    return polygon_index == that.polygon_index;
  }

  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }

  inline reference operator*() const {
    return vertex_;
  }


  inline void evaluate_() {
    vertex_.first = pts[1].get(orient_.get_perpendicular());
    vertex_.second.first =pts[1].get(orient_);
    if(pts[1] == pts[2]) {
      vertex_.second.second = 0;
    } else if(pts[0].get(HORIZONTAL) != pts[1].get(HORIZONTAL)) {
      vertex_.second.second = -1;
    } else if(pts[0].get(VERTICAL) != pts[1].get(VERTICAL)) {
      vertex_.second.second = 1;
    } else {
      vertex_.second.second = 0;
    }
    vertex_.second.second *= multiplier_;
  }

  iterator_geometry_to_set() : itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {}

  iterator_geometry_to_set(const polygon_with_holes_type& polygon, direction_1d dir,
                           orientation_2d orient = HORIZONTAL, bool is_hole = false, bool = false, direction_1d = CLOCKWISE) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(orient), is_hole_(is_hole), started_holes() {
    itre = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, HIGH, orient, is_hole_);
    itrhe = end_holes(polygon);
    if(dir == HIGH) {
      itrb = itre;
      itrhb = itrhe;
      started_holes = true;
    } else {
      itrb = iterator_geometry_to_set<polygon_90_concept, polygon_with_holes_type>(polygon, LOW, orient, is_hole_);
      itrhb = begin_holes(polygon);
      started_holes = false;
    }
  }

  iterator_geometry_to_set(const iterator_geometry_to_set& that) :
    itrb(), itre(), itrhib(), itrhie(), itrhb(), itrhe(), orient_(), is_hole_(), started_holes() {
    itrb = that.itrb;
    itre = that.itre;
    if(that.itrhib != that.itrhie) {
      itrhib = that.itrhib;
      itrhie = that.itrhie;
    }
    itrhb = that.itrhb;
    itrhe = that.itrhe;
    orient_ = that.orient_;
    is_hole_ = that.is_hole_;
    started_holes = that.started_holes;
  }

  inline iterator_geometry_to_set& operator++() {
    //this code can be folded with flow control factoring
    if(itrb == itre) {
      if(itrhib == itrhie) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        } else {
          //in this case we have no holes so we just need the iterhib == itrhie, which
          //is always true if they were default initialized in the initial case or
          //both point to end of the previous hole processed
          //no need to explicitly reset them, and it causes an stl debug assertion to use
          //the default constructed iterator this way
          //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
          //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
        }
      } else {
        ++itrhib;
        if(itrhib == itrhie) {
          if(itrhb != itrhe) {
            itrhib = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
            itrhie = iterator_geometry_to_set<polygon_90_concept,
              typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
            ++itrhb;
          } else {
            //this is the same case as above
            //itrhib = itrhie = iterator_geometry_to_set<polygon_90_concept,
            //  typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>();
          }
        }
      }
    } else {
      ++itrb;
      if(itrb == itre) {
        if(itrhb != itrhe) {
          itrhib = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, LOW, orient_, !is_hole_);
          itrhie = iterator_geometry_to_set<polygon_90_concept,
            typename polygon_with_holes_traits<polygon_with_holes_type>::hole_type>(*itrhb, HIGH, orient_, !is_hole_);
          ++itrhb;
        }
      }
    }
    return *this;
  }

  inline const iterator_geometry_to_set operator++(int) {
    iterator_geometry_to_set tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_geometry_to_set& that) const {
    return itrb == that.itrb && itrhb == that.itrhb && itrhib == that.itrhib;
  }

  inline bool operator!=(const iterator_geometry_to_set& that) const {
    return !(*this == that);
  }

  inline reference operator*() const {
    if(itrb != itre) return *itrb;
    return *itrhib;
  }

    inline polygon_90_set_data() : orient_(HORIZONTAL), data_(), dirty_(false), unsorted_(false) {}

    inline polygon_90_set_data(orientation_2d orient) : orient_(orient), data_(), dirty_(false), unsorted_(false) {}

    template <typename iT>
    inline polygon_90_set_data(orientation_2d orient, iT input_begin, iT input_end) :
      orient_(HORIZONTAL), data_(), dirty_(false), unsorted_(false) {
      dirty_ = true;
      unsorted_ = true;
      for( ; input_begin != input_end; ++input_begin) { insert(*input_begin); }
    }

    inline polygon_90_set_data(const polygon_90_set_data& that) :
      orient_(that.orient_), data_(that.data_), dirty_(that.dirty_), unsorted_(that.unsorted_) {}

    inline polygon_90_set_data(orientation_2d orient, const polygon_90_set_data& that) :
      orient_(orient), data_(), dirty_(false), unsorted_(false) {
      insert(that, false, that.orient_);
    }

    inline ~polygon_90_set_data() {}

    inline polygon_90_set_data& operator=(const polygon_90_set_data& that) {
      if(this == &that) return *this;
      orient_ = that.orient_;
      data_ = that.data_;
      dirty_ = that.dirty_;
      unsorted_ = that.unsorted_;
      return *this;
    }


    template <typename geometry_object>
    inline polygon_90_set_data& operator=(const geometry_object& geometry) {
      data_.clear();
      insert(geometry);
      return *this;
    }

    inline void insert(iterator_type input_begin, iterator_type input_end, orientation_2d orient = HORIZONTAL) {
      if(input_begin == input_end || (!data_.empty() && &(*input_begin) == &(*(data_.begin())))) return;
      dirty_ = true;
      unsorted_ = true;
      if(orient == orient_)
        data_.insert(data_.end(), input_begin, input_end);
      else {
        for( ; input_begin != input_end; ++input_begin) {
          insert(*input_begin, false, orient);
        }
      }
    }

    template <typename iT>
    inline void insert(iT input_begin, iT input_end, orientation_2d orient = HORIZONTAL) {
      if(input_begin == input_end) return;
      dirty_ = true;
      unsorted_ = true;
      for( ; input_begin != input_end; ++input_begin) {
        insert(*input_begin, false, orient);
      }
    }


    inline void insert(const polygon_90_set_data& polygon_set) {
      insert(polygon_set.begin(), polygon_set.end(), polygon_set.orient());
    }


    template <typename geometry_type>
    inline void insert(const geometry_type& geometry_object, bool is_hole = false, orientation_2d = HORIZONTAL) {
      iterator_geometry_to_set<typename geometry_concept<geometry_type>::type, geometry_type>
        begin_input(geometry_object, LOW, orient_, is_hole), end_input(geometry_object, HIGH, orient_, is_hole);
      insert(begin_input, end_input, orient_);
    }


    template <typename output_container>
    inline void get(output_container& output) const {
      get_dispatch(output, typename geometry_concept<typename output_container::value_type>::type());
    }


    template <typename output_container>
    inline void get_polygons(output_container& output) const {
      get_dispatch(output, polygon_90_concept());
    }


    template <typename output_container>
    inline void get_rectangles(output_container& output) const {
      clean();
      form_rectangles(output, data_.begin(), data_.end(), orient_, rectangle_concept());
    }


    template <typename output_container>
    inline void get_rectangles(output_container& output, orientation_2d slicing_orientation) const {
      if(slicing_orientation == orient_) {
        get_rectangles(output);
      } else {
        polygon_90_set_data<coordinate_type> ps(*this);
        ps.transform(axis_transformation(axis_transformation::SWAP_XY));
        output_container result;
        ps.get_rectangles(result);
        for(typename output_container::iterator itr = result.begin(); itr != result.end(); ++itr) {
          ::boost::polygon::transform(*itr, axis_transformation(axis_transformation::SWAP_XY));
        }
        output.insert(output.end(), result.begin(), result.end());
      }
    }

    inline bool operator==(const polygon_90_set_data& p) const {
      if(orient_ == p.orient()) {
        clean();
        p.clean();
        return data_ == p.data_;
      } else {
        return false;
      }
    }

    inline bool operator!=(const polygon_90_set_data& p) const {
      return !((*this) == p);
    }

    inline iterator_type begin() const {
      return data_.begin();
    }

    inline iterator_type end() const {
      return data_.end();
    }


    const value_type& value() const {
      return data_;
    }

    inline void clear() { data_.clear(); dirty_ = unsorted_ = false; }

    inline bool empty() const { clean(); return data_.empty(); }

    inline std::size_t size() const { clean(); return data_.size(); }

    inline std::size_t capacity() const { return data_.capacity(); }

    inline void reserve(std::size_t size) { return data_.reserve(size); }

    inline bool sorted() const { return !unsorted_; }

    inline bool dirty() const { return dirty_; }

    inline orientation_2d orient() const { return orient_; }


    void clean() const {
      sort();
      if(dirty_) {
        boolean_op::default_arg_workaround<int>::applyBooleanOr(data_);
        dirty_ = false;
      }
    }


    void sort() const{
      if(unsorted_) {
        polygon_sort(data_.begin(), data_.end());
        unsorted_ = false;
      }
    }


    template <typename input_iterator_type>
    void set(input_iterator_type input_begin, input_iterator_type input_end, orientation_2d orient) {
      data_.clear();
      reserve(std::distance(input_begin, input_end));
      data_.insert(data_.end(), input_begin, input_end);
      orient_ = orient;
      dirty_ = true;
      unsorted_ = true;
    }

    template <typename rectangle_type>
    bool
    extents(rectangle_type& extents_rectangle) const {
      clean();
      if(data_.empty()) return false;
      if(orient_ == HORIZONTAL)
        set_points(extents_rectangle, point_data<coordinate_type>(data_[0].second.first, data_[0].first),
                   point_data<coordinate_type>(data_[data_.size() - 1].second.first, data_[data_.size() - 1].first));
      else
        set_points(extents_rectangle, point_data<coordinate_type>(data_[0].first, data_[0].second.first),
                   point_data<coordinate_type>(data_[data_.size() - 1].first, data_[data_.size() - 1].second.first));
      for(std::size_t i = 1; i < data_.size() - 1; ++i) {
        if(orient_ == HORIZONTAL)
          encompass(extents_rectangle, point_data<coordinate_type>(data_[i].second.first, data_[i].first));
        else
          encompass(extents_rectangle, point_data<coordinate_type>(data_[i].first, data_[i].second.first));
      }
      return true;
    }


    polygon_90_set_data&
    bloat2(typename coordinate_traits<coordinate_type>::unsigned_area_type west_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type east_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type south_bloating,
          typename coordinate_traits<coordinate_type>::unsigned_area_type north_bloating) {
      std::vector<rectangle_data<coordinate_type> > rects;
      clean();
      rects.reserve(data_.size() / 2);
      get(rects);
      rectangle_data<coordinate_type> convolutionRectangle(interval_data<coordinate_type>(-((coordinate_type)west_bloating),
                                                                                          (coordinate_type)east_bloating),
                                                           interval_data<coordinate_type>(-((coordinate_type)south_bloating),
                                                                                          (coordinate_type)north_bloating));
      for(typename std::vector<rectangle_data<coordinate_type> >::iterator itr = rects.begin();
          itr != rects.end(); ++itr) {
        convolve(*itr, convolutionRectangle);
      }
      clear();
      insert(rects.begin(), rects.end());
      return *this;
    }


    static void modify_pt(point_data<coordinate_type>& pt, const point_data<coordinate_type>&  prev_pt,
                          const point_data<coordinate_type>&  current_pt,  const point_data<coordinate_type>&  next_pt,
                          coordinate_type west_bloating,
                          coordinate_type east_bloating,
                          coordinate_type south_bloating,
                          coordinate_type north_bloating) {
      bool pxl = prev_pt.x() < current_pt.x();
      bool pyl = prev_pt.y() < current_pt.y();
      bool nxl = next_pt.x() < current_pt.x();
      bool nyl = next_pt.y() < current_pt.y();
      bool pxg = prev_pt.x() > current_pt.x();
      bool pyg = prev_pt.y() > current_pt.y();
      bool nxg = next_pt.x() > current_pt.x();
      bool nyg = next_pt.y() > current_pt.y();
      //two of the four if statements will execute
      if(pxl)
        pt.y(current_pt.y() - south_bloating);
      if(pxg)
        pt.y(current_pt.y() + north_bloating);
      if(nxl)
        pt.y(current_pt.y() + north_bloating);
      if(nxg)
        pt.y(current_pt.y() - south_bloating);
      if(pyl)
        pt.x(current_pt.x() + east_bloating);
      if(pyg)
        pt.x(current_pt.x() - west_bloating);
      if(nyl)
        pt.x(current_pt.x() - west_bloating);
      if(nyg)
        pt.x(current_pt.x() + east_bloating);
    }

    static void resize_poly_up(std::vector<point_data<coordinate_type> >& poly,
                               coordinate_type west_bloating,
                               coordinate_type east_bloating,
                               coordinate_type south_bloating,
                               coordinate_type north_bloating) {
      point_data<coordinate_type> first_pt = poly[0];
      point_data<coordinate_type> second_pt = poly[1];
      point_data<coordinate_type> prev_pt = poly[0];
      point_data<coordinate_type> current_pt = poly[1];
      for(std::size_t i = 2; i < poly.size(); ++i) {
        point_data<coordinate_type> next_pt = poly[i];
        modify_pt(poly[i-1], prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
        prev_pt = current_pt;
        current_pt = next_pt;
      }
      point_data<coordinate_type> next_pt = first_pt;
      modify_pt(poly.back(), prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
      prev_pt = current_pt;
      current_pt = next_pt;
      next_pt = second_pt;
      modify_pt(poly[0], prev_pt, current_pt, next_pt, west_bloating, east_bloating, south_bloating, north_bloating);
      remove_colinear_pts(poly);
    }

    static bool resize_poly_down(std::vector<point_data<coordinate_type> >& poly,
                                 coordinate_type west_shrinking,
                                 coordinate_type east_shrinking,
                                 coordinate_type south_shrinking,
                                 coordinate_type north_shrinking) {
      rectangle_data<coordinate_type> extents_rectangle;
      set_points(extents_rectangle, poly[0], poly[0]);
      point_data<coordinate_type> first_pt = poly[0];
      point_data<coordinate_type> second_pt = poly[1];
      point_data<coordinate_type> prev_pt = poly[0];
      point_data<coordinate_type> current_pt = poly[1];
      encompass(extents_rectangle, current_pt);
      for(std::size_t i = 2; i < poly.size(); ++i) {
        point_data<coordinate_type> next_pt = poly[i];
        encompass(extents_rectangle, next_pt);
        modify_pt(poly[i-1], prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
        prev_pt = current_pt;
        current_pt = next_pt;
      }
      if(delta(extents_rectangle, HORIZONTAL) < std::abs(west_shrinking + east_shrinking))
        return false;
      if(delta(extents_rectangle, VERTICAL) < std::abs(north_shrinking + south_shrinking))
        return false;
      point_data<coordinate_type> next_pt = first_pt;
      modify_pt(poly.back(), prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
      prev_pt = current_pt;
      current_pt = next_pt;
      next_pt = second_pt;
      modify_pt(poly[0], prev_pt, current_pt, next_pt, west_shrinking, east_shrinking, south_shrinking, north_shrinking);
      return remove_colinear_pts(poly);
    }


    static bool remove_colinear_pts(std::vector<point_data<coordinate_type> >& poly) {
      bool found_colinear = true;
      while(found_colinear && poly.size() >= 4) {
        found_colinear = false;
        typename std::vector<point_data<coordinate_type> >::iterator itr = poly.begin();
        itr += poly.size() - 1; //get last element position
        typename std::vector<point_data<coordinate_type> >::iterator itr2 = poly.begin();
        typename std::vector<point_data<coordinate_type> >::iterator itr3 = itr2;
        ++itr3;
        std::size_t count = 0;
        for( ; itr3 < poly.end(); ++itr3) {
          if(((*itr).x() == (*itr2).x() && (*itr).x() == (*itr3).x()) ||
             ((*itr).y() == (*itr2).y() && (*itr).y() == (*itr3).y()) ) {
            ++count;
            found_colinear = true;
          } else {
            itr = itr2;
            ++itr2;
          }
          *itr2 = *itr3;
        }
        itr3 = poly.begin();
        if(((*itr).x() == (*itr2).x() && (*itr).x() == (*itr3).x()) ||
           ((*itr).y() == (*itr2).y() && (*itr).y() == (*itr3).y()) ) {
          ++count;
          found_colinear = true;
        }
        poly.erase(poly.end() - count, poly.end());
      }
      return poly.size() >= 4;
    }


    polygon_90_set_data&
    bloat(typename coordinate_traits<coordinate_type>::unsigned_area_type west_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type east_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type south_bloating,
           typename coordinate_traits<coordinate_type>::unsigned_area_type north_bloating) {
      std::list<polygon_45_with_holes_data<coordinate_type> > polys;
      get(polys);
      clear();
      for(typename std::list<polygon_45_with_holes_data<coordinate_type> >::iterator itr = polys.begin();
          itr != polys.end(); ++itr) {
        //polygon_90_set_data<coordinate_type> psref;
        //psref.insert(view_as<polygon_90_concept>((*itr).self_));
        //rectangle_data<coordinate_type> prerect;
        //psref.extents(prerect);
        resize_poly_up((*itr).self_.coords_, (coordinate_type)west_bloating, (coordinate_type)east_bloating,
                       (coordinate_type)south_bloating, (coordinate_type)north_bloating);
        iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
          begin_input(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE),
          end_input(view_as<polygon_90_concept>((*itr).self_), HIGH, orient_, false, true, COUNTERCLOCKWISE);
        insert(begin_input, end_input, orient_);
        //polygon_90_set_data<coordinate_type> pstest;
        //pstest.insert(view_as<polygon_90_concept>((*itr).self_));
        //psref.bloat2(west_bloating, east_bloating, south_bloating, north_bloating);
        //if(!equivalence(psref, pstest)) {
        // std::cout << "test failed\n";
        //}
        for(typename std::list<polygon_45_data<coordinate_type> >::iterator itrh = (*itr).holes_.begin();
            itrh != (*itr).holes_.end(); ++itrh) {
          //rectangle_data<coordinate_type> rect;
          //psref.extents(rect);
          //polygon_90_set_data<coordinate_type> psrefhole;
          //psrefhole.insert(prerect);
          //psrefhole.insert(view_as<polygon_90_concept>(*itrh), true);
          //polygon_45_data<coordinate_type> testpoly(*itrh);
          if(resize_poly_down((*itrh).coords_,(coordinate_type)west_bloating, (coordinate_type)east_bloating,
                              (coordinate_type)south_bloating, (coordinate_type)north_bloating)) {
            iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
              begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true),
              end_input2(view_as<polygon_90_concept>(*itrh), HIGH, orient_, true, true);
            insert(begin_input2, end_input2, orient_);
            //polygon_90_set_data<coordinate_type> pstesthole;
            //pstesthole.insert(rect);
            //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            // begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true);
            //pstesthole.insert(begin_input2, end_input, orient_);
            //psrefhole.bloat2(west_bloating, east_bloating, south_bloating, north_bloating);
            //if(!equivalence(psrefhole, pstesthole)) {
            // std::cout << (winding(testpoly) == CLOCKWISE) << std::endl;
            // std::cout << (winding(*itrh) == CLOCKWISE) << std::endl;
            // polygon_90_set_data<coordinate_type> c(psrefhole);
            // c.clean();
            // polygon_90_set_data<coordinate_type> a(pstesthole);
            // polygon_90_set_data<coordinate_type> b(pstesthole);
            // a.sort();
            // b.clean();
            // std::cout << "test hole failed\n";
            // //std::cout << testpoly << std::endl;
            //}
          }
        }
      }
      return *this;
    }


    polygon_90_set_data&
    shrink(typename coordinate_traits<coordinate_type>::unsigned_area_type west_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type east_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type south_shrinking,
           typename coordinate_traits<coordinate_type>::unsigned_area_type north_shrinking) {
      std::list<polygon_45_with_holes_data<coordinate_type> > polys;
      get(polys);
      clear();
      for(typename std::list<polygon_45_with_holes_data<coordinate_type> >::iterator itr = polys.begin();
          itr != polys.end(); ++itr) {
        //polygon_90_set_data<coordinate_type> psref;
        //psref.insert(view_as<polygon_90_concept>((*itr).self_));
        //rectangle_data<coordinate_type> prerect;
        //psref.extents(prerect);
        //polygon_45_data<coordinate_type> testpoly((*itr).self_);
        if(resize_poly_down((*itr).self_.coords_, -(coordinate_type)west_shrinking, -(coordinate_type)east_shrinking,
                            -(coordinate_type)south_shrinking, -(coordinate_type)north_shrinking)) {
          iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            begin_input(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE),
            end_input(view_as<polygon_90_concept>((*itr).self_), HIGH, orient_, false, true, COUNTERCLOCKWISE);
          insert(begin_input, end_input, orient_);
          //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
          //  begin_input2(view_as<polygon_90_concept>((*itr).self_), LOW, orient_, false, true, COUNTERCLOCKWISE);
          //polygon_90_set_data<coordinate_type> pstest;
          //pstest.insert(begin_input2, end_input, orient_);
          //psref.shrink2(west_shrinking, east_shrinking, south_shrinking, north_shrinking);
          //if(!equivalence(psref, pstest)) {
          //  std::cout << "test failed\n";
          //}
          for(typename std::list<polygon_45_data<coordinate_type> >::iterator itrh = (*itr).holes_.begin();
              itrh != (*itr).holes_.end(); ++itrh) {
            //rectangle_data<coordinate_type> rect;
            //psref.extents(rect);
            //polygon_90_set_data<coordinate_type> psrefhole;
            //psrefhole.insert(prerect);
            //psrefhole.insert(view_as<polygon_90_concept>(*itrh), true);
            //polygon_45_data<coordinate_type> testpoly(*itrh);
            resize_poly_up((*itrh).coords_, -(coordinate_type)west_shrinking, -(coordinate_type)east_shrinking,
                            -(coordinate_type)south_shrinking, -(coordinate_type)north_shrinking);
            iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
              begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true),
              end_input2(view_as<polygon_90_concept>(*itrh), HIGH, orient_, true, true);
            insert(begin_input2, end_input2, orient_);
            //polygon_90_set_data<coordinate_type> pstesthole;
            //pstesthole.insert(rect);
            //iterator_geometry_to_set<polygon_90_concept, view_of<polygon_90_concept, polygon_45_data<coordinate_type> > >
            //  begin_input2(view_as<polygon_90_concept>(*itrh), LOW, orient_, true, true);
            //pstesthole.insert(begin_input2, end_input, orient_);
            //psrefhole.shrink2(west_shrinking, east_shrinking, south_shrinking, north_shrinking);
            //if(!equivalence(psrefhole, pstesthole)) {
            //  std::cout << (winding(testpoly) == CLOCKWISE) << std::endl;
            //  std::cout << (winding(*itrh) == CLOCKWISE) << std::endl;
            //  polygon_90_set_data<coordinate_type> c(psrefhole);
            //  c.clean();
            //  polygon_90_set_data<coordinate_type> a(pstesthole);
            //  polygon_90_set_data<coordinate_type> b(pstesthole);
            //  a.sort();
            //  b.clean();
            //  std::cout << "test hole failed\n";
            //  //std::cout << testpoly << std::endl;
            //}
          }
        }
      }
      return *this;
    }


    polygon_90_set_data&
    shrink2(typename coordinate_traits<coordinate_type>::unsigned_area_type west_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type east_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type south_shrinking,
            typename coordinate_traits<coordinate_type>::unsigned_area_type north_shrinking) {
      rectangle_data<coordinate_type> externalBoundary;
      if(!extents(externalBoundary)) return *this;
      ::boost::polygon::bloat(externalBoundary, 10); //bloat by diferential ammount
      //insert a hole that encompasses the data
      insert(externalBoundary, true); //note that the set is in a dirty state now
      sort();  //does not apply implicit OR operation
      std::vector<rectangle_data<coordinate_type> > rects;
      rects.reserve(data_.size() / 2);
      //begin does not apply implicit or operation, this is a dirty range
      form_rectangles(rects, data_.begin(), data_.end(), orient_, rectangle_concept());
      clear();
      rectangle_data<coordinate_type> convolutionRectangle(interval_data<coordinate_type>(-((coordinate_type)east_shrinking),
                                                                                          (coordinate_type)west_shrinking),
                                                           interval_data<coordinate_type>(-((coordinate_type)north_shrinking),
                                                                                          (coordinate_type)south_shrinking));
      for(typename std::vector<rectangle_data<coordinate_type> >::iterator itr = rects.begin();
          itr != rects.end(); ++itr) {
        rectangle_data<coordinate_type>& rect = *itr;
        convolve(rect, convolutionRectangle);
        //insert rectangle as a hole
        insert(rect, true);
      }
      convolve(externalBoundary, convolutionRectangle);
      //insert duplicate of external boundary as solid to cancel out the external hole boundaries
      insert(externalBoundary);
      clean(); //we have negative values in the set, so we need to apply an OR operation to make it valid input to a boolean
      return *this;
    }


    polygon_90_set_data&
    shrink(direction_2d dir, typename coordinate_traits<coordinate_type>::unsigned_area_type shrinking) {
      if(dir == WEST)
        return shrink(shrinking, 0, 0, 0);
      if(dir == EAST)
        return shrink(0, shrinking, 0, 0);
      if(dir == SOUTH)
        return shrink(0, 0, shrinking, 0);
      return shrink(0, 0, 0, shrinking);
    }


    polygon_90_set_data&
    bloat(direction_2d dir, typename coordinate_traits<coordinate_type>::unsigned_area_type shrinking) {
      if(dir == WEST)
        return bloat(shrinking, 0, 0, 0);
      if(dir == EAST)
        return bloat(0, shrinking, 0, 0);
      if(dir == SOUTH)
        return bloat(0, 0, shrinking, 0);
      return bloat(0, 0, 0, shrinking);
    }


    polygon_90_set_data& move(coordinate_type x_delta, coordinate_type y_delta) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          (*itr).first += x_delta;
          (*itr).second.first += y_delta;
        } else {
          (*itr).second.first += x_delta;
          (*itr).first += y_delta;
        }
      }
      return *this;
    }

    template <typename transformation_type>
    polygon_90_set_data& transform(const transformation_type& transformation) {
      direction_2d dir1, dir2;
      transformation.get_directions(dir1, dir2);
      int sign = dir1.get_sign() * dir2.get_sign();
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          transformation.transform((*itr).first, (*itr).second.first);
        } else {
          transformation.transform((*itr).second.first, (*itr).first);
        }
        (*itr).second.second *= sign;
      }
      if(dir1 != EAST || dir2 != NORTH)
        unsorted_ = true; //some mirroring or rotation must have happened
      return *this;
    }

    polygon_90_set_data& scale_up(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first *= (coordinate_type)factor;
        (*itr).second.first *= (coordinate_type)factor;
      }
      return *this;
    }

    polygon_90_set_data& scale_down(typename coordinate_traits<coordinate_type>::unsigned_area_type factor) {
      typedef typename coordinate_traits<coordinate_type>::coordinate_distance dt;
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first = scaling_policy<coordinate_type>::round((dt)((*itr).first) / (dt)factor);
        (*itr).second.first = scaling_policy<coordinate_type>::round((dt)((*itr).second.first) / (dt)factor);
      }
      unsorted_ = true; //scaling down can make coordinates equal that were not previously equal
      return *this;
    }

    template <typename scaling_type>
    polygon_90_set_data& scale(const anisotropic_scale_factor<scaling_type>& scaling) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          scaling.scale((*itr).first, (*itr).second.first);
        } else {
          scaling.scale((*itr).second.first, (*itr).first);
        }
      }
      unsorted_ = true;
      return *this;
    }

    template <typename scaling_type>
    polygon_90_set_data& scale_with(const scaling_type& scaling) {
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        if(orient_ == orientation_2d(VERTICAL)) {
          scaling.scale((*itr).first, (*itr).second.first);
        } else {
          scaling.scale((*itr).second.first, (*itr).first);
        }
      }
      unsorted_ = true;
      return *this;
    }

    polygon_90_set_data& scale(double factor) {
      typedef typename coordinate_traits<coordinate_type>::coordinate_distance dt;
      for(typename std::vector<std::pair<coordinate_type, std::pair<coordinate_type, int> > >::iterator
            itr = data_.begin(); itr != data_.end(); ++itr) {
        (*itr).first = scaling_policy<coordinate_type>::round((dt)((*itr).first) * (dt)factor);
        (*itr).second.first = scaling_policy<coordinate_type>::round((dt)((*itr).second.first) * (dt)factor);
      }
      unsorted_ = true; //scaling make coordinates equal that were not previously equal
      return *this;
    }


    polygon_90_set_data& self_xor() {
      sort();
      if(dirty_) { //if it is clean it is a no-op
        boolean_op::default_arg_workaround<boolean_op::UnaryCount>::applyBooleanOr(data_);
        dirty_ = false;
      }
      return *this;
    }


    polygon_90_set_data& self_intersect() {
      sort();
      if(dirty_) { //if it is clean it is a no-op
        interval_data<coordinate_type> ivl((std::numeric_limits<coordinate_type>::min)(), (std::numeric_limits<coordinate_type>::max)());
        rectangle_data<coordinate_type> rect(ivl, ivl);
        insert(rect, true);
        clean();
      }
      return *this;
    }


    inline polygon_90_set_data& interact(const polygon_90_set_data& that) {
      typedef coordinate_type Unit;
      if(that.dirty_) that.clean();
      typename touch_90_operation<Unit>::TouchSetData tsd;
      touch_90_operation<Unit>::populateTouchSetData(tsd, that.data_, 0);
      std::vector<polygon_90_data<Unit> > polys;
      get(polys);
      std::vector<std::set<int> > graph(polys.size()+1, std::set<int>());
      for(std::size_t i = 0; i < polys.size(); ++i){
        polygon_90_set_data<Unit> psTmp(that.orient_);
        psTmp.insert(polys[i]);
        psTmp.clean();
        touch_90_operation<Unit>::populateTouchSetData(tsd, psTmp.data_, i+1);
      }
      touch_90_operation<Unit>::performTouch(graph, tsd);
      clear();
      for(std::set<int>::iterator itr = graph[0].begin(); itr != graph[0].end(); ++itr){
        insert(polys[(*itr)-1]);
      }
      dirty_ = false;
      return *this;
    }



    template <class T2, typename iterator_type_1, typename iterator_type_2>
    void applyBooleanBinaryOp(iterator_type_1 itr1, iterator_type_1 itr1_end,
                              iterator_type_2 itr2, iterator_type_2 itr2_end,
                              T2 defaultCount) {
      data_.clear();
      boolean_op::applyBooleanBinaryOp(data_, itr1, itr1_end, itr2, itr2_end, defaultCount);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, rectangle_concept ) const {
      clean();
      form_rectangles(output, data_.begin(), data_.end(), orient_, rectangle_concept());
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_90_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container, typename concept_type>
    void get_fracture(output_container& container, bool fracture_holes, concept_type tag) const {
      clean();
      ::boost::polygon::get_polygons(container, data_.begin(), data_.end(), orient_, fracture_holes, tag);
    }


  template <typename coordinate_type>
  polygon_90_set_data<coordinate_type>&
  polygon_90_set_data<coordinate_type>::resize(coordinate_type west,
                                               coordinate_type east,
                                               coordinate_type south,
                                               coordinate_type north) {
    move(-west, -south);
    coordinate_type e_total = west + east;
    coordinate_type n_total = south + north;
    if((e_total < 0) ^ (n_total < 0)) {
      //different signs
      if(e_total < 0) {
        shrink(0, -e_total, 0, 0);
        if(n_total != 0)
          return bloat(0, 0, 0, n_total);
        else
          return (*this);
      } else {
        shrink(0, 0, 0, -n_total); //shrink first
        if(e_total != 0)
          return bloat(0, e_total, 0, 0);
        else
          return (*this);
      }
    } else {
      if(e_total < 0) {
        return shrink(0, -e_total, 0, -n_total);
      }
      return bloat(0, e_total, 0, n_total);
    }
  }

    inline property_merge_90() : pmd_() {}

    inline property_merge_90(const property_merge_90& that) : pmd_(that.pmd_) {}

    inline property_merge_90& operator=(const property_merge_90& that) { pmd_ = that.pmd_; return *this; }

    inline void insert(const polygon_90_set_data<coordinate_type>& ps, const property_type& property) {
      merge_scanline<coordinate_type, property_type, polygon_90_set_data<coordinate_type> >::
        populate_property_merge_data(pmd_, ps.begin(), ps.end(), property, ps.orient());
    }

    template <class GeoObjT>
    inline void insert(const GeoObjT& geoObj, const property_type& property) {
      polygon_90_set_data<coordinate_type> ps;
      ps.insert(geoObj);
      insert(ps, property);
    }

    template <typename ResultType>
    inline void merge(ResultType& result) {
      merge_scanline<coordinate_type, property_type, polygon_90_set_data<coordinate_type>, typename ResultType::key_type> ms;
      ms.perform_merge(result, pmd_);
    }

    inline connectivity_extraction_90() : tsd_(), nodeCount_(0) {}

    inline connectivity_extraction_90(const connectivity_extraction_90& that) : tsd_(that.tsd_),
                                                                          nodeCount_(that.nodeCount_) {}

    inline connectivity_extraction_90& operator=(const connectivity_extraction_90& that) {
      tsd_ = that.tsd_;
      nodeCount_ = that.nodeCount_; {}
      return *this;
    }

    inline unsigned int insert(const polygon_90_set_data<coordinate_type>& ps) {
      ps.clean();
      touch_90_operation<coordinate_type>::populateTouchSetData(tsd_, ps.begin(), ps.end(), nodeCount_);
      return nodeCount_++;
    }

    template <class GeoObjT>
    inline unsigned int insert(const GeoObjT& geoObj) {
      polygon_90_set_data<coordinate_type> ps;
      ps.insert(geoObj);
      return insert(ps);
    }

    template <class GraphT>
    inline void extract(GraphT& graph) {
      touch_90_operation<coordinate_type>::performTouch(graph, tsd_);
    }

      inline Count2()
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = counts[1] = 0; }

      inline Count2(int count1, int count2)
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = count1; counts[1] = count2; }

      inline Count2(const Count2& count)
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = count.counts[0]; counts[1] = count.counts[1]; }

      inline bool operator==(const Count2& count) const { return counts[0] == count.counts[0] && counts[1] == count.counts[1]; }

      inline bool operator!=(const Count2& count) const { return !((*this) == count); }

      inline Count2& operator=(int count) { counts[0] = counts[1] = count; return *this; }

      inline Count2& operator=(const Count2& count) { counts[0] = count.counts[0]; counts[1] = count.counts[1]; return *this; }

      inline int& operator[](bool index) { return counts[index]; }

      inline int operator[](bool index) const {return counts[index]; }

      inline Count2& operator+=(const Count2& count){
        counts[0] += count[0];
        counts[1] += count[1];
        return *this;
      }

      inline Count2& operator-=(const Count2& count){
        counts[0] -= count[0];
        counts[1] -= count[1];
        return *this;
      }

      inline Count2 operator+(const Count2& count) const {
        return Count2(*this)+=count;
      }

      inline Count2 operator-(const Count2& count) const {
        return Count2(*this)-=count;
      }

      inline Count2 invert() const {
        return Count2(-counts[0], -counts[1]);
      }

      inline Count1() : count_(0) { }

      inline Count1(int count) : count_(count) { }

      inline Count1(const Count1& count) : count_(count.count_) { }

      inline bool operator==(const Count1& count) const { return count_ == count.count_; }

      inline bool operator!=(const Count1& count) const { return !((*this) == count); }

      inline Count1& operator=(int count) { count_ = count; return *this; }

      inline Count1& operator=(const Count1& count) { count_ = count.count_; return *this; }

      inline Count1& operator+=(const Count1& count){
        count_ += count.count_;
        return *this;
      }

      inline Count1& operator-=(const Count1& count){
        count_ -= count.count_;
        return *this;
      }

      inline Count1 operator+(const Count1& count) const {
        return Count1(*this)+=count;
      }

      inline Count1 operator-(const Count1& count) const {
        return Count1(*this)-=count;
      }

      inline Count1 invert() const {
        return Count1(-count_);
      }

      inline Scan45ElementT() : x(), y(), rise(), count() {}

      inline Scan45ElementT(Unit xIn, Unit yIn, int riseIn, CountType countIn = CountType()) :
        x(xIn), y(yIn), rise(riseIn), count(countIn) {}

      inline Scan45ElementT(const Scan45ElementT& that) :
        x(that.x), y(that.y), rise(that.rise), count(that.count) {}

      inline Scan45ElementT& operator=(const Scan45ElementT& that) {
        x = that.x; y = that.y; rise = that.rise; count = that.count;
        return *this;
      }

      inline Unit evalAtX(Unit xIn) const {
        return y + rise * (xIn - x);
      }


      inline bool cross(Point& crossPoint, const Scan45ElementT& edge, Unit currentX) const {
        Unit y1 = evalAtX(currentX);
        Unit y2 = edge.evalAtX(currentX);
        int rise1 = rise;
        int rise2 = edge.rise;
        if(rise > edge.rise){
          if(y1 > y2) return false;
        } else if(rise < edge.rise){
          if(y2 > y1) return false;
          std::swap(y1, y2);
          std::swap(rise1, rise2);
        } else { return false; }
        if(rise1 == 1) {
          if(rise2 == 0) {
            crossPoint = Point(currentX + y2 - y1, y2);
          } else {
            //rise2 == -1
            Unit delta = (y2 - y1)/2;
            crossPoint = Point(currentX + delta, y1 + delta);
          }
        } else {
          //rise1 == 0 and rise2 == -1
          crossPoint = Point(currentX + y2 - y1, y1);
        }
        return true;
      }

      inline lessScan45ElementRise() {}

      inline bool operator () (Scan45Element elm1, Scan45Element elm2) const {
        return elm1.rise < elm2.rise;
      }

      inline lessScan45Element() : x_(0), justBefore_(0) {}

      inline lessScan45Element(Unit *x, int *justBefore) : x_(x), justBefore_(justBefore) {}

      inline lessScan45Element(const lessScan45Element& that) : x_(that.x_), justBefore_(that.justBefore_) {}

      inline lessScan45Element& operator=(const lessScan45Element& that) { x_ = that.x_; justBefore_ = that.justBefore_; return *this; }

      inline bool operator () (const Scan45ElementT<CountType>& elm1,
                               const Scan45ElementT<CountType>& elm2) const {
        Unit y1 = elm1.evalAtX(*x_);
        Unit y2 = elm2.evalAtX(*x_);
        if(y1 < y2) return true;
        if(y1 == y2) {
          //if justBefore is true we invert the result of the comparison of slopes
          if(*justBefore_) {
            return elm1.rise > elm2.rise;
          } else {
            return elm1.rise < elm2.rise;
          }
        }
        return false;
      }

      inline Scan45CountT() : counts() {}

      inline Scan45CountT(CountType count) : counts() { counts[0] = counts[1] = counts[2] = counts[3] = count; }

      inline Scan45CountT(const CountType& count1, const CountType& count2, const CountType& count3,
                          const CountType& count4) : counts() {
        counts[0] = count1;
        counts[1] = count2;
        counts[2] = count3;
        counts[3] = count4;
      }

      inline Scan45CountT(const Scan45CountT& count) : counts() {
        (*this) = count;
      }

      inline bool operator==(const Scan45CountT& count) const {
        for(unsigned int i = 0; i < 4; ++i) {
          if(counts[i] != count.counts[i]) return false;
        }
        return true;
      }

      inline bool operator!=(const Scan45CountT& count) const { return !((*this) == count); }

      inline Scan45CountT& operator=(CountType count) {
        counts[0] = counts[1] = counts[2] = counts[3] = count; return *this; }

      inline Scan45CountT& operator=(const Scan45CountT& count) {
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] = count.counts[i];
        }
        return *this;
      }

      inline CountType& operator[](int index) { return counts[index]; }

      inline CountType operator[](int index) const {return counts[index]; }

      inline Scan45CountT& operator+=(const Scan45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] += count.counts[i];
        }
        return *this;
      }

      inline Scan45CountT& operator-=(const Scan45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] -= count.counts[i];
        }
        return *this;
      }

      inline Scan45CountT operator+(const Scan45CountT& count) const {
        return Scan45CountT(*this)+=count;
      }

      inline Scan45CountT operator-(const Scan45CountT& count) const {
        return Scan45CountT(*this)-=count;
      }

      inline Scan45CountT invert() const {
        return Scan45CountT(CountType())-=(*this);
      }

      inline Scan45CountT& operator+=(const Scan45ElementT<CountType>& element){
        counts[element.rise+1] += element.count; return *this;
      }

      inline Vertex45T() : pt(), rise(), count() {}

      inline Vertex45T(const Point& point, int riseIn, ct countIn) : pt(point), rise(riseIn), count(countIn) {}

      inline Vertex45T(const Vertex45T& vertex) : pt(vertex.pt), rise(vertex.rise), count(vertex.count) {}

      inline Vertex45T& operator=(const Vertex45T& vertex){
        pt = vertex.pt; rise = vertex.rise; count = vertex.count; return *this; }

      inline bool operator==(const Vertex45T& vertex) const {
        return pt == vertex.pt && rise == vertex.rise && count == vertex.count; }

      inline bool operator!=(const Vertex45T& vertex) const { return !((*this) == vertex); }

      inline bool operator<(const Vertex45T& vertex) const {
        if(pt.x() < vertex.pt.x()) return true;
        if(pt.x() == vertex.pt.x()) {
          if(pt.y() < vertex.pt.y()) return true;
          if(pt.y() == vertex.pt.y()) { return rise < vertex.rise; }
        }
        return false;
      }

      inline bool operator>(const Vertex45T& vertex) const { return vertex < (*this); }

      inline bool operator<=(const Vertex45T& vertex) const { return !((*this) > vertex); }

      inline bool operator>=(const Vertex45T& vertex) const { return !((*this) < vertex); }

      inline Unit evalAtX(Unit xIn) const { return pt.y() + rise * (xIn - pt.x()); }

      inline lessVertex45() : x_(0), justBefore_() {}


      inline lessVertex45(Unit *x, int *justBefore) : x_(x), justBefore_(justBefore) {}


      inline lessVertex45(const lessVertex45& that) : x_(that.x_), justBefore_(that.justBefore_) {}


      inline lessVertex45& operator=(const lessVertex45& that) { x_ = that.x_; justBefore_ = that.justBefore_; return *this; }


      template <typename ct>
      inline bool operator () (const Vertex45T<ct>& elm1, const Vertex45T<ct>& elm2) const {
        Unit y1 = elm1.evalAtX(*x_);
        Unit y2 = elm2.evalAtX(*x_);
        if(y1 < y2) return true;
        if(y1 == y2) {
          //if justBefore is true we invert the result of the comparison of slopes
          if(*justBefore_) {
            return elm1.rise > elm2.rise;
          } else {
            return elm1.rise < elm2.rise;
          }
        }
        return false;
      }

    static inline int classifyEdge45(const Point& prevPt, const Point& nextPt) {
      if(prevPt.x() == nextPt.x()) {
        //2 or 6
        return predicated_value(prevPt.y() < nextPt.y(), 6, 2);
      }
      if(prevPt.y() == nextPt.y()) {
        //0 or 4
        return predicated_value(prevPt.x() < nextPt.x(), 4, 0);
      }
      if(prevPt.x() < nextPt.x()) {
        //3 or 5
        return predicated_value(prevPt.y() < nextPt.y(), 5, 3);
      }
      //prevPt.x() > nextPt.y()
      //1 or 7
      return predicated_value(prevPt.y() < nextPt.y(), 7, 1);
    }


    template <int op, typename CountType>
    static int applyLogic(CountType count1, CountType count2){
      bool l1 = applyLogic<op>(count1);
      bool l2 = applyLogic<op>(count2);
      if(l1 && !l2)
        return -1; //was true before and became false like a trailing edge
      if(!l1 && l2)
        return 1; //was false before and became true like a leading edge
      return 0; //no change in logic between the two counts
    }

    template <int op>
    static bool applyLogic(Count2 count) {
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op == 0) { //apply or
        return count[0] > 0 || count[1] > 0;
      } else if(op == 1) { //apply and
        return count[0] > 0 && count[1] > 0;
      } else if(op == 2) { //apply not
        return count[0] > 0 && !(count[1] > 0);
      } else if(op == 3) { //apply xor
        return (count[0] > 0) ^ (count[1] > 0);
      } else
        return false;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

      template <typename cT>
      void operator()(cT& output, const Count2& count1, const Count2& count2,
                      const Point& pt, int rise, direction_1d end) {
        int edgeType = applyLogic<op>(count1, count2);
        if(edgeType) {
          int multiplier = end == LOW ? -1 : 1;
          //std::cout << "cross logic: " << edgeType << "\n";
          output.insert(output.end(), Vertex45(pt, rise, edgeType * multiplier));
          //std::cout << "write out: " << crossPoint << " " << Point(eraseItrs[i]->x, eraseItrs[i]->y) << "\n";
        }
      }


    template <int op>
    static bool applyLogic(Count1 count) {
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op == 0) { //apply or
        return count.count_ > 0;
      } else if(op == 1) { //apply and
        return count.count_ > 1;
      } else if(op == 3) { //apply xor
        return (count.count_ % 2) != 0;
      } else
        return false;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

      template <typename cT>
      void operator()(cT& output, const Count1& count1, const Count1& count2,
                      const Point& pt, int rise, direction_1d end) {
        int edgeType = applyLogic<op>(count1, count2);
        if(edgeType) {
          int multiplier = end == LOW ? -1 : 1;
          //std::cout << "cross logic: " << edgeType << "\n";
          output.insert(output.end(), Vertex45(pt, rise, edgeType * multiplier));
          //std::cout << "write out: " << crossPoint << " " << Point(eraseItrs[i]->x, eraseItrs[i]->y) << "\n";
        }
      }

      inline lessScan45Vertex() {}

      template <typename Scan45Vertex>
      inline bool operator () (const Scan45Vertex& v1, const Scan45Vertex& v2) const {
        return (v1.first.x() < v2.first.x()) || (v1.first.x() == v2.first.x() && v1.first.y() < v2.first.y());
      }

    template <typename S45V>
    static inline void sortScan45Vector(S45V& vec) {
      polygon_sort(vec.begin(), vec.end(), lessScan45Vertex());
    }

      static inline Scan45Element getElement(const Scan45Vertex& vertex, int index) {
        return Scan45Element(vertex.first.x(), vertex.first.y(), index - 1, vertex.second[index]);
      }

        inline lessScan45Point() {}

        inline bool operator () (const Point& v1, const Point& v2) const {
          return (v1.x() < v2.x()) || (v1.x() == v2.x() && v1.y() < v2.y());
        }

      inline Scan45() : scanData_(), crossQueue_(), crossVector_(),
                        x_((std::numeric_limits<Unit>::min)()), justBefore_(false) {
        lessScan45Element<CountType>  lessElm(&x_, &justBefore_);
        scanData_ = std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> >(lessElm);
      }

      inline Scan45(const Scan45& that) : scanData_(), crossQueue_(), crossVector_(),
                                          x_((std::numeric_limits<Unit>::min)()), justBefore_(false) {
        (*this) = that; }

      inline Scan45& operator=(const Scan45& that) {
        x_ = that.x_;
        justBefore_ = that.justBefore_;
        crossQueue_ = that.crossQueue_;
        crossVector_ = that.crossVector_;
        lessScan45Element<CountType>  lessElm(&x_, &justBefore_);
        scanData_ = std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> >(lessElm);
        for(const_iterator itr = that.scanData_.begin(); itr != that.scanData_.end(); ++itr){
          scanData_.insert(scanData_.end(), *itr);
        }
        return *this;
      }

      template <class cT, class iT>
      void scan(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "1\n";
        while(inputBegin != inputEnd) {
          //std::cout << "2\n";
          //std::cout << "x_ = " << x_ << "\n";
          //std::cout << "scan line size: " << scanData_.size() << "\n";
          //for(iterator iter = scanData_.begin();
          //     iter != scanData_.end(); ++iter) {
          //   std::cout << "scan element\n";
          //   std::cout << *iter << " " << iter->evalAtX(x_) << "\n";
          // }
          // std::cout << "cross queue size: " << crossQueue_.size() << "\n";
          // std::cout << "cross vector size: " << crossVector_.size() << "\n";
          //for(CrossQueue::iterator cqitr = crossQueue_.begin(); cqitr != crossQueue_.end(); ++cqitr) {
          //   std::cout << *cqitr << " ";
          //} std::cout << "\n";
          Unit nextX = (*inputBegin).first.x();
          if(!crossVector_.empty() && crossVector_[0].first.x() < nextX) nextX = crossVector_[0].first.x();
          if(nextX != x_) {
            //std::cout << "3\n";
            //we need to move to the next scanline stop
            //we need to process end events then cross events
            //process end events
            if(!crossQueue_.empty() &&
               (*crossQueue_.begin()).x() < nextX) {
              //std::cout << "4\n";
              nextX = (std::min)(nextX, (*crossQueue_.begin()).x());
            }
            //std::cout << "6\n";
            justBefore_ = true;
            x_ = nextX;
            advance_(output);
            justBefore_ = false;
            if(!crossVector_.empty() &&
               nextX == (*inputBegin).first.x()) {
              inputBegin = mergeCross_(inputBegin, inputEnd);
            }
            processEvent_(output, crossVector_.begin(), crossVector_.end());
            crossVector_.clear();
          } else {
            //std::cout << "7\n";
            //our scanline has progressed to the event that is next in the queue
            inputBegin = processEvent_(output, inputBegin, inputEnd);
          }
        }
        //std::cout << "done scanning\n";
      }


      template <class cT>
      inline void advance_(cT& output) {
        //process all cross points on the cross queue at the current x_
        //std::cout << "advance_\n";
        std::vector<iterator> eraseVec;
        while(!crossQueue_.empty() &&
              (*crossQueue_.begin()).x() == x_){
          //std::cout << "loop\n";
          //pop point off the cross queue
          Point crossPoint = *(crossQueue_.begin());
          //std::cout << crossPoint << "\n";
          //for(iterator iter = scanData_.begin();
          //    iter != scanData_.end(); ++iter) {
          //  std::cout << "scan element\n";
          //  std::cout << *iter << " " << iter->evalAtX(x_) << "\n";
          //}
          crossQueue_.erase(crossQueue_.begin());
          Scan45Vertex vertex(crossPoint, Scan45Count());
          iterator lowIter = lookUp_(vertex.first.y());
          //std::cout << "searching at: " << vertex.first.y() << "\n";
          //if(lowIter == scanData_.end()) std::cout << "could not find\n";
          //else std::cout << "found: " << *lowIter << "\n";
          if(lowIter == scanData_.end() ||
             lowIter->evalAtX(x_) != vertex.first.y()) {
            //   std::cout << "skipping\n";
            //there weren't any edges at this potential cross point
            continue;
          }
          CountType countBelow;
          iterator searchDownItr = lowIter;
          while(searchDownItr != scanData_.begin()
                && searchDownItr->evalAtX(x_) == vertex.first.y()) {
            //get count from below
            --searchDownItr;
            countBelow = searchDownItr->count;
          }
          //std::cout << "Below Count: " << countBelow << "\n";
          Scan45Count count(countBelow);
          std::size_t numEdges = 0;
          iterator eraseItrs[3];
          while(lowIter != scanData_.end() &&
                lowIter->evalAtX(x_) == vertex.first.y()) {
            for(int index = lowIter->rise +1; index >= 0; --index)
              count[index] = lowIter->count;
            //std::cout << count << "\n";
            eraseItrs[numEdges] = lowIter;
            ++numEdges;
            ++lowIter;
          }
          if(numEdges == 1) {
            //look for the next crossing point and continue
            //std::cout << "found only one edge\n";
            findCross_(eraseItrs[0]);
            continue;
          }
          //before we erase the elements we need to decide if they should be written out
          CountType currentCount = countBelow;
          for(std::size_t i = 0; i < numEdges; ++i) {
            output_functor f;
            f(output, currentCount, eraseItrs[i]->count, crossPoint, eraseItrs[i]->rise, LOW);
            currentCount = eraseItrs[i]->count;
          }
          //schedule erase of the elements
          for(std::size_t i = 0; i < numEdges; ++i) {
            eraseVec.push_back(eraseItrs[i]);
          }

          //take the derivative wrt theta of the count at the crossing point
          vertex.second[2] = count[2] - countBelow;
          vertex.second[1] = count[1] - count[2];
          vertex.second[0] = count[0] - count[1];
          //add the point, deriviative pair into the cross vector
          //std::cout << "LOOK HERE!\n";
          //std::cout << count << "\n";
          //std::cout << vertex << "\n";
          crossVector_.push_back(vertex);
        }
        //erase crossing elements
        std::vector<iterator> searchVec;
        for(std::size_t i = 0; i < eraseVec.size(); ++i) {
          if(eraseVec[i] != scanData_.begin()) {
            iterator searchItr = eraseVec[i];
            --searchItr;
            if(searchVec.empty() ||
               searchVec.back() != searchItr)
              searchVec.push_back(searchItr);
          }
          scanData_.erase(eraseVec[i]);
        }
        for(std::size_t i = 0; i < searchVec.size(); ++i) {
          findCross_(searchVec[i]);
        }
      }


      template <class iT>
      inline iT mergeCross_(iT inputBegin, iT inputEnd) {
        Scan45Vector vec;
        swap(vec, crossVector_);
        iT mergeEnd = inputBegin;
        std::size_t mergeCount = 0;
        while(mergeEnd != inputEnd &&
              (*mergeEnd).first.x() == x_) {
          ++mergeCount;
          ++mergeEnd;
        }
        crossVector_.reserve((std::max)(vec.capacity(), vec.size() + mergeCount));
        for(std::size_t i = 0; i < vec.size(); ++i){
          while(inputBegin != mergeEnd &&
                (*inputBegin).first.y() < vec[i].first.y()) {
            crossVector_.push_back(*inputBegin);
            ++inputBegin;
          }
          crossVector_.push_back(vec[i]);
        }
        while(inputBegin != mergeEnd){
          crossVector_.push_back(*inputBegin);
          ++inputBegin;
        }
        return inputBegin;
      }


      template <class cT, class iT>
      inline iT processEvent_(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "processEvent_\n";
        CountType verticalCount = CountType();
        Point prevPoint;
        iterator prevIter = scanData_.end();
        while(inputBegin != inputEnd &&
              (*inputBegin).first.x() == x_) {
          //std::cout << (*inputBegin) << "\n";
          //std::cout << "loop\n";
          Scan45Vertex vertex = *inputBegin;
          //std::cout << vertex.first << "\n";
          //if vertical count propigating up fake a null event at the next element
          if(verticalCount != CountType() && (prevIter != scanData_.end() &&
                                              prevIter->evalAtX(x_) < vertex.first.y())) {
            //std::cout << "faking null event\n";
            vertex = Scan45Vertex(Point(x_, prevIter->evalAtX(x_)), Scan45Count());
          } else {
            ++inputBegin;
            //std::cout << "after increment\n";
            //accumulate overlapping changes in Scan45Count
            while(inputBegin != inputEnd &&
                  (*inputBegin).first.x() == x_ &&
                  (*inputBegin).first.y() == vertex.first.y()) {
              //std::cout << "accumulate\n";
              vertex.second += (*inputBegin).second;
              ++inputBegin;
            }
          }
          //std::cout << vertex.second << "\n";
          //integrate vertex
          CountType currentCount = verticalCount;// + vertex.second[0];
          for(unsigned int i = 0; i < 3; ++i) {
            vertex.second[i] = currentCount += vertex.second[i];
          }
          //std::cout << vertex.second << "\n";
          //vertex represents the change in state at this point

          //get counts at current vertex
          CountType countBelow;
          iterator lowIter = lookUp_(vertex.first.y());
          if(lowIter != scanData_.begin()) {
            //get count from below
            --lowIter;
            countBelow = lowIter->count;
            ++lowIter;
          }
          //std::cout << "Count Below: " << countBelow[0] << " " << countBelow[1] << "\n";
          //std::cout << "vertical count: " << verticalCount[0] << " " << verticalCount[1] << "\n";
          Scan45Count countAt(countBelow - verticalCount);
          //check if the vertical edge should be written out
          if(verticalCount != CountType()) {
            output_functor f;
            f(output, countBelow - verticalCount, countBelow, prevPoint, 2, HIGH);
            f(output, countBelow - verticalCount, countBelow, vertex.first, 2, LOW);
          }
          currentCount = countBelow - verticalCount;
          while(lowIter != scanData_.end() &&
                lowIter->evalAtX(x_) == vertex.first.y()) {
            for(unsigned int i = lowIter->rise + 1; i < 3; ++i) {
              countAt[i] = lowIter->count;
            }
            Point lp(lowIter->x, lowIter->y);
            if(lp != vertex.first) {
              output_functor f;
              f(output, currentCount, lowIter->count, vertex.first, lowIter->rise, LOW);
            }
            currentCount = lowIter->count;
            iterator nextIter = lowIter;
            ++nextIter;
            //std::cout << "erase\n";
            scanData_.erase(lowIter);
            if(nextIter != scanData_.end())
              findCross_(nextIter);
            lowIter = nextIter;
          }
          verticalCount += vertex.second[3];
          prevPoint = vertex.first;
          //std::cout << "new vertical count: " << verticalCount[0] << " " << verticalCount[1] << "\n";
          prevIter = lowIter;
          //count represents the current state at this point
          //std::cout << vertex.second << "\n";
          //std::cout << countAt << "\n";
          //std::cout << "ADD\n";
          vertex.second += countAt;
          //std::cout << vertex.second << "\n";

          //add elements to the scanline
          for(int i = 0; i < 3; ++i) {
            if(vertex.second[i] != countBelow) {
              //std::cout << "insert: " << vertex.first.x() << " " << vertex.first.y() << " " << i-1 <<
              //  " " << vertex.second[i][0] << " " << vertex.second[i][1] << "\n";
              iterator insertIter = scanData_.insert(scanData_.end(),
                                                     Scan45ElementT<CountType>(vertex.first.x(),
                                                                               vertex.first.y(),
                                                                               i - 1, vertex.second[i]));
              findCross_(insertIter);
              output_functor f;
              f(output, countBelow, vertex.second[i], vertex.first, i - 1, HIGH);
            }
            countBelow = vertex.second[i];
          }
        }
        //std::cout << "end processEvent\n";
        return inputBegin;
      }

      inline void scheduleCross0_(iterator iter1, iterator iter2) {
        //std::cout << "0, ";
        Unit y1 = iter1->evalAtX(x_);
        Unit y2 = iter2->evalAtX(x_);
        LongUnit delta = local_abs(LongUnit(y1) - LongUnit(y2));
        if(delta + static_cast<LongUnit>(x_) <= (std::numeric_limits<Unit>::max)())
          crossQueue_.insert(crossQueue_.end(), Point(x_ + static_cast<Unit>(delta), y1));
        //std::cout <<  Point(x_ + delta, y1);
      }

      inline void scheduleCross1_(iterator iter1, iterator iter2) {
        //std::cout << "1, ";
        Unit y1 = iter1->evalAtX(x_);
        Unit y2 = iter2->evalAtX(x_);
        //std::cout << y1 << " " << y2 << ": ";
        //note that half the delta cannot exceed the positive inter range
        LongUnit delta = y1;
        delta -= y2;
        Unit UnitMax = (std::numeric_limits<Unit>::max)();
        if((delta & 1) == 1) {
          //delta is odd, division by 2 will result in integer trunctaion
          if(delta == 1) {
            //the cross point is not on the integer grid and cannot be represented
            //we must throw an exception
            std::string msg = "GTL 45 Boolean error, precision insufficient to represent edge intersection coordinate value.";
            throw(msg);
          } else {
            //note that result of this subtraction is always positive because itr1 is above itr2 in scanline
            LongUnit halfDelta2 = (LongUnit)((((LongUnit)y1) - y2)/2);
            //note that halfDelta2 has been truncated
            if(halfDelta2 + x_ <= UnitMax && halfDelta2 + y2 <= UnitMax) {
              crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta2), y2+static_cast<Unit>(halfDelta2)));
              crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta2), y2+static_cast<Unit>(halfDelta2)+1));
            }
          }
        } else {
          LongUnit halfDelta = (LongUnit)((((LongUnit)y1) - y2)/2);
          if(halfDelta + x_ <= UnitMax && halfDelta + y2 <= UnitMax)
            crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta), y2+static_cast<Unit>(halfDelta)));
          //std::cout << Point(x_+halfDelta, y2+halfDelta);
        }
      }


      inline void findCross_(iterator iter) {
        //std::cout << "find cross ";
        iterator iteratorBelow = iter;
        iterator iteratorAbove = iter;
        if(iter != scanData_.begin() && iter->rise < 1) {
          --iteratorBelow;
          if(iter->rise == 0){
            if(iteratorBelow->rise == 1) {
              scheduleCross0_(iter, iteratorBelow);
            }
          } else {
            //iter->rise == -1
            if(iteratorBelow->rise == 1) {
              scheduleCross1_(iter, iteratorBelow);
            } else if(iteratorBelow->rise == 0) {
              scheduleCross0_(iteratorBelow, iter);
            }
          }
        }
        ++iteratorAbove;
        if(iteratorAbove != scanData_.end() && iter->rise > -1) {
          if(iter->rise == 0) {
            if(iteratorAbove->rise == -1) {
              scheduleCross0_(iter, iteratorAbove);
            }
          } else {
            //iter->rise == 1
            if(iteratorAbove->rise == -1) {
              scheduleCross1_(iteratorAbove, iter);
            } else if(iteratorAbove->rise == 0) {
              scheduleCross0_(iteratorAbove, iter);
            }
          }
        }
        //std::cout << "\n";
      }


      inline iterator lookUp_(Unit y){
        //if just before then we need to look from 1 not -1
        return scanData_.lower_bound(Scan45ElementT<CountType>(x_, y, -1+2*justBefore_));
      }


    template <typename streamtype>
    static inline bool testScan45Data(streamtype& stdcout) {
      Unit x = 0;
      int justBefore = false;
      lessScan45Element<Count2> lessElm(&x, &justBefore);
      std::set<Scan45ElementT<Count2>, lessScan45Element<Count2> > testData(lessElm);
      //Unit size = testData.size();
      typedef std::set<Scan45ElementT<Count2>, lessScan45Element<Count2> > Scan45Data;
      typename Scan45Data::iterator itr10 = testData.insert(testData.end(), Scan45Element(0, 10, 1));
      typename Scan45Data::iterator itr20 = testData.insert(testData.end(), Scan45Element(0, 20, 1));
      typename Scan45Data::iterator itr30 = testData.insert(testData.end(), Scan45Element(0, 30, -1));
      typename Scan45Data::iterator itr40 = testData.insert(testData.end(), Scan45Element(0, 40, -1));
      typename Scan45Data::iterator itrA = testData.lower_bound(Scan45Element(0, 29, -1));
      typename Scan45Data::iterator itr1 = testData.lower_bound(Scan45Element(0, 10, -1));
      x = 4;
      //now at 14 24 26 36
      typename Scan45Data::iterator itrB = testData.lower_bound(Scan45Element(4, 29, -1));
      typename Scan45Data::iterator itr2 = testData.lower_bound(Scan45Element(4, 14, -1));
      if(itr1 != itr2) stdcout << "test1 failed\n";
      if(itrA == itrB) stdcout << "test2 failed\n";
      //remove crossing elements
      testData.erase(itr20);
      testData.erase(itr30);
      x = 5;
      itr20 = testData.insert(testData.end(), Scan45Element(0, 20, 1));
      itr30 = testData.insert(testData.end(), Scan45Element(0, 30, -1));
      //now at 15 25 25 35
      typename Scan45Data::iterator itr = testData.begin();
      if(itr != itr10) stdcout << "test3 failed\n";
      ++itr;
      if(itr != itr30) stdcout << "test4 failed\n";
      ++itr;
      if(itr != itr20) stdcout << "test5 failed\n";
      ++itr;
      if(itr != itr40) stdcout << "test6 failed\n";
      stdcout << "done testing Scan45Data\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45Rect(stream_type& stdcout) {
      stdcout << "testing Scan45Rect\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 0 1
      // result == 0 0 2 1
      // result == 0 10 2 -1
      // result == 0 10 0 -1
      // result == 10 0 0 -1
      // result == 10 0 2 -1
      // result == 10 10 2 1
      // result == 10 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 0, 1));
      reference.push_back(Vertex45(Point(0, 0), 2, 1));
      reference.push_back(Vertex45(Point(0, 10), 2, -1));
      reference.push_back(Vertex45(Point(0, 10), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 2, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //std::cout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //std::cout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45Rect\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45P1(stream_type& stdcout) {
      stdcout << "testing Scan45P1\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), Count2(0, 0), ncount, ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), Count2(0, 0), ncount, ncount)));
      vertices.push_back(Scan45Vertex(Point(10,20), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 1 1
      // result == 0 0 2 1
      // result == 0 10 2 -1
      // result == 0 10 1 -1
      // result == 10 10 1 -1
      // result == 10 10 2 -1
      // result == 10 20 2 1
      // result == 10 20 1 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 1, 1));
      reference.push_back(Vertex45(Point(0, 0), 2, 1));
      reference.push_back(Vertex45(Point(0, 10), 2, -1));
      reference.push_back(Vertex45(Point(0, 10), 1, -1));
      reference.push_back(Vertex45(Point(10, 10), 1, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, -1));
      reference.push_back(Vertex45(Point(10, 20), 2, 1));
      reference.push_back(Vertex45(Point(10, 20), 1, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //std::cout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //std::cout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45P1\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45P2(stream_type& stdcout) {
      stdcout << "testing Scan45P2\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, count, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), ncount, count, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(20,10), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 0 1
      // result == 0 0 1 -1
      // result == 10 0 0 -1
      // result == 10 0 1 1
      // result == 10 10 1 1
      // result == 10 10 0 -1
      // result == 20 10 1 -1
      // result == 20 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 0, 1));
      reference.push_back(Vertex45(Point(0, 0), 1, -1));
      reference.push_back(Vertex45(Point(10, 0), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 1, 1));
      reference.push_back(Vertex45(Point(10, 10), 1, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, -1));
      reference.push_back(Vertex45(Point(20, 10), 1, -1));
      reference.push_back(Vertex45(Point(20, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //stdcout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //stdcout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45P2\n";
      return true;
    }


    template <typename streamtype>
    static inline bool testScan45And(streamtype& stdcout) {
      stdcout << "testing Scan45And\n";
      Scan45<Count2, boolean_op_45_output_functor<1> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(2,2), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(2,12), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,2), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,12), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      //result size == 8
      //result == 2 2 0 1
      //result == 2 2 2 1
      //result == 2 10 2 -1
      //result == 2 10 0 -1
      //result == 10 2 0 -1
      //result == 10 2 2 -1
      //result == 10 10 2 1
      //result == 10 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(2, 2), 0, 1));
      reference.push_back(Vertex45(Point(2, 2), 2, 1));
      reference.push_back(Vertex45(Point(2, 10), 2, -1));
      reference.push_back(Vertex45(Point(2, 10), 0, -1));
      reference.push_back(Vertex45(Point(10, 2), 0, -1));
      reference.push_back(Vertex45(Point(10, 2), 2, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //stdcout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //stdcout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45And\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45Star1(stream_type& stdcout) {
      stdcout << "testing Scan45Star1\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(8,16), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(12,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(4,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(4,16), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 24
      // result == 0 8 -1 1
      // result == 0 8 1 -1
      // result == 4 0 1 1
      // result == 4 0 2 1
      // result == 4 4 2 -1
      // result == 4 4 -1 -1
      // result == 4 12 1 1
      // result == 4 12 2 1
      // result == 4 16 2 -1
      // result == 4 16 -1 -1
      // result == 6 2 1 -1
      // result == 6 14 -1 1
      // result == 6 2 -1 1
      // result == 6 14 1 -1
      // result == 8 0 -1 -1
      // result == 8 0 2 -1
      // result == 8 4 2 1
      // result == 8 4 1 1
      // result == 8 12 -1 -1
      // result == 8 12 2 -1
      // result == 8 16 2 1
      // result == 8 16 1 1
      // result == 12 8 1 -1
      // result == 12 8 -1 1
      if(result.size() != 24) {
        //stdcout << "result size == " << result.size() << "\n";
        //stdcout << "reference size == " << 24 << "\n";
        return false;
      }
      stdcout << "done testing Scan45Star1\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45Star2(stream_type& stdcout) {
      stdcout << "testing Scan45Star2\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 24
      // result == 0 4 0 1
      // result == 0 4 1 -1
      // result == 0 8 -1 1
      // result == 0 8 0 -1
      // result == 2 6 1 1
      // result == 2 6 -1 -1
      // result == 4 4 0 -1
      // result == 4 8 0 1
      // result == 4 4 -1 1
      // result == 4 8 1 -1
      // result == 8 0 -1 -1
      // result == 8 0 1 1
      // result == 8 12 1 1
      // result == 8 12 -1 -1
      // result == 12 4 1 -1
      // result == 12 8 -1 1
      // result == 12 4 0 1
      // result == 12 8 0 -1
      // result == 14 6 -1 -1
      // result == 14 6 1 1
      // result == 16 4 0 -1
      // result == 16 4 -1 1
      // result == 16 8 1 -1
      // result == 16 8 0 1
      if(result.size() != 24) {
        //std::cout << "result size == " << result.size() << "\n";
        //std::cout << "reference size == " << 24 << "\n";
        return false;
      }
      stdcout << "done testing Scan45Star2\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45Star3(stream_type& stdcout) {
      stdcout << "testing Scan45Star3\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(8,16), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));

      vertices.push_back(Scan45Vertex(Point(6,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(6,14), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,14), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(12,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(4,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(4,16), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 28
      // result == 0 8 -1 1
      // result == 0 8 1 -1
      // result == 4 0 1 1
      // result == 4 0 2 1
      // result == 4 4 2 -1
      // result == 4 4 -1 -1
      // result == 4 12 1 1
      // result == 4 12 2 1
      // result == 4 16 2 -1
      // result == 4 16 -1 -1
      // result == 6 2 1 -1
      // result == 6 14 -1 1
      // result == 6 0 0 1
      // result == 6 0 2 1
      // result == 6 2 2 -1
      // result == 6 14 1 -1
      // result == 8 0 0 -1
      // result == 8 0 0 1
      // result == 8 14 0 -1
      // result == 8 14 2 -1
      // result == 8 16 2 1
      // result == 8 16 1 1
      // result == 12 0 0 -1
      // result == 12 0 2 -1
      // result == 12 8 2 1
      // result == 12 8 2 -1
      // result == 12 14 2 1
      // result == 12 14 0 1
      if(result.size() != 28) {
        //std::cout << "result size == " << result.size() << "\n";
        //std::cout << "reference size == " << 28 << "\n";
        return false;
      }

      stdcout << "done testing Scan45Star3\n";
      return true;
    }



    template <typename stream_type>
    static inline bool testScan45Star4(stream_type& stdcout) {
      stdcout << "testing Scan45Star4\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));

      vertices.push_back(Scan45Vertex(Point(0,6), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,12), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(16,6), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(16,12), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 28
      // result == 0 4 0 1
      // result == 0 4 1 -1
      // result == 0 6 0 1
      // result == 0 6 2 1
      // result == 0 8 2 -1
      // result == 0 8 2 1
      // result == 0 12 2 -1
      // result == 0 12 0 -1
      // result == 2 6 1 1
      // result == 2 6 0 -1
      // result == 4 4 0 -1
      // result == 4 4 -1 1
      // result == 8 12 0 1
      // result == 8 0 -1 -1
      // result == 8 0 1 1
      // result == 8 12 0 -1
      // result == 12 4 1 -1
      // result == 12 4 0 1
      // result == 14 6 -1 -1
      // result == 14 6 0 1
      // result == 16 4 0 -1
      // result == 16 4 -1 1
      // result == 16 6 0 -1
      // result == 16 6 2 -1
      // result == 16 8 2 1
      // result == 16 8 2 -1
      // result == 16 12 2 1
      // result == 16 12 0 1
      if(result.size() != 28) {
        //stdcout << "result size == " << result.size() << "\n";
        //stdcout << "reference size == " << 28 << "\n";
        return false;
      }

      stdcout << "done testing Scan45Star4\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45(stream_type& stdcout) {
      if(!testScan45Rect(stdcout)) return false;
      if(!testScan45P1(stdcout)) return false;
      if(!testScan45P2(stdcout)) return false;
      if(!testScan45And(stdcout)) return false;
      if(!testScan45Star1(stdcout)) return false;
      if(!testScan45Star2(stdcout)) return false;
      if(!testScan45Star3(stdcout)) return false;
      if(!testScan45Star4(stdcout)) return false;
      return true;
    }

      inline PolyLine45() : points() {}

      template<class iT>
      inline PolyLine45& set(iT inputBegin, iT inputEnd) {
        points.clear();  //just in case there was some old data there
        while(inputBegin != inputEnd) {
          points.insert(points.end(), *inputBegin);
          ++inputBegin;
        }
        return *this;
      }

      inline PolyLine45(const PolyLine45& that) : points(that.points) {}

      inline PolyLine45& operator=(const PolyLine45& that) {
        points = that.points;
        return *this;
      }

      inline iterator begin() const { return points.begin(); }

      inline iterator end() const { return points.end(); }


      inline std::size_t size() const { return points.size(); }

      inline ActiveTail45() : tailp_(0), otherTailp_(0), holesList_(), head_(0) {}

      inline ActiveTail45(const Vertex45& vertex, ActiveTail45* otherTailp = 0) :
        tailp_(0), otherTailp_(0), holesList_(), head_(0) {
        tailp_ = new PolyLine45;
        tailp_->points.push_back(vertex.pt);
        bool headArray[4] = {false, true, true, true};
        bool inverted = vertex.count == -1;
        head_ = headArray[vertex.rise+1] ^ inverted;
        otherTailp_ = otherTailp;
      }


      inline ActiveTail45(Point point, ActiveTail45* otherTailp, bool head = true) :
        tailp_(0), otherTailp_(0), holesList_(), head_(0) {
        tailp_ = new PolyLine45;
        tailp_->points.push_back(point);
        head_ = head;
        otherTailp_ = otherTailp;

      }

      inline ActiveTail45(ActiveTail45* otherTailp) :
        tailp_(0), otherTailp_(0), holesList_(), head_(0)  {
        tailp_ = otherTailp->tailp_;
        otherTailp_ = otherTailp;
      }

      inline ActiveTail45(const ActiveTail45& that) :
        tailp_(0), otherTailp_(0), holesList_(), head_(0)  { (*this) = that; }

      inline ~ActiveTail45() {
        destroyContents();
      }

      inline ActiveTail45& operator=(const ActiveTail45& that) {
        tailp_ = new PolyLine45(*(that.tailp_));
        head_ = that.head_;
        otherTailp_ = that.otherTailp_;
        holesList_ = that.holesList_;
        return *this;
      }

      inline bool operator==(const ActiveTail45& b) const {
        return tailp_ == b.tailp_ && head_ == b.head_;
      }

      inline PolyLine45* getTail() const { return tailp_; }

      inline PolyLine45* getOtherTail() const { return otherTailp_->tailp_; }

      inline ActiveTail45* getOtherActiveTail() const { return otherTailp_; }

      inline bool isOtherTail(const ActiveTail45& b) const { return &b == otherTailp_; }

      inline ActiveTail45& updateTail(PolyLine45* newTail) { tailp_ = newTail; return *this; }


      inline bool join(ActiveTail45* tail) {
        if(tail == otherTailp_) {
          //std::cout << "joining to other tail!\n";
          return false;
        }
        if(tail->head_ == head_) {
          //std::cout << "joining head to head!\n";
          return false;
        }
        if(!tailp_) {
          //std::cout << "joining empty tail!\n";
          return false;
        }
        if(!(otherTailp_->head_)) {
          otherTailp_->copyHoles(*tail);
          otherTailp_->copyHoles(*this);
        } else {
          tail->otherTailp_->copyHoles(*this);
          tail->otherTailp_->copyHoles(*tail);
        }
        PolyLine45* tail1 = tailp_;
        PolyLine45* tail2 = tail->tailp_;
        if(head_) std::swap(tail1, tail2);
        tail1->points.splice(tail1->points.end(), tail2->points);
        delete tail2;
        otherTailp_->tailp_ = tail1;
        tail->otherTailp_->tailp_ = tail1;
        otherTailp_->otherTailp_ = tail->otherTailp_;
        tail->otherTailp_->otherTailp_ = otherTailp_;
        tailp_ = 0;
        tail->tailp_ = 0;
        tail->otherTailp_ = 0;
        otherTailp_ = 0;
        return true;
      }

      inline ActiveTail45* addHole(ActiveTail45* hole) {
        holesList_.push_back(hole);
        copyHoles(*hole);
        copyHoles(*(hole->otherTailp_));
        return this;
      }

      inline Vertex45CountT()
#ifndef BOOST_POLYGON_MSVC
        : counts()
#endif
      { counts[0] = counts[1] = counts[2] = counts[3] = 0; }

      inline Vertex45CountT(const ct& count1, const ct& count2, const ct& count3,
                           const ct& count4)
#ifndef BOOST_POLYGON_MSVC
        : counts()
#endif
      {
        counts[0] = count1;
        counts[1] = count2;
        counts[2] = count3;
        counts[3] = count4;
      }

      inline Vertex45CountT(const Vertex45& vertex)
#ifndef BOOST_POLYGON_MSVC
        : counts()
#endif
      {
        counts[0] = counts[1] = counts[2] = counts[3] = 0;
        (*this) += vertex;
      }

      inline Vertex45CountT(const Vertex45CountT& count)
#ifndef BOOST_POLYGON_MSVC
        : counts()
#endif
      {
        (*this) = count;
      }

      inline bool operator==(const Vertex45CountT& count) const {
        for(unsigned int i = 0; i < 4; ++i) {
          if(counts[i] != count.counts[i]) return false;
        }
        return true;
      }

      inline bool operator!=(const Vertex45CountT& count) const { return !((*this) == count); }

      inline Vertex45CountT& operator=(ct count) {
        counts[0] = counts[1] = counts[2] = counts[3] = count; return *this; }

      inline Vertex45CountT& operator=(const Vertex45CountT& count) {
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] = count.counts[i];
        }
        return *this;
      }

      inline ct& operator[](int index) { return counts[index]; }

      inline ct operator[](int index) const {return counts[index]; }

      inline Vertex45CountT& operator+=(const Vertex45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] += count.counts[i];
        }
        return *this;
      }

      inline Vertex45CountT& operator-=(const Vertex45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] -= count.counts[i];
        }
        return *this;
      }

      inline Vertex45CountT operator+(const Vertex45CountT& count) const {
        return Vertex45CountT(*this)+=count;
      }

      inline Vertex45CountT operator-(const Vertex45CountT& count) const {
        return Vertex45CountT(*this)-=count;
      }

      inline Vertex45CountT invert() const {
        return Vertex45CountT()-=(*this);
      }

      inline Vertex45CountT& operator+=(const Vertex45& element){
        counts[element.rise+1] += element.count; return *this;
      }

      inline bool is_45() const {
        return counts[0] != 0 || counts[2] != 0;
      }

      inline Vertex45CompactT() : pt(), count() {}

      inline Vertex45CompactT(const Point& point, int riseIn, int countIn) : pt(point), count() {
        count[riseIn+1] = countIn;
      }

      template <typename ct2>
      inline Vertex45CompactT(const typename boolean_op_45<Unit>::template Vertex45T<ct2>& vertex) : pt(vertex.pt), count() {
        count[vertex.rise+1] = vertex.count;
      }

      inline Vertex45CompactT(const Vertex45CompactT& vertex) : pt(vertex.pt), count(vertex.count) {}

      inline Vertex45CompactT& operator=(const Vertex45CompactT& vertex){
        pt = vertex.pt; count = vertex.count; return *this; }

      inline bool operator==(const Vertex45CompactT& vertex) const {
        return pt == vertex.pt && count == vertex.count; }

      inline bool operator!=(const Vertex45CompactT& vertex) const { return !((*this) == vertex); }

      inline bool operator<(const Vertex45CompactT& vertex) const {
        if(pt.x() < vertex.pt.x()) return true;
        if(pt.x() == vertex.pt.x()) {
          return pt.y() < vertex.pt.y();
        }
        return false;
      }

      inline bool operator>(const Vertex45CompactT& vertex) const { return vertex < (*this); }

      inline bool operator<=(const Vertex45CompactT& vertex) const { return !((*this) > vertex); }

      inline bool operator>=(const Vertex45CompactT& vertex) const { return !((*this) < vertex); }

      inline bool haveVertex45(int index) const { return count[index]; }

      inline Vertex45T operator[](int index) const {
        return Vertex45T(pt, index-1, count[index]); }

      inline Polygon45Formation() : scanData_(), x_((std::numeric_limits<Unit>::min)()), justBefore_(false), fractureHoles_(0) {
        lessVertex45 lessElm(&x_, &justBefore_);
        scanData_ = Polygon45FormationData(lessElm);
      }

      inline Polygon45Formation(bool fractureHoles) : scanData_(), x_((std::numeric_limits<Unit>::min)()), justBefore_(false), fractureHoles_(fractureHoles) {
        lessVertex45 lessElm(&x_, &justBefore_);
        scanData_ = Polygon45FormationData(lessElm);
      }

      inline Polygon45Formation(const Polygon45Formation& that) :
        scanData_(), x_((std::numeric_limits<Unit>::min)()), justBefore_(false), fractureHoles_(0) { (*this) = that; }

      inline Polygon45Formation& operator=(const Polygon45Formation& that) {
        x_ = that.x_;
        justBefore_ = that.justBefore_;
        fractureHoles_ = that.fractureHoles_;
        lessVertex45 lessElm(&x_, &justBefore_);
        scanData_ = Polygon45FormationData(lessElm);
        for(const_iterator itr = that.scanData_.begin(); itr != that.scanData_.end(); ++itr){
          scanData_.insert(scanData_.end(), *itr);
        }
        return *this;
      }

      template <class cT, class iT>
      void scan(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "1\n";
        while(inputBegin != inputEnd) {
          //std::cout << "2\n";
          x_ = (*inputBegin).pt.x();
          //std::cout << "SCAN FORMATION " << x_ << "\n";
          //std::cout << "x_ = " << x_ << "\n";
          //std::cout << "scan line size: " << scanData_.size() << "\n";
          inputBegin = processEvent_(output, inputBegin, inputEnd);
        }
      }


    template <typename stream_type>
    static inline bool testPolygon45FormationRect(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 0, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationP1(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 1, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 1, -1));
      data.push_back(Vertex45(Point(10, 10), 1, -1));
      data.push_back(Vertex45(Point(10, 10), 2, -1));
      data.push_back(Vertex45(Point(10, 20), 2, 1));
      data.push_back(Vertex45(Point(10, 20), 1, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationP2(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 1, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 1, 1));
      data.push_back(Vertex45(Point(10, 10), 1, 1));
      data.push_back(Vertex45(Point(10, 10), 0, -1));
      data.push_back(Vertex45(Point(20, 10), 1, -1));
      data.push_back(Vertex45(Point(20, 10), 0, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationStar1(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationStar2(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      Scan45 scan45;
      std::vector<Vertex45 > result;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());

      polygon_sort(result.begin(), result.end());
      pf.scan(polys, result.begin(), result.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationStarHole1(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(true);
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));

      data.push_back(Vertex45(Point(6, 4), 1, -1));
      data.push_back(Vertex45(Point(6, 4), 2, -1));
      data.push_back(Vertex45(Point(6, 8), -1, 1));
      data.push_back(Vertex45(Point(6, 8), 2, 1));
      data.push_back(Vertex45(Point(8, 6), -1, -1));
      data.push_back(Vertex45(Point(8, 6), 1, 1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45FormationStarHole2(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(false);
      std::vector<Polygon45WithHoles> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));

      data.push_back(Vertex45(Point(6, 4), 1, -1));
      data.push_back(Vertex45(Point(6, 4), 2, -1));
      data.push_back(Vertex45(Point(6, 12), -1, 1));
      data.push_back(Vertex45(Point(6, 12), 2, 1));
      data.push_back(Vertex45(Point(10, 8), -1, -1));
      data.push_back(Vertex45(Point(10, 8), 1, 1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45Formation(stream_type& stdcout) {
      stdcout << "testing polygon formation\n";
      Polygon45Formation pf(false);
      std::vector<Polygon45WithHoles> polys;
      std::vector<Vertex45> data;

      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 100), 2, -1));
      data.push_back(Vertex45(Point(0, 100), 0, -1));
      data.push_back(Vertex45(Point(100, 0), 0, -1));
      data.push_back(Vertex45(Point(100, 0), 2, -1));
      data.push_back(Vertex45(Point(100, 100), 2, 1));
      data.push_back(Vertex45(Point(100, 100), 0, 1));

      data.push_back(Vertex45(Point(2, 2), 0, -1));
      data.push_back(Vertex45(Point(2, 2), 2, -1));
      data.push_back(Vertex45(Point(2, 10), 2, 1));
      data.push_back(Vertex45(Point(2, 10), 0, 1));
      data.push_back(Vertex45(Point(10, 2), 0, 1));
      data.push_back(Vertex45(Point(10, 2), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 0, -1));

      data.push_back(Vertex45(Point(2, 12), 0, -1));
      data.push_back(Vertex45(Point(2, 12), 2, -1));
      data.push_back(Vertex45(Point(2, 22), 2, 1));
      data.push_back(Vertex45(Point(2, 22), 0, 1));
      data.push_back(Vertex45(Point(10, 12), 0, 1));
      data.push_back(Vertex45(Point(10, 12), 2, 1));
      data.push_back(Vertex45(Point(10, 22), 2, -1));
      data.push_back(Vertex45(Point(10, 22), 0, -1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon formation\n";
      return true;
    }

      inline Polygon45Tiling() : scanData_(), x_((std::numeric_limits<Unit>::min)()), justBefore_(false) {
        lessVertex45 lessElm(&x_, &justBefore_);
        scanData_ = Polygon45FormationData(lessElm);
      }

      inline Polygon45Tiling(const Polygon45Tiling& that) :
        scanData_(), x_((std::numeric_limits<Unit>::min)()), justBefore_(false) { (*this) = that; }

      inline Polygon45Tiling& operator=(const Polygon45Tiling& that) {
        x_ = that.x_;
        justBefore_ = that.justBefore_;
        lessVertex45 lessElm(&x_, &justBefore_);
        scanData_ = Polygon45FormationData(lessElm);
        for(const_iterator itr = that.scanData_.begin(); itr != that.scanData_.end(); ++itr){
          scanData_.insert(scanData_.end(), *itr);
        }
        return *this;
      }

      template <class cT, class iT>
      void scan(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "1\n";
        while(inputBegin != inputEnd) {
          //std::cout << "2\n";
          x_ = (*inputBegin).pt.x();
          //std::cout << "SCAN FORMATION " << x_ << "\n";
          //std::cout << "x_ = " << x_ << "\n";
          //std::cout << "scan line size: " << scanData_.size() << "\n";
          inputBegin = processEvent_(output, inputBegin, inputEnd);
        }
      }


      inline void getVerticalPair_(std::pair<ActiveTail45*, ActiveTail45*>& verticalPair,
                                   iterator previter) {
        ActiveTail45* iterTail = (*previter).second;
        Point prevPoint(x_, previter->first.evalAtX(x_));
        iterTail->pushPoint(prevPoint);
        std::pair<ActiveTail45*, ActiveTail45*> tailPair =
          ActiveTail45::createActiveTail45sAsPair(prevPoint, true, 0, false);
        verticalPair.first = iterTail;
        verticalPair.second = tailPair.first;
        (*previter).second = tailPair.second;
      }


    template <typename stream_type>
    static inline bool testPolygon45TilingRect(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 0, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP1(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 1, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 1, -1));
      data.push_back(Vertex45(Point(10, 10), 1, -1));
      data.push_back(Vertex45(Point(10, 10), 2, -1));
      data.push_back(Vertex45(Point(10, 20), 2, 1));
      data.push_back(Vertex45(Point(10, 20), 1, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP2(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 1, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 1, 1));
      data.push_back(Vertex45(Point(10, 10), 1, 1));
      data.push_back(Vertex45(Point(10, 10), 0, -1));
      data.push_back(Vertex45(Point(20, 10), 1, -1));
      data.push_back(Vertex45(Point(20, 10), 0, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP3(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(20, 0), 0, -1));
      data.push_back(Vertex45(Point(20, 0), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 1, -1));
      data.push_back(Vertex45(Point(10, 10), 0, 1));
      data.push_back(Vertex45(Point(20, 20), 1, 1));
      data.push_back(Vertex45(Point(20, 20), 2, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP4(stream_type& stdcout) {
      stdcout << "testing polygon tiling p4\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(10, 0), -1, 1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(20, 10), 2, 1));
      data.push_back(Vertex45(Point(20, 10), 0, 1));
      data.push_back(Vertex45(Point(20, -10), -1, -1));
      data.push_back(Vertex45(Point(20, -10), 2, -1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP5(stream_type& stdcout) {
      stdcout << "testing polygon tiling P5\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 0, 1));

      data.push_back(Vertex45(Point(1, 1), 0, -1));
      data.push_back(Vertex45(Point(1, 1), 1, 1));
      data.push_back(Vertex45(Point(2, 1), 0, 1));
      data.push_back(Vertex45(Point(2, 1), 1, -1));
      data.push_back(Vertex45(Point(2, 2), 1, -1));
      data.push_back(Vertex45(Point(2, 2), 0, 1));
      data.push_back(Vertex45(Point(3, 2), 1, 1));
      data.push_back(Vertex45(Point(3, 2), 0, -1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingP6(stream_type& stdcout) {
      stdcout << "testing polygon tiling P6\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 10), 2, -1));
      data.push_back(Vertex45(Point(0, 10), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 0, -1));
      data.push_back(Vertex45(Point(10, 0), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 0, 1));

      data.push_back(Vertex45(Point(1, 1), 0, -1));
      data.push_back(Vertex45(Point(1, 1), 2, -1));
      data.push_back(Vertex45(Point(1, 2), 2, 1));
      data.push_back(Vertex45(Point(1, 2), 0, 1));
      data.push_back(Vertex45(Point(2, 1), 0, 1));
      data.push_back(Vertex45(Point(2, 1), 2, 1));
      data.push_back(Vertex45(Point(2, 2), 2, -1));
      data.push_back(Vertex45(Point(2, 2), 0, -1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingStar1(stream_type& stdcout) {
      stdcout << "testing polygon tiling star1\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));
      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingStar2(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;

      Scan45 scan45;
      std::vector<Vertex45 > result;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());

      polygon_sort(result.begin(), result.end());
      pf.scan(polys, result.begin(), result.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingStarHole1(stream_type& stdcout) {
      stdcout << "testing polygon tiling star hole 1\n";
      Polygon45Tiling pf;
      std::vector<Polygon45> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));

      data.push_back(Vertex45(Point(6, 4), 1, -1));
      data.push_back(Vertex45(Point(6, 4), 2, -1));
      data.push_back(Vertex45(Point(6, 8), -1, 1));
      data.push_back(Vertex45(Point(6, 8), 2, 1));
      data.push_back(Vertex45(Point(8, 6), -1, -1));
      data.push_back(Vertex45(Point(8, 6), 1, 1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45TilingStarHole2(stream_type& stdcout) {
      stdcout << "testing polygon tiling star hole 2\n";
      Polygon45Tiling pf;
      std::vector<Polygon45WithHoles> polys;
      std::vector<Vertex45> data;
      // result == 0 8 -1 1
      data.push_back(Vertex45(Point(0, 8), -1, 1));
      // result == 0 8 1 -1
      data.push_back(Vertex45(Point(0, 8), 1, -1));
      // result == 4 0 1 1
      data.push_back(Vertex45(Point(4, 0), 1, 1));
      // result == 4 0 2 1
      data.push_back(Vertex45(Point(4, 0), 2, 1));
      // result == 4 4 2 -1
      data.push_back(Vertex45(Point(4, 4), 2, -1));
      // result == 4 4 -1 -1
      data.push_back(Vertex45(Point(4, 4), -1, -1));
      // result == 4 12 1 1
      data.push_back(Vertex45(Point(4, 12), 1, 1));
      // result == 4 12 2 1
      data.push_back(Vertex45(Point(4, 12), 2, 1));
      // result == 4 16 2 -1
      data.push_back(Vertex45(Point(4, 16), 2, 1));
      // result == 4 16 -1 -1
      data.push_back(Vertex45(Point(4, 16), -1, -1));
      // result == 6 2 1 -1
      data.push_back(Vertex45(Point(6, 2), 1, -1));
      // result == 6 14 -1 1
      data.push_back(Vertex45(Point(6, 14), -1, 1));
      // result == 6 2 -1 1
      data.push_back(Vertex45(Point(6, 2), -1, 1));
      // result == 6 14 1 -1
      data.push_back(Vertex45(Point(6, 14), 1, -1));
      // result == 8 0 -1 -1
      data.push_back(Vertex45(Point(8, 0), -1, -1));
      // result == 8 0 2 -1
      data.push_back(Vertex45(Point(8, 0), 2, -1));
      // result == 8 4 2 1
      data.push_back(Vertex45(Point(8, 4), 2, 1));
      // result == 8 4 1 1
      data.push_back(Vertex45(Point(8, 4), 1, 1));
      // result == 8 12 -1 -1
      data.push_back(Vertex45(Point(8, 12), -1, -1));
      // result == 8 12 2 -1
      data.push_back(Vertex45(Point(8, 12), 2, -1));
      // result == 8 16 2 1
      data.push_back(Vertex45(Point(8, 16), 2, 1));
      // result == 8 16 1 1
      data.push_back(Vertex45(Point(8, 16), 1, 1));
      // result == 12 8 1 -1
      data.push_back(Vertex45(Point(12, 8), 1, -1));
      // result == 12 8 -1 1
      data.push_back(Vertex45(Point(12, 8), -1, 1));

      data.push_back(Vertex45(Point(6, 4), 1, -1));
      data.push_back(Vertex45(Point(6, 4), 2, -1));
      data.push_back(Vertex45(Point(6, 12), -1, 1));
      data.push_back(Vertex45(Point(6, 12), 2, 1));
      data.push_back(Vertex45(Point(10, 8), -1, -1));
      data.push_back(Vertex45(Point(10, 8), 1, 1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testPolygon45Tiling(stream_type& stdcout) {
      stdcout << "testing polygon tiling\n";
      Polygon45Tiling pf;
      std::vector<Polygon45WithHoles> polys;
      std::vector<Vertex45> data;

      data.push_back(Vertex45(Point(0, 0), 0, 1));
      data.push_back(Vertex45(Point(0, 0), 2, 1));
      data.push_back(Vertex45(Point(0, 100), 2, -1));
      data.push_back(Vertex45(Point(0, 100), 0, -1));
      data.push_back(Vertex45(Point(100, 0), 0, -1));
      data.push_back(Vertex45(Point(100, 0), 2, -1));
      data.push_back(Vertex45(Point(100, 100), 2, 1));
      data.push_back(Vertex45(Point(100, 100), 0, 1));

      data.push_back(Vertex45(Point(2, 2), 0, -1));
      data.push_back(Vertex45(Point(2, 2), 2, -1));
      data.push_back(Vertex45(Point(2, 10), 2, 1));
      data.push_back(Vertex45(Point(2, 10), 0, 1));
      data.push_back(Vertex45(Point(10, 2), 0, 1));
      data.push_back(Vertex45(Point(10, 2), 2, 1));
      data.push_back(Vertex45(Point(10, 10), 2, -1));
      data.push_back(Vertex45(Point(10, 10), 0, -1));

      data.push_back(Vertex45(Point(2, 12), 0, -1));
      data.push_back(Vertex45(Point(2, 12), 2, -1));
      data.push_back(Vertex45(Point(2, 22), 2, 1));
      data.push_back(Vertex45(Point(2, 22), 0, 1));
      data.push_back(Vertex45(Point(10, 12), 0, 1));
      data.push_back(Vertex45(Point(10, 12), 2, 1));
      data.push_back(Vertex45(Point(10, 22), 2, -1));
      data.push_back(Vertex45(Point(10, 22), 0, -1));

      polygon_sort(data.begin(), data.end());
      pf.scan(polys, data.begin(), data.end());
      stdcout << "result size: " << polys.size() << "\n";
      for(std::size_t i = 0; i < polys.size(); ++i) {
        stdcout << polys[i] << "\n";
      }
      stdcout << "done testing polygon tiling\n";
      return true;
    }


    inline PolyLine45HoleData() : p_(0) {}

    inline PolyLine45HoleData(ActiveTail45* p) : p_(p) {}

    inline iterator begin() const { return p_->getTail()->begin(); }

    inline iterator end() const { return p_->getTail()->end(); }

    inline std::size_t size() const { return 0; }

    template<class iT>
    inline PolyLine45HoleData& set(iT inputBegin, iT inputEnd) {
      return *this;
    }

      inline iteratorHoles() : itr_() {}

      inline iteratorHoles(typename ActiveTail45::iteratorHoles itr) : itr_(itr) {}

      inline iteratorHoles(const iteratorHoles& that) : itr_(that.itr_) {}

      inline iteratorHoles& operator=(const iteratorHoles& that) {
        itr_ = that.itr_;
        return *this;
      }

      inline bool operator==(const iteratorHoles& that) { return itr_ == that.itr_; }

      inline bool operator!=(const iteratorHoles& that) { return itr_ != that.itr_; }

      inline iteratorHoles& operator++() {
        ++itr_;
        return *this;
      }

      inline const iteratorHoles operator++(int) {
        iteratorHoles tmp = *this;
        ++(*this);
        return tmp;
      }

      inline holeType operator*() {
        return *itr_;
      }



    inline PolyLine45PolygonData() : p_(0) {}

    inline PolyLine45PolygonData(ActiveTail45* p) : p_(p) {}

    inline iterator begin() const { return p_->getTail()->begin(); }

    inline iterator end() const { return p_->getTail()->end(); }

    inline iteratorHoles begin_holes() const { return iteratorHoles(p_->getHoles().begin()); }

    inline iteratorHoles end_holes() const { return iteratorHoles(p_->getHoles().end()); }

    inline ActiveTail45* yield() { return p_; }

    inline std::size_t size_holes() const { return 0; }

    inline std::size_t size() const { return 0; }

    template<class iT>
    inline PolyLine45PolygonData& set(iT inputBegin, iT inputEnd) {
      return *this;
    }

    template<class iT>
    inline PolyLine45PolygonData& set_holes(iT inputBegin, iT inputEnd) {
      return *this;
    }


    template <typename property_map>
    static inline void merge_property_maps(property_map& mp, const property_map& mp2, bool subtract = false) {
      property_map newmp;
      newmp.reserve(mp.size() + mp2.size());
      std::size_t i = 0;
      std::size_t j = 0;
      while(i != mp.size() && j != mp2.size()) {
        if(mp[i].first < mp2[j].first) {
          newmp.push_back(mp[i]);
          ++i;
        } else if(mp[i].first > mp2[j].first) {
          newmp.push_back(mp2[j]);
          if(subtract) newmp.back().second *= -1;
          ++j;
        } else {
          int count = mp[i].second;
          if(subtract) count -= mp2[j].second;
          else count += mp2[j].second;
          if(count) {
            newmp.push_back(mp[i]);
            newmp.back().second = count;
          }
          ++i;
          ++j;
        }
      }
      while(i != mp.size()) {
        newmp.push_back(mp[i]);
        ++i;
      }
      while(j != mp2.size()) {
        newmp.push_back(mp2[j]);
        if(subtract) newmp.back().second *= -1;
        ++j;
      }
      mp.swap(newmp);
    }

      inline CountTouch() : counts() {}

      inline CountTouch(const CountTouch& count) : counts(count.counts) {}

      inline bool operator==(const CountTouch& count) const { return counts == count.counts; }

      inline bool operator!=(const CountTouch& count) const { return !((*this) == count); }

      inline CountTouch& operator=(const CountTouch& count) { counts = count.counts; return *this; }

      inline int& operator[](int index) {
        std::vector<std::pair<int, int> >::iterator itr = lower_bound(counts.begin(), counts.end(), std::make_pair(index, int(0)));
        if(itr != counts.end() && itr->first == index) {
            return itr->second;
        }
        itr = counts.insert(itr, std::make_pair(index, int(0)));
        return itr->second;
      }

      inline CountTouch& operator+=(const CountTouch& count){
        merge_property_maps(counts, count.counts, false);
        return *this;
      }

      inline CountTouch& operator-=(const CountTouch& count){
        merge_property_maps(counts, count.counts, true);
        return *this;
      }

      inline CountTouch operator+(const CountTouch& count) const {
        return CountTouch(*this)+=count;
      }

      inline CountTouch operator-(const CountTouch& count) const {
        return CountTouch(*this)-=count;
      }

      inline CountTouch invert() const {
        CountTouch retval;
        retval -= *this;
        return retval;
      }


    template <typename cT>
    static void process_previous_x(cT& output) {
      std::map<Unit, std::set<int> >& y_prop_map = output.first.second;
      for(typename std::map<Unit, std::set<int> >::iterator itr = y_prop_map.begin();
          itr != y_prop_map.end(); ++itr) {
        for(std::set<int>::iterator inner_itr = itr->second.begin();
            inner_itr != itr->second.end(); ++inner_itr) {
          std::set<int>& output_edges = (*(output.second))[*inner_itr];
          std::set<int>::iterator inner_inner_itr = inner_itr;
          ++inner_inner_itr;
          for( ; inner_inner_itr != itr->second.end(); ++inner_inner_itr) {
            output_edges.insert(output_edges.end(), *inner_inner_itr);
            std::set<int>& output_edges_2 = (*(output.second))[*inner_inner_itr];
            output_edges_2.insert(output_edges_2.end(), *inner_itr);
          }
        }
      }
      y_prop_map.clear();
    }

      template <typename cT>
      void operator()(cT& output, const CountTouch& count1, const CountTouch& count2,
                      const Point& pt, int , direction_1d ) {
        Unit& x = output.first.first;
        std::map<Unit, std::set<int> >& y_prop_map = output.first.second;
        if(pt.x() != x) process_previous_x(output);
        x = pt.x();
        std::set<int>& output_set = y_prop_map[pt.y()];
        for(std::vector<std::pair<int, int> >::const_iterator itr1 = count1.counts.begin();
            itr1 != count1.counts.end(); ++itr1) {
          if(itr1->second > 0) {
            output_set.insert(output_set.end(), itr1->first);
          }
        }
        for(std::vector<std::pair<int, int> >::const_iterator itr2 = count2.counts.begin();
            itr2 != count2.counts.end(); ++itr2) {
          if(itr2->second > 0) {
            output_set.insert(output_set.end(), itr2->first);
          }
        }
      }

      bool operator()(const Vertex45Compact& l, const Vertex45Compact& r) {
        return l.first < r.first;
      }


    template <typename graph_type>
    static void performTouch(graph_type& graph, TouchSetData& tsd) {

      polygon_sort(tsd.begin(), tsd.end(), lessVertex45Compact());
      typedef std::vector<std::pair<Point, typename boolean_op_45<Unit>::template Scan45CountT<CountTouch> > > TSD;
      TSD tsd_;
      tsd_.reserve(tsd.size());
      for(typename TouchSetData::iterator itr = tsd.begin(); itr != tsd.end(); ) {
        typename TouchSetData::iterator itr2 = itr;
        ++itr2;
        for(; itr2 != tsd.end() && itr2->first == itr->first; ++itr2) {
          (itr->second) += (itr2->second); //accumulate
        }
        tsd_.push_back(std::make_pair(itr->first, itr->second));
        itr = itr2;
      }
      std::pair<std::pair<Unit, std::map<Unit, std::set<int> > >, graph_type*> output
        (std::make_pair(std::make_pair((std::numeric_limits<Unit>::max)(), std::map<Unit, std::set<int> >()), &graph));
      typename boolean_op_45<Unit>::template Scan45<CountTouch, touch_45_output_functor> scanline;
      for(typename TSD::iterator itr = tsd_.begin(); itr != tsd_.end(); ) {
        typename TSD::iterator itr2 = itr;
        ++itr2;
        while(itr2 != tsd_.end() && itr2->first.x() == itr->first.x()) {
          ++itr2;
        }
        scanline.scan(output, itr, itr2);
        itr = itr2;
      }
      process_previous_x(output);
    }


    template <typename iT>
    static void populateTouchSetData(TouchSetData& tsd, iT begin, iT end, int nodeCount) {
      for( ; begin != end; ++begin) {
        Vertex45Compact vertex;
        vertex.first = typename Vertex45Compact::first_type(begin->pt.x() * 2, begin->pt.y() * 2);
        tsd.push_back(vertex);
        for(unsigned int i = 0; i < 4; ++i) {
          if(begin->count[i]) {
            tsd.back().second[i][nodeCount] += begin->count[i];
          }
        }
      }
    }


    template <typename property_map>
    static inline void merge_property_maps(property_map& mp, const property_map& mp2, bool subtract = false) {
      polygon_45_touch<Unit>::merge_property_maps(mp, mp2, subtract);
    }

      inline CountMerge() : counts() {}

      inline CountMerge(const CountMerge& count) : counts(count.counts) {}

      inline bool operator==(const CountMerge& count) const { return counts == count.counts; }

      inline bool operator!=(const CountMerge& count) const { return !((*this) == count); }

      inline CountMerge& operator=(const CountMerge& count) { counts = count.counts; return *this; }

      inline int& operator[](property_type index) {
        std::vector<std::pair<int, int> >::iterator itr = lower_bound(counts.begin(), counts.end(), std::make_pair(index, int(0)));
        if(itr != counts.end() && itr->first == index) {
            return itr->second;
        }
        itr = counts.insert(itr, std::make_pair(index, int(0)));
        return itr->second;
      }

      inline CountMerge& operator+=(const CountMerge& count){
        merge_property_maps(counts, count.counts, false);
        return *this;
      }

      inline CountMerge& operator-=(const CountMerge& count){
        merge_property_maps(counts, count.counts, true);
        return *this;
      }

      inline CountMerge operator+(const CountMerge& count) const {
        return CountMerge(*this)+=count;
      }

      inline CountMerge operator-(const CountMerge& count) const {
        return CountMerge(*this)-=count;
      }

      inline CountMerge invert() const {
        CountMerge retval;
        retval -= *this;
        return retval;
      }

      template <typename cT>
      void operator()(cT& output, const CountMerge& count1, const CountMerge& count2,
                      const Point& pt, int rise, direction_1d end) {
        typedef typename cT::key_type keytype;
        keytype left;
        keytype right;
        int edgeType = end == LOW ? -1 : 1;
        for(typename std::vector<std::pair<property_type, int> >::const_iterator itr = count1.counts.begin();
            itr != count1.counts.end(); ++itr) {
          left.insert(left.end(), (*itr).first);
        }
        for(typename std::vector<std::pair<property_type, int> >::const_iterator itr = count2.counts.begin();
            itr != count2.counts.end(); ++itr) {
          right.insert(right.end(), (*itr).first);
        }
        if(left == right) return;
        if(!left.empty()) {
          //std::cout << pt.x() << " " << pt.y() << " " << rise << " " << edgeType << std::endl;
          output[left].insert_clean(typename boolean_op_45<Unit>::Vertex45(pt, rise, -edgeType));
        }
        if(!right.empty()) {
          //std::cout << pt.x() << " " << pt.y() << " " << rise << " " << -edgeType << std::endl;
          output[right].insert_clean(typename boolean_op_45<Unit>::Vertex45(pt, rise, edgeType));
        }
      }

      bool operator()(const Vertex45Compact& l, const Vertex45Compact& r) {
        return l.first < r.first;
      }


    template <typename output_type>
    static void performMerge(output_type& result, MergeSetData& tsd) {

      polygon_sort(tsd.begin(), tsd.end(), lessVertex45Compact());
      typedef std::vector<std::pair<Point, typename boolean_op_45<Unit>::template Scan45CountT<CountMerge> > > TSD;
      TSD tsd_;
      tsd_.reserve(tsd.size());
      for(typename MergeSetData::iterator itr = tsd.begin(); itr != tsd.end(); ) {
        typename MergeSetData::iterator itr2 = itr;
        ++itr2;
        for(; itr2 != tsd.end() && itr2->first == itr->first; ++itr2) {
          (itr->second) += (itr2->second); //accumulate
        }
        tsd_.push_back(std::make_pair(itr->first, itr->second));
        itr = itr2;
      }
      typename boolean_op_45<Unit>::template Scan45<CountMerge, merge_45_output_functor> scanline;
      for(typename TSD::iterator itr = tsd_.begin(); itr != tsd_.end(); ) {
        typename TSD::iterator itr2 = itr;
        ++itr2;
        while(itr2 != tsd_.end() && itr2->first.x() == itr->first.x()) {
          ++itr2;
        }
        scanline.scan(result, itr, itr2);
        itr = itr2;
      }
    }


    template <typename iT>
    static void populateMergeSetData(MergeSetData& tsd, iT begin, iT end, property_type property) {
      for( ; begin != end; ++begin) {
        Vertex45Compact vertex;
        vertex.first = typename Vertex45Compact::first_type(begin->pt.x() * 2, begin->pt.y() * 2);
        tsd.push_back(vertex);
        for(unsigned int i = 0; i < 4; ++i) {
          if(begin->count[i]) {
            tsd.back().second[i][property] += begin->count[i];
          }
        }
      }
    }

    inline polygon_45_set_data() : error_data_(), data_(), dirty_(false), unsorted_(false), is_manhattan_(true) {}

    template <typename geometry_type>
    inline polygon_45_set_data(const geometry_type& that) : error_data_(), data_(), dirty_(false), unsorted_(false), is_manhattan_(true) {
      insert(that);
    }

    inline polygon_45_set_data(const polygon_45_set_data& that) :
      error_data_(that.error_data_), data_(that.data_), dirty_(that.dirty_),
      unsorted_(that.unsorted_), is_manhattan_(that.is_manhattan_) {}


    template <typename ltype, typename rtype, int op_type>
    inline polygon_45_set_data(const polygon_45_set_view<ltype, rtype, op_type>& that) :
      error_data_(), data_(), dirty_(false), unsorted_(false), is_manhattan_(true) {
      (*this) = that.value();
    }

    inline ~polygon_45_set_data() {}

    inline polygon_45_set_data& operator=(const polygon_45_set_data& that) {
      if(this == &that) return *this;
      error_data_ = that.error_data_;
      data_ = that.data_;
      dirty_ = that.dirty_;
      unsorted_ = that.unsorted_;
      is_manhattan_ = that.is_manhattan_;
      return *this;
    }


    template <typename ltype, typename rtype, int op_type>
    inline polygon_45_set_data& operator=(const polygon_45_set_view<ltype, rtype, op_type>& that) {
      (*this) = that.value();
      return *this;
    }


    template <typename geometry_object>
    inline polygon_45_set_data& operator=(const geometry_object& geometry) {
      data_.clear();
      insert(geometry);
      return *this;
    }

    inline void insert(iterator_type input_begin, iterator_type input_end, bool is_hole = false) {
      if(input_begin == input_end || (!data_.empty() && &(*input_begin) == &(*(data_.begin())))) return;
      dirty_ = true;
      unsorted_ = true;
      while(input_begin != input_end) {
        insert(*input_begin, is_hole);
        ++input_begin;
      }
    }

    template <typename iT>
    inline void insert(iT input_begin, iT input_end, bool is_hole = false) {
      if(input_begin == input_end) return;
      dirty_ = true;
      unsorted_ = true;
      while(input_begin != input_end) {
        insert(*input_begin, is_hole);
        ++input_begin;
      }
    }


    template <typename geometry_type>
    inline void insert(const geometry_type& geometry_object, bool is_hole = false) {
      insert_dispatch(geometry_object, is_hole, typename geometry_concept<geometry_type>::type());
    }


    inline void insert_clean(const Vertex45Compact& vertex_45, bool is_hole = false) {
      if(vertex_45.count.is_45()) is_manhattan_ = false;
      data_.push_back(vertex_45);
      if(is_hole) data_.back().count.invert();
    }


    inline void insert(const Vertex45Compact& vertex_45, bool is_hole = false) {
      dirty_ = true;
      unsorted_ = true;
      insert_clean(vertex_45, is_hole);
    }


    template <typename coordinate_type_2>
    inline void insert(const polygon_90_set_data<coordinate_type_2>& polygon_set, bool is_hole = false) {
      if(polygon_set.orient() == VERTICAL) {
        for(typename polygon_90_set_data<coordinate_type_2>::iterator_type itr = polygon_set.begin();
            itr != polygon_set.end(); ++itr) {
          Vertex45Compact vertex_45(point_data<Unit>((*itr).first, (*itr).second.first), 2, (*itr).second.second);
          vertex_45.count[1] = (*itr).second.second;
          if(is_hole) vertex_45.count[1] *= - 1;
          insert_clean(vertex_45, is_hole);
        }
      } else {
        for(typename polygon_90_set_data<coordinate_type_2>::iterator_type itr = polygon_set.begin();
            itr != polygon_set.end(); ++itr) {
          Vertex45Compact vertex_45(point_data<Unit>((*itr).second.first, (*itr).first), 2, (*itr).second.second);
          vertex_45.count[1] = (*itr).second.second;
          if(is_hole) vertex_45.count[1] *= - 1;
          insert_clean(vertex_45, is_hole);
        }
      }
      dirty_ = true;
      unsorted_ = true;
    }


    template <typename output_container>
    inline void get(output_container& output) const {
      get_dispatch(output, typename geometry_concept<typename output_container::value_type>::type());
    }


    inline bool has_error_data() const { return !error_data_.empty(); }

    inline std::size_t error_count() const { return error_data_.size() / 4; }

    inline void get_error_data(polygon_45_set_data& p) const {
      p.data_.insert(p.data_.end(), error_data_.begin(), error_data_.end());
    }

    inline bool operator==(const polygon_45_set_data& p) const {
      clean();
      p.clean();
      return data_ == p.data_;
    }

    inline bool operator!=(const polygon_45_set_data& p) const {
      return !((*this) == p);
    }

    inline iterator_type begin() const {
      return data_.begin();
    }

    inline iterator_type end() const {
      return data_.end();
    }


    const value_type& value() const {
      return data_;
    }

    inline void clear() { data_.clear(); error_data_.clear(); dirty_ = unsorted_ = false; is_manhattan_ = true; }

    inline bool empty() const { return data_.empty(); }

    inline std::size_t size() const { clean(); return data_.size(); }

    inline std::size_t capacity() const { return data_.capacity(); }

    inline void reserve(std::size_t size) { return data_.reserve(size); }

    inline bool sorted() const { return !unsorted_; }

    inline bool dirty() const { return dirty_; }

    inline bool is_manhattan() const { return is_manhattan_; }


    void sort() const{
      if(unsorted_) {
        polygon_sort(data_.begin(), data_.end());
        unsorted_ = false;
      }
    }


    template <typename input_iterator_type>
    void set(input_iterator_type input_begin, input_iterator_type input_end) {
      data_.clear();
      reserve(std::distance(input_begin, input_end));
      insert(input_begin, input_end);
      dirty_ = true;
      unsorted_ = true;
    }


    void set_clean(const value_type& value) {
      data_ = value;
      dirty_ = false;
      unsorted_ = false;
    }


    void set(const value_type& value) {
      data_ = value;
      dirty_ = true;
      unsorted_ = true;
    }

    template <class cT>
    void get_polygons(cT& container) const {
      get_dispatch(container, polygon_45_concept());
    }

    template <class cT>
    void get_polygons_with_holes(cT& container) const {
      get_dispatch(container, polygon_45_with_holes_concept());
    }

    template <class cT>
    void get_trapezoids(cT& container) const {
      clean();
      typename polygon_45_formation<Unit>::Polygon45Tiling pf;
      //std::cout << "FORMING POLYGONS\n";
      pf.scan(container, data_.begin(), data_.end());
      //std::cout << "DONE FORMING POLYGONS\n";
    }

    template <class cT>
    void get_trapezoids(cT& container, orientation_2d slicing_orientation) const {
      if(slicing_orientation == VERTICAL) {
        get_trapezoids(container);
      } else {
        polygon_45_set_data<Unit> ps(*this);
        ps.transform(axis_transformation(axis_transformation::SWAP_XY));
        cT result;
        ps.get_trapezoids(result);
        for(typename cT::iterator itr = result.begin(); itr != result.end(); ++itr) {
          ::boost::polygon::transform(*itr, axis_transformation(axis_transformation::SWAP_XY));
        }
        container.insert(container.end(), result.begin(), result.end());
      }
    }

    polygon_45_set_data& self_intersect() {
      sort();
      applyAdaptiveUnary_<1>(); //1 = AND
      dirty_ = false;
      return *this;
    }

    polygon_45_set_data& self_xor() {
      sort();
      applyAdaptiveUnary_<3>(); //3 = XOR
      dirty_ = false;
      return *this;
    }

    template <typename geometry_type>
    polygon_45_set_data& insert_with_resize(const geometry_type& poly,
                                            coordinate_type resizing, RoundingOption rounding = CLOSEST,
                                            CornerOption corner = INTERSECTION,
                                            bool hole = false) {
      return insert_with_resize_dispatch(poly, resizing, rounding, corner, hole, typename geometry_concept<geometry_type>::type());
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_45_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_concept tag) const {
      get_fracture(output, true, tag);
    }

    template <typename output_container>
    void get_dispatch(output_container& output, polygon_with_holes_concept tag) const {
      get_fracture(output, false, tag);
    }

    template <typename output_container, typename concept_type>
    void get_fracture(output_container& container, bool fracture_holes, concept_type ) const {
      clean();
      typename polygon_45_formation<Unit>::Polygon45Formation pf(fracture_holes);
      //std::cout << "FORMING POLYGONS\n";
      pf.scan(container, data_.begin(), data_.end());
    }


    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, undefined_concept) {
      insert(geometry_object.begin(), geometry_object.end(), is_hole);
    }

    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, polygon_90_concept ) {
      insert_vertex_sequence(begin_points(geometry_object), end_points(geometry_object), winding(geometry_object), is_hole);
    }

    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, polygon_90_with_holes_concept ) {
      insert_vertex_sequence(begin_points(geometry_object), end_points(geometry_object), winding(geometry_object), is_hole);
      for(typename polygon_with_holes_traits<geometry_type>::iterator_holes_type itr =
            begin_holes(geometry_object); itr != end_holes(geometry_object);
          ++itr) {
        insert_vertex_sequence(begin_points(*itr), end_points(*itr), winding(*itr), !is_hole);
      }
    }

    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, polygon_45_concept ) {
      insert_vertex_sequence(begin_points(geometry_object), end_points(geometry_object), winding(geometry_object), is_hole);
    }

    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, polygon_45_with_holes_concept ) {
      insert_vertex_sequence(begin_points(geometry_object), end_points(geometry_object), winding(geometry_object), is_hole);
      for(typename polygon_with_holes_traits<geometry_type>::iterator_holes_type itr =
            begin_holes(geometry_object); itr != end_holes(geometry_object);
          ++itr) {
        insert_vertex_sequence(begin_points(*itr), end_points(*itr), winding(*itr), !is_hole);
      }
    }

    template <typename geometry_type>
    void insert_dispatch(const geometry_type& geometry_object, bool is_hole, polygon_45_set_concept ) {
      polygon_45_set_data ps;
      assign(ps, geometry_object);
      insert(ps, is_hole);
    }


  template <typename iT, typename T>
  void scale_up_vertex_45_compact_range(iT beginr, iT endr, T factor) {
    for( ; beginr != endr; ++beginr) {
      scale_up((*beginr).pt, factor);
    }
  }

  template <typename iT, typename T>
  void scale_down_vertex_45_compact_range_blindly(iT beginr, iT endr, T factor) {
    for( ; beginr != endr; ++beginr) {
      scale_down((*beginr).pt, factor);
    }
  }

    inline connectivity_extraction_45() : tsd_(), nodeCount_(0) {}

    inline connectivity_extraction_45(const connectivity_extraction_45& that) : tsd_(that.tsd_),
                                                                          nodeCount_(that.nodeCount_) {}

    inline connectivity_extraction_45& operator=(const connectivity_extraction_45& that) {
      tsd_ = that.tsd_;
      nodeCount_ = that.nodeCount_; {}
      return *this;
    }

    inline unsigned int insert(const polygon_45_set_data<coordinate_type>& ps) {
      ps.clean();
      polygon_45_touch<big_coord>::populateTouchSetData(tsd_, ps.begin(), ps.end(), nodeCount_);
      return nodeCount_++;
    }

    template <class GeoObjT>
    inline unsigned int insert(const GeoObjT& geoObj) {
      polygon_45_set_data<coordinate_type> ps;
      ps.insert(geoObj);
      return insert(ps);
    }

    template <class GraphT>
    inline void extract(GraphT& graph) {
      polygon_45_touch<big_coord>::performTouch(graph, tsd_);
    }


    static inline iterator_type begin(const T& polygon_set) {
      return get_iterator_type<T>::begin(polygon_set);
    }


    static inline iterator_type end(const T& polygon_set) {
      return get_iterator_type<T>::end(polygon_set);
    }


    static inline bool clean(const T& ) { return false; }


    static inline bool sorted(const T& ) { return false; }


  template <typename T>
  bool fracture_holes_45_by_concept() { return false; }


  template <typename T, typename iT>
  void get_45_polygons_T(T& t, iT begin, iT end) {
    typedef typename polygon_45_set_traits<T>::coordinate_type Unit;
    typedef typename geometry_concept<typename T::value_type>::type CType;
    typename polygon_45_formation<Unit>::Polygon45Formation pf(fracture_holes_45_by_concept<CType>());
    //std::cout << "FORMING POLYGONS\n";
    pf.scan(t, begin, end);
  }

    template <typename input_iterator_type>
    static inline void set(polygon_45_set_data<T>& polygon_set,
                           input_iterator_type input_begin, input_iterator_type input_end) {
      polygon_set.set(input_begin, input_end);
    }


    static inline iterator_type begin(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.begin();
    }


    static inline iterator_type end(const polygon_45_set_data<T>& polygon_set) {
      return polygon_set.end();
    }


    static inline bool clean(const polygon_45_set_data<T>& polygon_set) { polygon_set.clean(); return true; }


    static inline bool sorted(const polygon_45_set_data<T>& polygon_set) { polygon_set.sort(); return true; }


  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type>::type>::type,
                       typename polygon_45_set_traits<polygon_set_type>::iterator_type>::type
  begin_45_set_data(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::begin(polygon_set);
  }


  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type>::type>::type,
                       typename polygon_45_set_traits<polygon_set_type>::iterator_type>::type
  end_45_set_data(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::end(polygon_set);
  }


  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       bool>::type
  clean(const polygon_set_type& polygon_set) {
    return polygon_45_set_traits<polygon_set_type>::clean(polygon_set);
  }

  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type_1>::type>::type,
                                         typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type>::type,
                       polygon_set_type_1>::type &
  assign(polygon_set_type_1& lvalue, const polygon_set_type_2& rvalue) {
    polygon_45_set_mutable_traits<polygon_set_type_1>::set(lvalue, begin_45_set_data(rvalue), end_45_set_data(rvalue));
    return lvalue;
  }

  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output);
  }

  template <typename output_container_type, typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  get_trapezoids(output_container_type& output, const polygon_set_type& polygon_set, orientation_2d slicing_orientation) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.get_trapezoids(output, slicing_orientation);
  }

  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if< typename gtl_and_3<typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_1>::type>::type,
                                          typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type,
                                          typename gtl_if<typename is_either_polygon_45_set_type<polygon_set_type_1,
                                                                                                 polygon_set_type_2>::type>::type>::type,
                       bool>::type
  equivalence(const polygon_set_type_1& lvalue,
              const polygon_set_type_2& rvalue) {
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type_1>::coordinate_type> ps1;
    assign(ps1, lvalue);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type_2>::coordinate_type> ps2;
    assign(ps2, rvalue);
    return ps1 == ps2;
  }

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                       void>::type
  clear(polygon_set_type& polygon_set) {
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(polygon_set, ps);
  }

  template <typename polygon_set_type>
  typename enable_if< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                       bool>::type
  empty(const polygon_set_type& polygon_set) {
    if(clean(polygon_set)) return begin_45_set_data(polygon_set) == end_45_set_data(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    ps.clean();
    return ps.empty();
  }

  template <typename polygon_set_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type>::type>::type,
                      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  extents(rectangle_type& extents_rectangle,
          const polygon_set_type& polygon_set) {
    clean(polygon_set);
    polygon_45_set_data<typename polygon_45_set_traits<polygon_set_type>::coordinate_type> ps;
    assign(ps, polygon_set);
    return ps.extents(extents_rectangle);
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type>::type
  area(const polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef polygon_45_with_holes_data<Unit> p_type;
    typedef typename coordinate_traits<Unit>::area_type area_type;
    std::vector<p_type> polys;
    assign(polys, polygon_set);
    area_type retval = (area_type)0;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      retval += area(polys[i]);
    }
    return retval;
  }

  template <typename polygon_set_type_1, typename polygon_set_type_2>
  typename enable_if <
    typename gtl_and< typename gtl_if<typename is_mutable_polygon_45_set_type<polygon_set_type_1>::type>::type,
                      typename gtl_if<typename is_polygon_45_or_90_set_type<polygon_set_type_2>::type>::type >::type,
    polygon_set_type_1>::type&
  interact(polygon_set_type_1& polygon_set_1, const polygon_set_type_2& polygon_set_2) {
    typedef typename polygon_45_set_traits<polygon_set_type_1>::coordinate_type Unit;
    std::vector<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set_1);
    std::vector<std::set<int> > graph(polys.size()+1, std::set<int>());
    connectivity_extraction_45<Unit> ce;
    ce.insert(polygon_set_2);
    for(std::size_t i = 0; i < polys.size(); ++i){
      ce.insert(polys[i]);
    }
    ce.extract(graph);
    clear(polygon_set_1);
    polygon_45_set_data<Unit> ps;
    for(std::set<int>::iterator itr = graph[0].begin(); itr != graph[0].end(); ++itr){
      ps.insert(polys[(*itr)-1]);
    }
    assign(polygon_set_1, ps);
    return polygon_set_1;
  }


  template <typename polygon_set_type, typename coord_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  resize(polygon_set_type& polygon_set, coord_type resizing,
         RoundingOption rounding = CLOSEST, CornerOption corner = INTERSECTION) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.resize(resizing, rounding, corner);
    assign(polygon_set, ps);
    return polygon_set;
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  bloat(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    return resize(polygon_set, static_cast<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>(bloating));
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  shrink(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type shrinking) {
    return resize(polygon_set, -(typename polygon_45_set_traits<polygon_set_type>::coordinate_type)shrinking);
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  grow_and(polygon_set_type& polygon_set,
        typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type bloating) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    std::vector<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set);
    clear(polygon_set);
    polygon_45_set_data<Unit> ps;
    for(std::size_t i = 0; i < polys.size(); ++i) {
      polygon_45_set_data<Unit> tmpPs;
      tmpPs.insert(polys[i]);
      bloat(tmpPs, bloating);
      tmpPs.clean(); //apply implicit OR on tmp polygon set
      ps.insert(tmpPs);
    }
    ps.self_intersect();
    assign(polygon_set, ps);
    return polygon_set;
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_up(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_up(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale_down(polygon_set_type& polygon_set,
           typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale_down(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }


  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  scale(polygon_set_type& polygon_set, double factor) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.scale(factor);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_intersect(polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_intersect();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  self_xor(polygon_set_type& polygon_set) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.self_xor();
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type, typename transformation_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  transform(polygon_set_type& polygon_set,
            const transformation_type& transformation) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    clean(polygon_set);
    polygon_45_set_data<Unit> ps;
    assign(ps, polygon_set);
    ps.transform(transformation);
    assign(polygon_set, ps);
    return polygon_set;
  }

  template <typename polygon_set_type>
  typename enable_if< typename is_mutable_polygon_45_set_type<polygon_set_type>::type,
                       polygon_set_type>::type &
  keep(polygon_set_type& polygon_set,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type min_area,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::area_type max_area,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_width,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_width,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type min_height,
       typename coordinate_traits<typename polygon_45_set_traits<polygon_set_type>::coordinate_type>::unsigned_area_type max_height) {
    typedef typename polygon_45_set_traits<polygon_set_type>::coordinate_type Unit;
    typedef typename coordinate_traits<Unit>::unsigned_area_type uat;
    std::list<polygon_45_data<Unit> > polys;
    assign(polys, polygon_set);
    typename std::list<polygon_45_data<Unit> >::iterator itr_nxt;
    for(typename std::list<polygon_45_data<Unit> >::iterator itr = polys.begin(); itr != polys.end(); itr = itr_nxt){
      itr_nxt = itr;
      ++itr_nxt;
      rectangle_data<Unit> bbox;
      extents(bbox, *itr);
      uat pwidth = delta(bbox, HORIZONTAL);
      if(pwidth > min_width && pwidth <= max_width){
        uat pheight = delta(bbox, VERTICAL);
        if(pheight > min_height && pheight <= max_height){
          typename coordinate_traits<Unit>::area_type parea = area(*itr);
          if(parea <= max_area && parea >= min_area) {
            continue;
          }
        }
      }
      polys.erase(itr);
    }
    assign(polygon_set, polys);
    return polygon_set;
  }


    static inline iterator_type begin(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.begin();
    }


    static inline iterator_type end(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.end();
    }


    static inline orientation_2d orient(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.orient(); }


    static inline bool clean(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.clean(); }


    static inline bool sorted(const view_of<polygon_90_set_concept, T>& polygon_set) {
      return polygon_set.sorted(); }

    static type begin(const view_of<polygon_90_set_concept, T>& t) { return t.begin(); }

    static type end(const view_of<polygon_90_set_concept, T>& t) { return t.end(); }

    static
    void value(value_type& output_, const ltype& lvalue_, const rtype& rvalue_) {
      output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                  polygon_45_set_traits<ltype>::end(lvalue_));
      value_type rinput_;
      rinput_.set(polygon_45_set_traits<rtype>::begin(rvalue_),
                  polygon_45_set_traits<rtype>::end(rvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op_type == 0)
        output_ |= rinput_;
      else if(op_type == 1)
        output_ &= rinput_;
      else if(op_type == 2)
        output_ ^= rinput_;
      else
        output_ -= rinput_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

    static
    void value(value_type& output_, const ltype& lvalue_, const polygon_45_set_data<rcoord>& rvalue_) {
      output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                  polygon_45_set_traits<ltype>::end(lvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op_type == 0)
        output_ |= rvalue_;
      else if(op_type == 1)
        output_ &= rvalue_;
      else if(op_type == 2)
        output_ ^= rvalue_;
      else
        output_ -= rvalue_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

    polygon_45_set_view(const ltype& lvalue,
                        const rtype& rvalue ) :
      lvalue_(lvalue), rvalue_(rvalue), output_(), evaluated_(false) {}

    const value_type& value() const {
      if(!evaluated_) {
        evaluated_ = true;
        compute_45_set_value<value_type, ltype, rtype, op_type>::value(output_, lvalue_, rvalue_);
      }
      return output_;
    }

    iterator_type begin() const { return value().begin(); }

    iterator_type end() const { return value().end(); }


    bool dirty() const { return value().dirty(); }

    bool sorted() const { return value().sorted(); }


  template <typename ltype, typename rtype, int op_type>
  typename polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  begin(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.begin();
  }

  template <typename ltype, typename rtype, int op_type>
  typename polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::iterator_type
  polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  end(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.end();
  }

  template <typename ltype, typename rtype, int op_type>
  bool polygon_45_set_traits<polygon_45_set_view<ltype, rtype, op_type> >::
  clean(const polygon_45_set_view<ltype, rtype, op_type>& polygon_45_set) {
    return polygon_45_set.value().clean(); }


  template <typename geometry_type_1, typename geometry_type_2, int op_type>
  geometry_type_1& self_assignment_boolean_op_45(geometry_type_1& lvalue_, const geometry_type_2& rvalue_) {
    typedef geometry_type_1 ltype;
    typedef geometry_type_2 rtype;
    typedef typename polygon_45_set_traits<ltype>::coordinate_type coordinate_type;
    typedef polygon_45_set_data<coordinate_type> value_type;
    value_type output_;
    value_type rinput_;
    output_.set(polygon_45_set_traits<ltype>::begin(lvalue_),
                polygon_45_set_traits<ltype>::end(lvalue_));
    rinput_.set(polygon_45_set_traits<rtype>::begin(rvalue_),
                polygon_45_set_traits<rtype>::end(rvalue_));
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
    if(op_type == 0)
      output_ |= rinput_;
    else if(op_type == 1)
      output_ &= rinput_;
    else if(op_type == 2)
      output_ ^= rinput_;
    else
      output_ -= rinput_;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    polygon_45_set_mutable_traits<geometry_type_1>::set(lvalue_, output_.begin(), output_.end());
    return lvalue_;
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_b,
    typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
    typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
    typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator|(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_p,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type>::type,
  polygon_45_set_view<geometry_type_1, geometry_type_2, 0> >::type
  operator+(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 0>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_s, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator*(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_a, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 1> >::type
  operator&(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 1>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_x, typename is_polygon_45_or_90_set_type<geometry_type_1>::type,
                                           typename is_polygon_45_or_90_set_type<geometry_type_2>::type,
                                           typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type,
                       polygon_45_set_view<geometry_type_1, geometry_type_2, 2> >::type
  operator^(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 2>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4< y_ps45_m,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_1>::type>::type,
    typename gtl_if<typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    typename gtl_if<typename is_either_polygon_45_set_type<geometry_type_1, geometry_type_2>::type>::type>::type,
  polygon_45_set_view<geometry_type_1, geometry_type_2, 3> >::type
  operator-(const geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return polygon_45_set_view<geometry_type_1, geometry_type_2, 3>
      (lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_4<y_ps45_pe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type, gtl_yes,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_be, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator|=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 0>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3< y_ps45_se,
    typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
    typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator*=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_ae, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator&=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 1>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if<
    typename gtl_and_3<y_ps45_xe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                      typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
    geometry_type_1>::type &
  operator^=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 2>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename geometry_type_2>
  typename enable_if< typename gtl_and_3<y_ps45_me, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename is_polygon_45_or_90_set_type<geometry_type_2>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, const geometry_type_2& rvalue) {
    return self_assignment_boolean_op_45<geometry_type_1, geometry_type_2, 3>(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3< y_ps45_rpe, typename is_mutable_polygon_45_set_type<geometry_type_1>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator+=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, rvalue);
  }


  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rme, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                         typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                                coordinate_concept>::type>::type,
                       geometry_type_1>::type &
  operator-=(geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    return resize(lvalue, -rvalue);
  }


  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rp, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator+(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval += rvalue;
    return retval;
  }


  template <typename geometry_type_1, typename coordinate_type_1>
  typename enable_if< typename gtl_and_3<y_ps45_rm, typename gtl_if<typename is_mutable_polygon_45_set_type<geometry_type_1>::type>::type,
                                        typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type,
                                                               coordinate_concept>::type>
  ::type, geometry_type_1>::type
  operator-(const geometry_type_1& lvalue, coordinate_type_1 rvalue) {
    geometry_type_1 retval(lvalue);
    retval -= rvalue;
    return retval;
  }


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }


  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }


  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}


  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }


  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }


  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }


  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }


  coordinate_type low() const {
    return coords_[0];
  }


  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }


  coordinate_type high() const {
    return coords_[1];
  }


  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }


  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }


  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }


  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }


  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }


  bool operator>(const interval_data& that) const {
    return that < *this;
  }


  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

  inline rectangle_data():ranges_() {}

  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }

  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }


  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }

  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }

  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }


  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }

  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }

  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }


  template <typename T1, typename T2>
  view_of<T1, T2> view_as(const T2& obj) { return view_of<T1, T2>(obj); }


  template <typename T>
  T convert_high_precision_type(const typename high_precision_type<T>::type& v) {
    return T(v);
  }

    template <typename T2>
    static inline T round(T2 t2) {
      return (T)std::floor(t2+0.5);
    }


    static inline T round(T t2) {
      return t2;
    }


  template <typename coordinate_type_1, typename coordinate_type_2>
    typename enable_if<
    typename gtl_and_3<y_c_edist, typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type,
                       typename gtl_same_type<typename geometry_concept<coordinate_type_1>::type, coordinate_concept>::type>::type,
    typename coordinate_traits<coordinate_type_1>::coordinate_difference>::type
  euclidean_distance(const coordinate_type_1& lvalue, const coordinate_type_2& rvalue) {
    typedef typename coordinate_traits<coordinate_type_1>::coordinate_difference Unit;
    return (lvalue < rvalue) ? (Unit)rvalue - (Unit)lvalue : (Unit)lvalue - (Unit)rvalue;
  }

  template <class T>
  inline bool predicated_swap(const bool& pred,
                              T& a,
                              T& b) {
    const T tmp = a;
    const T* input[2] = {&b, &tmp};
    a = *input[!pred];
    b = *input[pred];
    return pred;
  }

    inline direction_1d() : val_(LOW) {}

    inline direction_1d(const direction_1d& that) : val_(that.val_) {}

    inline direction_1d(const direction_1d_enum val) : val_(val) {}

    inline direction_1d& operator = (const direction_1d& d) {
      val_ = d.val_; return * this; }

    inline bool operator==(direction_1d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_1d d) const { return !((*this) == d); }

    inline unsigned int to_int(void) const { return val_; }

    inline direction_1d& backward() { val_ ^= 1; return *this; }

    inline int get_sign() const { return val_ * 2 - 1; }

    inline orientation_2d() : val_(HORIZONTAL) {}

    inline orientation_2d(const orientation_2d& ori) : val_(ori.val_) {}

    inline orientation_2d(const orientation_2d_enum val) : val_(val) {}

    inline orientation_2d& operator=(const orientation_2d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_2d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_2d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }

    inline void turn_90() { val_ = val_^ 1; }

    inline orientation_2d get_perpendicular() const {
      orientation_2d retval = *this;
      retval.turn_90();
      return retval;
    }


    inline direction_2d() : val_(WEST) {}


    inline direction_2d(const direction_2d& that) : val_(that.val_) {}


    inline direction_2d(const direction_2d_enum val) : val_(val) {}


    inline direction_2d& operator=(const direction_2d& d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_2d() { }


    inline bool operator==(direction_2d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_2d d) const { return !((*this) == d); }

    inline bool operator< (direction_2d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_2d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_2d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_2d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_2d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline direction_2d turn(direction_1d t) const {
      return direction_2d(direction_2d_enum(val_ ^ 3 ^ (val_ >> 1) ^ t.to_int()));
    }

    inline direction_2d left() const {return turn(HIGH);}

    inline direction_2d right() const {return turn(LOW);}

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_2d& that) : val_(that.to_int() & 1) {}


  orientation_2d::orientation_2d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_2d orientation_2d::get_direction(direction_1d dir) const {
    return direction_2d(direction_2d_enum((val_ << 1) + dir.to_int()));
  }

    inline orientation_3d() : val_((int)HORIZONTAL) {}

    inline orientation_3d(const orientation_3d& ori) : val_(ori.val_) {}

    inline orientation_3d(orientation_2d ori) : val_(ori.to_int()) {}

    inline orientation_3d(const orientation_3d_enum val) : val_(val) {}

    inline ~orientation_3d() {  }

    inline orientation_3d& operator=(const orientation_3d& ori) {
      val_ = ori.val_; return * this; }

    inline bool operator==(orientation_3d that) const { return (val_ == that.val_); }

    inline bool operator!=(orientation_3d that) const { return (val_ != that.val_); }

    inline unsigned int to_int() const { return (val_); }


    inline direction_3d() : val_(WEST) {}


    inline direction_3d(direction_2d that) : val_(that.to_int()) {}

    inline direction_3d(const direction_3d& that) : val_(that.val_) {}


    inline direction_3d(const direction_2d_enum val) : val_(val) {}

    inline direction_3d(const direction_3d_enum val) : val_(val) {}


    inline direction_3d& operator=(direction_3d d) {
      val_ = d.val_;
      return * this;
    }


    inline ~direction_3d() { }


    inline bool operator==(direction_3d d) const { return (val_ == d.val_); }

    inline bool operator!=(direction_3d d) const { return !((*this) == d); }

    inline bool operator< (direction_3d d) const { return (val_ < d.val_); }

    inline bool operator<=(direction_3d d) const { return (val_ <= d.val_); }

    inline bool operator> (direction_3d d) const { return (val_ > d.val_); }

    inline bool operator>=(direction_3d d) const { return (val_ >= d.val_); }

    inline unsigned int to_int(void) const { return val_; }


    inline direction_3d backward() const {
      // flip the LSB, toggles 0 - 1   and 2 - 3 and 4 - 5
      return direction_2d(direction_2d_enum(val_ ^ 1));
    }

    inline bool is_positive() const {return (val_ & 1);}

    inline bool is_negative() const {return !is_positive();}

    inline int get_sign() const {return ((is_positive()) << 1) -1;}


  direction_1d::direction_1d(const direction_3d& that) : val_(that.to_int() & 1) {}

  orientation_3d::orientation_3d(const direction_3d& that) : val_(that.to_int() >> 1) {}

  orientation_3d::orientation_3d(const direction_2d& that) : val_(that.to_int() >> 1) {}


  direction_3d orientation_3d::get_direction(direction_1d dir) const {
    return direction_3d(direction_3d_enum((val_ << 1) + dir.to_int()));
  }


  static coordinate_type get(
      const point_type& point, orientation_2d orient) {
    return point.get(orient);
  }


  static void set(
      point_type& point, orientation_2d orient, coordinate_type value) {
    point.set(orient, value);
  }


  static point_type construct(coordinate_type x, coordinate_type y) {
    return point_type(x, y);
  }


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_get,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type get(const PointType& point, orientation_2d orient) {
  return point_traits<PointType>::get(point, orient);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_set,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  void
>::type set(PointType& point, orientation_2d orient,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  point_mutable_traits<PointType>::set(point, orient, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_construct,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type construct(
    typename point_mutable_traits<PointType>::coordinate_type x,
    typename point_mutable_traits<PointType>::coordinate_type y) {
  return point_mutable_traits<PointType>::construct(x, y);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_assign,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
>::type,
PointType1>::type& assign(PointType1& lvalue, const PointType2& rvalue) {
  set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
  set(lvalue, VERTICAL, get(rvalue, VERTICAL));
  return lvalue;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_x,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type x(const PointType& point) {
  return get(point, HORIZONTAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_y,
    typename is_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
  typename point_coordinate_type<PointType>::type
>::type y(const PointType& point) {
  return get(point, VERTICAL);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sx,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type x(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, HORIZONTAL, value);
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_p_sy,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
void>::type y(PointType& point,
    typename point_mutable_traits<PointType>::coordinate_type value) {
  set(point, VERTICAL, value);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_equiv,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
bool>::type equivalence(
    const PointType1& point1, const PointType2& point2) {
  return (x(point1) == x(point2)) && (y(point1) == y(point2));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_man_dist,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
manhattan_distance(const PointType1& point1, const PointType2& point2) {
  return euclidean_distance(point1, point2, HORIZONTAL) +
         euclidean_distance(point1, point2, VERTICAL);
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed1,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
euclidean_distance(
    const PointType1& point1,
    const PointType2& point2,
    orientation_2d orient) {
  typename point_difference_type<PointType1>::type dif =
      get(point1, orient) - get(point2, orient);
  return (dif < 0) ? -dif : dif;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_eds,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_difference_type<PointType1>::type>::type
distance_squared(const PointType1& point1, const PointType2& point2) {
  typename point_difference_type<PointType1>::type dx =
      euclidean_distance(point1, point2, HORIZONTAL);
  typename point_difference_type<PointType1>::type dy =
      euclidean_distance(point1, point2, VERTICAL);
  dx *= dx;
  dy *= dy;
  return dx + dy;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_ed2,
    typename is_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
typename point_distance_type<PointType1>::type>::type
euclidean_distance(const PointType1& point1, const PointType2& point2) {
  return (std::sqrt)(
      static_cast<double>(distance_squared(point1, point2)));
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_convolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& convolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) + x(rvalue));
  y(lvalue, y(lvalue) + y(rvalue));
  return lvalue;
}


template <typename PointType1, typename PointType2>
typename enable_if<
  typename gtl_and_3<
    y_pt_deconvolve,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<PointType2>::type
    >::type
  >::type,
PointType1>::type& deconvolve(PointType1& lvalue, const PointType2& rvalue) {
  x(lvalue, x(lvalue) - x(rvalue));
  y(lvalue, y(lvalue) - y(rvalue));
  return lvalue;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_up,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_up(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  x(point, x(point) * (Unit)factor);
  y(point, y(point) * (Unit)factor);
  return point;
}


template <typename PointType, typename CType>
typename enable_if<
  typename gtl_and<
    y_pt_scale_down,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale_down(PointType& point, CType factor) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  typedef typename coordinate_traits<Unit>::coordinate_distance dt;
  x(point, scaling_policy<Unit>::round((dt)(x(point)) / (dt)factor));
  y(point, scaling_policy<Unit>::round((dt)(y(point)) / (dt)factor));
  return point;
}


template <typename PointType, typename ScaleType>
typename enable_if<
  typename gtl_and<
    y_pt_scale,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& scale(PointType& point, const ScaleType& scaling) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  scaling.scale(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType, typename TransformType>
typename enable_if<
  typename gtl_and<
    y_pt_transform,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& transform(PointType& point, const TransformType& transform) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit x_coord(x(point));
  Unit y_coord(y(point));
  transform.transform(x_coord, y_coord);
  x(point, x_coord);
  y(point, y_coord);
  return point;
}


template <typename PointType>
typename enable_if<
  typename gtl_and<
    y_pt_move,
    typename is_mutable_point_concept<
      typename geometry_concept<PointType>::type
    >::type
  >::type,
PointType>::type& move(PointType& point, orientation_2d orient,
    typename point_coordinate_type<PointType>::type displacement) {
  typedef typename point_coordinate_type<PointType>::type Unit;
  Unit coord = get(point, orient);
  set(point, orient, coord + displacement);
  return point;
}


  axis_transformation() : atr_(NULL_TRANSFORM) {}

  explicit axis_transformation(ATR atr) : atr_(atr) {}

  axis_transformation(const axis_transformation& atr) : atr_(atr.atr_) {}


  explicit axis_transformation(const orientation_2d& orient) {
    const ATR tmp[2] = {
      NORTH_EAST,  // sort x, then y
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[orient.to_int()];
  }


  explicit axis_transformation(const direction_2d& dir) {
    const ATR tmp[4] = {
      SOUTH_EAST,  // sort x, then y
      NORTH_EAST,  // sort x, then y
      EAST_SOUTH,  // sort y, then x
      EAST_NORTH   // sort y, then x
    };
    atr_ = tmp[dir.to_int()];
  }

  axis_transformation& operator=(const axis_transformation& a) {
    atr_ = a.atr_;
    return *this;
  }

  axis_transformation& operator=(const ATR& atr) {
    atr_ = atr;
    return *this;
  }

  bool operator==(const axis_transformation& a) const {
    return atr_ == a.atr_;
  }

  bool operator!=(const axis_transformation& a) const {
    return !(*this == a);
  }

  bool operator<(const axis_transformation& a) const {
    return atr_ < a.atr_;
  }

  axis_transformation& operator+=(const axis_transformation& a) {
    bool abit2 = (a.atr_ & 4) != 0;
    bool abit1 = (a.atr_ & 2) != 0;
    bool abit0 = (a.atr_ & 1) != 0;
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    int indexes[2][2] = {
      { (int)bit2, (int)(!bit2) },
      { (int)abit2, (int)(!abit2) }
    };
    int zero_bits[2][2] = {
      {bit0, bit1}, {abit0, abit1}
    };
    int nbit1 = zero_bits[0][1] ^ zero_bits[1][indexes[0][1]];
    int nbit0 = zero_bits[0][0] ^ zero_bits[1][indexes[0][0]];
    indexes[0][0] = indexes[1][indexes[0][0]];
    indexes[0][1] = indexes[1][indexes[0][1]];
    int nbit2 = indexes[0][0] & 1;  // swap xy
    atr_ = (ATR)((nbit2 << 2) + (nbit1 << 1) + nbit0);
    return *this;
  }

  axis_transformation operator+(const axis_transformation& a) const {
    axis_transformation retval(*this);
    return retval+=a;
  }

  void populate_axis_array(INDIVIDUAL_AXIS axis_array[]) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    axis_array[1] = (INDIVIDUAL_AXIS)(((int)(!bit2) << 1) + bit1);
    axis_array[0] = (INDIVIDUAL_AXIS)(((int)(bit2) << 1) + bit0);
  }

  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    bool bit2 = (atr_ & 4) != 0;
    bool bit1 = (atr_ & 2) != 0;
    bool bit0 = (atr_ & 1) != 0;
    vertical_dir = direction_2d((direction_2d_enum)(((int)(!bit2) << 1) + !bit1));
    horizontal_dir = direction_2d((direction_2d_enum)(((int)(bit2) << 1) + !bit0));
  }

  static void combine_axis_arrays(INDIVIDUAL_AXIS this_array[],
                                  const INDIVIDUAL_AXIS that_array[]) {
    int indexes[2] = { this_array[0] >> 1, this_array[1] >> 1 };
    int zero_bits[2][2] = {
      { this_array[0] & 1, this_array[1] & 1 },
      { that_array[0] & 1, that_array[1] & 1 }
    };
    this_array[0] = (INDIVIDUAL_AXIS)((int)this_array[0] |
                                      ((int)zero_bits[0][0] ^
                                       (int)zero_bits[1][indexes[0]]));
    this_array[1] = (INDIVIDUAL_AXIS)((int)this_array[1] |
                                      ((int)zero_bits[0][1] ^
                                       (int)zero_bits[1][indexes[1]]));
  }

  void write_back_axis_array(const INDIVIDUAL_AXIS this_array[]) {
    int bit2 = ((int)this_array[0] & 2) != 0;  // swap xy
    int bit1 = ((int)this_array[1] & 1);
    int bit0 = ((int)this_array[0] & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
  }

  axis_transformation& set_directions(const direction_2d& horizontal_dir,
                                      const direction_2d& vertical_dir) {
    int bit2 = (static_cast<orientation_2d>(horizontal_dir).to_int()) != 0;
    int bit1 = !(vertical_dir.to_int() & 1);
    int bit0 = !(horizontal_dir.to_int() & 1);
    atr_ = ATR((bit2 << 2) + (bit1 << 1) + bit0);
    return *this;
  }

  template <typename coordinate_type>
  void transform(coordinate_type& x, coordinate_type& y) const {
    int bit2 = (atr_ & 4) != 0;
    int bit1 = (atr_ & 2) != 0;
    int bit0 = (atr_ & 1) != 0;
    x *= -((bit0 << 1) - 1);
    y *= -((bit1 << 1) - 1);
    predicated_swap(bit2 != 0, x, y);
  }

  axis_transformation& invert() {
    int bit2 = ((atr_ & 4) != 0);
    int bit1 = ((atr_ & 2) != 0);
    int bit0 = ((atr_ & 1) != 0);
    // swap bit 0 and bit 1 if bit2 is 1
    predicated_swap(bit2 != 0, bit0, bit1);
    bit1 = bit1 << 1;
    atr_ = (ATR)(atr_ & (32+16+8+4));  // mask away bit0 and bit1
    atr_ = (ATR)(atr_ | bit0 | bit1);
    return *this;
  }

  axis_transformation inverse() const {
    axis_transformation retval(*this);
    return retval.invert();
  }

  anisotropic_scale_factor() {
    scale_[0] = 1;
    scale_[1] = 1;
  }

  anisotropic_scale_factor(scale_factor_type xscale,
                           scale_factor_type yscale) {
    scale_[0] = xscale;
    scale_[1] = yscale;
  }

  scale_factor_type get(orientation_2d orient) const {
    return scale_[orient.to_int()];
  }

  void set(orientation_2d orient, scale_factor_type value) {
    scale_[orient.to_int()] = value;
  }


  scale_factor_type x() const {
    return scale_[HORIZONTAL];
  }


  scale_factor_type y() const {
    return scale_[VERTICAL];
  }


  void x(scale_factor_type value) {
    scale_[HORIZONTAL] = value;
  }


  void y(scale_factor_type value) {
    scale_[VERTICAL] = value;
  }

  anisotropic_scale_factor operator+(const anisotropic_scale_factor& s) const {
    anisotropic_scale_factor<scale_factor_type> retval(*this);
    return retval += s;
  }

  const anisotropic_scale_factor& operator+=(
      const anisotropic_scale_factor& s) {
    scale_[0] *= s.scale_[0];
    scale_[1] *= s.scale_[1];
    return *this;
  }

  anisotropic_scale_factor& transform(axis_transformation atr) {
    direction_2d dirs[2];
    atr.get_directions(dirs[0], dirs[1]);
    scale_factor_type tmp[2] = {scale_[0], scale_[1]};
    for (int i = 0; i < 2; ++i) {
      scale_[orientation_2d(dirs[i]).to_int()] = tmp[i];
    }
    return *this;
  }

  template <typename coordinate_type>
  void scale(coordinate_type& x, coordinate_type& y) const {
    x = scaling_policy<coordinate_type>::round(
        (scale_factor_type)x * get(HORIZONTAL));
    y = scaling_policy<coordinate_type>::round(
        (scale_factor_type)y * get(HORIZONTAL));
  }

  anisotropic_scale_factor& invert() {
    x(1/x());
    y(1/y());
    return *this;
  }

  transformation() : atr_(), p_(0, 0) {}

  explicit transformation(axis_transformation atr) : atr_(atr), p_(0, 0) {}

  explicit transformation(axis_transformation::ATR atr) : atr_(atr), p_(0, 0) {}

  transformation(const transformation& tr) : atr_(tr.atr_), p_(tr.p_) {}


  template <typename point_type>
  explicit transformation(const point_type& p) : atr_(), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& p) : atr_(atr), p_(0, 0) {
    set_translation(p);
  }


  template <typename point_type>
  transformation(axis_transformation atr,
                 const point_type& referencePt,
                 const point_type& destinationPt) : atr_(), p_(0, 0) {
    transformation<coordinate_type> tmp(referencePt);
    transformation<coordinate_type> rotRef(atr);
    transformation<coordinate_type> tmpInverse = tmp.inverse();
    point_type decon(referencePt);
    deconvolve(decon, destinationPt);
    transformation<coordinate_type> displacement(decon);
    tmp += rotRef;
    tmp += tmpInverse;
    tmp += displacement;
    (*this) = tmp;
  }

  bool operator==(const transformation& tr) const {
    return (atr_ == tr.atr_) && (p_ == tr.p_);
  }

  bool operator!=(const transformation& tr) const {
    return !(*this == tr);
  }

  bool operator<(const transformation& tr) const {
    return (atr_ < tr.atr_) || ((atr_ == tr.atr_) && (p_ < tr.p_));
  }

  transformation operator+(const transformation& tr) const {
    transformation<coordinate_type> retval(*this);
    return retval+=tr;
  }

  const transformation& operator+=(const transformation& tr) {
    coordinate_type x, y;
    transformation<coordinate_type> inv = inverse();
    inv.transform(x, y);
    p_.set(HORIZONTAL, p_.get(HORIZONTAL) + x);
    p_.set(VERTICAL, p_.get(VERTICAL) + y);
    // concatenate axis transforms
    atr_ += tr.atr_;
    return *this;
  }

  axis_transformation get_axis_transformation() const {
    return atr_;
  }

  void set_axis_transformation(const axis_transformation& atr) {
    atr_ = atr;
  }

  template <typename point_type>
  void get_translation(point_type& p) const {
    assign(p, p_);
  }

  template <typename point_type>
  void set_translation(const point_type& p) {
    assign(p_, p);
  }

  void transform(coordinate_type& x, coordinate_type& y) const {
    y -= p_.get(VERTICAL);
    x -= p_.get(HORIZONTAL);
    atr_.transform(x, y);
  }

  transformation& invert() {
    coordinate_type x = p_.get(HORIZONTAL), y = p_.get(VERTICAL);
    atr_.transform(x, y);
    x *= -1;
    y *= -1;
    p_ = point_data<coordinate_type>(x, y);
    atr_.invert();
    return *this;
  }

  transformation inverse() const {
    transformation<coordinate_type> ret_val(*this);
    return ret_val.invert();
  }


  void get_directions(direction_2d& horizontal_dir,
                      direction_2d& vertical_dir) const {
    return atr_.get_directions(horizontal_dir, vertical_dir);
  }


  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }


  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }


  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type get(const IntervalType& interval, direction_1d dir) {
  return interval_traits<IntervalType>::get(interval, dir);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_set,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type set(IntervalType& interval, direction_1d dir,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  interval_mutable_traits<IntervalType>::set(interval, dir, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type construct(
    typename interval_mutable_traits<IntervalType>::coordinate_type low,
    typename interval_mutable_traits<IntervalType>::coordinate_type high) {
  if (low > high) {
    (std::swap)(low, high);
  }
  return interval_mutable_traits<IntervalType>::construct(low, high);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_copy_construct,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type copy_construct(const IntervalType2& interval) {
  return construct<IntervalType1>(get(interval, LOW), get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_assign,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& assign(IntervalType1& lvalue, const IntervalType2& rvalue) {
  set(lvalue, LOW, get(rvalue, LOW));
  set(lvalue, HIGH, get(rvalue, HIGH));
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type low(const IntervalType& interval) {
  return get(interval, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type high(const IntervalType& interval) {
  return get(interval, HIGH);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_low2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type low(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, LOW, value);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_high2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  void
>::type high(IntervalType& interval,
    typename interval_mutable_traits<IntervalType>::coordinate_type value) {
  set(interval, HIGH, value);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_equivalence,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type equivalence(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return (get(interval1, LOW) == get(interval2, LOW)) &&
         (get(interval1, HIGH) == get(interval2, HIGH));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_contains,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value,
    bool consider_touch = true ) {
  if (consider_touch) {
    return value <= high(interval) && value >= low(interval);
  } else {
    return value < high(interval) && value > low(interval);
  }
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_contains2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type contains(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return contains(interval1, get(interval2, LOW), consider_touch) &&
         contains(interval1, get(interval2, HIGH), consider_touch);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_center,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_coordinate_type<IntervalType>::type
>::type center(const IntervalType& interval) {
  return (high(interval) + low(interval)) / 2;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_delta,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type delta(const IntervalType& interval) {
  typedef typename interval_difference_type<IntervalType>::type diff_type;
  return static_cast<diff_type>(high(interval)) -
         static_cast<diff_type>(low(interval));
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_flip,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
IntervalType>::type& flip(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type axis = 0) {
  typename interval_coordinate_type<IntervalType>::type newLow, newHigh;
  newLow  = 2 * axis - high(interval);
  newHigh = 2 * axis - low(interval);
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_up,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_up(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) * factor;
  low(interval, low(interval) * factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale_down,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale_down(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  typename interval_coordinate_type<IntervalType>::type newHigh =
      high(interval) / factor;
  low(interval, low(interval) / factor);
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_scale,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& scale(IntervalType& interval, double factor) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newHigh = scaling_policy<Unit>::round(
      static_cast<double>(high(interval)) * factor);
  low(interval, scaling_policy<Unit>::round(
      static_cast<double>(low(interval)) * factor));
  high(interval, (newHigh));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_move,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& move(
    IntervalType& interval,
    typename interval_difference_type<IntervalType>::type displacement) {
  typedef typename interval_coordinate_type<IntervalType>::type ctype;
  typedef typename coordinate_traits<ctype>::coordinate_difference Unit;
  low(interval, static_cast<ctype>(
      static_cast<Unit>(low(interval)) + displacement));
  high(interval, static_cast<ctype>(
      static_cast<Unit>(high(interval)) + displacement));
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_convolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& convolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) + value;
  Unit newHigh = high(interval) + value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_deconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& deconvolve(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
    typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit newLow  = low(interval) - value;
  Unit newHigh = high(interval) - value;
  low(interval, newLow);
  high(interval, newHigh);
  return interval;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_convolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& convolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) + low(rvalue);
  Unit newHigh = high(lvalue) + high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_deconvolve2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& deconvolve(IntervalType1& lvalue, const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - low(rvalue);
  Unit newHigh = high(lvalue) - high(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_reconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_convolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue) - high(rvalue);
  Unit newHigh = high(lvalue) - low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_redeconvolve,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& reflected_deconvolve(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit newLow  = low(lvalue)  + high(rvalue);
  Unit newHigh = high(lvalue) + low(rvalue);
  low(lvalue, newLow);
  high(lvalue, newHigh);
  return lvalue;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<y_i_e_dist1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType>::type
>::type euclidean_distance(
    const IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type position) {
  typedef typename interval_difference_type<IntervalType>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval) - (Unit)position,
      (Unit)position - (Unit)high(interval)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_dist2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  typename interval_difference_type<IntervalType1>::type
>::type euclidean_distance(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  typedef typename interval_difference_type<IntervalType1>::type Unit;
  Unit dist[3] = {
      0,
      (Unit)low(interval1) - (Unit)high(interval2),
      (Unit)low(interval2) - (Unit)high(interval1)
  };
  return dist[(dist[1] > 0) + ((dist[2] > 0) << 1)];
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_intersects,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersects(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return consider_touch ?
      (low(interval1) <= high(interval2)) &&
      (high(interval1) >= low(interval2)) :
      (low(interval1) < high(interval2)) &&
      (high(interval1) > low(interval2));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_e_bintersect,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type boundaries_intersect(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    bool consider_touch = true) {
  return (contains(interval1, low(interval2), consider_touch) ||
          contains(interval1, high(interval2), consider_touch)) &&
         (contains(interval2, low(interval1), consider_touch) ||
          contains(interval2, high(interval1), consider_touch));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue,
    bool consider_touch = true) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit lowVal = (std::max)(low(lvalue), low(rvalue));
  Unit highVal = (std::min)(high(lvalue), high(rvalue));
  bool valid = consider_touch ? lowVal <= highVal : lowVal < highVal;
  if (valid) {
    low(lvalue, lowVal);
    high(lvalue, highVal);
  }
  return valid;
}

template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_g_intersect,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  IntervalType1
>::type& generalized_intersect(
    IntervalType1& lvalue,
    const IntervalType2& rvalue) {
  typedef typename interval_coordinate_type<IntervalType1>::type Unit;
  Unit coords[4] = {low(lvalue), high(lvalue), low(rvalue), high(rvalue)};
  // TODO(asydorchuk): consider implementing faster sorting of small
  // fixed length range.
  polygon_sort(coords, coords+4);
  low(lvalue, coords[1]);
  high(lvalue, coords[2]);
  return lvalue;
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts1,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2,
    direction_1d dir) {
  return dir.to_int() ? low(interval2) == high(interval1) :
                        low(interval1) == high(interval2);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_abuts2,
    typename is_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type abuts(
    const IntervalType1& interval1,
    const IntervalType2& interval2) {
  return abuts(interval1, interval2, HIGH) ||
         abuts(interval1, interval2, LOW);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  low(interval, low(interval) - bloating);
  high(interval, high(interval) + bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_bloat2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& bloat(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type bloating) {
  set(interval, dir, get(interval, dir) + dir.get_sign() * bloating);
  return interval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, -shrinking);
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_shrink2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type& shrink(
    IntervalType& interval,
    direction_1d dir,
    typename interval_coordinate_type<IntervalType>::type shrinking) {
  return bloat(interval, dir, -shrinking);
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_encompass,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type
  >::type,
  bool
>::type encompass(IntervalType1& interval1, const IntervalType2& interval2) {
  bool retval = !contains(interval1, interval2, true);
  low(interval1, (std::min)(low(interval1), low(interval2)));
  high(interval1, (std::max)(high(interval1), high(interval2)));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_encompass2,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  bool
>::type encompass(
    IntervalType& interval,
    typename interval_coordinate_type<IntervalType>::type value) {
  bool retval = !contains(interval, value, true);
  low(interval, (std::min)(low(interval), value));
  high(interval, (std::max)(high(interval), value));
  return retval;
}


template <typename IntervalType>
typename enable_if<
  typename gtl_and<
    y_i_get_half,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType>::type
    >::type
  >::type,
  IntervalType
>::type get_half(const IntervalType& interval, direction_1d dir) {
  typedef typename interval_coordinate_type<IntervalType>::type Unit;
  Unit c = (get(interval, LOW) + get(interval, HIGH)) / 2;
  return construct<IntervalType>(
      (dir == LOW) ? get(interval, LOW) : c,
      (dir == LOW) ? c : get(interval, HIGH));
}


template <typename IntervalType1, typename IntervalType2>
typename enable_if<
  typename gtl_and_3<
    y_i_join_with,
    typename is_mutable_interval_concept<
      typename geometry_concept<IntervalType1>::type
    >::type,
    typename is_interval_concept<
      typename geometry_concept<IntervalType2>::type
    >::type>::type,
  bool
>::type join_with(IntervalType1& interval1, const IntervalType2& interval2) {
  if (abuts(interval1, interval2)) {
    encompass(interval1, interval2);
    return true;
  }
  return false;
}


  point_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  point_data(coordinate_type x, coordinate_type y) {
    coords_[HORIZONTAL] = x;
    coords_[VERTICAL] = y;
  }


  explicit point_data(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  point_data& operator=(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename PointType>
  explicit point_data(const PointType& that) {
    *this = that;
  }


  template <typename PointType>
  point_data& operator=(const PointType& that) {
    assign(*this, that);
    return *this;
  }

  template <typename CT>
  point_data(const point_data<CT>& that) {
    coords_[HORIZONTAL] = (coordinate_type)that.x();
    coords_[VERTICAL] = (coordinate_type)that.y();
  }


  coordinate_type get(orientation_2d orient) const {
    return coords_[orient.to_int()];
  }


  void set(orientation_2d orient, coordinate_type value) {
    coords_[orient.to_int()] = value;
  }


  coordinate_type x() const {
    return coords_[HORIZONTAL];
  }


  point_data& x(coordinate_type value) {
    coords_[HORIZONTAL] = value;
    return *this;
  }


  coordinate_type y() const {
    return coords_[VERTICAL];
  }


  point_data& y(coordinate_type value) {
    coords_[VERTICAL] = value;
    return *this;
  }


  bool operator==(const point_data& that) const {
    return (coords_[0] == that.coords_[0]) &&
      (coords_[1] == that.coords_[1]);
  }


  bool operator!=(const point_data& that) const {
    return !(*this == that);
  }


  bool operator<(const point_data& that) const {
    return (coords_[0] < that.coords_[0]) ||
      ((coords_[0] == that.coords_[0]) &&
       (coords_[1] < that.coords_[1]));
  }


  bool operator<=(const point_data& that) const {
    return !(that < *this);
  }


  bool operator>(const point_data& that) const {
    return that < *this;
  }


  bool operator>=(const point_data& that) const {
    return !(*this < that);
  }


  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}


  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }


  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }


  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }


  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }


  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }


  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }


  coordinate_type low() const {
    return coords_[0];
  }


  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }


  coordinate_type high() const {
    return coords_[1];
  }


  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }


  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }


  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }


  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }


  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }


  bool operator>(const interval_data& that) const {
    return that < *this;
  }


  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

  inline rectangle_data():ranges_() {}

  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }

  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }


  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }

  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }

  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }


  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }

  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }

  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }

    static inline interval_type get(const T& rectangle, orientation_2d orient) {
      return rectangle.get(orient); }

    template <typename T2>
    static inline void set(T& rectangle, orientation_2d orient, const T2& interval) {
      rectangle.set(orient, interval); }

    template <typename T2, typename T3>
    static inline T construct(const T2& interval_horizontal,
                              const T3& interval_vertical) {
      return T(interval_horizontal, interval_vertical); }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_get_interval, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                      typename rectangle_interval_type<T>::type>::type
  get(const T& rectangle, orientation_2d orient) {
    return rectangle_traits<T>::get(rectangle, orient);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_h, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  horizontal(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, HORIZONTAL);
  }


  template <typename T>
  typename enable_if< typename gtl_and<y_r_v, typename is_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       typename rectangle_interval_type<T>::type>::type
  vertical(const T& rectangle) {
    return rectangle_traits<T>::get(rectangle, VERTICAL);
  }


  template <orientation_2d_enum orient, typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_set2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  set(T& rectangle, orientation_2d orient, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, orient, interval);
  }


  template <typename T, typename T2>
  typename enable_if< typename gtl_and_3<y_r_h2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                                        typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type,
                       void>::type
  horizontal(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, HORIZONTAL, interval);
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_v2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
                     typename is_interval_concept<typename geometry_concept<T2>::type>::type>::type, void>::type
  vertical(T& rectangle, const T2& interval) {
    rectangle_mutable_traits<T>::set(rectangle, VERTICAL, interval);
  }


  template <typename T, typename T2, typename T3>
  typename enable_if< typename gtl_and<y_r_construct, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(const T2& interval_horizontal,
            const T3& interval_vertical) {
    return rectangle_mutable_traits<T>::construct(interval_horizontal, interval_vertical); }


  template <typename T, typename coord_type>
  typename enable_if< typename gtl_and<y_r_construct2, typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type>::type,
                       T>::type
  construct(coord_type xl, coord_type yl, coord_type xh, coord_type yh) {
    return rectangle_mutable_traits<T>::construct(interval_data<coord_type>(xl, xh),
                                                  interval_data<coord_type>(yl, yh));
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3<y_r_cconstruct,
      typename is_mutable_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    T>::type
  copy_construct(const T2& rectangle) {
    return construct<T> (get(rectangle, HORIZONTAL), get(rectangle, VERTICAL));
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_assign,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  assign(rectangle_type_1& lvalue, const rectangle_type_2& rvalue) {
    set(lvalue, HORIZONTAL, get(rvalue, HORIZONTAL));
    set(lvalue, VERTICAL, get(rvalue, VERTICAL));
    return lvalue;
  }


  template <typename T, typename T2>
  typename enable_if<
    typename gtl_and_3< y_r_equiv,
      typename is_rectangle_concept<typename geometry_concept<T>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type,
    bool>::type
  equivalence(const T& rect1, const T2& rect2) {
    return equivalence(get(rect1, HORIZONTAL), get(rect2, HORIZONTAL)) &&
      equivalence(get(rect1, VERTICAL), get(rect2, VERTICAL));
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_get, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  get(const rectangle_type& rectangle, orientation_2d orient, direction_1d dir) {
    return get(rectangle_traits<rectangle_type>::get(rectangle, orient), dir);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_set3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  set(rectangle_type& rectangle, orientation_2d orient, direction_1d dir,
      typename rectangle_coordinate_type<rectangle_type>::type value) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    set(ivl, dir, value);
    set(rectangle, orient, ivl);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xl(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      xl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_xh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  xh(const rectangle_type& rectangle) {
    return get(rectangle, HORIZONTAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_xh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
  xh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, HORIZONTAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yl, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yl(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, LOW);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yl2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yl(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, LOW, value);
  }


  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_yh, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_coordinate_type<rectangle_type>::type>::type
  yh(const rectangle_type& rectangle) {
    return get(rectangle, VERTICAL, HIGH);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_yh2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type, void>::type
      yh(rectangle_type& rectangle, typename rectangle_coordinate_type<rectangle_type>::type value) {
    return set(rectangle, VERTICAL, HIGH, value);
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ll,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ll(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_lr,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  lr(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yl(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ul,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ul(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xl(rectangle), yh(rectangle));
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_ur,  typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       point_data<typename rectangle_coordinate_type<rectangle_type>::type> >::type
  ur(const rectangle_type& rectangle) {
    return point_data<typename rectangle_coordinate_type<rectangle_type>::type> (xh(rectangle), yh(rectangle));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_contains, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  contains(const rectangle_type& rectangle, const rectangle_type_2 rectangle_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), horizontal(rectangle_contained), consider_touch) &&
      contains(vertical(rectangle), vertical(rectangle_contained), consider_touch);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_contains2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, bool>::type
  contains(const rectangle_type& rectangle, const point_type point_contained,
           bool consider_touch = true) {
    return contains(horizontal(rectangle), x(point_contained), consider_touch) &&
      contains(vertical(rectangle), y(point_contained), consider_touch);
  }

  template <typename rectangle_type, typename point_type_1, typename point_type_2>
  typename enable_if< typename gtl_and_4< y_r_set_points,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_1>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type_2>::type>::type>::type,
                       rectangle_type>::type &
  set_points(rectangle_type& rectangle, const point_type_1& p1,
             const point_type_2& p2) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit x1(x(p1));
    Unit x2(x(p2));
    Unit y1(y(p1));
    Unit y2(y(p2));
    horizontal(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(x1, x2));
    vertical(rectangle, construct<typename rectangle_interval_type<rectangle_type>::type>(y1, y2));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_move, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  move(rectangle_type& rectangle, orientation_2d orient,
       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference delta) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    move(ivl, delta);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3< y_r_convolve,
      typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  convolve(rectangle_type_1& rectangle,
           const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3< y_r_deconvolve,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_reconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_convolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_convolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_convolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_redeconvolve, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    rectangle_type_1>::type &
  reflected_deconvolve(rectangle_type_1& rectangle, const rectangle_type_2& convolution_rectangle) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = horizontal(rectangle);
    horizontal(rectangle, reflected_deconvolve(ivl, horizontal(convolution_rectangle)));
    ivl = vertical(rectangle);
    vertical(rectangle, reflected_deconvolve(ivl, vertical(convolution_rectangle)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_convolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       rectangle_type>::type &
  convolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, convolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, convolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_deconvolve2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type, rectangle_type>::type &
  deconvolve(rectangle_type& rectangle, const point_type& convolution_point) {
    typename rectangle_interval_type<rectangle_type>::type ivl = horizontal(rectangle);
    horizontal(rectangle, deconvolve(ivl, x(convolution_point)));
    ivl = vertical(rectangle);
    vertical(rectangle, deconvolve(ivl, y(convolution_point)));
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_delta, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  delta(const rectangle_type& rectangle, orientation_2d orient) {
    return delta(get(rectangle, orient));
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_area, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type>::type
  area(const rectangle_type& rectangle) {
    typedef typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::manhattan_area_type area_type;
    return (area_type)delta(rectangle, HORIZONTAL) * (area_type)delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_go, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      orientation_2d>::type
  guess_orientation(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) >= delta(rectangle, VERTICAL) ?
      HORIZONTAL : VERTICAL;
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_half_p, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  half_perimeter(const rectangle_type& rectangle) {
    return delta(rectangle, HORIZONTAL) + delta(rectangle, VERTICAL);
  }

  template <typename rectangle_type>
  typename enable_if< typename gtl_and<y_r_perimeter, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  perimeter(const rectangle_type& rectangle) {
    return 2 * half_perimeter(rectangle);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_intersects, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  intersects(const rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    return intersects(horizontal(rectangle), horizontal(b), consider_touch) &&
      intersects(vertical(rectangle), vertical(b), consider_touch);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    bool>::type
  boundaries_intersect(const rectangle_type_1& rectangle, const rectangle_type_2& b,
                       bool consider_touch = true) {
    return (intersects(rectangle, b, consider_touch) &&
            !(contains(rectangle, b, !consider_touch)) &&
            !(contains(b, rectangle, !consider_touch)));
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        direction_2d dir) {
    return
      abuts(get(rectangle, orientation_2d(dir)),
            get(b, orientation_2d(dir)),
            direction_1d(dir)) &&
      intersects(get(rectangle, orientation_2d(dir).get_perpendicular()),
                 get(b, orientation_2d(dir).get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts2, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b,
        orientation_2d orient) {
    return
      abuts(get(rectangle, orient), get(b, orient)) &&
      intersects(get(rectangle, orient.get_perpendicular()),
                 get(b, orient.get_perpendicular()), true);
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_abuts3, typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  abuts(const rectangle_type_1& rectangle, const rectangle_type_2& b) {
    return abuts(rectangle, b, HORIZONTAL) || abuts(rectangle, b, VERTICAL);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<
    typename gtl_and_3<y_r_b_intersect2, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                      typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
    bool>::type
  intersect(rectangle_type& rectangle, const interval_type& b,
            orientation_2d orient, bool consider_touch = true) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(intersect(ivl, b, consider_touch)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_b_intersect3, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  intersect(rectangle_type_1& rectangle, const rectangle_type_2& b, bool consider_touch = true) {
    if(intersects(rectangle, b)) {
      intersect(rectangle, horizontal(b), HORIZONTAL, consider_touch);
      intersect(rectangle, vertical(b), VERTICAL, consider_touch);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_g_intersect,
    typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       rectangle_type_1>::type &
  generalized_intersect(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typename rectangle_interval_type<rectangle_type_1>::type ivl = get(rectangle, HORIZONTAL);
    generalized_intersect(ivl, horizontal(b));
    horizontal(rectangle, ivl);
    ivl = vertical(rectangle);
    generalized_intersect(ivl, vertical(b));
    vertical(rectangle, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, orientation_2d orient,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    bloat(ivl, bloating);
    set(rectangle, orient, ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    bloat(rectangle, HORIZONTAL, bloating);
    return bloat(rectangle, VERTICAL, bloating);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_bloat3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  bloat(rectangle_type& rectangle, direction_2d dir,
        typename rectangle_coordinate_type<rectangle_type>::type bloating) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orientation_2d(dir));
    bloat(ivl, direction_1d(dir), bloating);
    set(rectangle, orientation_2d(dir), ivl);
    return rectangle;
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, orientation_2d orient,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, orient, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, -shrinking);
  }

  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_shrink3, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                      rectangle_type>::type &
  shrink(rectangle_type& rectangle, direction_2d dir,
         typename rectangle_coordinate_type<rectangle_type>::type shrinking) {
    return bloat(rectangle, dir, -shrinking);
  }

  template <typename rectangle_type, typename interval_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
        typename is_interval_concept<typename geometry_concept<interval_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type& rectangle, const interval_type& b, orientation_2d orient) {
    typename rectangle_interval_type<rectangle_type>::type ivl = get(rectangle, orient);
    if(encompass(ivl, b)) {
      set(rectangle, orient, ivl);
      return true;
    }
    return false;
  }

  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<
        y_r_encompass2,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type >::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    //note that operator | is intentional because both should be called regardless
    return encompass(rectangle, horizontal(b), HORIZONTAL) |
      encompass(rectangle, vertical(b), VERTICAL);
  }

  template <typename rectangle_type_1, typename point_type>
  typename enable_if<typename gtl_and_3<
        y_r_encompass3,
        typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
        typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
      bool>::type
  encompass(rectangle_type_1& rectangle, const point_type& b) {
    typename rectangle_interval_type<rectangle_type_1>::type hivl, vivl;
    hivl = horizontal(rectangle);
    vivl = vertical(rectangle);
    //note that operator | is intentional because both should be called regardless
    bool retval = encompass(hivl, x(b)) | encompass(vivl, y(b));
    if(retval) {
      horizontal(rectangle, hivl);
      vertical(rectangle, vivl);
    }
    return retval;
  }

  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_center, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  center(point_type& center_point, const rectangle_type& rectangle) {
    center_point = construct<point_type>(center(horizontal(rectangle)),
                                         center(vertical(rectangle)));
    return true;
  }


  template <typename point_type, typename rectangle_type>
  typename enable_if<
    typename gtl_and_3<y_r_get_corner, typename is_mutable_point_concept<typename geometry_concept<point_type>::type>::type,
                      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
    bool>::type
  get_corner(point_type& corner_point, const rectangle_type& rectangle, direction_2d direction_facing, direction_1d direction_turning) {
    typedef typename rectangle_coordinate_type<rectangle_type>::type Unit;
    Unit u1 = get(rectangle, direction_facing);
    Unit u2 = get(rectangle, direction_facing.turn(direction_turning));
    if(orientation_2d(direction_facing).to_int()) std::swap(u1, u2);
    corner_point = construct<point_type>(u1, u2);
    return true;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_get_half, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type
  get_half(const rectangle_type& rectangle, direction_2d dir) {
    rectangle_type retval(rectangle);
    set(retval, orientation_2d(dir), get_half(get(rectangle, orientation_2d(dir)), direction_1d(dir)));
    return retval;
  }


  template <typename rectangle_type_1, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_join_with, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                                         typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       bool>::type
  join_with(rectangle_type_1& rectangle, const rectangle_type_2& b) {
    typedef typename rectangle_interval_type<rectangle_type_1>::type Interval1;
    typedef typename rectangle_interval_type<rectangle_type_2>::type Interval2;
    Interval1 hi1 = get(rectangle, HORIZONTAL);
    Interval1 vi1 = get(rectangle, VERTICAL);
    Interval2 hi2 = get(b, HORIZONTAL), vi2 = get(b, VERTICAL);
    Interval1 temp;
    if (equivalence(hi1, hi2) && join_with(vi1, vi2)) {
      vertical(rectangle, vi1);
      return true;
    }
    if (equivalence(vi1, vi2) && join_with(hi1, hi2)) {
      horizontal(rectangle, hi1);
      return true;
    }
    return false;
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_eda2,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                      typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const point_type& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_eda,
      typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue, orientation_2d orient) {
    return euclidean_distance(get(lvalue, orient), get(rvalue, orient));
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_sed,
    typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
    typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_sed2, typename is_rectangle_concept< typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept< typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  square_euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return (xdist * xdist) + (ydist * ydist);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if< typename gtl_and_3<y_r_edist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(rectangle_type& lvalue, const point_type& rvalue) {
    return std::sqrt((double)(square_euclidean_distance(lvalue, rvalue)));
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if< typename gtl_and_3<y_r_edist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                                          typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
                       typename rectangle_distance_type<rectangle_type>::type>::type
  euclidean_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    double val = (int)square_euclidean_distance(lvalue, rvalue);
    return std::sqrt(val);
  }


  template <typename rectangle_type, typename point_type>
  typename enable_if<
    typename gtl_and_3<y_r_mdist, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(rectangle_type& lvalue, const point_type& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type, typename rectangle_type_2>
  typename enable_if<
    typename gtl_and_3<y_r_mdist2, typename is_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type,
                                       typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
    typename rectangle_difference_type<rectangle_type>::type>::type
  manhattan_distance(const rectangle_type& lvalue, const rectangle_type_2& rvalue) {
    typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::coordinate_difference xdist, ydist;
    xdist = euclidean_distance(lvalue, rvalue, HORIZONTAL);
    ydist = euclidean_distance(lvalue, rvalue, VERTICAL);
    return xdist + ydist;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_up, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_up(rectangle_type& rectangle,
           typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_up(horizontal(rectangle), factor));
    vertical(rectangle, scale_up(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type>
  typename enable_if<typename gtl_and<y_r_scale_down, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale_down(rectangle_type& rectangle,
             typename coordinate_traits<typename rectangle_coordinate_type<rectangle_type>::type>::unsigned_area_type factor) {
    horizontal(rectangle, scale_down(horizontal(rectangle), factor));
    vertical(rectangle, scale_down(vertical(rectangle), factor));
    return rectangle;
  }


  template <typename rectangle_type, typename scaling_type>
  typename enable_if<typename gtl_and<y_r_scale, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  scale(rectangle_type& rectangle, const scaling_type& scaling) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xl(rectangle), yl(rectangle));
    scale(llp, scaling);
    scale(urp, scaling);
    set_points(rectangle, llp, urp);
    return rectangle;
  }


  template <typename rectangle_type, typename transformation_type>
  typename enable_if<typename gtl_and<y_r_transform, typename is_mutable_rectangle_concept<typename geometry_concept<rectangle_type>::type>::type>::type,
                     rectangle_type>::type &
  transform(rectangle_type& rectangle, const transformation_type& transformation) {
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> llp(xl(rectangle), yl(rectangle));
    point_data<typename rectangle_coordinate_type<rectangle_type>::type> urp(xh(rectangle), yh(rectangle));
    transform(llp, transformation);
    transform(urp, transformation);
    set_points(rectangle, llp, urp);
    return rectangle;
  }

    inline less_rectangle_concept(orientation_2d orient = VERTICAL) : orient_(orient) {}

    typename enable_if<
      typename gtl_and< typename is_rectangle_concept<typename geometry_concept<rectangle_type_1>::type>::type,
                        typename is_rectangle_concept<typename geometry_concept<rectangle_type_2>::type>::type>::type,
      bool>::type
    operator () (const rectangle_type_1& a,
                 const rectangle_type_2& b) const {
      typedef typename rectangle_coordinate_type<rectangle_type_1>::type Unit;
      Unit vl1 = get(get(a, orient_), LOW);
      Unit vl2 = get(get(b, orient_), LOW);
      if(vl1 > vl2) return false;
      if(vl1 == vl2) {
        orientation_2d perp = orient_.get_perpendicular();
        Unit hl1 = get(get(a, perp), LOW);
        Unit hl2 = get(get(b, perp), LOW);
        if(hl1 > hl2) return false;
        if(hl1 == hl2) {
          Unit vh1 = get(get(a, orient_), HIGH);
          Unit vh2 = get(get(b, orient_), HIGH);
          if(vh1 > vh2) return false;
          if(vh1 == vh2) {
            Unit hh1 = get(get(a, perp), HIGH);
            Unit hh2 = get(get(b, perp), HIGH);
            return hh1 < hh2;
          }
        }
      }
      return true;
    }

  template <typename interval_type_1>
  inline void rectangle_data<T>::set(orientation_2d orient, const interval_type_1& interval) {
    assign(ranges_[orient.to_int()], interval);
  }

  template <class T2>
  rectangle_data<T>& rectangle_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }

  template <class T2>
  bool rectangle_data<T>::operator==(const T2& rvalue) const {
    return equivalence(*this, rvalue);
  }


  static point_type get(
      const segment_type& segment, direction_1d dir) {
    return segment.get(dir);
  }


  static void set(
      segment_type& segment, direction_1d dir, const point_type& point) {
    segment.set(dir, point);
  }


  static segment_type construct(const point_type& low, const point_type& high) {
    return segment_type(low, high);
  }


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_get,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
get(const Segment& segment, direction_1d dir) {
  return segment_traits<Segment>::get(segment, dir);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_set,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type set(Segment& segment, direction_1d dir, const Point& point) {
  segment_mutable_traits<Segment>::set(segment, dir, point);
}


template <typename Segment, typename Point1, typename Point2>
typename enable_if<
  typename gtl_and_4<
    y_s_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point1>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point2>::type
    >::type
  >::type,
Segment>::type construct(const Point1& low, const Point2& high) {
  return segment_mutable_traits<Segment>::construct(low, high);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_copy_construct,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type copy_construct(const Segment2& segment) {
  return construct<Segment1>(get(segment, LOW), get(segment, HIGH));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_assign,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
Segment1>::type& assign(Segment1& segment1, const Segment2& segment2) {
  return segment1 = copy_construct<Segment1>(segment2);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_equivalence,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type equivalence(const Segment1& segment1, const Segment2& segment2) {
  return get(segment1, LOW) == get(segment2, LOW) &&
         get(segment1, HIGH) == get(segment2, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_low,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type low(const Segment& segment) {
  return get(segment, LOW);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_high,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type high(const Segment& segment) {
  return get(segment, HIGH);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_center,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_point_type<Segment>::type>::type
center(const Segment& segment) {
  return construct<typename segment_point_type<Segment>::type>(
      (x(high(segment)) + x(low(segment)))/2,
      (y(high(segment)) + y(low(segment)))/2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_low2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type low(Segment& segment, const Point& point) {
  set(segment, LOW, point);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_high2,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
void>::type high(Segment& segment, const Point& point) {
  set(segment, HIGH, point);
}

template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
int>::type orientation(const Segment1& segment1, const Segment2& segment2) {
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::manhattan_area_type int_x2;
  typedef typename coordinate_traits<
    typename segment_traits<Segment1>::coordinate_type
  >::unsigned_area_type uint_x2;
  int_x2 a1 = (int_x2)x(high(segment1)) - (int_x2)x(low(segment1));
  int_x2 b1 = (int_x2)y(high(segment1)) - (int_x2)y(low(segment1));
  int_x2 a2 = (int_x2)x(high(segment2)) - (int_x2)x(low(segment2));
  int_x2 b2 = (int_x2)y(high(segment2)) - (int_x2)y(low(segment2));

  int sign1 = 0;
  int sign2 = 0;
  if (a1 && b2)
    sign1 = ((a1 > 0) ^ (b2 > 0)) ? -1 : 1;
  if (a2 && b1)
    sign2 = ((a2 > 0) ^ (b1 > 0)) ? -1 : 1;

  if (sign1 != sign2)
    return (sign1 < sign2) ? -1 : 1;
  uint_x2 a3 = (uint_x2)(a1 < 0 ? -a1 : a1) * (uint_x2)(b2 < 0 ? -b2 : b2);
  uint_x2 b3 = (uint_x2)(b1 < 0 ? -b1 : b1) * (uint_x2)(a2 < 0 ? -a2 : a2);
  if (a3 == b3)
    return 0;
  return ((a3 < b3) ^ (sign1 == 1)) ? 1 : -1;
}

template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_orientation2,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
int>::type orientation(const Segment& segment, const Point& point) {
  Segment segment2 = construct<Segment>(high(segment), point);
  return orientation(segment, segment2);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_contains,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
bool>::type contains(const Segment& segment,
    const Point& point, bool consider_touch = true ) {
  if (orientation(segment, point))
    return false;
  rectangle_data<typename segment_coordinate_type<Segment>::type> rect;
  set_points(rect, low(segment), high(segment));
  if (!contains(rect, point, true))
    return false;
  if (!consider_touch &&
      (equivalence(low(segment), point) ||
       equivalence(high(segment), point)))
    return false;
  return true;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_contains2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type contains(const Segment1& segment1,
    const Segment2& segment2, bool consider_touch = true) {
  return contains(segment1, get(segment2, LOW), consider_touch) &&
         contains(segment1, get(segment2, HIGH), consider_touch);
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_length,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
length(const Segment& segment) {
  return euclidean_distance(low(segment), high(segment));
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_up,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_up(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_up(l, factor));
  high(segment, scale_up(h, factor));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_scale_down,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale_down(Segment& segment,
    typename coordinate_traits<
      typename segment_coordinate_type<Segment>::type
    >::unsigned_area_type factor) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale_down(l, factor));
  high(segment, scale_down(h, factor));
  return segment;
}


template <typename Segment, typename Scale>
typename enable_if<
  typename gtl_and<
    y_s_scale,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& scale(Segment& segment, const Scale& sc) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, scale(l, sc));
  high(segment, scale(h, sc));
  return segment;
}


template <typename Segment, typename Transform>
typename enable_if<
  typename gtl_and<
    y_s_transform,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& transform(Segment& segment, const Transform& tr) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, transform(l, tr));
  high(segment, transform(h, tr));
  return segment;
}


template <typename Segment>
typename enable_if<
  typename gtl_and<
    y_s_move,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type
  >::type,
Segment>::type& move(Segment& segment, orientation_2d orient,
    typename segment_coordinate_type<Segment>::type displacement) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, move(l, orient, displacement));
  high(segment, move(h, orient, displacement));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_convolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& convolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, convolve(l, point));
  high(segment, convolve(h, point));
  return segment;
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_deconvolve,
    typename is_mutable_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
Segment>::type& deconvolve(Segment& segment, const Point& point) {
  typename segment_point_type<Segment>::type l = low(segment);
  typename segment_point_type<Segment>::type h = high(segment);
  low(segment, deconvolve(l, point));
  high(segment, deconvolve(h, point));
  return segment;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts1,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1,
    const Segment2& segment2, direction_1d dir) {
  return dir.to_int() ? equivalence(low(segment2) , high(segment1)) :
                        equivalence(low(segment1) , high(segment2));
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_abuts2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool>::type abuts(const Segment1& segment1, const Segment2& segment2) {
  return abuts(segment1, segment2, HIGH) || abuts(segment1, segment2, LOW);
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_intersects,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
bool
>::type intersects(const Segment1& segment1, const Segment2& segment2,
    bool consider_touch = true) {
  rectangle_data<typename segment_coordinate_type<Segment1>::type> rect1, rect2;
  set_points(rect1, low(segment1), high(segment1));
  set_points(rect2, low(segment2), high(segment2));
  // Check if axis-parallel rectangles containing segments intersect.
  if (!intersects(rect1, rect2, true))
    return false;
  int or1_1 = orientation(segment1, low(segment2));
  int or1_2 = orientation(segment1, high(segment2));
  if (or1_1 * or1_2 > 0)
    return false;
  int or2_1 = orientation(segment2, low(segment1));
  int or2_2 = orientation(segment2, high(segment1));
  if (or2_1 * or2_2 > 0)
    return false;
  if (consider_touch || (or1_1 && or1_2) || (or2_1 && or2_2))
    return true;
  if (or1_1 || or1_2)
    return false;
  return intersects(vertical(rect1), vertical(rect2), false) ||
         intersects(horizontal(rect1), horizontal(rect2), false);
}


template <typename Segment, typename Point>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist,
    typename is_segment_concept<
      typename geometry_concept<Segment>::type
    >::type,
    typename is_point_concept<
      typename geometry_concept<Point>::type
    >::type
  >::type,
typename segment_distance_type<Segment>::type>::type
euclidean_distance(const Segment& segment, const Point& point) {
  typedef typename segment_distance_type<Segment>::type Unit;
  Unit x1 = x(low(segment));
  Unit y1 = y(low(segment));
  Unit x2 = x(high(segment));
  Unit y2 = y(high(segment));
  Unit X = x(point);
  Unit Y = y(point);
  Unit A = X - x1;
  Unit B = Y - y1;
  Unit C = x2 - x1;
  Unit D = y2 - y1;
  Unit param = (A * C + B * D);
  Unit length_sq = C * C + D * D;
  if (param > length_sq) {
    return euclidean_distance(high(segment), point);
  } else if (param < 0.0) {
    return euclidean_distance(low(segment), point);
  }
  if (length_sq == 0.0)
    return 0.0;
  Unit denom = std::sqrt(length_sq);
  Unit result = (A * D - C * B) / denom;
  return (result < 0.0) ? -result : result;
}


template <typename Segment1, typename Segment2>
typename enable_if<
  typename gtl_and_3<
    y_s_e_dist2,
    typename is_segment_concept<
      typename geometry_concept<Segment1>::type
    >::type,
    typename is_segment_concept<
      typename geometry_concept<Segment2>::type
    >::type
  >::type,
typename segment_distance_type<Segment1>::type>::type
euclidean_distance(const Segment1& segment1, const Segment2& segment2) {
  if (intersects(segment1, segment2))
    return 0.0;
  typename segment_distance_type<Segment1>::type
      result1 = euclidean_distance(segment1, low(segment2)),
      result2 = euclidean_distance(segment1, high(segment2)),
      result3 = euclidean_distance(segment2, low(segment1)),
      result4 = euclidean_distance(segment2, high(segment1));
  if (result2 < result1)
    result1 = result2;
  if (result4 < result3)
    result3 = result4;
  return (result1 < result3) ? result1 : result3;
}


  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}

  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}

  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}

  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }

  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }

  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }

  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }


  inline iterator_compact_to_points() : iter_(), iter_end_(), pt_(), firstX_(), orient_() {}

  inline iterator_compact_to_points(iterator_type iter, iterator_type iter_end) :
    iter_(iter), iter_end_(iter_end), pt_(), firstX_(), orient_(HORIZONTAL) {
    if(iter_ != iter_end_) {
      firstX_ = *iter_;
      x(pt_, firstX_);
      ++iter_;
      if(iter_ != iter_end_) {
        y(pt_, *iter_);
      }
    }
  }

  inline iterator_compact_to_points& operator++() {
    iterator_type prev_iter = iter_;
    ++iter_;
    if(iter_ == iter_end_) {
      if(x(pt_) != firstX_) {
        iter_ = prev_iter;
        x(pt_, firstX_);
      }
    } else {
      set(pt_, orient_, *iter_);
      orient_.turn_90();
    }
    return *this;
  }

  inline const iterator_compact_to_points operator++(int) {
    iterator_compact_to_points tmp(*this);
    ++(*this);
    return tmp;
  }

  inline bool operator==(const iterator_compact_to_points& that) const {
    return (iter_ == that.iter_);
  }

  inline bool operator!=(const iterator_compact_to_points& that) const {
    return (iter_ != that.iter_);
  }

  inline reference operator*() const { return pt_; }

    static inline compact_iterator_type begin_compact(const T& t) {
      return t.begin_compact();
    }

    static inline compact_iterator_type end_compact(const T& t) {
      return t.end_compact();
    }

    static inline std::size_t size(const T& t) {
      return t.size();
    }

    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }

    static inline iterator_type begin_points(const T& t) {
      return t.begin();
    }

    static inline iterator_type end_points(const T& t) {
      return t.end();
    }

    static inline std::size_t size(const T& t) {
      return t.size();
    }

    static inline winding_direction winding(const T&) {
      return unknown_winding;
    }

    static inline iterator_type begin_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::begin_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    static inline iterator_type end_points(const T& t) {
      return iterator_type(polygon_90_traits<T>::end_compact(t),
                           polygon_90_traits<T>::end_compact(t));
    }

    static inline std::size_t size(const T& t) {
      return polygon_90_traits<T>::size(t);
    }

    static inline winding_direction winding(const T& t) {
      return polygon_90_traits<T>::winding(t);
    }

    static inline iterator_holes_type begin_holes(const T& t) {
      return t.begin_holes();
    }

    static inline iterator_holes_type end_holes(const T& t) {
      return t.end_holes();
    }

    static inline std::size_t size_holes(const T& t) {
      return t.size_holes();
    }

    template <typename iT>
    static inline T& set_compact(T& t, iT input_begin, iT input_end) {
      t.set_compact(input_begin, input_end);
      return t;
    }

    template <typename iT>
    static inline T& set_points(T& t, iT input_begin, iT input_end) {
      t.set(input_begin, input_end);
      return t;
    }

    template <typename iT>
    static inline T& set_holes(T& t, iT inputBegin, iT inputEnd) {
      t.set_holes(inputBegin, inputEnd);
      return t;
    }


  inline polygon_45_data() : coords_() {}


  template<class iT>
  inline polygon_45_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}


  template<class iT>
  inline polygon_45_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  inline polygon_45_data(const polygon_45_data& that) : coords_(that.coords_) {}

  inline polygon_45_data& operator=(const polygon_45_data& that) {
    coords_ = that.coords_;
    return *this;
  }


  inline bool operator==(const polygon_45_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }


  inline bool operator!=(const polygon_45_data& that) const { return !((*this) == that); }

  inline iterator_type begin() const { return coords_.begin(); }

  inline iterator_type end() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }


  inline polygon_data() : coords_() {}


  template<class iT>
  inline polygon_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}


  template<class iT>
  inline polygon_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  inline polygon_data(const polygon_data& that) : coords_(that.coords_) {}

  inline polygon_data& operator=(const polygon_data& that) {
    coords_ = that.coords_;
    return *this;
  }


  inline bool operator==(const polygon_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }


  inline bool operator!=(const polygon_data& that) const { return !((*this) == that); }

  inline iterator_type begin() const { return coords_.begin(); }

  inline iterator_type end() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }


  inline polygon_90_data() : coords_() {}

  template<class iT>
  inline polygon_90_data& set(iT begin_point, iT end_point) {
    return set_compact(iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(begin_point, end_point),
                       iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(end_point, end_point));
  }


  template<class iT>
  inline polygon_90_data& set_compact(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    while(input_begin != input_end) {
       coords_.insert(coords_.end(), *input_begin);
       ++input_begin;
    }
    return *this;
  }

  inline polygon_90_data(const polygon_90_data& that) : coords_(that.coords_) {}

  inline polygon_90_data& operator=(const polygon_90_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  inline bool operator==(const polygon_90_data& that) const {
    return coords_ == that.coords_;
  }

  inline iterator_type begin() const { return iterator_type(coords_.begin(), coords_.end()); }

  inline iterator_type end() const { return iterator_type(coords_.end(), coords_.end()); }

  inline compact_iterator_type begin_compact() const { return coords_.begin(); }

  inline compact_iterator_type end_compact() const { return coords_.end(); }


  inline std::size_t size() const { return coords_.size(); }

  inline polygon_90_with_holes_data() : self_(), holes_() {}

  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }

  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  inline polygon_45_with_holes_data() : self_(), holes_() {}


  template<class iT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }


  template<class iT, typename hiT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }


  template<class iT>
  inline polygon_45_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_45_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  inline polygon_45_with_holes_data(const polygon_45_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_45_with_holes_data& operator=(const polygon_45_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  inline polygon_with_holes_data() : self_(), holes_() {}


  template<class iT>
  inline polygon_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }


  template<class iT, typename hiT>
  inline polygon_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }


  template<class iT>
  inline polygon_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  template<class iT>
  inline polygon_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  inline polygon_with_holes_data(const polygon_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  inline polygon_with_holes_data& operator=(const polygon_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  inline const iterator_type begin() const {
    return self_.begin();
  }

  inline const iterator_type end() const {
    return self_.end();
  }


  inline std::size_t size() const {
    return self_.size();
  }

  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }


  inline std::size_t size_holes() const {
    return holes_.size();
  }

  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_type<T>::type, T>::type &
  set_points(T& t, iT begin_points, iT end_points) {
    polygon_mutable_traits<T>::set_points(t, begin_points, end_points);
    return t;
  }

  template <typename T, typename iT>
  typename enable_if <typename gtl_or<
    typename is_mutable_polygon_90_type<T>::type,
    typename is_mutable_polygon_90_with_holes_type<T>::type>::type, T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    polygon_90_mutable_traits<T>::set_compact(t, begin_compact_coordinates, end_compact_coordinates);
    return t;
  }

  template <typename T, typename iT>
  typename enable_if< typename gtl_and <
    typename is_any_mutable_polygon_with_holes_type<T>::type,
    typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                                manhattan_domain>::type>::type,
                       T>::type &
  set_compact(T& t, iT begin_compact_coordinates, iT end_compact_coordinates) {
    iterator_compact_to_points<iT, point_data<typename polygon_traits<T>::coordinate_type> >
      itrb(begin_compact_coordinates, end_compact_coordinates),
      itre(end_compact_coordinates, end_compact_coordinates);
    return set_points(t, itrb, itre);
  }

  template <typename T, typename iT>
  typename enable_if <typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  set_holes(T& t, iT begin_holes, iT end_holes) {
    polygon_with_holes_mutable_traits<T>::set_holes(t, begin_holes, end_holes);
    return t;
  }

  begin_compact(const T& polygon,
    typename enable_if<
      typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                        typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
                manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::begin_compact(polygon);
  }

  end_compact(const T& polygon,
    typename enable_if<
    typename gtl_and <typename is_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_domain<typename geometry_concept<T>::type>::type,
              manhattan_domain>::type>::type>::type * = 0
  ) {
    return polygon_90_traits<T>::end_compact(polygon);
  }

  begin_points(const T& polygon) {
    return polygon_traits<T>::begin_points(polygon);
  }

  end_points(const T& polygon) {
    return polygon_traits<T>::end_points(polygon);
  }

  size(const T& polygon) {
    return polygon_traits<T>::size(polygon);
  }

  begin_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::begin_holes(polygon);
  }

  end_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::end_holes(polygon);
  }

  size_holes(const T& polygon) {
    return polygon_with_holes_traits<T>::size_holes(polygon);
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_type<T1>::type,
                      typename is_polygon_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_with_holes_type<T1>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_45_type<T1>::type, typename is_polygon_45_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_45_with_holes_type<T1>::type,
                      typename is_polygon_45_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_mutable_traits<T1>::set_points(lvalue, polygon_traits<T2>::begin_points(rvalue),
                                           polygon_traits<T2>::end_points(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_type<T1>::type,
                      typename is_polygon_90_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_polygon_90_with_holes_type<T1>::type,
                      typename is_polygon_90_with_holes_type<T2>::type>::type, T1>::type &
  assign(T1& lvalue, const T2& rvalue) {
    polygon_90_mutable_traits<T1>::set_compact(lvalue, polygon_90_traits<T2>::begin_compact(rvalue),
                                               polygon_90_traits<T2>::end_compact(rvalue));
    polygon_with_holes_mutable_traits<T1>::set_holes(lvalue, polygon_with_holes_traits<T2>::begin_holes(rvalue),
                                                     polygon_with_holes_traits<T2>::end_holes(rvalue));
    return lvalue;
  }

  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_type<T1>::type,
                      typename is_rectangle_concept<typename geometry_concept<T2>::type>::type>::type, T1>::type &
  assign(T1& polygon, const T2& rect) {
    typedef point_data<typename polygon_traits<T1>::coordinate_type> PT;
    PT points[4] = {PT(xl(rect), yl(rect)), PT(xh(rect), yl(rect)), PT(xh(rect), yh(rect)), PT(xl(rect), yh(rect))};
    set_points(polygon, points, points+4);
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename is_mutable_polygon_90_type<polygon_type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename polygon_90_traits<polygon_type>::coordinate_type> coords;
    coords.reserve(size(polygon));
    bool pingpong = true;
    for(typename polygon_90_traits<polygon_type>::compact_iterator_type iter = begin_compact(polygon);
        iter != end_compact(polygon); ++iter) {
      coords.push_back((*iter) + (pingpong ? x(point) : y(point)));
      pingpong = !pingpong;
    }
    polygon_90_mutable_traits<polygon_type>::set_compact(polygon, coords.begin(), coords.end());
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if< typename gtl_and< typename gtl_or<
    typename is_mutable_polygon_45_type<polygon_type>::type,
    typename is_mutable_polygon_type<polygon_type>::type>::type,
                                         typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
                       polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      convolve(points.back(), point);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename polygon_type, typename point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type,
                      typename is_point_concept<typename geometry_concept<point_type>::type>::type>::type,
    polygon_type>::type &
  convolve(polygon_type& polygon, const point_type& point) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    convolve(h, point);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      convolve(holes.back(), point);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename polygon_type, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  transform(polygon_type& polygon, const transform_type& tr) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      transform(points.back(), tr);
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }

  template <typename T, typename transform_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<T>::type, T>::type &
  transform(T& polygon, const transform_type& tr) {
    typedef typename polygon_with_holes_traits<T>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    transform(h, tr);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<T>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      transform(holes.back(), tr);
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }


  template <typename Unit>
  Unit local_abs(Unit value) { return value < 0 ? (Unit)-value : value; }


  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
    }
    snap_point_vector_to_45(points);
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }


  template <typename polygon_type>
  typename enable_if< typename is_any_mutable_polygon_with_holes_type<polygon_type>::type, polygon_type>::type &
  snap_to_45(polygon_type& polygon) {
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    hole_type h;
    set_points(h, begin_points(polygon), end_points(polygon));
    snap_to_45(h);
    std::vector<hole_type> holes;
    holes.reserve(size_holes(polygon));
    for(typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itr = begin_holes(polygon);
        itr != end_holes(polygon); ++itr) {
      holes.push_back(*itr);
      snap_to_45(holes.back());
    }
    assign(polygon, h);
    set_holes(polygon, holes.begin(), holes.end());
    return polygon;
  }

  template <typename polygon_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_without_holes_type<polygon_type>::type,
                      typename gtl_not<typename gtl_same_type
                                       < forty_five_domain,
                                         typename geometry_domain<typename geometry_concept<polygon_type>::type>::type>::type>::type>::type,
    polygon_type>::type &
  scale(polygon_type& polygon, double factor) {
    std::vector<typename std::iterator_traits<typename polygon_traits<polygon_type>::iterator_type>::value_type> points;
    points.reserve(size(polygon));
    for(typename polygon_traits<polygon_type>::iterator_type iter = begin_points(polygon);
        iter != end_points(polygon); ++iter) {
      points.push_back(*iter);
      scale(points.back(), anisotropic_scale_factor<double>(factor, factor));
    }
    polygon_mutable_traits<polygon_type>::set_points(polygon, points.begin(), points.end());
    return polygon;
  }


  template <typename iterator_type, typename area_type>
  static area_type
  point_sequence_area(iterator_type begin_range, iterator_type end_range) {
    typedef typename std::iterator_traits<iterator_type>::value_type point_type;
    typedef typename point_traits<point_type>::coordinate_type Unit;
    if(begin_range == end_range) return area_type(0);
    point_type first = *begin_range;
    point_type previous = first;
    ++begin_range;
    // Initialize trapezoid base line
    area_type y_base = (area_type)y(first);
    // Initialize area accumulator

    area_type area(0);
    while (begin_range != end_range) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(*begin_range);
#ifdef BOOST_POLYGON_ICC
#pragma warning (push)
#pragma warning (disable:1572)
#endif
      if(x1 != x2) {
#ifdef BOOST_POLYGON_ICC
#pragma warning (pop)
#endif
        // do trapezoid area accumulation
        area += (x2 - x1) * (((area_type)y(*begin_range) - y_base) +
                             ((area_type)y(previous) - y_base)) / 2;
      }
      previous = *begin_range;
      // go to next point
      ++begin_range;
    }
    //wrap around to evaluate the edge between first and last if not closed
    if(!equivalence(first, previous)) {
      area_type x1 = (area_type)x(previous);
      area_type x2 = (area_type)x(first);
      area += (x2 - x1) * (((area_type)y(first) - y_base) +
                           ((area_type)y(previous) - y_base)) / 2;
    }
    return area;
  }


  template <typename iT>
  bool point_sequence_is_45(iT itr, iT itr_end) {
    typedef typename std::iterator_traits<iT>::value_type Point;
    typedef typename point_traits<Point>::coordinate_type Unit;
    if(itr == itr_end) return true;
    Point firstPt = *itr;
    Point prevPt = firstPt;
    ++itr;
    while(itr != itr_end) {
      Point pt = *itr;
      Unit deltax = x(pt) - x(prevPt);
      Unit deltay = y(pt) - y(prevPt);
      if(deltax && deltay &&
         local_abs(deltax) != local_abs(deltay))
        return false;
      prevPt = pt;
      ++itr;
    }
    Unit deltax = x(firstPt) - x(prevPt);
    Unit deltay = y(firstPt) - y(prevPt);
    if(deltax && deltay &&
       local_abs(deltax) != local_abs(deltay))
      return false;
    return true;
  }


  template <typename polygon_type>
  typename enable_if< typename is_polygon_with_holes_type<polygon_type>::type, bool>::type
  is_45(const polygon_type& polygon) {
    typename polygon_traits<polygon_type>::iterator_type itr = begin_points(polygon), itr_end = end_points(polygon);
    if(!point_sequence_is_45(itr, itr_end)) return false;
    typename polygon_with_holes_traits<polygon_type>::iterator_holes_type itrh = begin_holes(polygon), itrh_end = end_holes(polygon);
    typedef typename polygon_with_holes_traits<polygon_type>::hole_type hole_type;
    for(; itrh != itrh_end; ++ itrh) {
      typename polygon_traits<hole_type>::iterator_type itr1 = begin_points(polygon), itr1_end = end_points(polygon);
      if(!point_sequence_is_45(itr1, itr1_end)) return false;
    }
    return true;
  }


  template <typename distance_type, typename iterator_type>
  distance_type point_sequence_distance(iterator_type itr, iterator_type itr_end) {
    typedef distance_type Unit;
    typedef iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    Unit return_value = Unit(0);
    point_type previous_point, first_point;
    if(itr == itr_end) return return_value;
    previous_point = first_point = *itr;
    ++itr;
    for( ; itr != itr_end; ++itr) {
      point_type current_point = *itr;
      return_value += (Unit)euclidean_distance(current_point, previous_point);
      previous_point = current_point;
    }
    return_value += (Unit)euclidean_distance(previous_point, first_point);
    return return_value;
  }


  template <typename T>
  typename enable_if <typename is_polygon_with_holes_type<T>::type,
                       direction_1d>::type
  winding(const T& polygon) {
    winding_direction wd = polygon_traits<T>::winding(polygon);
    if(wd != unknown_winding) {
      return wd == clockwise_winding ? CLOCKWISE: COUNTERCLOCKWISE;
    }
    typedef typename area_type_by_domain< typename geometry_domain<typename geometry_concept<T>::type>::type,
      typename polygon_traits<T>::coordinate_type>::type area_type;
    return point_sequence_area<typename polygon_traits<T>::iterator_type, area_type>(begin_points(polygon), end_points(polygon)) < 0 ?
      COUNTERCLOCKWISE : CLOCKWISE;
  }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and< typename is_polygon_90_type<T>::type,
                      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef T polygon_type;
    typedef typename polygon_traits<polygon_type>::coordinate_type coordinate_type;
    typedef typename polygon_traits<polygon_type>::iterator_type iterator;
    typedef typename std::iterator_traits<iterator>::value_type point_type;
    coordinate_type point_x = x(point);
    coordinate_type point_y = y(point);
    bool inside = false;
    for (iterator iter = begin_points(polygon); iter != end_points(polygon);) {
      point_type curr_point = *iter;
      ++iter;
      point_type next_point = (iter == end_points(polygon)) ? *begin_points(polygon) : *iter;
      if (x(curr_point) == x(next_point)) {
        if (x(curr_point) > point_x) {
          continue;
        }
        coordinate_type min_y = (std::min)(y(curr_point), y(next_point));
        coordinate_type max_y = (std::max)(y(curr_point), y(next_point));
        if (point_y > min_y && point_y < max_y) {
          if (x(curr_point) == point_x) {
            return consider_touch;
          }
          inside ^= true;
        }
      } else {
        coordinate_type min_x = (std::min)(x(curr_point), x(next_point));
        coordinate_type max_x = (std::max)(x(curr_point), x(next_point));
        if (point_x >= min_x && point_x <= max_x) {
          if (y(curr_point) == point_y) {
            return consider_touch;
          }
        }
      }
    }
    return inside;
  }

      inline less_point() {}

      inline bool operator () (const Point& pt1, const Point& pt2) const {
        if(pt1.get(HORIZONTAL) < pt2.get(HORIZONTAL)) return true;
        if(pt1.get(HORIZONTAL) == pt2.get(HORIZONTAL)) {
          if(pt1.get(VERTICAL) < pt2.get(VERTICAL)) return true;
        }
        return false;
      }


    static inline bool between(Point pt, Point pt1, Point pt2) {
      less_point lp;
      if(lp(pt1, pt2))
        return lp(pt, pt2) && lp(pt1, pt);
      return lp(pt, pt1) && lp(pt2, pt);
    }


    template <typename area_type>
    static inline bool equal_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      return cross_1 == cross_2 && (cross_1_sign == cross_2_sign || cross_1 == 0);
    }


    static inline bool equal_slope(const Unit& x, const Unit& y,
                                   const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return equal_slope(dx1, dy1, dx2, dy2);
    }


    template <typename area_type>
    static inline bool less_slope(area_type dx1, area_type dy1, area_type dx2, area_type dy2) {
      //reflext x and y slopes to right hand side half plane
      if(dx1 < 0) {
        dy1 *= -1;
        dx1 *= -1;
      } else if(dx1 == 0) {
        //if the first slope is vertical the first cannot be less
        return false;
      }
      if(dx2 < 0) {
        dy2 *= -1;
        dx2 *= -1;
      } else if(dx2 == 0) {
        //if the second slope is vertical the first is always less unless it is also vertical, in which case they are equal
        return dx1 != 0;
      }
      typedef typename coordinate_traits<Unit>::unsigned_area_type unsigned_product_type;
      unsigned_product_type cross_1 = (unsigned_product_type)(dx2 < 0 ? -dx2 :dx2) * (unsigned_product_type)(dy1 < 0 ? -dy1 : dy1);
      unsigned_product_type cross_2 = (unsigned_product_type)(dx1 < 0 ? -dx1 :dx1) * (unsigned_product_type)(dy2 < 0 ? -dy2 : dy2);
      int dx1_sign = dx1 < 0 ? -1 : 1;
      int dx2_sign = dx2 < 0 ? -1 : 1;
      int dy1_sign = dy1 < 0 ? -1 : 1;
      int dy2_sign = dy2 < 0 ? -1 : 1;
      int cross_1_sign = dx2_sign * dy1_sign;
      int cross_2_sign = dx1_sign * dy2_sign;
      if(cross_1_sign < cross_2_sign) return true;
      if(cross_2_sign < cross_1_sign) return false;
      if(cross_1_sign == -1) return cross_2 < cross_1;
      return cross_1 < cross_2;
    }


    static inline bool less_slope(const Unit& x, const Unit& y,
                                  const Point& pt1, const Point& pt2) {
      const Point* pts[2] = {&pt1, &pt2};
      //compute y value on edge from pt_ to pts[1] at the x value of pts[0]
      typedef typename coordinate_traits<Unit>::manhattan_area_type at;
      at dy2 = (at)pts[1]->get(VERTICAL) - (at)y;
      at dy1 = (at)pts[0]->get(VERTICAL) - (at)y;
      at dx2 = (at)pts[1]->get(HORIZONTAL) - (at)x;
      at dx1 = (at)pts[0]->get(HORIZONTAL) - (at)x;
      return less_slope(dx1, dy1, dx2, dy2);
    }

    static inline int on_above_or_below(Point pt, const half_edge& he) {
      if(pt == he.first || pt == he.second) return 0;
      if(equal_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second)) return 0;
      bool less_result = less_slope(pt.get(HORIZONTAL), pt.get(VERTICAL), he.first, he.second);
      int retval = less_result ? -1 : 1;
      less_point lp;
      if(lp(he.second, he.first)) retval *= -1;
      if(!between(pt, he.first, he.second)) retval *= -1;
      return retval;
    }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and< typename is_any_mutable_polygon_with_holes_type<T>::type,
                      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename polygon_with_holes_traits<T>::iterator_holes_type holes_iterator;
    bool isInside = contains( view_as< typename polygon_from_polygon_with_holes_type<
                              typename geometry_concept<T>::type>::type>( polygon ), point, consider_touch );
    if(!isInside) return false; //no need to check holes
    holes_iterator itH = begin_holes( polygon );
    while( itH != end_holes( polygon ) ) {
      if(  contains( *itH, point, !consider_touch )  ) {
        isInside = false;
        break;
      }
      ++itH;
    }
    return isInside;
  }


  template <typename T, typename input_point_type>
  typename enable_if<
    typename gtl_and_3<
      typename is_polygon_type<T>::type,
      typename gtl_different_type<typename geometry_domain<typename geometry_concept<T>::type>::type, manhattan_domain>::type,
      typename gtl_same_type<typename geometry_concept<input_point_type>::type, point_concept>::type>::type,
    bool>::type
  contains(const T& polygon, const input_point_type& point, bool consider_touch = true) {
    typedef typename point_traits<input_point_type>::coordinate_type Unit;
    typedef point_data<Unit> Point;
    typedef std::pair<Point, Point> half_edge;
    typedef typename polygon_traits<T>::iterator_type iterator;
    iterator itr = begin_points(polygon);
    iterator itrEnd = end_points(polygon);
    half_edge he;
    if(itr == itrEnd) return false;
    assign(he.first, *itr);
    Point firstPt;
    assign(firstPt, *itr);
    ++itr;
    if(itr == itrEnd) return false;
    bool done = false;
    int above = 0;
    while(!done) {
      Point currentPt;
      if(itr == itrEnd) {
        done = true;
        currentPt = firstPt;
      } else {
        assign(currentPt, *itr);
        ++itr;
      }
      if(currentPt == he.first) {
        continue;
      } else {
        he.second = currentPt;
        if(equivalence(point, currentPt)) return consider_touch;
        Unit xmin = (std::min)(x(he.first), x(he.second));
        Unit xmax = (std::max)(x(he.first), x(he.second));
        if(x(point) >= xmin && x(point) < xmax) { //double counts if <= xmax
          Point tmppt;
          assign(tmppt, point);
          int oabedge = edge_utils<Unit>::on_above_or_below(tmppt, he);
          if(oabedge == 0) return consider_touch;
          if(oabedge == 1) ++above;
        } else if(x(point) == xmax) {
          if(x(point) == xmin) {
            Unit ymin = (std::min)(y(he.first), y(he.second));
            Unit ymax = (std::max)(y(he.first), y(he.second));
            Unit ypt = y(point);
            if(ypt <= ymax && ypt >= ymin)
              return consider_touch;
          } else {
            Point tmppt;
            assign(tmppt, point);
            if( edge_utils<Unit>::on_above_or_below(tmppt, he) == 0 ) {
              return consider_touch;
            }
          }
        }
      }
      he.first = he.second;
    }
    return above % 2 != 0; //if the point is above an odd number of edges is must be inside polygon
  }


  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_point_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  center(T1& center_point, const T2& polygon) {
    typedef typename polygon_traits<T2>::coordinate_type coordinate_type;
    rectangle_data<coordinate_type> bbox;
    extents(bbox, polygon);
    return center(center_point, bbox);
  }


  template <typename T1, typename T2>
  typename enable_if<
    typename gtl_and< typename is_mutable_rectangle_concept<typename geometry_concept<T1>::type>::type,
                      typename is_polygon_with_holes_type<T2>::type>::type,
    bool>::type
  extents(T1& bounding_box, const T2& polygon) {
    typedef typename polygon_traits<T2>::iterator_type iterator;
    bool first_iteration = true;
    iterator itr_end = end_points(polygon);
    for(iterator itr = begin_points(polygon); itr != itr_end; ++itr) {
      if(first_iteration) {
        set_points(bounding_box, *itr, *itr);
        first_iteration = false;
      } else {
        encompass(bounding_box, *itr);
      }
    }
    if(first_iteration) return false;
    return true;
  }

  template <class T2>
  polygon_90_data<T>& polygon_90_data<T>::operator=(const T2& rvalue) {
    assign(*this, rvalue);
    return *this;
  }
