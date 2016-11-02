
    template<typename Range, typename Strategy, typename OutputIterator, typename Distance>
    static inline void apply(Range const& range, OutputIterator out,
                             Distance const& max_distance, Strategy const& strategy)
    {
        if (boost::size(range) <= 2 || max_distance < 0)
        {
            std::copy(boost::begin(range), boost::end(range), out);
        }
        else
        {
            strategy.apply(range, out, max_distance);
        }
    }

    template <typename Range, typename Strategy, typename Distance>
    static inline void apply(Range const& range, Range& out,
                             Distance const& , Strategy const& )
    {
        std::copy
            (
                boost::begin(range), boost::end(range), std::back_inserter(out)
            );
    }

    template <typename Range, typename Strategy, typename Distance>
    static inline void apply(Range const& range, Range& out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        // Call do_container for a linestring / ring

        /* For a RING:
            The first/last point (the closing point of the ring) should maybe
            be excluded because it lies on a line with second/one but last.
            Here it is never excluded.

            Note also that, especially if max_distance is too large,
            the output ring might be self intersecting while the input ring is
            not, although chances are low in normal polygons

            Finally the inputring might have 3 (open) or 4 (closed) points (=correct),
                the output < 3 or 4(=wrong)
        */

        if (boost::size(range) <= int(Minimum) || max_distance < 0.0)
        {
            simplify_copy::apply(range, out, max_distance, strategy);
        }
        else
        {
            simplify_range_insert::apply
                (
                    range, std::back_inserter(out), max_distance, strategy
                );
        }
    }

    template <typename Polygon, typename Strategy, typename Distance>
    static inline void apply(Polygon const& poly_in, Polygon& poly_out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        typedef typename ring_type<Polygon>::type ring_type;

        int const Minimum = core_detail::closure::minimum_ring_size
            <
                geometry::closure<Polygon>::value
            >::value;

        // Note that if there are inner rings, and distance is too large,
        // they might intersect with the outer ring in the output,
        // while it didn't in the input.
        simplify_range<Minimum>::apply(exterior_ring(poly_in),
                                       exterior_ring(poly_out),
                                       max_distance, strategy);

        traits::resize
            <
                typename boost::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon>::type
                >::type
            >::apply(interior_rings(poly_out), num_interior_rings(poly_in));

        typename interior_return_type<Polygon const>::type rings_in
                    = interior_rings(poly_in);
        typename interior_return_type<Polygon>::type rings_out
                    = interior_rings(poly_out);
        BOOST_AUTO_TPL(it_out, boost::begin(rings_out));
        for (BOOST_AUTO_TPL(it_in,  boost::begin(rings_in));
            it_in != boost::end(rings_in);
            ++it_in, ++it_out)
        {
            simplify_range<Minimum>::apply(*it_in, *it_out, max_distance, strategy);
        }
    }

    template <typename Distance, typename Strategy>
    static inline void apply(Point const& point, Point& out,
                    Distance const& , Strategy const& )
    {
        geometry::convert(point, out);
    }

template<typename Geometry, typename Distance, typename Strategy>
inline void simplify(Geometry const& geometry, Geometry& out,
                     Distance const& max_distance, Strategy const& strategy)
{
    concept::check<Geometry>();

    BOOST_CONCEPT_ASSERT( (geometry::concept::SimplifyStrategy<Strategy>) );

    geometry::clear(out);

    dispatch::simplify<Geometry>::apply(geometry, out, max_distance, strategy);
}

template<typename Geometry, typename Distance>
inline void simplify(Geometry const& geometry, Geometry& out,
                     Distance const& max_distance)
{
    concept::check<Geometry>();

    typedef typename point_type<Geometry>::type point_type;
    typedef typename strategy::distance::services::default_strategy
            <
                segment_tag, point_type
            >::type ds_strategy_type;

    typedef strategy::simplify::douglas_peucker
        <
            point_type, ds_strategy_type
        > strategy_type;

    simplify(geometry, out, max_distance, strategy_type());
}

template<typename Geometry, typename OutputIterator, typename Distance, typename Strategy>
inline void simplify_insert(Geometry const& geometry, OutputIterator out,
                              Distance const& max_distance, Strategy const& strategy)
{
    concept::check<Geometry const>();
    BOOST_CONCEPT_ASSERT( (geometry::concept::SimplifyStrategy<Strategy>) );

    dispatch::simplify_insert<Geometry>::apply(geometry, out, max_distance, strategy);
}

template<typename Geometry, typename OutputIterator, typename Distance>
inline void simplify_insert(Geometry const& geometry, OutputIterator out,
                              Distance const& max_distance)
{
    typedef typename point_type<Geometry>::type point_type;

    // Concept: output point type = point type of input geometry
    concept::check<Geometry const>();
    concept::check<point_type>();

    typedef typename strategy::distance::services::default_strategy
        <
            segment_tag, point_type
        >::type ds_strategy_type;

    typedef strategy::simplify::douglas_peucker
        <
            point_type, ds_strategy_type
        > strategy_type;

    dispatch::simplify_insert<Geometry>::apply(geometry, out, max_distance, strategy_type());
}

    template<typename Geometry, typename Box>
    static inline void apply(Geometry const& geometry, Box& mbr)
    {
        assign_inverse(mbr);
        geometry::expand(mbr, geometry);
    }

template<typename Range, typename Box>
inline void envelope_range_additional(Range const& range, Box& mbr)
{
    typedef typename boost::range_iterator<Range const>::type iterator_type;

    for (iterator_type it = boost::begin(range);
        it != boost::end(range);
        ++it)
    {
        geometry::expand(mbr, *it);
    }
}

    template <typename Range, typename Box>
    static inline void apply(Range const& range, Box& mbr)
    {
        assign_inverse(mbr);
        envelope_range_additional(range, mbr);
    }

template<typename Geometry, typename Box>
inline void envelope(Geometry const& geometry, Box& mbr)
{
    concept::check<Geometry const>();
    concept::check<Box>();

    dispatch::envelope<Geometry>::apply(geometry, mbr);
}

template<typename Box, typename Geometry>
inline Box return_envelope(Geometry const& geometry)
{
    concept::check<Geometry const>();
    concept::check<Box>();

    Box mbr;
    dispatch::envelope<Geometry>::apply(geometry, mbr);
    return mbr;
}


    inline centroid_exception() {}


    virtual char const* what() const throw()
    {
        return "Boost.Geometry Centroid calculation exception";
    }

    template<typename Point, typename PointCentroid, typename Strategy>
    static inline void apply(Point const& point, PointCentroid& centroid,
            Strategy const&)
    {
        geometry::convert(point, centroid);
    }

    static inline void apply(Box const& box, Point& centroid)
    {
        coordinate_type const c1 = get<min_corner, Dimension>(box);
        coordinate_type const c2 = get<max_corner, Dimension>(box);
        coordinate_type m = c1 + c2;
        m /= 2.0;

        set<Dimension>(centroid, m);

        centroid_box_calculator
            <
                Box, Point,
                Dimension + 1, DimensionCount
            >::apply(box, centroid);
    }

    static inline void apply(Box const& , Point& )
    {
    }

    template<typename Box, typename Point, typename Strategy>
    static inline void apply(Box const& box, Point& centroid,
            Strategy const&)
    {
        centroid_box_calculator
            <
                Box, Point,
                0, dimension<Box>::type::value
            >::apply(box, centroid);
    }

template<typename Point, typename Range>
inline bool range_ok(Range const& range, Point& centroid)
{
    std::size_t const n = boost::size(range);
    if (n > 1)
    {
        return true;
    }
    else if (n <= 0)
    {
#if ! defined(BOOST_GEOMETRY_CENTROID_NO_THROW)
        throw centroid_exception();
#endif
        return false;
    }
    else // if (n == 1)
    {
        // Take over the first point in a "coordinate neutral way"
        geometry::convert(*boost::begin(range), centroid);
        return false;
    }
    return true;
}

    template<typename Ring, typename Strategy>
    static inline void apply(Ring const& ring,
            Strategy const& strategy, typename Strategy::state_type& state)
    {
        typedef typename closeable_view<Ring const, Closure>::type view_type;

        typedef typename boost::range_iterator<view_type const>::type iterator_type;

        view_type view(ring);
        iterator_type it = boost::begin(view);
        iterator_type end = boost::end(view);

        for (iterator_type previous = it++;
            it != end;
            ++previous, ++it)
        {
            strategy.apply(*previous, *it, state);
        }
    }

    template<typename Range, typename Point, typename Strategy>
    static inline void apply(Range const& range, Point& centroid,
            Strategy const& strategy)
    {
        if (range_ok(range, centroid))
        {
            typename Strategy::state_type state;
            centroid_range_state<Closure>::apply(range, strategy, state);
            strategy.result(state, centroid);
        }
    }

    template<typename Polygon, typename Strategy>
    static inline void apply(Polygon const& poly,
            Strategy const& strategy, typename Strategy::state_type& state)
    {
        typedef typename ring_type<Polygon>::type ring_type;
        typedef centroid_range_state<geometry::closure<ring_type>::value> per_ring;

        per_ring::apply(exterior_ring(poly), strategy, state);

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            per_ring::apply(*it, strategy, state);
        }
    }

    template<typename Polygon, typename Point, typename Strategy>
    static inline void apply(Polygon const& poly, Point& centroid,
            Strategy const& strategy)
    {
        if (range_ok(exterior_ring(poly), centroid))
        {
            typename Strategy::state_type state;
            centroid_polygon_state::apply(poly, strategy, state);
            strategy.result(state, centroid);
        }
    }

template<typename Geometry, typename Point, typename Strategy>
inline void centroid(Geometry const& geometry, Point& c,
        Strategy const& strategy)
{
    //BOOST_CONCEPT_ASSERT( (geometry::concept::CentroidStrategy<Strategy>) );

    concept::check_concepts_and_equal_dimensions<Point, Geometry const>();

    typedef typename point_type<Geometry>::type point_type;

    // Call dispatch apply method. That one returns true if centroid
    // should be taken from state.
    dispatch::centroid<Geometry>::apply(geometry, c, strategy);
}

template<typename Geometry, typename Point>
inline void centroid(Geometry const& geometry, Point& c)
{
    concept::check_concepts_and_equal_dimensions<Point, Geometry const>();

    typedef typename strategy::centroid::services::default_strategy
        <
            typename cs_tag<Geometry>::type,
            typename tag_cast
                <
                    typename tag<Geometry>::type,
                    pointlike_tag,
                    linear_tag,
                    areal_tag
                >::type,
            dimension<Geometry>::type::value,
            Point,
            Geometry
        >::type strategy_type;

    centroid(geometry, c, strategy_type());
}

template<typename Point, typename Geometry>
inline Point return_centroid(Geometry const& geometry)
{
    concept::check_concepts_and_equal_dimensions<Point, Geometry const>();

    Point c;
    centroid(geometry, c);
    return c;
}

template<typename Point, typename Geometry, typename Strategy>
inline Point return_centroid(Geometry const& geometry, Strategy const& strategy)
{
    //BOOST_CONCEPT_ASSERT( (geometry::concept::CentroidStrategy<Strategy>) );

    concept::check_concepts_and_equal_dimensions<Point, Geometry const>();

    Point c;
    centroid(geometry, c, strategy);
    return c;
}

    template <typename Ring, typename Strategy>
    static inline typename Strategy::return_type
    apply(Ring const& ring, Strategy const& strategy)
    {
        BOOST_CONCEPT_ASSERT( (geometry::concept::AreaStrategy<Strategy>) );
        assert_dimension<Ring, 2>();

        // Ignore warning (because using static method sometimes) on strategy
        boost::ignore_unused_variable_warning(strategy);

        // An open ring has at least three points,
        // A closed ring has at least four points,
        // if not, there is no (zero) area
        if (int(boost::size(ring))
                < core_detail::closure::minimum_ring_size<Closure>::value)
        {
            return typename Strategy::return_type();
        }

        typedef typename reversible_view<Ring const, Direction>::type rview_type;
        typedef typename closeable_view
            <
                rview_type const, Closure
            >::type view_type;
        typedef typename boost::range_iterator<view_type const>::type iterator_type;

        rview_type rview(ring);
        view_type view(rview);
        typename Strategy::state_type state;
        iterator_type it = boost::begin(view);
        iterator_type end = boost::end(view);

        for (iterator_type previous = it++;
            it != end;
            ++previous, ++it)
        {
            strategy.apply(*previous, *it, state);
        }

        return strategy.result(state);
    }

    template <typename Strategy>
    static inline typename Strategy::return_type apply(Geometry const& geometry,
                                                       Strategy const& strategy)
    {
        return area<Geometry>::apply(geometry, strategy);
    }

template <typename Geometry, typename Strategy>
inline typename Strategy::return_type area(
        Geometry const& geometry, Strategy const& strategy)
{
    concept::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);
    
    return dispatch::devarianted_area<Geometry>::apply(geometry, strategy);
}

    template <typename Point, typename Functor>
    static inline void apply(Point& point, Functor& f)
    {
        f(point);
    }

    template <typename Point, typename Functor>
    static inline void apply(Point& , Functor& f)
    {
        // TODO: if non-const, we should extract the points from the segment
        // and call the functor on those two points
    }

    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        // The previous implementation called the std library:
        // return (std::for_each(boost::begin(range), boost::end(range), f));
        // But that is not accepted for capturing lambda's.
        // It needs to do it like that to return the state of Functor f (f is passed by value in std::for_each).

        // So we now loop manually.

        for (typename boost::range_iterator<Range>::type it = boost::begin(range); it != boost::end(range); ++it)
        {
            f(*it);
        }
    }

    template <typename Range, typename Functor>
    static inline void apply(Range& range, Functor& f)
    {
        typedef typename add_const_if_c
            <
                is_const<Range>::value,
                typename point_type<Range>::type
            >::type point_type;

        BOOST_AUTO_TPL(it, boost::begin(range));
        BOOST_AUTO_TPL(previous, it++);
        while(it != boost::end(range))
        {
            model::referring_segment<point_type> s(*previous, *it);
            f(s);
            previous = it++;
        }
    }

    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_point::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            fe_range_per_point::apply(*it, f);
        }
    }

    template <typename Polygon, typename Functor>
    static inline void apply(Polygon& poly, Functor& f)
    {
        fe_range_per_segment::apply(exterior_ring(poly), f);

        typename interior_return_type<Polygon>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            fe_range_per_segment::apply(*it, f);
        }
    }

template<typename Geometry, typename Functor>
inline Functor for_each_point(Geometry& geometry, Functor f)
{
    concept::check<Geometry>();

    dispatch::for_each_point<Geometry>::apply(geometry, f);
    return f;
}

template<typename Geometry, typename Functor>
inline Functor for_each_segment(Geometry& geometry, Functor f)
{
    concept::check<Geometry>();

    dispatch::for_each_segment<Geometry>::apply(geometry, f);
    return f;
}

    template <typename Point1, typename Point2, typename Strategy>
    static inline bool apply(Point1 const& p1, Point2& p2,
                Strategy const& strategy)
    {
        return strategy.apply(p1, p2);
    }

    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2& b2,
                Strategy const& strategy)
    {
        typedef typename point_type<Box1>::type point_type1;
        typedef typename point_type<Box2>::type point_type2;

        point_type1 lower_left, upper_right;
        detail::assign::assign_box_2d_corner<min_corner, min_corner>(
                    b1, lower_left);
        detail::assign::assign_box_2d_corner<max_corner, max_corner>(
                    b1, upper_right);

        point_type2 p1, p2;
        if (strategy.apply(lower_left, p1) && strategy.apply(upper_right, p2))
        {
            // Create a valid box and therefore swap if necessary
            typedef typename coordinate_type<point_type2>::type coordinate_type;
            coordinate_type x1 = geometry::get<0>(p1)
                    , y1  = geometry::get<1>(p1)
                    , x2  = geometry::get<0>(p2)
                    , y2  = geometry::get<1>(p2);

            if (x1 > x2) { std::swap(x1, x2); }
            if (y1 > y2) { std::swap(y1, y2); }

            set<min_corner, 0>(b2, x1);
            set<min_corner, 1>(b2, y1);
            set<max_corner, 0>(b2, x2);
            set<max_corner, 1>(b2, y2);

            return true;
        }
        return false;
    }

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& source, Geometry2& target,
                Strategy const& strategy)
    {
        typedef typename point_type<Geometry1>::type point_type1;
        typedef typename point_type<Geometry2>::type point_type2;

        point_type1 source_point[2];
        geometry::detail::assign_point_from_index<0>(source, source_point[0]);
        geometry::detail::assign_point_from_index<1>(source, source_point[1]);

        point_type2 target_point[2];
        if (strategy.apply(source_point[0], target_point[0])
            && strategy.apply(source_point[1], target_point[1]))
        {
            geometry::detail::assign_point_to_index<0>(target_point[0], target);
            geometry::detail::assign_point_to_index<1>(target_point[1], target);
            return true;
        }
        return false;
    }



template
<
    typename PointOut,
    typename OutputIterator,
    typename Range,
    typename Strategy
>
inline bool transform_range_out(Range const& range,
    OutputIterator out, Strategy const& strategy)
{
    PointOut point_out;
    for(typename boost::range_iterator<Range const>::type
        it = boost::begin(range);
        it != boost::end(range);
        ++it)
    {
        if (! transform_point::apply(*it, point_out, strategy))
        {
            return false;
        }
        *out++ = point_out;
    }
    return true;
}

    template <typename Polygon1, typename Polygon2, typename Strategy>
    static inline bool apply(Polygon1 const& poly1, Polygon2& poly2,
                Strategy const& strategy)
    {
        typedef typename ring_type<Polygon1>::type ring1_type;
        typedef typename ring_type<Polygon2>::type ring2_type;
        typedef typename point_type<Polygon2>::type point2_type;

        geometry::clear(poly2);

        if (!transform_range_out<point2_type>(exterior_ring(poly1),
                    std::back_inserter(exterior_ring(poly2)), strategy))
        {
            return false;
        }

        // Note: here a resizeable container is assumed.
        traits::resize
            <
                typename boost::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(interior_rings(poly2), num_interior_rings(poly1));

        typename interior_return_type<Polygon1 const>::type rings1
                    = interior_rings(poly1);
        typename interior_return_type<Polygon2>::type rings2
                    = interior_rings(poly2);
        BOOST_AUTO_TPL(it1, boost::begin(rings1));
        BOOST_AUTO_TPL(it2, boost::begin(rings2));
        for ( ; it1 != boost::end(interior_rings(poly1)); ++it1, ++it2)
        {
            if (!transform_range_out<point2_type>(*it1,
                std::back_inserter(*it2), strategy))
            {
                return false;
            }
        }

        return true;
    }

    template <typename Range1, typename Range2, typename Strategy>
    static inline bool apply(Range1 const& range1,
            Range2& range2, Strategy const& strategy)
    {
        typedef typename point_type<Range2>::type point_type;

        // Should NOT be done here!
        // geometry::clear(range2);
        return transform_range_out<point_type>(range1,
                std::back_inserter(range2), strategy);
    }

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2,
            Strategy const& strategy)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2>();

    typedef dispatch::transform<Geometry1, Geometry2> transform_type;

    return transform_type::apply(geometry1, geometry2, strategy);
}

template <typename Geometry1, typename Geometry2>
inline bool transform(Geometry1 const& geometry1, Geometry2& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2>();

    typename detail::transform::select_strategy<Geometry1, Geometry2>::type strategy;
    return transform(geometry1, geometry2, strategy);
}

    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        ::boost::ignore_unused_variable_warning(strategy);
        return strategy.apply(point, box);
    }

template<typename Geometry1, typename Geometry2>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    assert_dimension_equal<Geometry1, Geometry2>();

    typedef typename point_type<Geometry1>::type point_type1;
    typedef typename point_type<Geometry2>::type point_type2;

    typedef typename strategy::covered_by::services::default_strategy
        <
            typename tag<Geometry1>::type,
            typename tag<Geometry2>::type,
            typename tag<Geometry1>::type,
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            typename tag_cast
                <
                    typename cs_tag<point_type1>::type, spherical_tag
                >::type,
            typename tag_cast
                <
                    typename cs_tag<point_type2>::type, spherical_tag
                >::type,
            Geometry1,
            Geometry2
        >::type strategy_type;

    return dispatch::covered_by
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy_type());
}

template<typename Geometry1, typename Geometry2, typename Strategy>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2,
        Strategy const& strategy)
{
    concept::within::check
        <
            typename tag<Geometry1>::type, 
            typename tag<Geometry2>::type, 
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            Strategy
        >();
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    assert_dimension_equal<Geometry1, Geometry2>();

    return dispatch::covered_by
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}

    static inline std::size_t apply(Geometry const&)
    {
        return 1;
    }

template <typename Geometry>
inline std::size_t num_geometries(Geometry const& geometry)
{
    concept::check<Geometry const>();

    return dispatch::num_geometries<Geometry>::apply(geometry);
}

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
            Geometry2 const& g2, OutputIterator out,
            Strategy const& strategy)
    {
        return union_insert
            <
                Geometry2, Geometry1, GeometryOut
            >::apply(g2, g1, out, strategy);
    }


template
<
    typename GeometryOut,
    typename Geometry1, typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    return dispatch::union_insert
           <
               Geometry1, Geometry2, GeometryOut
           >::apply(geometry1, geometry2, out, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator union_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();

    return detail::union_::insert<GeometryOut>(geometry1, geometry2, out, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator union_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();

    typedef strategy_intersection
        <
            typename cs_tag<GeometryOut>::type,
            Geometry1,
            Geometry2,
            typename geometry::point_type<GeometryOut>::type
        > strategy;

    return union_insert<GeometryOut>(geometry1, geometry2, out, strategy());
}

template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void union_(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            Collection& output_collection)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    typedef typename boost::range_value<Collection>::type geometry_out;
    concept::check<geometry_out>();

    detail::union_::union_insert<geometry_out>(geometry1, geometry2,
                std::back_inserter(output_collection));
}

template <typename Geometry, typename Range>
inline Geometry make_points(Range const& range)
{
    concept::check<Geometry>();

    Geometry geometry;
    geometry::append(geometry, range);
    return geometry;
}

template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2)
{
    concept::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
    return geometry;
}

template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3)
{
    concept::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
    return geometry;
}


template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concept::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
    return geometry;
}

template <typename Geometry>
inline Geometry make_inverse()
{
    concept::check<Geometry>();

    Geometry geometry;
    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

template <typename Geometry>
inline Geometry make_zero()
{
    concept::check<Geometry>();

    Geometry geometry;
    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

    template <typename Range, typename ComparePolicy>
    static inline void apply(Range& range, ComparePolicy const& policy)
    {
        typename boost::range_iterator<Range>::type it
            = std::unique
                (
                    boost::begin(range),
                    boost::end(range),
                    policy
                );

        traits::resize<Range>::apply(range, it - boost::begin(range));
    }

    template <typename Polygon, typename ComparePolicy>
    static inline void apply(Polygon& polygon, ComparePolicy const& policy)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        range_unique::apply(exterior_ring(polygon), policy);

        typename interior_return_type<Polygon>::type rings
                    = interior_rings(polygon);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            range_unique::apply(*it, policy);
        }
    }

template <typename Geometry>
inline void unique(Geometry& geometry)
{
    concept::check<Geometry>();

    // Default strategy is the default point-comparison policy
    typedef geometry::equal_to
        <
            typename geometry::point_type<Geometry>::type
        > policy;


    dispatch::unique<Geometry>::apply(geometry, policy());
}

    template <typename Geometry, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry const& geometry,
            OutputIterator out, Strategy const& strategy)
    {
        typename Strategy::state_type state;

        strategy.apply(geometry, state);
        strategy.result(state, out, Order == clockwise);
        return out;
    }

    template <typename Geometry, typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry, OutputGeometry& out,
            Strategy const& strategy)
    {
        hull_insert
            <
                geometry::point_order<OutputGeometry>::value
            >::apply(geometry,
                std::back_inserter(
                    // Handle linestring, ring and polygon the same:
                    detail::as_range
                        <
                            typename range_type<OutputGeometry>::type
                        >(out)), strategy);
    }

    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Box const& box, OutputGeometry& out,
            Strategy const& )
    {
        static bool const Close
            = geometry::closure<OutputGeometry>::value == closed;
        static bool const Reverse
            = geometry::point_order<OutputGeometry>::value == counterclockwise;

        // A hull for boxes is trivial. Any strategy is (currently) skipped.
        boost::array<typename point_type<Box>::type, 4> range;
        geometry::detail::assign_box_corners_oriented<Reverse>(box, range);
        geometry::append(out, range);
        if (Close)
        {
            geometry::append(out, *boost::begin(range));
        }
    }



template<typename Geometry, typename OutputGeometry, typename Strategy>
inline void convex_hull(Geometry const& geometry,
            OutputGeometry& out, Strategy const& strategy)
{
    concept::check_concepts_and_equal_dimensions
        <
            const Geometry,
            OutputGeometry
        >();

    BOOST_CONCEPT_ASSERT( (geometry::concept::ConvexHullStrategy<Strategy>) );

    if (geometry::num_points(geometry) == 0)
    {
        // Leave output empty
        return;
    }

    dispatch::convex_hull<Geometry>::apply(geometry, out, strategy);
}

template<typename Geometry, typename OutputGeometry>
inline void convex_hull(Geometry const& geometry,
            OutputGeometry& hull)
{
    concept::check_concepts_and_equal_dimensions
        <
            const Geometry,
            OutputGeometry
        >();

    typedef typename detail::convex_hull::default_strategy<Geometry>::type strategy_type;

    convex_hull(geometry, hull, strategy_type());
}



template<typename Geometry, typename OutputIterator, typename Strategy>
inline OutputIterator convex_hull_insert(Geometry const& geometry,
            OutputIterator out, Strategy const& strategy)
{
    // Concept: output point type = point type of input geometry
    concept::check<Geometry const>();
    concept::check<typename point_type<Geometry>::type>();

    BOOST_CONCEPT_ASSERT( (geometry::concept::ConvexHullStrategy<Strategy>) );

    return dispatch::convex_hull_insert
        <
            geometry::point_order<Geometry>::value
        >::apply(geometry, out, strategy);
}

template<typename Geometry, typename OutputIterator>
inline OutputIterator convex_hull_insert(Geometry const& geometry,
            OutputIterator out)
{
    // Concept: output point type = point type of input geometry
    concept::check<Geometry const>();
    concept::check<typename point_type<Geometry>::type>();

    typedef typename detail::convex_hull::default_strategy<Geometry>::type strategy_type;

    return convex_hull_insert(geometry, out, strategy_type());
}

    static inline void apply(Geometry& geometry)
    {
        traits::clear<Geometry>::apply(geometry);
    }

    static inline void apply(Polygon& polygon)
    {
        traits::clear
            <
                typename boost::remove_reference
                    <
                        typename traits::interior_mutable_type<Polygon>::type
                    >::type
            >::apply(interior_rings(polygon));
        traits::clear
            <
                typename boost::remove_reference
                    <
                        typename traits::ring_mutable_type<Polygon>::type
                    >::type
            >::apply(exterior_ring(polygon));
    }

    static inline void apply(Geometry& )
    {
    }

    static inline void apply(Geometry& geometry)
    {
        clear<Geometry>::apply(geometry);
    }

template <typename Geometry>
inline void clear(Geometry& geometry)
{
    concept::check<Geometry>();

    dispatch::devarianted_clear<Geometry>::apply(geometry);
}


    static inline void apply(BoxIn const& box_in, T const& distance, BoxOut& box_out)
    {
        coordinate_type d = distance;
        set<C, D>(box_out, get<C, D>(box_in) + d);
        box_loop<BoxIn, BoxOut, T, C, D + 1, N>::apply(box_in, distance, box_out);
    }

    static inline void apply(BoxIn const&, T const&, BoxOut&) {}

template<typename BoxIn, typename BoxOut, typename T>
inline void buffer_box(BoxIn const& box_in, T const& distance, BoxOut& box_out)
{
    assert_dimension_equal<BoxIn, BoxOut>();

    static const std::size_t N = dimension<BoxIn>::value;

    box_loop<BoxIn, BoxOut, T, min_corner, 0, N>::apply(box_in, -distance, box_out);
    box_loop<BoxIn, BoxOut, T, max_corner, 0, N>::apply(box_in, distance, box_out);
}

    template <typename Distance>
    static inline void apply(BoxIn const& box_in, Distance const& distance,
                Distance const& , BoxIn& box_out)
    {
        detail::buffer::buffer_box(box_in, distance, box_out);
    }

template <typename Input, typename Output, typename Distance>
inline void buffer(Input const& geometry_in, Output& geometry_out,
            Distance const& distance, Distance const& chord_length = -1)
{
    concept::check<Input const>();
    concept::check<Output>();

    dispatch::buffer
        <
            Input,
            Output
        >::apply(geometry_in, distance, chord_length, geometry_out);
}

template <typename Output, typename Input, typename Distance>
Output return_buffer(Input const& geometry, Distance const& distance, Distance const& chord_length = -1)
{
    concept::check<Input const>();
    concept::check<Output>();

    Output geometry_out;

    dispatch::buffer
        <
            Input,
            Output
        >::apply(geometry, distance, chord_length, geometry_out);

    return geometry_out;
}


template <typename Turn>
inline bool ok_for_touch(Turn const& turn)
{
    return turn.both(detail::overlay::operation_union)
        || turn.both(detail::overlay::operation_blocked)
        || turn.combination(detail::overlay::operation_union, detail::overlay::operation_blocked)
        ;
}


template <typename Turns>
inline bool has_only_turns(Turns const& turns)
{
    bool has_touch = false;
    typedef typename boost::range_iterator<Turns const>::type iterator_type;
    for (iterator_type it = boost::begin(turns); it != boost::end(turns); ++it)
    {
        if (it->has(detail::overlay::operation_intersection))
        {
            return false;
        }

        switch(it->method)
        {
            case detail::overlay::method_crosses: 
                return false;
            case detail::overlay::method_equal: 
                // Segment spatially equal means: at the right side
                // the polygon internally overlaps. So return false.
                return false;
            case detail::overlay::method_touch: 
            case detail::overlay::method_touch_interior: 
            case detail::overlay::method_collinear: 
                if (ok_for_touch(*it))
                {
                    has_touch = true;
                }
                else
                {
                    return false;
                }
                break;
            case detail::overlay::method_none :
            case detail::overlay::method_disjoint :
            case detail::overlay::method_error :
                break;
        }
    }
    return has_touch;
}

template <typename Geometry>
inline bool touches(Geometry const& geometry)
{
    concept::check<Geometry const>();

    typedef detail::overlay::turn_info
        <
            typename geometry::point_type<Geometry>::type
        > turn_info;

    typedef detail::overlay::get_turn_info
        <
            typename point_type<Geometry>::type,
            typename point_type<Geometry>::type,
            turn_info,
            detail::overlay::assign_null_policy
        > policy_type;

    std::deque<turn_info> turns;
    detail::self_get_turn_points::no_interrupt_policy policy;
    detail::self_get_turn_points::get_turns
            <
                Geometry,
                std::deque<turn_info>,
                policy_type,
                detail::self_get_turn_points::no_interrupt_policy
            >::apply(geometry, turns, policy);

    return detail::touches::has_only_turns(turns);
}

template <typename Geometry1, typename Geometry2>
inline bool touches(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();


    typedef detail::overlay::turn_info
        <
            typename geometry::point_type<Geometry1>::type
        > turn_info;

    typedef detail::overlay::get_turn_info
        <
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type,
            turn_info,
            detail::overlay::assign_null_policy
        > policy_type;

    std::deque<turn_info> turns;
    detail::get_turns::no_interrupt_policy policy;
    boost::geometry::get_turns
            <
                false, false,
                detail::overlay::assign_null_policy
            >(geometry1, geometry2, turns, policy);

    return detail::touches::has_only_turns(turns)
        && ! geometry::detail::disjoint::rings_containing(geometry1, geometry2)
        && ! geometry::detail::disjoint::rings_containing(geometry2, geometry1)
        ;
}

template <typename Geometry, typename Range>
inline void assign_points(Geometry& geometry, Range const& range)
{
    concept::check<Geometry>();

    clear(geometry);
    geometry::append(geometry, range, -1, 0);
}

template <typename Geometry>
inline void assign_inverse(Geometry& geometry)
{
    concept::check<Geometry>();

    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

template <typename Geometry>
inline void assign_zero(Geometry& geometry)
{
    concept::check<Geometry>();

    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

template <typename Geometry1, typename Geometry2>
inline void assign(Geometry1& geometry1, Geometry2 const& geometry2)
{
    concept::check_concepts_and_equal_dimensions<Geometry1, Geometry2 const>();

    bool const same_point_order = 
            point_order<Geometry1>::value == point_order<Geometry2>::value;
    bool const same_closure = 
            closure<Geometry1>::value == closure<Geometry2>::value;

    BOOST_MPL_ASSERT_MSG
        (
            same_point_order, ASSIGN_IS_NOT_SUPPORTED_FOR_DIFFERENT_POINT_ORDER
            , (types<Geometry1, Geometry2>)
        );
    BOOST_MPL_ASSERT_MSG
        (
            same_closure, ASSIGN_IS_NOT_SUPPORTED_FOR_DIFFERENT_CLOSURE
            , (types<Geometry1, Geometry2>)
        );

    dispatch::convert<Geometry2, Geometry1>::apply(geometry2, geometry1);
}

    template <typename Box, typename Point>
    static inline void apply(Box& box, Point const& source)
    {
        typedef typename strategy::compare::detail::select_strategy
            <
                StrategyLess, 1, Point, Dimension
            >::type less_type;

        typedef typename strategy::compare::detail::select_strategy
            <
                StrategyGreater, -1, Point, Dimension
            >::type greater_type;

        typedef typename select_coordinate_type<Point, Box>::type coordinate_type;

        less_type less;
        greater_type greater;

        coordinate_type const coord = get<Dimension>(source);

        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        point_loop
            <
                StrategyLess, StrategyGreater,
                Dimension + 1, DimensionCount
            >::apply(box, source);
    }

    template <typename Box, typename Point>
    static inline void apply(Box&, Point const&) {}

    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& source)
    {
        typedef typename strategy::compare::detail::select_strategy
            <
                StrategyLess, 1, Box, Dimension
            >::type less_type;

        typedef typename strategy::compare::detail::select_strategy
            <
                StrategyGreater, -1, Box, Dimension
            >::type greater_type;

        typedef typename select_coordinate_type
                <
                    Box,
                    Geometry
                >::type coordinate_type;

        less_type less;
        greater_type greater;

        coordinate_type const coord = get<Index, Dimension>(source);

        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        indexed_loop
            <
                StrategyLess, StrategyGreater,
                Index, Dimension + 1, DimensionCount
            >::apply(box, source);
    }

    template <typename Box, typename Geometry>
    static inline void apply(Box&, Geometry const&) {}

    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& geometry)
    {
        indexed_loop
            <
                StrategyLess, StrategyGreater,
                0, 0, dimension<Geometry>::type::value
            >::apply(box, geometry);

        indexed_loop
            <
                StrategyLess, StrategyGreater,
                1, 0, dimension<Geometry>::type::value
            >::apply(box, geometry);
    }

template <typename Box, typename Geometry>
inline void expand(Box& box, Geometry const& geometry)
{
    concept::check_concepts_and_equal_dimensions<Box, Geometry const>();

    dispatch::expand<Box, Geometry>::apply(box, geometry);
}

    template <typename Range>
    static inline void apply(Range& range)
    {
        std::reverse(boost::begin(range), boost::end(range));
    }

    template <typename Polygon>
    static inline void apply(Polygon& polygon)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        range_reverse::apply(exterior_ring(polygon));

        typename interior_return_type<Polygon>::type rings
                    = interior_rings(polygon);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            range_reverse::apply(*it);
        }
    }

template <typename Geometry>
inline void reverse(Geometry& geometry)
{
    concept::check<Geometry>();

    dispatch::reverse<Geometry>::apply(geometry);
}


    static inline return_type apply(Point const& point, Range const& range,
            PPStrategy const& pp_strategy, PSStrategy const& ps_strategy)
    {
        return_type const zero = return_type(0);

        if (boost::size(range) == 0)
        {
            return zero;
        }

        typedef typename closeable_view<Range const, Closure>::type view_type;

        view_type view(range);

        // line of one point: return point distance
        typedef typename boost::range_iterator<view_type const>::type iterator_type;
        iterator_type it = boost::begin(view);
        iterator_type prev = it++;
        if (it == boost::end(view))
        {
            return pp_strategy.apply(point, *boost::begin(view));
        }

        // Create comparable (more efficient) strategy
        typedef typename strategy::distance::services::comparable_type<PSStrategy>::type eps_strategy_type;
        eps_strategy_type eps_strategy = strategy::distance::services::get_comparable<PSStrategy>::apply(ps_strategy);

        // start with first segment distance
        return_type d = eps_strategy.apply(point, *prev, *it);
        return_type rd = ps_strategy.apply(point, *prev, *it);

        // check if other segments are closer
        for (++prev, ++it; it != boost::end(view); ++prev, ++it)
        {
            return_type const ds = eps_strategy.apply(point, *prev, *it);
            if (geometry::math::equals(ds, zero))
            {
                return ds;
            }
            else if (ds < d)
            {
                d = ds;
                rd = ps_strategy.apply(point, *prev, *it);
            }
        }

        return rd;
    }


    static inline distance_containment apply(Point const& point,
                Ring const& ring,
                PPStrategy const& pp_strategy, PSStrategy const& ps_strategy)
    {
        return distance_containment
            (
                point_to_range
                    <
                        Point,
                        Ring,
                        Closure,
                        PPStrategy,
                        PSStrategy
                    >::apply(point, ring, pp_strategy, ps_strategy),
                geometry::within(point, ring)
            );
    }


    static inline distance_containment apply(Point const& point,
                Polygon const& polygon,
                PPStrategy const& pp_strategy, PSStrategy const& ps_strategy)
    {
        // Check distance to all rings
        typedef point_to_ring
            <
                Point,
                typename ring_type<Polygon>::type,
                Closure,
                PPStrategy,
                PSStrategy
            > per_ring;

        distance_containment dc = per_ring::apply(point,
                        exterior_ring(polygon), pp_strategy, ps_strategy);

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(polygon);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            distance_containment dcr = per_ring::apply(point,
                            *it, pp_strategy, ps_strategy);
            if (dcr.first < dc.first)
            {
                dc.first = dcr.first;
            }
            // If it was inside, and also inside inner ring,
            // turn off the inside-flag, it is outside the polygon
            if (dc.second && dcr.second)
            {
                dc.second = false;
            }
        }
        return dc;
    }


    static inline int apply(Point const& point, Ring const& ring,
            Strategy const& strategy)
    {
        boost::ignore_unused_variable_warning(strategy);
        if (int(boost::size(ring))
                < core_detail::closure::minimum_ring_size<Closure>::value)
        {
            return -1;
        }

        typedef typename reversible_view<Ring const, Direction>::type rev_view_type;
        typedef typename closeable_view
            <
                rev_view_type const, Closure
            >::type cl_view_type;
        typedef typename boost::range_iterator<cl_view_type const>::type iterator_type;

        rev_view_type rev_view(ring);
        cl_view_type view(rev_view);
        typename Strategy::state_type state;
        iterator_type it = boost::begin(view);
        iterator_type end = boost::end(view);

        bool stop = false;
        for (iterator_type previous = it++;
            it != end && ! stop;
            ++previous, ++it)
        {
            if (! strategy.apply(point, *previous, *it, state))
            {
                stop = true;
            }
        }

        return strategy.result(state);
    }


    static inline int apply(Point const& point, Polygon const& poly,
            Strategy const& strategy)
    {
        int const code = point_in_ring
            <
                Point,
                typename ring_type<Polygon>::type,
                Direction,
                Closure,
                Strategy
            >::apply(point, exterior_ring(poly), strategy);

        if (code == 1)
        {
            typename interior_return_type<Polygon const>::type rings
                        = interior_rings(poly);
            for (BOOST_AUTO_TPL(it, boost::begin(rings));
                it != boost::end(rings);
                ++it)
            {
                int const interior_code = point_in_ring
                    <
                        Point,
                        typename ring_type<Polygon>::type,
                        Direction,
                        Closure,
                        Strategy
                    >::apply(point, *it, strategy);

                if (interior_code != -1)
                {
                    // If 0, return 0 (touch)
                    // If 1 (inside hole) return -1 (outside polygon)
                    // If -1 (outside hole) check other holes if any
                    return -interior_code;
                }
            }
        }
        return code;
    }

    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        boost::ignore_unused_variable_warning(strategy);
        return strategy.apply(point, box);
    }

template<typename Geometry1, typename Geometry2>
inline bool within(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    assert_dimension_equal<Geometry1, Geometry2>();

    typedef typename point_type<Geometry1>::type point_type1;
    typedef typename point_type<Geometry2>::type point_type2;

    typedef typename strategy::within::services::default_strategy
        <
            typename tag<Geometry1>::type,
            typename tag<Geometry2>::type,
            typename tag<Geometry1>::type,
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            typename tag_cast
                <
                    typename cs_tag<point_type1>::type, spherical_tag
                >::type,
            typename tag_cast
                <
                    typename cs_tag<point_type2>::type, spherical_tag
                >::type,
            Geometry1,
            Geometry2
        >::type strategy_type;

    return dispatch::within
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy_type());
}

template<typename Geometry1, typename Geometry2, typename Strategy>
inline bool within(Geometry1 const& geometry1, Geometry2 const& geometry2,
        Strategy const& strategy)
{
    concept::within::check
        <
            typename tag<Geometry1>::type, 
            typename tag<Geometry2>::type, 
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            Strategy
        >();
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    assert_dimension_equal<Geometry1, Geometry2>();

    return dispatch::within
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}

template <typename Geometry>
inline bool intersects(Geometry const& geometry)
{
    concept::check<Geometry const>();


    typedef detail::overlay::turn_info
        <
            typename geometry::point_type<Geometry>::type
        > turn_info;
    std::deque<turn_info> turns;

    typedef typename strategy_intersection
        <
            typename cs_tag<Geometry>::type,
            Geometry,
            Geometry,
            typename geometry::point_type<Geometry>::type
        >::segment_intersection_strategy_type segment_intersection_strategy_type;

    typedef detail::overlay::get_turn_info
        <
            typename point_type<Geometry>::type,
            typename point_type<Geometry>::type,
            turn_info,
            detail::overlay::assign_null_policy
        > TurnPolicy;

    detail::disjoint::disjoint_interrupt_policy policy;
    detail::self_get_turn_points::get_turns
            <
                Geometry,
                std::deque<turn_info>,
                TurnPolicy,
                detail::disjoint::disjoint_interrupt_policy
            >::apply(geometry, turns, policy);
    return policy.has_intersections;
}

template <typename Geometry1, typename Geometry2>
inline bool intersects(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    return ! geometry::disjoint(geometry1, geometry2);
}

    template
    <
        typename Box1, typename Box2, typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const& box1,
            Box2 const& box2, BoxOut& box_out,
            Strategy const& strategy)
    {
        typedef typename coordinate_type<BoxOut>::type ct;

        ct min1 = get<min_corner, Dimension>(box1);
        ct min2 = get<min_corner, Dimension>(box2);
        ct max1 = get<max_corner, Dimension>(box1);
        ct max2 = get<max_corner, Dimension>(box2);

        if (max1 < min2 || max2 < min1)
        {
            return false;
        }
        // Set dimensions of output coordinate
        set<min_corner, Dimension>(box_out, min1 < min2 ? min2 : min1);
        set<max_corner, Dimension>(box_out, max1 > max2 ? max2 : max1);

        return intersection_box_box<Dimension + 1, DimensionCount>
               ::apply(box1, box2, box_out, strategy);
    }

    template
    <
        typename Box1, typename Box2, typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const&, Box2 const&, BoxOut&, Strategy const&)
    {
        return true;
    }

    template <typename GeometryOut, typename Strategy>
    static inline bool apply(
        Geometry1 const& g1,
        Geometry2 const& g2,
        GeometryOut& out,
        Strategy const& strategy)
    {
        return intersection<
                   Geometry2, Geometry1,
                   Tag2, Tag1,
                   false
               >::apply(g2, g1, out, strategy);
    }

template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut
>
inline bool intersection(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            GeometryOut& geometry_out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    typedef strategy_intersection
        <
            typename cs_tag<Geometry1>::type,
            Geometry1,
            Geometry2,
            typename geometry::point_type<Geometry1>::type
        > strategy;


    return dispatch::intersection<
               Geometry1,
               Geometry2
           >::apply(geometry1, geometry2, geometry_out, strategy());
}

    static inline void apply(Geometry& , Point const& ,
                int = 0, int = 0)
    {
    }

    static inline void apply(Geometry& geometry, Point const& point,
                int = 0, int = 0)
    {
        typename geometry::point_type<Geometry>::type copy;
        geometry::detail::conversion::convert_point_to_point(point, copy);
        traits::push_back<Geometry>::apply(geometry, copy);
    }


    static inline void apply(Geometry& geometry, Range const& range,
                int = 0, int = 0)
    {
        for (typename boost::range_iterator<Range const>::type
            it = boost::begin(range);
             it != boost::end(range);
             ++it)
        {
            append_point<Geometry, point_type>::apply(geometry, *it);
        }
    }


    static inline void apply(Polygon& polygon, Point const& point,
                int ring_index, int = 0)
    {
        if (ring_index == -1)
        {
            append_point<ring_type, Point>::apply(
                        exterior_ring(polygon), point);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            append_point<ring_type, Point>::apply(
                        interior_rings(polygon)[ring_index], point);
        }
    }


    static inline void apply(Polygon& polygon, Range const& range,
                int ring_index, int )
    {
        if (ring_index == -1)
        {
            append_range<ring_type, Range>::apply(
                        exterior_ring(polygon), range);
        }
        else if (ring_index < int(num_interior_rings(polygon)))
        {
            append_range<ring_type, Range>::apply(
                        interior_rings(polygon)[ring_index], range);
        }
    }

    template <typename RangeOrPoint>
    static inline void apply(Geometry& geometry,
                             RangeOrPoint const& range_or_point,
                             int ring_index,
                             int multi_index)
    {
        concept::check<Geometry>();
        append<Geometry, RangeOrPoint>::apply(geometry,
                                              range_or_point,
                                              ring_index,
                                              multi_index);
    }

template <typename Geometry, typename RangeOrPoint>
inline void append(Geometry& geometry, RangeOrPoint const& range_or_point,
                   int ring_index = -1, int multi_index = 0)
{
    dispatch::devarianted_append<Geometry>
            ::apply(geometry, range_or_point, ring_index, multi_index);
}

    static inline std::size_t apply(Polygon const& polygon)
    {
        return boost::size(geometry::interior_rings(polygon));
    }

template <typename Geometry>
inline std::size_t num_interior_rings(Geometry const& geometry)
{
    return dispatch::num_interior_rings<Geometry>::apply(geometry);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2, OutputIterator out,
            Strategy const& strategy)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();
    
    return geometry::dispatch::intersection_insert
        <
            Geometry1, Geometry2,
            GeometryOut,
            overlay_difference,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
        >::apply(geometry1, geometry2, out, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2, OutputIterator out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();

    typedef strategy_intersection
        <
            typename cs_tag<GeometryOut>::type,
            Geometry1,
            Geometry2,
            typename geometry::point_type<GeometryOut>::type
        > strategy;

    return difference_insert<GeometryOut>(geometry1, geometry2,
            out, strategy());
}

template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void difference(Geometry1 const& geometry1,
            Geometry2 const& geometry2, Collection& output_collection)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    typedef typename boost::range_value<Collection>::type geometry_out;
    concept::check<geometry_out>();

    detail::difference::difference_insert<geometry_out>(
            geometry1, geometry2,
            std::back_inserter(output_collection));
}


    template <typename Strategy>
    static inline return_type apply(
            Range const& range, Strategy const& strategy)
    {
        boost::ignore_unused_variable_warning(strategy);
        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_iterator
            <
                view_type const
            >::type iterator_type;

        return_type sum = return_type();
        view_type view(range);
        iterator_type it = boost::begin(view), end = boost::end(view);
        if(it != end)
        {
            for(iterator_type previous = it++;
                    it != end;
                    ++previous, ++it)
            {
                // Add point-point distance using the return type belonging
                // to strategy
                sum += strategy.apply(*previous, *it);
            }
        }

        return sum;
    }


    template <typename Strategy>
    static inline result_type apply(Geometry const& geometry,
                                    Strategy const& strategy)
    {
        return length<Geometry>::apply(geometry, strategy);
    }

template<typename Geometry>
inline typename dispatch::devarianted_length<Geometry>::result_type
length(Geometry const& geometry)
{
    concept::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    typedef typename strategy::distance::services::default_strategy
        <
            point_tag, typename point_type<Geometry>::type
        >::type strategy_type;

    return dispatch::devarianted_length<Geometry>::apply(geometry, strategy_type());
}

template<typename Geometry, typename Strategy>
inline typename dispatch::devarianted_length<Geometry>::result_type
length(Geometry const& geometry, Strategy const& strategy)
{
    concept::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);
    
    return dispatch::devarianted_length<Geometry>::apply(geometry, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator sym_difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2, OutputIterator out,
            Strategy const& strategy)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();

    out = geometry::dispatch::intersection_insert
        <
            Geometry1, Geometry2,
            GeometryOut,
            overlay_difference,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
        >::apply(geometry1, geometry2, out, strategy);
    out = geometry::dispatch::intersection_insert
        <
            Geometry2, Geometry1,
            GeometryOut,
            overlay_difference,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value, true>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value
        >::apply(geometry2, geometry1, out, strategy);
    return out;
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator sym_difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2, OutputIterator out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();
    concept::check<GeometryOut>();

    typedef strategy_intersection
        <
            typename cs_tag<GeometryOut>::type,
            Geometry1,
            Geometry2,
            typename geometry::point_type<GeometryOut>::type
        > strategy_type;

    return sym_difference_insert<GeometryOut>(geometry1, geometry2, out, strategy_type());
}

template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void sym_difference(Geometry1 const& geometry1,
            Geometry2 const& geometry2, Collection& output_collection)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    typedef typename boost::range_value<Collection>::type geometry_out;
    concept::check<geometry_out>();

    detail::sym_difference::sym_difference_insert<geometry_out>(
            geometry1, geometry2,
            std::back_inserter(output_collection));
}


    inline check_each_ring_for_within(Geometry const& g)
        : has_within(false)
        , m_geometry(g)
    {}


    template <typename Range>
    inline void apply(Range const& range)
    {
        typename geometry::point_type<Range>::type p;
        geometry::point_on_border(p, range);
        if (geometry::within(p, m_geometry))
        {
            has_within = true;
        }
    }


template <typename FirstGeometry, typename SecondGeometry>
inline bool rings_containing(FirstGeometry const& geometry1,
                SecondGeometry const& geometry2)
{
    check_each_ring_for_within<FirstGeometry> checker(geometry1);
    geometry::detail::for_each_range(geometry2, checker);
    return checker.has_within;
}

    template 
    <
        typename Info,
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(Info& , Point1 const& , Point2 const&,
                IntersectionInfo const&, DirInfo const&)
    {}

    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;

        typedef overlay::turn_info<point_type> turn_info;
        std::deque<turn_info> turns;

        // Specify two policies:
        // 1) Stop at any intersection
        // 2) In assignment, include also degenerate points (which are normally skipped)
        disjoint_interrupt_policy policy;
        geometry::get_turns
            <
                false, false, 
                assign_disjoint_policy
            >(geometry1, geometry2, turns, policy);
        if (policy.has_intersections)
        {
            return false;
        }

        return true;
    }

    static inline bool apply(Segment1 const& segment1, Segment2 const& segment2)
    {
        typedef typename point_type<Segment1>::type point_type;

        segment_intersection_points<point_type> is
            = strategy::intersection::relate_cartesian_segments
            <
                policies::relate::segments_intersection_points
                    <
                        Segment1,
                        Segment2,
                        segment_intersection_points<point_type>
                    >
            >::apply(segment1, segment2);

        return is.count == 0;
    }

    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        if (! disjoint_linear<Geometry1, Geometry2>::apply(geometry1, geometry2))
        {
            return false;
        }

        // If there is no intersection of segments, they might located
        // inside each other
        if (rings_containing(geometry1, geometry2)
            || rings_containing(geometry2, geometry1))
        {
            return false;
        }

        return true;
    }

    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        return disjoint
            <
                Geometry2, Geometry1,
                DimensionCount,
                Tag2, Tag1
            >::apply(g2, g1);
    }

template <typename Geometry1, typename Geometry2>
inline bool disjoint(Geometry1 const& geometry1,
            Geometry2 const& geometry2)
{
    concept::check_concepts_and_equal_dimensions
        <
            Geometry1 const,
            Geometry2 const
        >();

    return dispatch::disjoint<Geometry1, Geometry2>::apply(geometry1, geometry2);
}

    static inline void apply(Point const& point, Box& box)
    {
        typedef typename coordinate_type<Box>::type coordinate_type;

        set<Index, Dimension>(box,
                boost::numeric_cast<coordinate_type>(get<Dimension>(point)));
        point_to_box
            <
                Point, Box,
                Index, Dimension + 1, DimensionCount
            >::apply(point, box);
    }

    static inline void apply(Point const& , Box& )
    {}

    static inline void apply(Box const& box, Range& range)
    {
        traits::resize<Range>::apply(range, Close ? 5 : 4);
        assign_box_corners_oriented<Reverse>(box, range);
        if (Close)
        {
            range[4] = range[0];
        }
    }

    static inline void apply(Segment const& segment, Range& range)
    {
        traits::resize<Range>::apply(range, 2);

        typename boost::range_iterator<Range>::type it = boost::begin(range);

        assign_point_from_index<0>(segment, *it);
        ++it;
        assign_point_from_index<1>(segment, *it);
    }


    static inline void apply(Range1 const& source, Range2& destination)
    {
        geometry::clear(destination);

        rview_type rview(source);

        // We consider input always as closed, and skip last
        // point for open output.
        view_type view(rview);

        int n = boost::size(view);
        if (geometry::closure<Range2>::value == geometry::open)
        {
            n--;
        }

        int i = 0;
        for (typename boost::range_iterator<view_type const>::type it
            = boost::begin(view);
            it != boost::end(view) && i < n;
            ++it, ++i)
        {
            geometry::append(destination, *it);
        }
    }


    static inline void apply(Polygon1 const& source, Polygon2& destination)
    {
        // Clearing managed per ring, and in the resizing of interior rings

        per_ring::apply(geometry::exterior_ring(source), 
            geometry::exterior_ring(destination));

        // Container should be resizeable
        traits::resize
            <
                typename boost::remove_reference
                <
                    typename traits::interior_mutable_type<Polygon2>::type
                >::type
            >::apply(interior_rings(destination), num_interior_rings(source));

        typename interior_return_type<Polygon1 const>::type rings_source
                    = interior_rings(source);
        typename interior_return_type<Polygon2>::type rings_dest
                    = interior_rings(destination);

        BOOST_AUTO_TPL(it_source, boost::begin(rings_source));
        BOOST_AUTO_TPL(it_dest, boost::begin(rings_dest));

        for ( ; it_source != boost::end(rings_source); ++it_source, ++it_dest)
        {
            per_ring::apply(*it_source, *it_dest);
        }
    }

    static inline void apply(Geometry1 const& source, Geometry2& destination)
    {
        destination = source;
    }

    static inline void apply(Geometry1 const& geometry1, Geometry2& geometry2)
    {
        concept::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2>();
        convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
    }

template <typename Geometry1, typename Geometry2>
inline void convert(Geometry1 const& geometry1, Geometry2& geometry2)
{
    dispatch::devarianted_convert<Geometry1, Geometry2>::apply(geometry1, geometry2);
}

    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        if (!geometry::math::equals(get<min_corner, Dimension>(box1), get<min_corner, Dimension>(box2))
            || !geometry::math::equals(get<max_corner, Dimension>(box1), get<max_corner, Dimension>(box2)))
        {
            return false;
        }
        return box_box<Dimension + 1, DimensionCount>::apply(box1, box2);
    }

    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return true;
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        return geometry::math::equals(
                geometry::area(geometry1),
                geometry::area(geometry2));
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        return geometry::math::equals(
                geometry::length(geometry1),
                geometry::length(geometry2));
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        if (! TrivialCheck::apply(geometry1, geometry2))
        {
            return false;
        }

        typedef typename geometry::select_most_precise
            <
                typename select_coordinate_type
                    <
                        Geometry1, Geometry2
                    >::type,
                double
            >::type calculation_type;

        typedef std::vector<collected_vector<calculation_type> > v;
        v c1, c2;

        geometry::collect_vectors(c1, geometry1);
        geometry::collect_vectors(c2, geometry2);

        if (boost::size(c1) != boost::size(c2))
        {
            return false;
        }

        std::sort(c1.begin(), c1.end());
        std::sort(c2.begin(), c2.end());

        // Just check if these vectors are equal.
        return std::equal(c1.begin(), c1.end(), c2.begin());
    }

    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2)
    {
        return equals
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                DimensionCount,
                false
            >::apply(g2, g1);
    }

    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2)
    {
        concept::check_concepts_and_equal_dimensions
        <
            Geometry1 const,
            Geometry2 const
        >();
        return equals<Geometry1, Geometry2>::apply(geometry1, geometry2);
    }

template <typename Geometry1, typename Geometry2>
inline bool equals(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return dispatch::devarianted_equals<Geometry1, Geometry2>
               ::apply(geometry1, geometry2);
}

    static inline void apply(Geometry& )
    {}


    static inline void apply(Box& box)
    {
        if (get<min_corner, Dimension>(box) > get<max_corner, Dimension>(box))
        {
            // Swap the coordinates
            coordinate_type max_value = get<min_corner, Dimension>(box);
            coordinate_type min_value = get<max_corner, Dimension>(box);
            set<min_corner, Dimension>(box, min_value);
            set<max_corner, Dimension>(box, max_value);
        }

        correct_box_loop
            <
                Box, Dimension + 1, DimensionCount
            >::apply(box);
    }

    static inline void apply(Box& )
    {}


    static inline void apply(Box& box)
    {
        // Currently only for Cartesian coordinates
        // (or spherical without crossing dateline)
        // Future version: adapt using strategies
        correct_box_loop
            <
                Box, 0, dimension<Box>::type::value
            >::apply(box);
    }



    static inline void apply(Ring& r)
    {
        // Check close-ness
        if (boost::size(r) > 2)
        {
            // check if closed, if not, close it
            bool const disjoint = geometry::disjoint(*boost::begin(r), *(boost::end(r) - 1));
            closure_selector const s = geometry::closure<Ring>::value;

            if (disjoint && (s == closed))
            {
                geometry::append(r, *boost::begin(r));
            }
            if (! disjoint && s != closed)
            {
                // Open it by removing last point
                geometry::traits::resize<Ring>::apply(r, boost::size(r) - 1);
            }
        }
        // Check area
        Predicate predicate;
        typedef typename default_area_result<Ring>::type area_result_type;
        area_result_type const zero = area_result_type();
        if (predicate(ring_area_type::apply(r, strategy_type()), zero))
        {
            std::reverse(boost::begin(r), boost::end(r));
        }
    }


    static inline void apply(Polygon& poly)
    {
        correct_ring
            <
                ring_type,
                std::less<area_result_type>
            >::apply(exterior_ring(poly));

        typename interior_return_type<Polygon>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            correct_ring
                <
                    ring_type,
                    std::greater<area_result_type>
                >::apply(*it);
        }
    }

template <typename Geometry>
inline void correct(Geometry& geometry)
{
    concept::check<Geometry const>();

    dispatch::correct<Geometry>::apply(geometry);
}

    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& b1, Box2 const& b2,
            bool& overlaps, bool& one_in_two, bool& two_in_one)
    {
        assert_dimension_equal<Box1, Box2>();

        typedef typename coordinate_type<Box1>::type coordinate_type1;
        typedef typename coordinate_type<Box2>::type coordinate_type2;

        coordinate_type1 const& min1 = get<min_corner, Dimension>(b1);
        coordinate_type1 const& max1 = get<max_corner, Dimension>(b1);
        coordinate_type2 const& min2 = get<min_corner, Dimension>(b2);
        coordinate_type2 const& max2 = get<max_corner, Dimension>(b2);

        // We might use the (not yet accepted) Boost.Interval
        // submission in the future

        // If:
        // B1: |-------|
        // B2:           |------|
        // in any dimension -> no overlap
        if (max1 <= min2 || min1 >= max2)
        {
            overlaps = false;
            return;
        }

        // If:
        // B1: |--------------------|
        // B2:   |-------------|
        // in all dimensions -> within, then no overlap
        // B1: |--------------------|
        // B2: |-------------|
        // this is "within-touch" -> then no overlap. So use < and >
        if (min1 < min2 || max1 > max2)
        {
            one_in_two = false;
        }
        // Same other way round
        if (min2 < min1 || max2 > max1)
        {
            two_in_one = false;
        }

        box_box_loop
            <
                Dimension + 1,
                DimensionCount
            >::apply(b1, b2, overlaps, one_in_two, two_in_one);
    }

    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& , Box2 const&, bool&, bool&, bool&)
    {
    }

    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& b1, Box2 const& b2)
    {
        bool overlaps = true;
        bool within1 = true;
        bool within2 = true;
        box_box_loop
            <
                0,
                dimension<Box1>::type::value
            >::apply(b1, b2, overlaps, within1, within2);

        /*
        \see http://docs.codehaus.org/display/GEOTDOC/02+Geometry+Relationships#02GeometryRelationships-Overlaps
        where is stated that "inside" is not an "overlap",
        this is true and is implemented as such.
        */
        return overlaps && ! within1 && ! within2;
    }

template <typename Geometry1, typename Geometry2>
inline bool overlaps(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    return dispatch::overlaps
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2);
}

    template <typename Range>
    static inline std::size_t apply(Range const& range, bool add_for_open)
    {
        std::size_t n = boost::size(range);
        if (add_for_open && n > 0)
        {
            if (geometry::closure<Range>::value == open)
            {
                if (geometry::disjoint(*boost::begin(range), *(boost::begin(range) + n - 1)))
                {
                    return n + 1;
                }
            }
        }
        return n;
    }

    template <typename Geometry>
    static inline std::size_t apply(Geometry const&, bool)
    {
        return D;
    }

    template <typename Polygon>
    static inline std::size_t apply(Polygon const& poly, bool add_for_open)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        std::size_t n = range_count::apply(
                    exterior_ring(poly), add_for_open);

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            n += range_count::apply(*it, add_for_open);
        }

        return n;
    }

    static inline std::size_t apply(Geometry const& geometry,
                                    bool add_for_open)
    {
        return num_points<Geometry>::apply(geometry, add_for_open);
    }

template <typename Geometry>
inline std::size_t num_points(Geometry const& geometry, bool add_for_open = false)
{
    concept::check<Geometry const>();

    return dispatch::devarianted_num_points<Geometry>::apply(geometry, add_for_open);
}


template <typename Geometry>
inline void throw_on_empty_input(Geometry const& geometry)
{
#if ! defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
    if (geometry::num_points(geometry) == 0)
    {
        throw empty_input_exception();
    }
#endif
}

template <typename Box, typename Point>
inline void assign_box_corners(Box const& box,
        Point& lower_left, Point& lower_right,
        Point& upper_left, Point& upper_right)
{
    concept::check<Box const>();
    concept::check<Point>();

    detail::assign::assign_box_2d_corner
            <min_corner, min_corner>(box, lower_left);
    detail::assign::assign_box_2d_corner
            <max_corner, min_corner>(box, lower_right);
    detail::assign::assign_box_2d_corner
            <min_corner, max_corner>(box, upper_left);
    detail::assign::assign_box_2d_corner
            <max_corner, max_corner>(box, upper_right);
}



template <bool Reverse, typename Box, typename Range>
inline void assign_box_corners_oriented(Box const& box, Range& corners)
{
    if (Reverse)
    {
        // make counterclockwise ll,lr,ur,ul
        assign_box_corners(box, corners[0], corners[1], corners[3], corners[2]);
    }
    else
    {
        // make clockwise ll,ul,ur,lr
        assign_box_corners(box, corners[0], corners[3], corners[1], corners[2]);
    }
}

    template <typename ReturnType, typename Policy, typename Rings, typename Strategy>
    static inline ReturnType sum_interior_rings(Rings const& rings, Strategy const& strategy)
    {
        ReturnType sum = ReturnType();
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }

    template <typename ReturnType, typename Policy, typename Polygon, typename Strategy>
    static inline ReturnType apply(Polygon const& poly, Strategy const& strategy)
    {
        return Policy::apply(exterior_ring(poly), strategy)
            + sum_interior_rings<ReturnType, Policy>(interior_rings(poly), strategy)
            ;
    }


template <int Dimension, typename Box>
inline void divide_box(Box const& box, Box& lower_box, Box& upper_box)
{
    typedef typename coordinate_type<Box>::type ctype;

    // Divide input box into two parts, e.g. left/right
    ctype two = 2;
    ctype mid = (geometry::get<min_corner, Dimension>(box)
            + geometry::get<max_corner, Dimension>(box)) / two;

    lower_box = box;
    upper_box = box;
    geometry::set<max_corner, Dimension>(lower_box, mid);
    geometry::set<min_corner, Dimension>(upper_box, mid);
}

template <typename OverlapsPolicy, typename InputCollection, typename Box>
static inline void divide_into_subsets(Box const& lower_box,
        Box const& upper_box,
        InputCollection const& collection,
        index_vector_type const& input,
        index_vector_type& lower,
        index_vector_type& upper,
        index_vector_type& exceeding)
{
    typedef boost::range_iterator
        <
            index_vector_type const
        >::type index_iterator_type;

    for(index_iterator_type it = boost::begin(input);
        it != boost::end(input);
        ++it)
    {
        bool const lower_overlapping = OverlapsPolicy::apply(lower_box,
                    collection[*it]);
        bool const upper_overlapping = OverlapsPolicy::apply(upper_box,
                    collection[*it]);

        if (lower_overlapping && upper_overlapping)
        {
            exceeding.push_back(*it);
        }
        else if (lower_overlapping)
        {
            lower.push_back(*it);
        }
        else if (upper_overlapping)
        {
            upper.push_back(*it);
        }
        else
        {
            // Is nowhere! Should not occur!
            BOOST_ASSERT(true);
        }
    }
}

template <typename InputCollection, typename Policy>
static inline void handle_one(InputCollection const& collection,
        index_vector_type const& input,
        Policy& policy)
{
    typedef boost::range_iterator<index_vector_type const>::type
                index_iterator_type;
    // Quadratic behaviour at lowest level (lowest quad, or all exceeding)
    for(index_iterator_type it1 = boost::begin(input);
        it1 != boost::end(input);
        ++it1)
    {
        index_iterator_type it2 = it1;
        for(++it2; it2 != boost::end(input); ++it2)
        {
            policy.apply(collection[*it1], collection[*it2]);
        }
    }
}

template <typename InputCollection, typename Policy>
static inline void handle_two(
        InputCollection const& collection1, index_vector_type const& input1,
        InputCollection const& collection2, index_vector_type const& input2,
        Policy& policy)
{
    typedef boost::range_iterator
        <
            index_vector_type const
        >::type index_iterator_type;

    for(index_iterator_type it1 = boost::begin(input1);
        it1 != boost::end(input1);
        ++it1)
    {
        for(index_iterator_type it2 = boost::begin(input2);
            it2 != boost::end(input2);
            ++it2)
        {
            policy.apply(collection1[*it1], collection2[*it2]);
        }
    }
}


    template <typename InputCollection, typename Policy>
    static inline void next_level(Box const& box,
            InputCollection const& collection,
            index_vector_type const& input,
            int level, std::size_t min_elements,
            Policy& policy, VisitBoxPolicy& box_policy)
    {
        if (boost::size(input) > 0)
        {
            if (std::size_t(boost::size(input)) > min_elements && level < 100)
            {
                sub_divide::apply(box, collection, input, level + 1,
                            min_elements, policy, box_policy);
            }
            else
            {
                handle_one(collection, input, policy);
            }
        }
    }

    template <typename InputCollection, typename Policy>
    static inline void apply(Box const& box,
            InputCollection const& collection,
            index_vector_type const& input,
            int level,
            std::size_t min_elements,
            Policy& policy, VisitBoxPolicy& box_policy)
    {
        box_policy.apply(box, level);

        Box lower_box, upper_box;
        divide_box<Dimension>(box, lower_box, upper_box);

        index_vector_type lower, upper, exceeding;
        divide_into_subsets<OverlapsPolicy>(lower_box, upper_box, collection,
                    input, lower, upper, exceeding);

        if (boost::size(exceeding) > 0)
        {
            // All what is not fitting a partition should be combined
            // with each other, and with all which is fitting.
            handle_one(collection, exceeding, policy);
            handle_two(collection, exceeding, collection, lower, policy);
            handle_two(collection, exceeding, collection, upper, policy);
        }

        // Recursively call operation both parts
        next_level(lower_box, collection, lower, level, min_elements,
                        policy, box_policy);
        next_level(upper_box, collection, upper, level, min_elements,
                        policy, box_policy);
    }


    template <typename InputCollection, typename Policy>
    static inline void next_level(Box const& box,
            InputCollection const& collection1,
            index_vector_type const& input1,
            InputCollection const& collection2,
            index_vector_type const& input2,
            int level, std::size_t min_elements,
            Policy& policy, VisitBoxPolicy& box_policy)
    {
        if (boost::size(input1) > 0 && boost::size(input2) > 0)
        {
            if (std::size_t(boost::size(input1)) > min_elements
                && std::size_t(boost::size(input2)) > min_elements
                && level < 100)
            {
                sub_divide::apply(box, collection1, input1, collection2,
                                input2, level + 1, min_elements,
                                policy, box_policy);
            }
            else
            {
                box_policy.apply(box, level + 1);
                handle_two(collection1, input1, collection2, input2, policy);
            }
        }
    }

    template <typename InputCollection, typename Policy>
    static inline void apply(Box const& box,
            InputCollection const& collection1, index_vector_type const& input1,
            InputCollection const& collection2, index_vector_type const& input2,
            int level,
            std::size_t min_elements,
            Policy& policy, VisitBoxPolicy& box_policy)
    {
        box_policy.apply(box, level);

        Box lower_box, upper_box;
        divide_box<Dimension>(box, lower_box, upper_box);

        index_vector_type lower1, upper1, exceeding1;
        index_vector_type lower2, upper2, exceeding2;
        divide_into_subsets<OverlapsPolicy>(lower_box, upper_box, collection1,
                    input1, lower1, upper1, exceeding1);
        divide_into_subsets<OverlapsPolicy>(lower_box, upper_box, collection2,
                    input2, lower2, upper2, exceeding2);

        if (boost::size(exceeding1) > 0)
        {
            // All exceeding from 1 with 2:
            handle_two(collection1, exceeding1, collection2, exceeding2,
                        policy);

            // All exceeding from 1 with lower and upper of 2:
            handle_two(collection1, exceeding1, collection2, lower2, policy);
            handle_two(collection1, exceeding1, collection2, upper2, policy);
        }
        if (boost::size(exceeding2) > 0)
        {
            // All exceeding from 2 with lower and upper of 1:
            handle_two(collection1, lower1, collection2, exceeding2, policy);
            handle_two(collection1, upper1, collection2, exceeding2, policy);
        }

        next_level(lower_box, collection1, lower1, collection2, lower2, level,
                        min_elements, policy, box_policy);
        next_level(upper_box, collection1, upper1, collection2, upper2, level,
                        min_elements, policy, box_policy);
    }

    template <typename Box>
    static inline void apply(Box const&, int )
    {}


    template <typename InputCollection>
    static inline void expand_to_collection(InputCollection const& collection,
                Box& total, index_vector_type& index_vector)
    {
        std::size_t index = 0;
        for(typename boost::range_iterator<InputCollection const>::type it
            = boost::begin(collection);
            it != boost::end(collection);
            ++it, ++index)
        {
            ExpandPolicy::apply(total, *it);
            index_vector.push_back(index);
        }
    }

    template <typename InputCollection, typename VisitPolicy>
    static inline void apply(InputCollection const& collection,
            VisitPolicy& visitor,
            std::size_t min_elements = 16,
            VisitBoxPolicy box_visitor = visit_no_policy()
            )
    {
        if (std::size_t(boost::size(collection)) > min_elements)
        {
            index_vector_type index_vector;
            Box total;
            assign_inverse(total);
            expand_to_collection(collection, total, index_vector);

            detail::partition::partition_one_collection
                <
                    0, Box,
                    OverlapsPolicy,
                    VisitBoxPolicy
                >::apply(total, collection, index_vector, 0, min_elements,
                                visitor, box_visitor);
        }
        else
        {
            typedef typename boost::range_iterator
                <
                    InputCollection const
                >::type iterator_type;
            for(iterator_type it1 = boost::begin(collection);
                it1 != boost::end(collection);
                ++it1)
            {
                iterator_type it2 = it1;
                for(++it2; it2 != boost::end(collection); ++it2)
                {
                    visitor.apply(*it1, *it2);
                }
            }
        }
    }

template <std::size_t Index, typename Geometry, typename Point>
inline void assign_point_to_index(Point const& point, Geometry& geometry)
{
    concept::check<Point const>();
    concept::check<Geometry>();

    detail::assign::assign_point_to_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(point, geometry);
}

template <std::size_t Index, typename Point, typename Geometry>
inline void assign_point_from_index(Geometry const& geometry, Point& point)
{
    concept::check<Geometry const>();
    concept::check<Point>();

    detail::assign::assign_point_from_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(geometry, point);
}


    static inline void apply(Box& box, coordinate_type const& value)
    {
        geometry::set<Index, Dimension>(box, value);
        initialize<Box, Index, Dimension + 1, DimensionCount>::apply(box, value);
    }


    static inline void apply(Box&,  coordinate_type const& )
    {}

    static inline void apply(Point& point)
    {
        geometry::assign_value(point, 0);
    }


    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<point_type>::type bound_type;

        initialize
            <
                BoxOrSegment, 0, 0, dimension<BoxOrSegment>::type::value
            >::apply(
            geometry, boost::numeric::bounds<bound_type>::highest());
        initialize
            <
                BoxOrSegment, 1, 0, dimension<BoxOrSegment>::type::value
            >::apply(
            geometry, boost::numeric::bounds<bound_type>::lowest());
    }

    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<BoxOrSegment>::type coordinate_type;

        initialize
            <
                BoxOrSegment, 0, 0, dimension<BoxOrSegment>::type::value
            >::apply(geometry, coordinate_type());
        initialize
            <
                BoxOrSegment, 1, 0, dimension<BoxOrSegment>::type::value
            >::apply(geometry, coordinate_type());
    }



template
<
    std::size_t Corner1, std::size_t Corner2,
    typename Box, typename Point
>
inline void assign_box_2d_corner(Box const& box, Point& point)
{
    // Be sure both are 2-Dimensional
    assert_dimension<Box, 2>();
    assert_dimension<Point, 2>();

    // Copy coordinates
    typedef typename coordinate_type<Point>::type coordinate_type;

    geometry::set<0>(point, boost::numeric_cast<coordinate_type>(get<Corner1, 0>(box)));
    geometry::set<1>(point, boost::numeric_cast<coordinate_type>(get<Corner2, 1>(box)));
}


    static inline void apply(Point const& point, Geometry& geometry)
    {
        geometry::set<Index, Dimension>(geometry, boost::numeric_cast
            <
                typename coordinate_type<Geometry>::type
            >(geometry::get<Dimension>(point)));

        assign_point_to_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(point, geometry);
    }

    static inline void apply(Point const& , Geometry& )
    {
    }


    static inline void apply(Geometry const& geometry, Point& point)
    {
        geometry::set<Dimension>( point, boost::numeric_cast
            <
                typename coordinate_type<Point>::type
            >(geometry::get<Index, Dimension>(geometry)));

        assign_point_from_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(geometry, point);
    }

    static inline void apply(Geometry const&, Point&)
    {
    }


    template <typename Type>
    static inline void apply(Geometry& geometry,
                Type const& x1, Type const& y1, Type const& x2, Type const& y2)
    {
        geometry::set<0, 0>(geometry, boost::numeric_cast<coordinate_type>(x1));
        geometry::set<0, 1>(geometry, boost::numeric_cast<coordinate_type>(y1));
        geometry::set<1, 0>(geometry, boost::numeric_cast<coordinate_type>(x2));
        geometry::set<1, 1>(geometry, boost::numeric_cast<coordinate_type>(y2));
    }

template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry, Type const& c1, Type const& c2)
{
    concept::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
}

template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
            Type const& c1, Type const& c2, Type const& c3)
{
    concept::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
}

template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
                Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concept::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
}

    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        set<Dimension>(destination, boost::numeric_cast<coordinate_type>(get<Dimension>(source)));
        point_to_point<Source, Destination, Dimension + 1, DimensionCount>::apply(source, destination);
    }

    static inline void apply(Source const& , Destination& )
    {}



template <typename Source, typename Destination>
inline void convert_point_to_point(Source const& source, Destination& destination)
{
    point_to_point<Source, Destination, 0, dimension<Destination>::value>::apply(source, destination);
}

    static inline bool apply(Point& destination, Point const& source, bool)
    {
        destination = source;
        return true;
    }

    template <typename InputPoint>
    static inline bool apply(Point& p, InputPoint const& p1, InputPoint const& p2)
    {
        typename coordinate_type<Point>::type const two = 2;
        set<Dimension>(p,
                    (get<Dimension>(p1) + get<Dimension>(p2)) / two);
        return midpoint_helper<Point, Dimension + 1, DimensionCount>::apply(p, p1, p2);
    }

    template <typename InputPoint>
    static inline bool apply(Point& , InputPoint const& , InputPoint const& )
    {
        return true;
    }

    static inline bool apply(Point& point, Range const& range, bool midpoint)
    {
        const std::size_t n = boost::size(range);
        if (midpoint && n > 1)
        {
            typedef typename boost::range_iterator
                <
                    Range const
                >::type iterator;

            iterator it = boost::begin(range);
            iterator prev = it++;
            while (it != boost::end(range)
                && detail::equals::equals_point_point(*it, *prev))
            {
                prev = it++;
            }
            if (it != boost::end(range))
            {
                return midpoint_helper
                    <
                        Point,
                        0, dimension<Point>::value
                    >::apply(point, *prev, *it);
            }
        }

        if (n > 0)
        {
            geometry::detail::conversion::convert_point_to_point(*boost::begin(range), point);
            return true;
        }
        return false;
    }

    static inline bool apply(Point& point, Polygon const& polygon, bool midpoint)
    {
        return point_on_range
            <
                Point,
                typename ring_type<Polygon>::type
            >::apply(point, exterior_ring(polygon), midpoint);
    }

    static inline bool apply(Point& point, Box const& box, bool midpoint)
    {
        if (midpoint)
        {
            Point p1, p2;
            detail::assign::assign_box_2d_corner<min_corner, min_corner>(box, p1);
            detail::assign::assign_box_2d_corner<max_corner, min_corner>(box, p2);
            midpoint_helper
                <
                    Point,
                    0, dimension<Point>::value
                >::apply(point, p1, p2);
        }
        else
        {
            detail::assign::assign_box_2d_corner<min_corner, min_corner>(box, point);
        }

        return true;
    }

template <typename Point, typename Geometry>
inline bool point_on_border(Point& point,
            Geometry const& geometry,
            bool midpoint = false)
{
    concept::check<Point>();
    concept::check<Geometry const>();

    typedef typename point_type<Geometry>::type point_type;

    return dispatch::point_on_border
            <
                typename tag<Geometry>::type,
                Point,
                Geometry
            >::apply(point, geometry, midpoint);
}

    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }


    inline ring_identifier()
        : source_index(-1)
        , multi_index(-1)
        , ring_index(-1)
    {}


    inline ring_identifier(int src, int mul, int rin)
        : source_index(src)
        , multi_index(mul)
        , ring_index(rin)
    {}


    inline bool operator<(ring_identifier const& other) const
    {
        return source_index != other.source_index ? source_index < other.source_index
            : multi_index !=other.multi_index ? multi_index < other.multi_index
            : ring_index < other.ring_index
            ;
    }


    inline bool operator==(ring_identifier const& other) const
    {
        return source_index == other.source_index
            && ring_index == other.ring_index
            && multi_index == other.multi_index
            ;
    }

    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        geometry::set<min_corner, Dimension>(destination, 
            boost::numeric_cast<coordinate_type>(
                geometry::get<min_corner, Dimension>(source)));
        geometry::set<max_corner, Dimension>(destination, 
            boost::numeric_cast<coordinate_type>(
                geometry::get<max_corner, Dimension>(source)));
                
        indexed_to_indexed
            <
                Source, Destination, 
                Dimension + 1, DimensionCount
            >::apply(source, destination);
    }

    static inline void apply(Source const& , Destination& )
    {}


    inline disjoint_interrupt_policy()
        : has_intersections(false)
    {}


    template <typename Range>
    inline bool apply(Range const& range)
    {
        // If there is any IP in the range, it is NOT disjoint
        if (boost::size(range) > 0)
        {
            has_intersections = true;
            return true;
        }
        return false;
    }

    static inline bool apply(Point1 const& p1, Point2 const& p2)
    {
        if (! geometry::math::equals(get<Dimension>(p1), get<Dimension>(p2)))
        {
            return true;
        }
        return point_point
            <
                Point1, Point2,
                Dimension + 1, DimensionCount
            >::apply(p1, p2);
    }

    static inline bool apply(Point1 const& , Point2 const& )
    {
        return false;
    }

    static inline bool apply(Point const& point, Box const& box)
    {
        if (get<Dimension>(point) < get<min_corner, Dimension>(box)
            || get<Dimension>(point) > get<max_corner, Dimension>(box))
        {
            return true;
        }
        return point_box
            <
                Point, Box,
                Dimension + 1, DimensionCount
            >::apply(point, box);
    }

    static inline bool apply(Point const& , Box const& )
    {
        return false;
    }

    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        if (get<max_corner, Dimension>(box1) < get<min_corner, Dimension>(box2))
        {
            return true;
        }
        if (get<min_corner, Dimension>(box1) > get<max_corner, Dimension>(box2))
        {
            return true;
        }
        return box_box
            <
                Box1, Box2,
                Dimension + 1, DimensionCount
            >::apply(box1, box2);
    }

    static inline bool apply(Box1 const& , Box2 const& )
    {
        return false;
    }

    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        return ! geometry::covered_by(geometry1, geometry2);
    }

template <typename Box1, typename Box2>
inline bool disjoint_box_box(Box1 const& box1, Box2 const& box2)
{
    return box_box
        <
            Box1, Box2,
            0, dimension<Box1>::type::value
        >::apply(box1, box2);
}

template <typename Point1, typename Point2>
inline bool disjoint_point_point(Point1 const& point1, Point2 const& point2)
{
    return point_point
        <
            Point1, Point2,
            0, dimension<Point1>::type::value
        >::apply(point1, point2);
}

template <typename Point1, typename Point2>
inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
{
    return ! detail::disjoint::disjoint_point_point(point1, point2);
}


    inline overlay_invalid_input_exception() {}


    virtual char const* what() const throw()
    {
        return "Boost.Geometry Overlay invalid input exception";
    }



template <typename Geometry>
inline bool has_self_intersections(Geometry const& geometry)
{
    typedef typename point_type<Geometry>::type point_type;
    typedef detail::overlay::turn_info<point_type> turn_info;
    std::deque<turn_info> turns;
    detail::disjoint::disjoint_interrupt_policy policy;
    geometry::self_turns<detail::overlay::assign_null_policy>(geometry, turns, policy);
    
#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
    bool first = true;
#endif    
    for(typename std::deque<turn_info>::const_iterator it = boost::begin(turns); 
        it != boost::end(turns); ++it)
    {
        turn_info const& info = *it;
        bool const both_union_turn = 
            info.operations[0].operation == detail::overlay::operation_union
            && info.operations[1].operation == detail::overlay::operation_union;
        bool const both_intersection_turn = 
            info.operations[0].operation == detail::overlay::operation_intersection
            && info.operations[1].operation == detail::overlay::operation_intersection;

        bool const valid = (both_union_turn || both_intersection_turn)
            && (info.method == detail::overlay::method_touch
                || info.method == detail::overlay::method_touch_interior);

        if (! valid)
        {
#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
            if (first)
            {
                std::cout << "turn points: " << std::endl;
                first = false;
            }
            std::cout << method_char(info.method);
            for (int i = 0; i < 2; i++)
            {
                std::cout << " " << operation_char(info.operations[i].operation);
            }
            std::cout << " " << geometry::dsv(info.point) << std::endl;
#endif

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
            throw overlay_invalid_input_exception();
#endif
        }

    }
    return false;
}

    static inline void apply(
                    typename add_const_if_c<IsConst, Range>::type& range,
                    Actor& actor)
    {
        actor.apply(range);
    }

    static inline void apply(
                    typename add_const_if_c<IsConst, Polygon>::type& polygon,
                    Actor& actor)
    {
        actor.apply(exterior_ring(polygon));

        // TODO: If some flag says true, also do the inner rings.
        // for convex hull, it's not necessary
    }

    static inline void apply(
                    typename add_const_if_c<IsConst, Box>::type& box,
                    Actor& actor)
    {
        actor.apply(box_view<Box>(box));
    }


template <typename Geometry, typename Actor>
inline void for_each_range(Geometry const& geometry, Actor& actor)
{
    dispatch::for_each_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Actor,
            true
        >::apply(geometry, actor);
}


    inline relaxed_less()
    {
        // TODO: adapt for ttmath, and maybe build the map in another way 
        // (e.g. exact constellations of segment-id's), maybe adaptive.
        epsilon = std::numeric_limits<double>::epsilon() * 100.0;
    }


    inline bool operator()(P const& a, P const& b) const
    {
        coordinate_type const dx = math::abs(geometry::get<0>(a) - geometry::get<0>(b));
        coordinate_type const dy = math::abs(geometry::get<1>(a) - geometry::get<1>(b));


        if (dx < epsilon && dy < epsilon)
        {
            return false;
        }
        if (dx < epsilon)
        {
            return geometry::get<1>(a) < geometry::get<1>(b);
        }

        return geometry::get<0>(a) < geometry::get<0>(b);
    }


    inline bool equals(P const& a, P const& b) const
    {
        typedef typename geometry::coordinate_type<P>::type coordinate_type;

        coordinate_type const dx = math::abs(geometry::get<0>(a) - geometry::get<0>(b));
        coordinate_type const dy = math::abs(geometry::get<1>(a) - geometry::get<1>(b));

        return dx < epsilon && dy < epsilon;
    };



template <typename T, typename P1, typename P2>
inline T calculate_angle(P1 const& from_point, P2 const& to_point)
{
    typedef P1 vector_type;
    vector_type v = from_point;
    geometry::subtract_point(v, to_point);
    return atan2(geometry::get<1>(v), geometry::get<0>(v));
}


template <typename Iterator, typename Vector>
inline Iterator advance_circular(Iterator it, Vector const& vector, segment_identifier& seg_id, bool forward = true)
{
    int const increment = forward ? 1 : -1;
    if (it == boost::begin(vector) && increment < 0)
    {
        it = boost::end(vector);
        seg_id.segment_index = boost::size(vector);
    }
    it += increment;
    seg_id.segment_index += increment;
    if (it == boost::end(vector))
    {
        seg_id.segment_index = 0;
        it = boost::begin(vector);
    }
    return it;
}

        inline bool operator()(AngleInfo const& left, AngleInfo const& right) const
        {
            // In this case we can compare even double using equals
            // return geometry::math::equals(left.angle, right.angle)
            return left.angle == right.angle
                ? int(left.incoming) < int(right.incoming)
                : left.angle < right.angle
                ;
        }


    inline bool is_occupied()
    {
        if (boost::size(angles) <= 1)
        {
            return false;
        }

        std::sort(angles.begin(), angles.end(), angle_sort());

        typedef geometry::closing_iterator<collection_type const> closing_iterator;
        closing_iterator vit(angles);
        closing_iterator end(angles, true);

        closing_iterator prev = vit++;
        for( ; vit != end; prev = vit++)
        {
            if (! geometry::math::equals(prev->angle, vit->angle)
                && ! prev->incoming
                && vit->incoming)
            {
                return false;
            }
        }
        return true;
    }

    inline occupation_info()
        : m_occupied(false)
        , m_calculated(false)
    {}


    template <typename PointC, typename Point1, typename Point2>
    inline void add(PointC const& map_point, Point1 const& direction_point, Point2 const& intersection_point,
                    int turn_index, int operation_index,
                    segment_identifier const& seg_id, bool incoming)
    {
        //std::cout << "-> adding angle " << geometry::wkt(direction_point) << " .. " << geometry::wkt(intersection_point) << " " << int(incoming) << std::endl;
        if (geometry::equals(direction_point, intersection_point))
        {
            //std::cout << "EQUAL! Skipping" << std::endl;
            return;
        }

        AngleInfo info;
        info.incoming = incoming;
        info.angle = calculate_angle<typename AngleInfo::angle_type>(direction_point, map_point);
        info.seg_id = seg_id;
        info.turn_index = turn_index;
        info.operation_index = operation_index;
        info.intersection_point = intersection_point;
        info.direction_point = direction_point;
        angles.push_back(info);

        m_calculated = false;
    }


    inline bool occupied()
    {
        if (! m_calculated)
        {
            m_occupied = is_occupied();
            m_calculated = true;
        }
        return m_occupied;
    }


    template <typename Turns, typename TurnSegmentIndices>
    inline void get_left_turns(
                    Turns& turns, TurnSegmentIndices const& turn_segment_indices,
                    std::set<int>& keep_indices)
    {
        std::sort(angles.begin(), angles.end(), angle_sort());
        calculate_left_turns<AngleInfo>(angles, turns, turn_segment_indices, keep_indices);
    }



template <typename Point, typename Ring, typename Info>
inline void add_incoming_and_outgoing_angles(Point const& map_point, Point const& intersection_point,
                Ring const& ring, 
                int turn_index,
                int operation_index,
                segment_identifier seg_id,
                Info& info)
{
    typedef typename boost::range_iterator
        <
            Ring const
        >::type iterator_type;

    int const n = boost::size(ring);
    if (seg_id.segment_index >= n || seg_id.segment_index < 0)
    {
        return;
    }

    segment_identifier real_seg_id = seg_id;
    iterator_type it = boost::begin(ring) + seg_id.segment_index;

    // TODO: if we use turn-info ("to", "middle"), we know if to advance without resorting to equals
    relaxed_less<Point> comparator;

    if (comparator.equals(intersection_point, *it))
    {
        // It should be equal only once. But otherwise we skip it (in "add")
        it = advance_circular(it, ring, seg_id, false);
    }

    info.add(map_point, *it, intersection_point, turn_index, operation_index, real_seg_id, true);

    if (comparator.equals(intersection_point, *it))
    {
        it = advance_circular(it, ring, real_seg_id);
    }
    else
    {
        // Don't upgrade the ID
        it = advance_circular(it, ring, seg_id);
    }
    for (int defensive_check = 0; 
        comparator.equals(intersection_point, *it) && defensive_check < n; 
        defensive_check++)
    {
        it = advance_circular(it, ring, real_seg_id);
    }

    info.add(map_point, *it, intersection_point, turn_index, operation_index, real_seg_id, false);
}


    inline OccupationInfo& find_or_insert(Point const& point, Point& mapped_point)
    {
        typename map_type::iterator it = map.find(point);
        if (it == boost::end(map))
        {
            std::pair<typename map_type::iterator, bool> pair 
                        = map.insert(std::make_pair(point, OccupationInfo()));
            it = pair.first;
        }
        mapped_point = it->first;
        return it->second;
    }


    inline bool contains(Point const& point) const
    {
        typename map_type::const_iterator it = map.find(point);
        return it != boost::end(map);
    }


    inline bool contains_turn_index(int index) const
    {
        return turn_indices.count(index) > 0;
    }


    inline void insert_turn_index(int index)
    {
        turn_indices.insert(index);
    }

    static inline bool apply(Geometry1 const &geometry1, Geometry2 const& geometry2)
    {
        return ! Policy::apply(geometry1, geometry2);
    }

template <typename Range, typename Geometry>
inline Range& as_range(Geometry& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            false
        >::get(input);
}

template <typename Range, typename Geometry>
inline Range const& as_range(Geometry const& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            true
        >::get(input);
}

template <typename TurnInfo>
inline bool skip(TurnInfo const& turn_info)
{
    return (turn_info.discarded || turn_info.both(operation_union))
        && ! turn_info.any_blocked()
        && ! turn_info.both(operation_intersection)
        ;
}



template <typename TurnPoints, typename Map>
inline void map_turns(Map& map, TurnPoints const& turn_points)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;
    typedef typename turn_point_type::container_type container_type;

    int index = 0;
    for (typename boost::range_iterator<TurnPoints const>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it, ++index)
    {
        if (! skip(*it))
        {
            int op_index = 0;
            for (typename boost::range_iterator<container_type const>::type
                    op_it = boost::begin(it->operations);
                op_it != boost::end(it->operations);
                ++op_it, ++op_index)
            {
                ring_identifier ring_id
                    (
                        op_it->seg_id.source_index,
                        op_it->seg_id.multi_index,
                        op_it->seg_id.ring_index
                    );
                map[ring_id]++;
            }
        }
    }
}



template
<
    typename GeometryOut, overlay_type Direction, bool ReverseOut,
    typename Geometry1, typename Geometry2,
    typename OutputIterator
>
inline OutputIterator return_if_one_input_is_empty(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out)
{
    typedef std::deque
        <
            typename geometry::ring_type<GeometryOut>::type
        > ring_container_type;

    typedef ring_properties<typename geometry::point_type<Geometry1>::type> properties;

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)  
#pragma warning(disable : 4127)  
#endif

    // Union: return either of them
    // Intersection: return nothing
    // Difference: return first of them
    if (Direction == overlay_intersection
        || (Direction == overlay_difference
            && geometry::num_points(geometry1) == 0))
    {
        return out;
    }

#if defined(_MSC_VER)
#pragma warning(pop)  
#endif


    std::map<ring_identifier, int> empty;
    std::map<ring_identifier, properties> all_of_one_of_them;

    select_rings<Direction>(geometry1, geometry2, empty, all_of_one_of_them, false);
    ring_container_type rings;
    assign_parents(geometry1, geometry2, rings, all_of_one_of_them);
    return add_rings<GeometryOut>(all_of_one_of_them, geometry1, geometry2, rings, out);
}

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(
                Geometry1 const& geometry1, Geometry2 const& geometry2,
                OutputIterator out,
                Strategy const& )
    {
        if (geometry::num_points(geometry1) == 0
            && geometry::num_points(geometry2) == 0)
        {
            return out;
        }

        if (geometry::num_points(geometry1) == 0
            || geometry::num_points(geometry2) == 0)
        {
            return return_if_one_input_is_empty
                <
                    GeometryOut, Direction, ReverseOut
                >(geometry1, geometry2, out);
        }

        typedef typename geometry::point_type<GeometryOut>::type point_type;
        typedef detail::overlay::traversal_turn_info<point_type> turn_info;
        typedef std::deque<turn_info> container_type;

        typedef std::deque
            <
                typename geometry::ring_type<GeometryOut>::type
            > ring_container_type;

        container_type turn_points;

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        boost::timer timer;
#endif

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "get turns" << std::endl;
#endif
        detail::get_turns::no_interrupt_policy policy;
        geometry::get_turns
            <
                Reverse1, Reverse2,
                detail::overlay::calculate_distance_policy
            >(geometry1, geometry2, turn_points, policy);

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "get_turns: " << timer.elapsed() << std::endl;
#endif

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "enrich" << std::endl;
#endif
        typename Strategy::side_strategy_type side_strategy;
        geometry::enrich_intersection_points<Reverse1, Reverse2>(turn_points,
                Direction == overlay_union
                    ? geometry::detail::overlay::operation_union
                    : geometry::detail::overlay::operation_intersection,
                    geometry1, geometry2,
                    side_strategy);

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "enrich_intersection_points: " << timer.elapsed() << std::endl;
#endif


#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "traverse" << std::endl;
#endif
        // Traverse through intersection/turn points and create rings of them.
        // Note that these rings are always in clockwise order, even in CCW polygons,
        // and are marked as "to be reversed" below
        ring_container_type rings;
        traverse<Reverse1, Reverse2, Geometry1, Geometry2>::apply
                (
                    geometry1, geometry2,
                    Direction == overlay_union
                        ? geometry::detail::overlay::operation_union
                        : geometry::detail::overlay::operation_intersection,
                    turn_points, rings
                );

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "traverse: " << timer.elapsed() << std::endl;
#endif


        std::map<ring_identifier, int> map;
        map_turns(map, turn_points);

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "map_turns: " << timer.elapsed() << std::endl;
#endif

        typedef ring_properties<typename geometry::point_type<GeometryOut>::type> properties;

        std::map<ring_identifier, properties> selected;
        select_rings<Direction>(geometry1, geometry2, map, selected, ! turn_points.empty());

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "select_rings: " << timer.elapsed() << std::endl;
#endif


        // Add rings created during traversal
        {
            ring_identifier id(2, 0, -1);
            for (typename boost::range_iterator<ring_container_type>::type
                    it = boost::begin(rings);
                    it != boost::end(rings);
                    ++it)
            {
                selected[id] = properties(*it, true);
                selected[id].reversed = ReverseOut;
                id.multi_index++;
            }
        }

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "add traversal rings: " << timer.elapsed() << std::endl;
#endif


        assign_parents(geometry1, geometry2, rings, selected);

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << "assign_parents: " << timer.elapsed() << std::endl;
#endif

        return add_rings<GeometryOut>(selected, geometry1, geometry2, rings, out);
    }


    inline ring_properties()
        : area(area_type())
        , within_code(-1)
        , reversed(false)
        , discarded(false)
        , parent_area(-1)
    {}


    template <typename RingOrBox>
    inline ring_properties(RingOrBox const& ring_or_box, bool midpoint)
        : within_code(-1)
        , reversed(false)
        , discarded(false)
        , parent_area(-1)
    {
        this->area = geometry::area(ring_or_box);
        geometry::point_on_border(this->point, ring_or_box, midpoint);
    }


    inline area_type get_area() const
    {
        return reversed ? -area : area;
    }


template <typename Range, typename Point>
inline void append_no_duplicates(Range& range, Point const& point, bool force = false)
{
    if (boost::size(range) == 0
        || force 
        || ! geometry::detail::equals::equals_point_point(*(boost::end(range)-1), point))
    {
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
        std::cout << "  add: ("
            << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
            << std::endl;
#endif
        geometry::append(range, point);
    }
}

    inline sort_in_cluster(TurnPoints const& turn_points
            , Geometry1 const& geometry1
            , Geometry2 const& geometry2
            , Strategy const& strategy)
        : m_turn_points(turn_points)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_strategy(strategy)
    {}

    template <typename P>
    static inline void overlap_info(P const& pi, P const& pj,
        P const& ri, P const& rj,
        P const& si, P const& sj,
        bool& pr_overlap, bool& ps_overlap, bool& rs_overlap)
    {
        // Determine how p/r and p/s are located.
        // One of them is coming from opposite direction.

        typedef strategy::intersection::relate_cartesian_segments
            <
                policies::relate::segments_intersection_points
                    <
                        segment_type,
                        segment_type,
                        segment_intersection_points<point_type>
                    >
            > policy;

        segment_type p(pi, pj);
        segment_type r(ri, rj);
        segment_type s(si, sj);

        // Get the intersection point (or two points)
        segment_intersection_points<point_type> pr = policy::apply(p, r);
        segment_intersection_points<point_type> ps = policy::apply(p, s);
        segment_intersection_points<point_type> rs = policy::apply(r, s);

        // Check on overlap
        pr_overlap = pr.count == 2;
        ps_overlap = ps.count == 2;
        rs_overlap = rs.count == 2;
    }

    inline void debug_consider(int, Indexed const& ,
            Indexed const& , std::string const& ,
            bool = true,
            std::string const& = "", bool = false
        ) const
    {}

    inline bool consider_ux_ux(Indexed const& left,
            Indexed const& right
            , std::string const& // header
        ) const
    {
        bool ret = left.index < right.index;

        // In combination of u/x, x/u: take first union, then blocked.
        // Solves #88, #61, #56, #80
        if (left.subject.operation == operation_union
            && right.subject.operation == operation_blocked)
        {
            ret = true;
        }
        else if (left.subject.operation == operation_blocked
            && right.subject.operation == operation_union)
        {
            ret = false;
        }
        else
        {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
            std::cout << "ux/ux unhandled" << std::endl;
#endif
        }

        //debug_consider(0, left, right, header, false, "-> return ", ret);

        return ret;
    }


    inline bool consider_iu_ux(Indexed const& left,
            Indexed const& right,
            int order // 1: iu first, -1: ux first
            , std::string const& // header
        ) const
    {
        bool ret = false;

        if (left.subject.operation == operation_union
            && right.subject.operation == operation_union)
        {
            ret = order == 1;
        }
        else if (left.subject.operation == operation_union
            && right.subject.operation == operation_blocked)
        {
            ret = true;
        }
        else if (right.subject.operation == operation_union
            && left.subject.operation == operation_blocked)
        {
            ret = false;
        }
        else if (left.subject.operation == operation_union)
        {
            ret = true;
        }
        else if (right.subject.operation == operation_union)
        {
            ret = false;
        }
        else
        {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
            // this still happens in the traverse.cpp test
            std::cout << " iu/ux unhandled" << std::endl;
#endif
            ret = order == 1;
        }

        //debug_consider(0, left, right, header, false, "-> return", ret);
        return ret;
    }


    inline bool consider_iu_ix(Indexed const& left,
            Indexed const& right,
            int order // 1: iu first, -1: ix first
            , std::string const& // header
        ) const
    {
        //debug_consider(order, left, right, header, false, "iu/ix");

        return left.subject.operation == operation_intersection
                && right.subject.operation == operation_intersection ? order == 1
            : left.subject.operation == operation_intersection ? false
            : right.subject.operation == operation_intersection ? true
            : order == 1;
    }


    inline bool consider_ix_ix(Indexed const& left, Indexed const& right
            , std::string const& // header
            ) const
    {
        // Take first intersection, then blocked.
        if (left.subject.operation == operation_intersection
            && right.subject.operation == operation_blocked)
        {
            return true;
        }
        else if (left.subject.operation == operation_blocked
            && right.subject.operation == operation_intersection)
        {
            return false;
        }

        // Default case, should not occur

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
        std::cout << "ix/ix unhandled" << std::endl;
#endif
        //debug_consider(0, left, right, header, false, "-> return", ret);

        return left.index < right.index;
    }



    inline bool consider_iu_iu(Indexed const& left, Indexed const& right,
                    std::string const& header) const
    {
        //debug_consider(0, left, right, header);

        // In general, order it like "union, intersection".
        if (left.subject.operation == operation_intersection
            && right.subject.operation == operation_union)
        {
            //debug_consider(0, left, right, header, false, "i,u", false);
            return false;
        }
        else if (left.subject.operation == operation_union
            && right.subject.operation == operation_intersection)
        {
            //debug_consider(0, left, right, header, false, "u,i", true);
            return true;
        }

        point_type pi, pj, ri, rj, si, sj;
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.seg_id,
            pi, pj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.other_id,
            ri, rj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            right.subject.other_id,
            si, sj);

        int const side_ri_p = m_strategy.apply(pi, pj, ri);
        int const side_si_p = m_strategy.apply(pi, pj, si);
        int const side_si_r = m_strategy.apply(ri, rj, si);

        // Both located at same side (#58, pie_21_7_21_0_3)
        if (side_ri_p * side_si_p == 1 && side_si_r != 0)
        {
            // Take the most left one
            if (left.subject.operation == operation_union
                && right.subject.operation == operation_union)
            {
                bool ret = side_si_r == 1;
                //debug_consider(0, left, right, header, false, "same side", ret);
                return ret;
            }
        }


        // Coming from opposite sides (#59, #99)
        if (side_ri_p * side_si_p == -1)
        {
            bool ret = false;

            {
                ret = side_ri_p == 1; // #100
                debug_consider(0, left, right, header, false, "opp.", ret);
                return ret;
            }
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
            std::cout << " iu/iu coming from opposite unhandled" << std::endl;
#endif
        }

        // We need EXTRA information here: are p/r/s overlapping?
        bool pr_ov = false, ps_ov = false, rs_ov = false;
        overlap_info(pi, pj, ri, rj, si, sj, pr_ov, ps_ov, rs_ov);

        // One coming from right (#83,#90)
        // One coming from left (#90, #94, #95)
        if (side_si_r != 0 && (side_ri_p != 0 || side_si_p != 0))
        {
            bool ret = false;

            if (pr_ov || ps_ov)
            {
                int r = side_ri_p != 0 ? side_ri_p : side_si_p;
                ret = r * side_si_r == 1;
            }
            else
            {
                ret = side_si_r == 1;
            }

            debug_consider(0, left, right, header, false, "left or right", ret);
            return ret;
        }

        // All aligned (#92, #96)
        if (side_ri_p == 0 && side_si_p == 0 && side_si_r == 0)
        {
            // One of them is coming from opposite direction.

            // Take the one NOT overlapping
            bool ret = false;
            bool found = false;
            if (pr_ov && ! ps_ov)
            {
                ret = true;
                found = true;
            }
            else if (!pr_ov && ps_ov)
            {
                ret = false;
                found = true;
            }

            debug_consider(0, left, right, header, false, "aligned", ret);
            if (found)
            {
                return ret;
            }
        }

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
        std::cout << " iu/iu unhandled" << std::endl;
        debug_consider(0, left, right, header, false, "unhandled", left.index < right.index);
#endif
        return left.index < right.index;
    }


    inline bool consider_ii(Indexed const& left, Indexed const& right,
                    std::string const& header) const
    {
        debug_consider(0, left, right, header);

        point_type pi, pj, ri, rj, si, sj;
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.seg_id,
            pi, pj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.other_id,
            ri, rj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            right.subject.other_id,
            si, sj);

        int const side_ri_p = m_strategy.apply(pi, pj, ri);
        int const side_si_p = m_strategy.apply(pi, pj, si);

        // Two other points are (mostly) lying both right of the considered segment
        // Take the most left one
        int const side_si_r = m_strategy.apply(ri, rj, si);
        if (side_ri_p == -1
            && side_si_p == -1
            && side_si_r != 0)
        {
            bool const ret = side_si_r != 1;
            return ret;
        }
        return left.index < right.index;
    }

    inline bool operator()(Indexed const& left, Indexed const& right) const
    {
        bool const default_order = left.index < right.index;

        if ((m_turn_points[left.index].discarded || left.discarded)
            && (m_turn_points[right.index].discarded || right.discarded))
        {
            return default_order;
        }
        else if (m_turn_points[left.index].discarded || left.discarded)
        {
            // Be careful to sort discarded first, then all others
            return true;
        }
        else if (m_turn_points[right.index].discarded || right.discarded)
        {
            // See above so return false here such that right (discarded)
            // is sorted before left (not discarded)
            return false;
        }
        else if (m_turn_points[left.index].combination(operation_blocked, operation_union)
                && m_turn_points[right.index].combination(operation_blocked, operation_union))
        {
            // ux/ux
            return consider_ux_ux(left, right, "ux/ux");
        }
        else if (m_turn_points[left.index].both(operation_union)
            && m_turn_points[right.index].both(operation_union))
        {
            // uu/uu, Order is arbitrary
            // Note: uu/uu is discarded now before so this point will
            //       not be reached.
            return default_order;
        }
        else if (m_turn_points[left.index].combination(operation_intersection, operation_union)
                && m_turn_points[right.index].combination(operation_intersection, operation_union))
        {
            return consider_iu_iu(left, right, "iu/iu");
        }
        else if (m_turn_points[left.index].combination(operation_intersection, operation_blocked)
                && m_turn_points[right.index].combination(operation_intersection, operation_blocked))
        {
            return consider_ix_ix(left, right, "ix/ix");
        }
        else if (m_turn_points[left.index].both(operation_intersection)
                && m_turn_points[right.index].both(operation_intersection))
        {
            return consider_ii(left, right, "ii/ii");
        }
        else  if (m_turn_points[left.index].combination(operation_union, operation_blocked)
                && m_turn_points[right.index].combination(operation_intersection, operation_union))
        {
            return consider_iu_ux(left, right, -1, "ux/iu");
        }
        else if (m_turn_points[left.index].combination(operation_intersection, operation_union)
                && m_turn_points[right.index].combination(operation_union, operation_blocked))
        {
            return consider_iu_ux(left, right, 1, "iu/ux");
        }
        else  if (m_turn_points[left.index].combination(operation_intersection, operation_blocked)
                && m_turn_points[right.index].combination(operation_intersection, operation_union))
        {
            return consider_iu_ix(left, right, 1, "ix/iu");
        }
        else if (m_turn_points[left.index].combination(operation_intersection, operation_union)
                && m_turn_points[right.index].combination(operation_intersection, operation_blocked))
        {
            return consider_iu_ix(left, right, -1, "iu/ix");
        }
        else if (m_turn_points[left.index].method != method_equal
            && m_turn_points[right.index].method == method_equal
            )
        {
            // If one of them was EQUAL or CONTINUES, it should always come first
            return false;
        }
        else if (m_turn_points[left.index].method == method_equal
            && m_turn_points[right.index].method != method_equal
            )
        {
            return true;
        }

        // Now we have no clue how to sort.

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
        std::cout << " Consider: " << operation_char(m_turn_points[left.index].operations[0].operation)
                << operation_char(m_turn_points[left.index].operations[1].operation)
                << "/" << operation_char(m_turn_points[right.index].operations[0].operation)
                << operation_char(m_turn_points[right.index].operations[1].operation)
                << " " << " Take " << left.index << " < " << right.index
                << std::endl;
#endif

        return default_order;
    }




template
<
    typename IndexType,
    typename Iterator,
    typename TurnPoints,
    typename Geometry1,
    typename Geometry2,
    typename Strategy
>
inline void inspect_cluster(Iterator begin_cluster, Iterator end_cluster,
            TurnPoints& turn_points,
            operation_type ,
            Geometry1 const& , Geometry2 const& ,
            Strategy const& )
{
    int count = 0;

    // Make an analysis about all occuring cases here.
    std::map<std::pair<operation_type, operation_type>, int> inspection;
    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        operation_type first = turn_points[it->index].operations[0].operation;
        operation_type second = turn_points[it->index].operations[1].operation;
        if (first > second)
        {
            std::swap(first, second);
        }
        inspection[std::make_pair(first, second)]++;
        count++;
    }


    bool keep_cc = false;

    // Decide about which is going to be discarded here.
    if (inspection[std::make_pair(operation_union, operation_union)] == 1
        && inspection[std::make_pair(operation_continue, operation_continue)] == 1)
    {
        // In case of uu/cc, discard the uu, that indicates a tangency and
        // inclusion would disturb the (e.g.) cc-cc-cc ordering
        // NOTE: uu is now discarded anyhow.
        keep_cc = true;
    }
    else if (count == 2
        && inspection[std::make_pair(operation_intersection, operation_intersection)] == 1
        && inspection[std::make_pair(operation_union, operation_intersection)] == 1)
    {
        // In case of ii/iu, discard the iu. The ii should always be visited,
        // Because (in case of not discarding iu) correctly ordering of ii/iu appears impossible
        for (Iterator it = begin_cluster; it != end_cluster; ++it)
        {
            if (turn_points[it->index].combination(operation_intersection, operation_union))
            {
                it->discarded = true;
            }
        }
    }

    // Discard any continue turn, unless it is the only thing left
    //    (necessary to avoid cc-only rings, all being discarded
    //    e.g. traversal case #75)
    int nd_count= 0, cc_count = 0;
    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        if (! it->discarded)
        {
            nd_count++;
            if (turn_points[it->index].both(operation_continue))
            {
                cc_count++;
            }
        }
    }

    if (nd_count == cc_count)
    {
        keep_cc = true;
    }

    if (! keep_cc)
    {
        for (Iterator it = begin_cluster; it != end_cluster; ++it)
        {
            if (turn_points[it->index].both(operation_continue))
            {
                it->discarded = true;
            }
        }
    }
}



template
<
    typename IndexType,
    bool Reverse1, bool Reverse2,
    typename Iterator,
    typename TurnPoints,
    typename Geometry1,
    typename Geometry2,
    typename Strategy
>
inline void handle_cluster(Iterator begin_cluster, Iterator end_cluster,
            TurnPoints& turn_points,
            operation_type for_operation,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            Strategy const& strategy)
{
    // First inspect and (possibly) discard rows
    inspect_cluster<IndexType>(begin_cluster, end_cluster, turn_points,
            for_operation, geometry1, geometry2, strategy);


    // Then sort this range (discard rows will be ordered first and will be removed in enrich_assign)
    std::sort(begin_cluster, end_cluster,
                sort_in_cluster
                    <
                        TurnPoints,
                        IndexType,
                        Geometry1, Geometry2,
                        Reverse1, Reverse2,
                        Strategy
                    >(turn_points, geometry1, geometry2, strategy));


#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    typedef typename IndexType::type operations_type;
    operations_type const& op = turn_points[begin_cluster->index].operations[begin_cluster->operation_index];
    std::cout << "Clustered points on equal distance " << op.enriched.distance << std::endl;
    std::cout << "->Indexes ";

    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        std::cout << " " << it->index;
    }
    std::cout << std::endl << "->Methods: ";
    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        std::cout << " " << method_char(turn_points[it->index].method);
    }
    std::cout << std::endl << "->Operations: ";
    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        std::cout << " " << operation_char(turn_points[it->index].operations[0].operation)
            << operation_char(turn_points[it->index].operations[1].operation);
    }
    std::cout << std::endl << "->Discarded: ";
    for (Iterator it = begin_cluster; it != end_cluster; ++it)
    {
        std::cout << " " << (it->discarded ? "true" : "false");
    }
    std::cout << std::endl;
        //<< "\tOn segments: "    << prev_op.seg_id  << " / "  << prev_op.other_id
        //<< " and "  << op.seg_id << " / " << op.other_id
        //<< geometry::distance(turn_points[prev->index].point, turn_points[it->index].point)
#endif

}


    inline meta_turn(int i, Turn const& t)
        : index(i), turn(&t)
    {
        handled[0] = false;
        handled[1] = false;
    }



template <typename MetaTurn>
inline void display(MetaTurn const& meta_turn, std::string const& reason = "")
{
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << meta_turn.index
        << "\tMethods: " << method_char(meta_turn.turn->method)
        << " operations: "  << operation_char(meta_turn.turn->operations[0].operation)
                << operation_char(meta_turn.turn->operations[1].operation)
        << " travels to " << meta_turn.turn->operations[0].enriched.travels_to_ip_index
        << " and " << meta_turn.turn->operations[1].enriched.travels_to_ip_index
        //<< " -> " << op_index
        << " " << reason
        << std::endl;
#endif
}



template <typename MetaTurns, typename MetaTurn>
inline void check_detailed(MetaTurns& meta_turns, MetaTurn const& meta_turn,
            int op_index, int cycle, int start, operation_type for_operation,
            bool& error)
{
    display(meta_turn);
    int const ip_index = meta_turn.turn->operations[op_index].enriched.travels_to_ip_index;
    if (ip_index >= 0)
    {
        bool found = false;

        if (ip_index == start)
        {
            display(meta_turns[ip_index], " FINISH");
            return;
        }

        // check on continuing, or on same-operation-on-same-geometry
        if (! meta_turns[ip_index].handled[op_index]
            && (meta_turns[ip_index].turn->operations[op_index].operation == operation_continue
                || meta_turns[ip_index].turn->operations[op_index].operation == for_operation)
            )
        {
            meta_turns[ip_index].handled[op_index] = true;
            check_detailed(meta_turns, meta_turns[ip_index], op_index, cycle, start, for_operation, error);
            found = true;
        }
        // check on other geometry
        if (! found)
        {
            int const other_index = 1 - op_index;
            if (! meta_turns[ip_index].handled[other_index]
                && meta_turns[ip_index].turn->operations[other_index].operation == for_operation)
            {
                meta_turns[ip_index].handled[other_index] = true;
                check_detailed(meta_turns, meta_turns[ip_index], other_index, cycle, start, for_operation, error);
                found = true;
            }
        }

        if (! found)
        {
            display(meta_turns[ip_index], " STOP");
            error = true;
#ifndef BOOST_GEOMETRY_DEBUG_ENRICH
            //std::cout << " STOP";
#endif
        }
    }
}



template <typename TurnPoints>
inline bool check_graph(TurnPoints& turn_points, operation_type for_operation)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;

    bool error = false;
    int index = 0;

    std::vector<meta_turn<turn_point_type> > meta_turns;
    for (typename boost::range_iterator<TurnPoints const>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it, ++index)
    {
        meta_turns.push_back(meta_turn<turn_point_type>(index, *it));
    }

    int cycle = 0;
    for (typename boost::range_iterator<std::vector<meta_turn<turn_point_type> > > ::type
            it = boost::begin(meta_turns);
         it != boost::end(meta_turns);
         ++it)
    {
        if (! (it->turn->blocked() || it->turn->is_discarded()))
        {
            for (int i = 0 ; i < 2; i++)
            {
                if (! it->handled[i]
                    && it->turn->operations[i].operation == for_operation)
                {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout << "CYCLE " << cycle << std::endl;
#endif
                    it->handled[i] = true;
                    check_detailed(meta_turns, *it, i, cycle++, it->index, for_operation, error);
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout <<" END CYCLE " << it->index << std::endl;
#endif
                }
            }
        }
    }
    return error;
}



    static inline std::string dir(int d)
    {
        return d == 0 ? "-" : (d == 1 ? "L" : d == -1 ? "R" : "#");
    }

    static inline std::string how_str(int h)
    {
        return h == 0 ? "-" : (h == 1 ? "A" : "D");
    }


    template <typename P>
    std::ostream& operator<<(std::ostream &os, turn_info<P> const& info)
    {
        typename geometry::coordinate_type<P>::type d = info.distance;
        os  << "\t"
            << " src " << info.seg_id.source_index
            << " seg " << info.seg_id.segment_index
            << " (// " << info.other_id.source_index
                << "." << info.other_id.segment_index << ")"
            << " how " << info.how
                << "[" << how_str(info.arrival)
                << " " << dir(info.direction)
                << (info.opposite ? " o" : "")
                << "]"
            << " sd "
                << dir(info.sides.get<0,0>())
                << dir(info.sides.get<0,1>())
                << dir(info.sides.get<1,0>())
                << dir(info.sides.get<1,1>())
            << " nxt seg " << info.travels_to_vertex_index
            << " , ip " << info.travels_to_ip_index
            << " , or " << info.next_ip_index
            << " dst " << double(d)
            << info.visit_state;
        if (info.flagged)
        {
            os << " FLAGGED";
        }
        return os;
    }


    inline indexed_turn_operation(int i, int oi, TurnOperation const& s)
        : index(i)
        , operation_index(oi)
        , discarded(false)
        , subject(s)
    {}

    inline bool operator()(IndexedTurnOperation const& operation) const
    {
        return operation.discarded;
    }

    inline sort_on_segment_and_distance(TurnPoints const& turn_points
            , Geometry1 const& geometry1
            , Geometry2 const& geometry2
            , Strategy const& strategy
            , bool* clustered)
        : m_turn_points(turn_points)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_strategy(strategy)
        , m_clustered(clustered)
    {
    }


    inline bool consider_relative_order(Indexed const& left,
                    Indexed const& right) const
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;
        point_type pi, pj, ri, rj, si, sj;

        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.seg_id,
            pi, pj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject.other_id,
            ri, rj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            right.subject.other_id,
            si, sj);

        int const order = get_relative_order
            <
                point_type
            >::apply(pi, pj,ri, rj, si, sj);
        //debug("r/o", order == -1);
        return order == -1;
    }

    inline bool operator()(Indexed const& left, Indexed const& right) const
    {
        segment_identifier const& sl = left.subject.seg_id;
        segment_identifier const& sr = right.subject.seg_id;

        if (sl == sr)
        {
            // Both left and right are located on the SAME segment.
            typedef typename geometry::coordinate_type<Geometry1>::type coordinate_type;
            coordinate_type diff = geometry::math::abs(left.subject.enriched.distance - right.subject.enriched.distance);
            if (diff < geometry::math::relaxed_epsilon<coordinate_type>(10))
            {
                // First check "real" intersection (crosses)
                // -> distance zero due to precision, solve it by sorting
                if (m_turn_points[left.index].method == method_crosses
                    && m_turn_points[right.index].method == method_crosses)
                {
                    return consider_relative_order(left, right);
                }

                // If that is not the case, cluster it later on.
                // Indicate that this is necessary.
                *m_clustered = true;

                return left.subject.enriched.distance < right.subject.enriched.distance;
            }
        }
        return sl == sr
            ? left.subject.enriched.distance < right.subject.enriched.distance
            : sl < sr;

    }



template<typename Turns, typename Operations>
inline void update_discarded(Turns& turn_points, Operations& operations)
{
    // Vice-versa, set discarded to true for discarded operations;
    // AND set discarded points to true
    for (typename boost::range_iterator<Operations>::type it = boost::begin(operations);
         it != boost::end(operations);
         ++it)
    {
        if (turn_points[it->index].discarded)
        {
            it->discarded = true;
        }
        else if (it->discarded)
        {
            turn_points[it->index].discarded = true;
        }
    }
}

template
<
    typename IndexType,
    bool Reverse1, bool Reverse2,
    typename Container,
    typename TurnPoints,
    typename Geometry1, typename Geometry2,
    typename Strategy
>
inline void enrich_sort(Container& operations,
            TurnPoints& turn_points,
            operation_type for_operation,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            Strategy const& strategy)
{
    typedef typename IndexType::type operations_type;

    bool clustered = false;
    std::sort(boost::begin(operations),
                boost::end(operations),
                sort_on_segment_and_distance
                    <
                        TurnPoints,
                        IndexType,
                        Geometry1, Geometry2,
                        Reverse1, Reverse2,
                        Strategy
                    >(turn_points, geometry1, geometry2, strategy, &clustered));

    // DONT'T discard xx / (for union) ix / ii / (for intersection) ux / uu here
    // It would give way to "lonely" ui turn points, traveling all
    // the way round. See #105

    if (clustered)
    {
        typedef typename boost::range_iterator<Container>::type nc_iterator;
        nc_iterator it = boost::begin(operations);
        nc_iterator begin_cluster = boost::end(operations);
        for (nc_iterator prev = it++;
            it != boost::end(operations);
            prev = it++)
        {
            operations_type& prev_op = turn_points[prev->index]
                .operations[prev->operation_index];
            operations_type& op = turn_points[it->index]
                .operations[it->operation_index];

            if (prev_op.seg_id == op.seg_id
                && (turn_points[prev->index].method != method_crosses
                    || turn_points[it->index].method != method_crosses)
                && geometry::math::equals(prev_op.enriched.distance,
                        op.enriched.distance))
            {
                if (begin_cluster == boost::end(operations))
                {
                    begin_cluster = prev;
                }
            }
            else if (begin_cluster != boost::end(operations))
            {
                handle_cluster<IndexType, Reverse1, Reverse2>(begin_cluster, it, turn_points,
                        for_operation, geometry1, geometry2, strategy);
                begin_cluster = boost::end(operations);
            }
        }
        if (begin_cluster != boost::end(operations))
        {
            handle_cluster<IndexType, Reverse1, Reverse2>(begin_cluster, it, turn_points,
                    for_operation, geometry1, geometry2, strategy);
        }
    }

    update_discarded(turn_points, operations);
}



template
<
    typename IndexType,
    typename Container,
    typename TurnPoints
>
inline void enrich_discard(Container& operations, TurnPoints& turn_points)
{
    update_discarded(turn_points, operations);

    // Then delete discarded operations from vector
    remove_discarded<IndexType> predicate;
    operations.erase(
            std::remove_if(boost::begin(operations),
                    boost::end(operations),
                    predicate),
            boost::end(operations));
}


template
<
    typename IndexType,
    typename Container,
    typename TurnPoints,
    typename Geometry1,
    typename Geometry2,
    typename Strategy
>
inline void enrich_assign(Container& operations,
            TurnPoints& turn_points,
            operation_type ,
            Geometry1 const& , Geometry2 const& ,
            Strategy const& )
{
    typedef typename IndexType::type operations_type;
    typedef typename boost::range_iterator<Container const>::type iterator_type;


    if (operations.size() > 0)
    {
        // Assign travel-to-vertex/ip index for each turning point.
        // Because IP's are circular, PREV starts at the very last one,
        // being assigned from the first one.
        // "next ip on same segment" should not be considered circular.
        bool first = true;
        iterator_type it = boost::begin(operations);
        for (iterator_type prev = it + (boost::size(operations) - 1);
             it != boost::end(operations);
             prev = it++)
        {
            operations_type& prev_op
                    = turn_points[prev->index].operations[prev->operation_index];
            operations_type& op
                    = turn_points[it->index].operations[it->operation_index];

            prev_op.enriched.travels_to_ip_index
                    = it->index;
            prev_op.enriched.travels_to_vertex_index
                    = it->subject.seg_id.segment_index;

            if (! first
                && prev_op.seg_id.segment_index == op.seg_id.segment_index)
            {
                prev_op.enriched.next_ip_index = it->index;
            }
            first = false;
        }
    }

    // DEBUG
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    {
        for (iterator_type it = boost::begin(operations);
             it != boost::end(operations);
             ++it)
        {
            operations_type& op = turn_points[it->index]
                .operations[it->operation_index];

            std::cout << it->index
                << " meth: " << method_char(turn_points[it->index].method)
                << " seg: " << op.seg_id
                << " dst: " << boost::numeric_cast<double>(op.enriched.distance)
                << " op: " << operation_char(turn_points[it->index].operations[0].operation)
                << operation_char(turn_points[it->index].operations[1].operation)
                << " dsc: " << (turn_points[it->index].discarded ? "T" : "F")
                << " ->vtx " << op.enriched.travels_to_vertex_index
                << " ->ip " << op.enriched.travels_to_ip_index
                << " ->nxt ip " << op.enriched.next_ip_index
                //<< " vis: " << visited_char(op.visited)
                << std::endl;
                ;
        }
    }
#endif
    // END DEBUG

}



template <typename IndexedType, typename TurnPoints, typename MappedVector>
inline void create_map(TurnPoints const& turn_points, MappedVector& mapped_vector)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;
    typedef typename turn_point_type::container_type container_type;

    int index = 0;
    for (typename boost::range_iterator<TurnPoints const>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it, ++index)
    {
        // Add operations on this ring, but skip discarded ones
        if (! it->discarded)
        {
            int op_index = 0;
            for (typename boost::range_iterator<container_type const>::type
                    op_it = boost::begin(it->operations);
                op_it != boost::end(it->operations);
                ++op_it, ++op_index)
            {
                // We should NOT skip blocked operations here
                // because they can be relevant for "the other side"
                // NOT if (op_it->operation != operation_blocked)

                ring_identifier ring_id
                    (
                        op_it->seg_id.source_index,
                        op_it->seg_id.multi_index,
                        op_it->seg_id.ring_index
                    );
                mapped_vector[ring_id].push_back
                    (
                        IndexedType(index, op_index, *op_it)
                    );
            }
        }
    }
}

template
<
    bool Reverse1, bool Reverse2,
    typename TurnPoints,
    typename Geometry1, typename Geometry2,
    typename Strategy
>
inline void enrich_intersection_points(TurnPoints& turn_points,
    detail::overlay::operation_type for_operation,
    Geometry1 const& geometry1, Geometry2 const& geometry2,
    Strategy const& strategy)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;
    typedef typename turn_point_type::turn_operation_type turn_operation_type;
    typedef detail::overlay::indexed_turn_operation
        <
            turn_operation_type
        > indexed_turn_operation;

    typedef std::map
        <
            ring_identifier,
            std::vector<indexed_turn_operation>
        > mapped_vector_type;

    // DISCARD ALL UU
    // #76 is the reason that this is necessary...
    // With uu, at all points there is the risk that rings are being traversed twice or more.
    // Without uu, all rings having only uu will be untouched and gathered by assemble
    for (typename boost::range_iterator<TurnPoints>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it)
    {
        if (it->both(detail::overlay::operation_union))
        {
            it->discarded = true;
        }
    }


    // Create a map of vectors of indexed operation-types to be able
    // to sort intersection points PER RING
    mapped_vector_type mapped_vector;

    detail::overlay::create_map<indexed_turn_operation>(turn_points, mapped_vector);


    // No const-iterator; contents of mapped copy is temporary,
    // and changed by enrich
    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-sort Ring "
        << mit->first << std::endl;
#endif
        detail::overlay::enrich_sort<indexed_turn_operation, Reverse1, Reverse2>(mit->second, turn_points, for_operation,
                    geometry1, geometry2, strategy);
    }

    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-discard Ring "
        << mit->first << std::endl;
#endif
        detail::overlay::enrich_discard<indexed_turn_operation>(mit->second, turn_points);
    }

    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-assign Ring "
        << mit->first << std::endl;
#endif
        detail::overlay::enrich_assign<indexed_turn_operation>(mit->second, turn_points, for_operation,
                    geometry1, geometry2, strategy);
    }

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    //detail::overlay::check_graph(turn_points, for_operation);
#endif

}

    inline turn_info_exception(char const method) 
    {
        message = "Boost.Geometry Turn exception: ";
        message += method;
    }


    virtual ~turn_info_exception() throw()
    {}


    virtual char const* what() const throw()
    {
        return message.c_str();
    }

    static inline bool opposite(int side1, int side2)
    {
        // We cannot state side1 == -side2, because 0 == -0
        // So either side1*side2==-1 or side1==-side2 && side1 != 0
        return side1 * side2 == -1;
    }

    static inline bool same(int side1, int side2)
    {
        return side1 * side2 == 1;
    }

    template <typename TurnInfo>
    static inline void both(TurnInfo& ti, operation_type const op)
    {
        ti.operations[0].operation = op;
        ti.operations[1].operation = op;
    }

    template <typename TurnInfo>
    static inline void ui_else_iu(bool condition, TurnInfo& ti)
    {
        ti.operations[0].operation = condition
                    ? operation_union : operation_intersection;
        ti.operations[1].operation = condition
                    ? operation_intersection : operation_union;
    }

    template <typename TurnInfo>
    static inline void uu_else_ii(bool condition, TurnInfo& ti)
    {
        both(ti, condition ? operation_union : operation_intersection);
    }

    template
    <
        int Index,
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& pi, Point1 const& pj, Point1 const& ,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        ti.method = method_touch_interior;
        geometry::convert(intersection_info.intersections[0], ti.point);

        // Both segments of q touch segment p somewhere in its interior
        // 1) We know: if q comes from LEFT or RIGHT
        // (i.e. dir_info.sides.get<Index,0>() == 1 or -1)
        // 2) Important is: if q_k goes to LEFT, RIGHT, COLLINEAR
        //    and, if LEFT/COLL, if it is lying LEFT or RIGHT w.r.t. q_i

        static int const index_p = Index;
        static int const index_q = 1 - Index;

        int const side_qi_p = dir_info.sides.template get<index_q, 0>();
        int const side_qk_p = SideStrategy::apply(pi, pj, qk);

        if (side_qi_p == -side_qk_p)
        {
            // Q crosses P from left->right or from right->left (test "ML1")
            // Union: folow P (left->right) or Q (right->left)
            // Intersection: other turn
            int index = side_qk_p == -1 ? index_p : index_q;
            ti.operations[index].operation = operation_union;
            ti.operations[1 - index].operation = operation_intersection;
            return;
        }

        int const side_qk_q = SideStrategy::apply(qi, qj, qk);

        if (side_qi_p == -1 && side_qk_p == -1 && side_qk_q == 1)
        {
            // Q turns left on the right side of P (test "MR3")
            // Both directions for "intersection"
            both(ti, operation_intersection);
        }
        else if (side_qi_p == 1 && side_qk_p == 1 && side_qk_q == -1)
        {
            // Q turns right on the left side of P (test "ML3")
            // Union: take both operation
            // Intersection: skip
            both(ti, operation_union);
        }
        else if (side_qi_p == side_qk_p && side_qi_p == side_qk_q)
        {
            // Q turns left on the left side of P (test "ML2")
            // or Q turns right on the right side of P (test "MR2")
            // Union: take left turn (Q if Q turns left, P if Q turns right)
            // Intersection: other turn
            int index = side_qk_q == 1 ? index_q : index_p;
            ti.operations[index].operation = operation_union;
            ti.operations[1 - index].operation = operation_intersection;
        }
        else if (side_qk_p == 0)
        {
            // Q intersects on interior of P and continues collinearly
            if (side_qk_q == side_qi_p)
            {
                // Collinearly in the same direction
                // (Q comes from left of P and turns left,
                //  OR Q comes from right of P and turns right)
                // Omit intersection point.
                // Union: just continue
                // Intersection: just continue
                both(ti, operation_continue);
            }
            else
            {
                // Opposite direction, which is never travelled.
                // If Q turns left, P continues for intersection
                // If Q turns right, P continues for union
                ti.operations[Index].operation = side_qk_q == 1
                    ? operation_intersection
                    : operation_union;
                ti.operations[1 - Index].operation = operation_blocked;
            }
        }
        else
        {
            // Should not occur!
            ti.method = method_error;
        }
    }

    static inline bool between(int side1, int side2, int turn)
    {
        return side1 == side2 && ! opposite(side1, turn);
    }



    template
    <
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        ti.method = method_touch;
        geometry::convert(intersection_info.intersections[0], ti.point);

        int const side_qi_p1 = dir_info.sides.template get<1, 0>();
        int const side_qk_p1 = SideStrategy::apply(pi, pj, qk);


        // If Qi and Qk are both at same side of Pi-Pj,
        // or collinear (so: not opposite sides)
        if (! opposite(side_qi_p1, side_qk_p1))
        {
            int const side_pk_q2 = SideStrategy::apply(qj, qk, pk);
            int const side_pk_p  = SideStrategy::apply(pi, pj, pk);
            int const side_qk_q  = SideStrategy::apply(qi, qj, qk);

            bool const both_continue = side_pk_p == 0 && side_qk_q == 0;
            bool const robustness_issue_in_continue = both_continue && side_pk_q2 != 0;

            bool const q_turns_left = side_qk_q == 1;
            bool const block_q = side_qk_p1 == 0
                        && ! same(side_qi_p1, side_qk_q)
                        && ! robustness_issue_in_continue
                        ;

            // If Pk at same side as Qi/Qk
            // (the "or" is for collinear case)
            // or Q is fully collinear && P turns not to left
            if (side_pk_p == side_qi_p1
                || side_pk_p == side_qk_p1
                || (side_qi_p1 == 0 && side_qk_p1 == 0 && side_pk_p != -1)
                )
            {
                // Collinear -> lines join, continue
                // (#BRL2)
                if (side_pk_q2 == 0 && ! block_q)
                {
                    both(ti, operation_continue);
                    return;
                }

                int const side_pk_q1 = SideStrategy::apply(qi, qj, pk);


                // Collinear opposite case -> block P
                // (#BRL4, #BLR8)
                if (side_pk_q1 == 0)
                {
                    ti.operations[0].operation = operation_blocked;
                    // Q turns right -> union (both independent),
                    // Q turns left -> intersection
                    ti.operations[1].operation = block_q ? operation_blocked
                        : q_turns_left ? operation_intersection
                        : operation_union;
                    return;
                }

                // Pk between Qi and Qk
                // (#BRL3, #BRL7)
                if (between(side_pk_q1, side_pk_q2, side_qk_q))
                {
                    ui_else_iu(q_turns_left, ti);
                    if (block_q)
                    {
                        ti.operations[1].operation = operation_blocked;
                    }
                    //block_second(block_q, ti);
                    return;
                }

                // Pk between Qk and P, so left of Qk (if Q turns right) and vv
                // (#BRL1)
                if (side_pk_q2 == -side_qk_q)
                {
                    ui_else_iu(! q_turns_left, ti);
                    return;
                }

                //
                // (#BRL5, #BRL9)
                if (side_pk_q1 == -side_qk_q)
                {
                    uu_else_ii(! q_turns_left, ti);
                    if (block_q)
                    {
                        ti.operations[1].operation = operation_blocked;
                    }
                    //block_second(block_q, ti);
                    return;
                }
            }
            else
            {
                // Pk at other side than Qi/Pk
                int const side_qk_q = SideStrategy::apply(qi, qj, qk);
                bool const q_turns_left = side_qk_q == 1;

                ti.operations[0].operation = q_turns_left
                            ? operation_intersection
                            : operation_union;
                ti.operations[1].operation = block_q
                            ? operation_blocked
                            : side_qi_p1 == 1 || side_qk_p1 == 1
                            ? operation_union
                            : operation_intersection;

                return;
            }
        }
        else
        {
            // From left to right or from right to left
            int const side_pk_p  = SideStrategy::apply(pi, pj, pk);
            bool const right_to_left = side_qk_p1 == 1;

            // If p turns into direction of qi (1,2)
            if (side_pk_p == side_qi_p1)
            {
                int const side_pk_q1 = SideStrategy::apply(qi, qj, pk);

                // Collinear opposite case -> block P
                if (side_pk_q1 == 0)
                {
                    ti.operations[0].operation = operation_blocked;
                    ti.operations[1].operation = right_to_left
                                ? operation_union : operation_intersection;
                    return;
                }

                if (side_pk_q1 == side_qk_p1)
                {
                    uu_else_ii(right_to_left, ti);
                    return;
                }
            }

            // If p turns into direction of qk (4,5)
            if (side_pk_p == side_qk_p1)
            {
                int const side_pk_q2 = SideStrategy::apply(qj, qk, pk);

                // Collinear case -> lines join, continue
                if (side_pk_q2 == 0)
                {
                    both(ti, operation_continue);
                    return;
                }
                if (side_pk_q2 == side_qk_p1)
                {
                    ui_else_iu(right_to_left, ti);
                    return;
                }
            }
            // otherwise (3)
            ui_else_iu(! right_to_left, ti);
            return;
        }

#ifdef BOOST_GEOMETRY_DEBUG_GET_TURNS
        // Normally a robustness issue.
        // TODO: more research if still occuring
        std::cout << "Not yet handled" << std::endl
            << "pi " << get<0>(pi) << " , " << get<1>(pi)
            << " pj " << get<0>(pj) << " , " << get<1>(pj)
            << " pk " << get<0>(pk) << " , " << get<1>(pk)
            << std::endl
            << "qi " << get<0>(qi) << " , " << get<1>(qi)
            << " qj " << get<0>(qj) << " , " << get<1>(qj)
            << " qk " << get<0>(qk) << " , " << get<1>(qk)
            << std::endl;
#endif

    }

    template
    <
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& , Point2 const& qj, Point2 const& qk,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& )
    {
        ti.method = method_equal;
        // Copy the SECOND intersection point
        geometry::convert(intersection_info.intersections[1], ti.point);

        int const side_pk_q2  = SideStrategy::apply(qj, qk, pk);
        int const side_pk_p = SideStrategy::apply(pi, pj, pk);
        int const side_qk_p = SideStrategy::apply(pi, pj, qk);

        // If pk is collinear with qj-qk, they continue collinearly.
        // This can be on either side of p1 (== q1), or collinear
        // The second condition checks if they do not continue
        // oppositely
        if (side_pk_q2 == 0 && side_pk_p == side_qk_p)
        {
            both(ti, operation_continue);
            return;
        }


        // If they turn to same side (not opposite sides)
        if (! opposite(side_pk_p, side_qk_p))
        {
            int const side_pk_q2 = SideStrategy::apply(qj, qk, pk);

            // If pk is left of q2 or collinear: p: union, q: intersection
            ui_else_iu(side_pk_q2 != -1, ti);
        }
        else
        {
            // They turn opposite sides. If p turns left (or collinear),
            // p: union, q: intersection
            ui_else_iu(side_pk_p != -1, ti);
        }
    }

    template
    <
        typename Point1,
        typename Point2,
        typename OutputIterator,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(Point1 const& pi, Point2 const& qi,
                /* by value: */ TurnInfo tp,
                OutputIterator& out,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        // For equal-opposite segments, normally don't do anything.
        if (AssignPolicy::include_opposite)
        {
            tp.method = method_equal;
            for (int i = 0; i < 2; i++)
            {
                tp.operations[i].operation = operation_opposite;
            }
            for (unsigned int i = 0; i < intersection_info.count; i++)
            {
                geometry::convert(intersection_info.intersections[i], tp.point);
                AssignPolicy::apply(tp, pi, qi, intersection_info, dir_info);
                *out++ = tp;
            }
        }
    }

    template
    <
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        ti.method = method_collinear;
        geometry::convert(intersection_info.intersections[1], ti.point);

        int const arrival = dir_info.arrival[0];
        // Should not be 0, this is checked before
        BOOST_ASSERT(arrival != 0);

        int const side_p = SideStrategy::apply(pi, pj, pk);
        int const side_q = SideStrategy::apply(qi, qj, qk);

        // If p arrives, use p, else use q
        int const side_p_or_q = arrival == 1
            ? side_p
            : side_q
            ;

        int const side_pk = SideStrategy::apply(qi, qj, pk);
        int const side_qk = SideStrategy::apply(pi, pj, qk);

        // See comments above,
        // resulting in a strange sort of mathematic rule here:
        // The arrival-info multiplied by the relevant side
        // delivers a consistent result.

        int const product = arrival * side_p_or_q;

        // Robustness: side_p is supposed to be equal to side_pk (because p/q are collinear)
        // and side_q to side_qk
        bool const robustness_issue = side_pk != side_p || side_qk != side_q;

        if (robustness_issue)
        {
            handle_robustness(ti, arrival, side_p, side_q, side_pk, side_qk);
        }
        else if(product == 0)
        {
            both(ti, operation_continue);
        }
        else
        {
            ui_else_iu(product == 1, ti);
        }
    }


    static inline void handle_robustness(TurnInfo& ti, int arrival, 
                    int side_p, int side_q, int side_pk, int side_qk)
    {
        // We take the longer one, i.e. if q arrives in p (arrival == -1),
        // then p exceeds q and we should take p for a union...

        bool use_p_for_union = arrival == -1;

        // ... unless one of the sides consistently directs to the other side
        int const consistent_side_p = side_p == side_pk ? side_p : 0;
        int const consistent_side_q = side_q == side_qk ? side_q : 0;
        if (arrival == -1 && (consistent_side_p == -1 || consistent_side_q == 1))
        {
            use_p_for_union = false;
        }
        if (arrival == 1 && (consistent_side_p == 1 || consistent_side_q == -1))
        {
            use_p_for_union = true;
        }

        //std::cout << "ROBUSTNESS -> Collinear " 
        //    << " arr: " << arrival
        //    << " dir: " << side_p << " " << side_q
        //    << " rev: " << side_pk << " " << side_qk
        //    << " cst: " << cside_p << " " << cside_q
        //    << std::boolalpha << " " << use_p_for_union
        //    << std::endl;

        ui_else_iu(use_p_for_union, ti);
    }


    template
    <
        int Index,
        typename Point,
        typename IntersectionInfo
    >
    static inline bool set_tp(Point const& ri, Point const& rj, Point const& rk,
                bool const handle_robustness, Point const& si, Point const& sj,
                TurnInfo& tp, IntersectionInfo const& intersection_info)
    {
        int side_rk_r = SideStrategy::apply(ri, rj, rk);

        if (handle_robustness)
        {
            int const side_rk_s = SideStrategy::apply(si, sj, rk);

            // For Robustness: also calculate rk w.r.t. the other line. Because they are collinear opposite, that direction should be the reverse of the first direction.
            // If this is not the case, we make it all-collinear, so zero
            if (side_rk_r != 0 && side_rk_r != -side_rk_s)
            {
#ifdef BOOST_GEOMETRY_DEBUG_ROBUSTNESS
                std::cout << "Robustness correction: " << side_rk_r << " / " << side_rk_s << std::endl;
#endif
                side_rk_r = 0;
            }
        }

        operation_type blocked = operation_blocked;
        switch(side_rk_r)
        {

            case 1 :
                // Turning left on opposite collinear: intersection
                tp.operations[Index].operation = operation_intersection;
                break;
            case -1 :
                // Turning right on opposite collinear: union
                tp.operations[Index].operation = operation_union;
                break;
            case 0 :
                // No turn on opposite collinear: block, do not traverse
                // But this "xx" is usually ignored, it is useless to include
                // two operations blocked, so the whole point does not need
                // to be generated.
                // So return false to indicate nothing is to be done.
                if (AssignPolicy::include_opposite)
                {
                    tp.operations[Index].operation = operation_opposite;
                    blocked = operation_opposite;
                }
                else
                {
                    return false;
                }
                break;
        }

        // The other direction is always blocked when collinear opposite
        tp.operations[1 - Index].operation = blocked;

        // If P arrives within Q, set info on P (which is done above, index=0),
        // this turn-info belongs to the second intersection point, index=1
        // (see e.g. figure CLO1)
        geometry::convert(intersection_info.intersections[1 - Index], tp.point);
        return true;
    }

    template
    <
        typename Point1,
        typename Point2,
        typename OutputIterator,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,

                // Opposite collinear can deliver 2 intersection points,
                TurnInfo const& tp_model,
                OutputIterator& out,

                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        TurnInfo tp = tp_model;

        tp.method = method_collinear;

        // If P arrives within Q, there is a turn dependent on P
        if (dir_info.arrival[0] == 1
            && set_tp<0>(pi, pj, pk, true, qi, qj, tp, intersection_info))
        {
            AssignPolicy::apply(tp, pi, qi, intersection_info, dir_info);
            *out++ = tp;
        }

        // If Q arrives within P, there is a turn dependent on Q
        if (dir_info.arrival[1] == 1
            && set_tp<1>(qi, qj, qk, false, pi, pj, tp, intersection_info))
        {
            AssignPolicy::apply(tp, pi, qi, intersection_info, dir_info);
            *out++ = tp;
        }

        if (AssignPolicy::include_opposite)
        {
            // Handle cases not yet handled above
            if ((dir_info.arrival[1] == -1 && dir_info.arrival[0] == 0)
                || (dir_info.arrival[0] == -1 && dir_info.arrival[1] == 0))
            {
                for (int i = 0; i < 2; i++)
                {
                    tp.operations[i].operation = operation_opposite;
                }
                for (unsigned int i = 0; i < intersection_info.count; i++)
                {
                    geometry::convert(intersection_info.intersections[i], tp.point);
                    AssignPolicy::apply(tp, pi, qi, intersection_info, dir_info);
                    *out++ = tp;
                }
            }
        }

    }

    template
    <
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(
                Point1 const& , Point1 const& , Point1 const& ,
                Point2 const& , Point2 const& , Point2 const& ,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        ti.method = method_crosses;
        geometry::convert(intersection_info.intersections[0], ti.point);

        // In all casees:
        // If Q crosses P from left to right
        // Union: take P
        // Intersection: take Q
        // Otherwise: vice versa
        int const side_qi_p1 = dir_info.sides.template get<1, 0>();
        int const index = side_qi_p1 == 1 ? 0 : 1;
        ti.operations[index].operation = operation_union;
        ti.operations[1 - index].operation = operation_intersection;
    }

    template<typename IntersectionInfo>
    static inline void apply(TurnInfo& ti, IntersectionInfo const& intersection_info)
    {
        ti.method = method_collinear;
        geometry::convert(intersection_info.intersections[0], ti.point);
        ti.operations[0].operation = operation_continue;
        ti.operations[1].operation = operation_continue;
    }


    template 
    <
        typename Info,
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(Info& , Point1 const& , Point2 const&, IntersectionInfo const&, DirInfo const&)
    {}

    template <typename OutputIterator>
    static inline OutputIterator apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,
                TurnInfo const& tp_model,
                OutputIterator out)
    {
        typedef model::referring_segment<Point1 const> segment_type1;
        typedef model::referring_segment<Point1 const> segment_type2;
        segment_type1 p1(pi, pj), p2(pj, pk);
        segment_type2 q1(qi, qj), q2(qj, qk);

        typename strategy::return_type result = strategy::apply(p1, q1);

        char const method = result.template get<1>().how;

        // Copy, to copy possibly extended fields
        TurnInfo tp = tp_model;


        // Select method and apply
        switch(method)
        {
            case 'a' : // collinear, "at"
            case 'f' : // collinear, "from"
            case 's' : // starts from the middle
                if (AssignPolicy::include_no_turn
                    && result.template get<0>().count > 0)
                {
                    only_convert<TurnInfo>::apply(tp,
                                result.template get<0>());
                    AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                    *out++ = tp;
                }
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                typedef touch_interior
                    <
                        TurnInfo,
                        typename si::side_strategy_type
                    > policy;

                // If Q (1) arrives (1)
                if (result.template get<1>().arrival[1] == 1)
                {
                    policy::template apply<0>(pi, pj, pk, qi, qj, qk,
                                tp, result.template get<0>(), result.template get<1>());
                }
                else
                {
                    // Swap p/q
                    policy::template apply<1>(qi, qj, qk, pi, pj, pk,
                                tp, result.template get<0>(), result.template get<1>());
                }
                AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                *out++ = tp;
            }
            break;
            case 'i' :
            {
                typedef crosses
                    <
                        TurnInfo,
                        typename si::side_strategy_type
                    > policy;

                policy::apply(pi, pj, pk, qi, qj, qk,
                    tp, result.template get<0>(), result.template get<1>());
                AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                *out++ = tp;
            }
            break;
            case 't' :
            {
                // Both touch (both arrive there)
                typedef touch
                    <
                        TurnInfo,
                        typename si::side_strategy_type
                    > policy;

                policy::apply(pi, pj, pk, qi, qj, qk,
                    tp, result.template get<0>(), result.template get<1>());
                AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                *out++ = tp;
            }
            break;
            case 'e':
            {
                if (! result.template get<1>().opposite)
                {
                    // Both equal
                    // or collinear-and-ending at intersection point
                    typedef equal
                        <
                            TurnInfo,
                            typename si::side_strategy_type
                        > policy;

                    policy::apply(pi, pj, pk, qi, qj, qk,
                        tp, result.template get<0>(), result.template get<1>());
                    AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                    *out++ = tp;
                }
                else
                {
                    equal_opposite
                        <
                            TurnInfo,
                            AssignPolicy
                        >::apply(pi, qi,
                            tp, out, result.template get<0>(), result.template get<1>());
                }
            }
            break;
            case 'c' :
            {
                // Collinear
                if (! result.template get<1>().opposite)
                {

                    if (result.template get<1>().arrival[0] == 0)
                    {
                        // Collinear, but similar thus handled as equal
                        equal
                            <
                                TurnInfo,
                                typename si::side_strategy_type
                            >::apply(pi, pj, pk, qi, qj, qk,
                                tp, result.template get<0>(), result.template get<1>());

                        // override assigned method
                        tp.method = method_collinear;
                    }
                    else
                    {
                        collinear
                            <
                                TurnInfo,
                                typename si::side_strategy_type
                            >::apply(pi, pj, pk, qi, qj, qk,
                                tp, result.template get<0>(), result.template get<1>());
                    }

                    AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                    *out++ = tp;
                }
                else
                {
                    collinear_opposite
                        <
                            TurnInfo,
                            typename si::side_strategy_type,
                            AssignPolicy
                        >::apply(pi, pj, pk, qi, qj, qk,
                            tp, out, result.template get<0>(), result.template get<1>());
                }
            }
            break;
            case '0' :
            {
                // degenerate points
                if (AssignPolicy::include_degenerate)
                {
                    only_convert<TurnInfo>::apply(tp, result.template get<0>());
                    AssignPolicy::apply(tp, pi, qi, result.template get<0>(), result.template get<1>());
                    *out++ = tp;
                }
            }
            break;
            default :
            {
#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
                throw turn_info_exception(method);
#endif
            }
            break;
        }

        return out;
    }

    inline visit_info()
        : m_visit_code(0)
        , m_rejected(false)
    {}


    inline void set_visited() { m_visit_code = VISITED; }

    inline void set_started() { m_visit_code = STARTED; }

    inline void set_finished() { m_visit_code = FINISHED; }

    inline void set_rejected()
    {
        m_visit_code = REJECTED;
        m_rejected = true;
    }


    inline bool none() const { return m_visit_code == NONE; }

    inline bool visited() const { return m_visit_code == VISITED; }

    inline bool started() const { return m_visit_code == STARTED; }

    inline bool finished() const { return m_visit_code == FINISHED; }

    inline bool rejected() const { return m_rejected; }


    inline void clear()
    {
        if (! rejected())
        {
            m_visit_code = NONE;
        }
    }


    template <typename Point>
    static inline int value_via_product(Point const& ti, Point const& tj,
                    Point const& ui, Point const& uj, int factor)
    {
        int const side_ti_u = strategy::apply(ti, tj, ui);
        int const side_tj_u = strategy::apply(ti, tj, uj);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout << (factor == 1  ? " r//s " :  " s//r ")
            << side_ti_u << " / " << side_tj_u;
#endif

        return side_ti_u * side_tj_u >= 0
            ? factor * (side_ti_u != 0 ? side_ti_u : side_tj_u)
            : 0;
    }



    static inline int apply(
                Point1 const& pi, Point1 const& pj,
                Point1 const& ri, Point1 const& rj,
                Point1 const& si, Point1 const& sj)
    {
        int const side_ri_p = strategy::apply(pi, pj, ri);
        int const side_si_p = strategy::apply(pi, pj, si);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        int const side_rj_p = strategy::apply(pi, pj, rj);
        int const side_sj_p = strategy::apply(pi, pj, sj);
        std::cout << "r//p: " << side_ri_p << " / " << side_rj_p;
        std::cout << " s//p: " << side_si_p << " / " << side_sj_p;
#endif

        int value = value_via_product(si, sj, ri, rj, 1);
        if (value == 0)
        {
            value = value_via_product(ri, rj, si, sj, -1);
        }

        int const order = side_ri_p * side_ri_p * side_si_p * value;

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout
            << " o: " << order
            << std::endl << std::endl;
#endif

        return order;
    }


    inline turn_operation()
        : operation(operation_none)
    {}


template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename RingCollection
>
inline void convert_and_add(GeometryOut& result,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingCollection const& collection,
            ring_identifier id,
            bool reversed, bool append)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;
    typedef typename geometry::tag<GeometryOut>::type tag_out;

    if (id.source_index == 0)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<tag1>::apply(id, geometry1),
                    append, reversed);
    }
    else if (id.source_index == 1)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<tag2>::apply(id, geometry2),
                    append, reversed);
    }
    else if (id.source_index == 2)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<void>::apply(id, collection),
                    append, reversed);
    }
}


template
<
    typename GeometryOut,
    typename SelectionMap,
    typename Geometry1,
    typename Geometry2,
    typename RingCollection,
    typename OutputIterator
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingCollection const& collection,
            OutputIterator out)
{
    typedef typename SelectionMap::const_iterator iterator;
    typedef typename SelectionMap::mapped_type property_type;
    typedef typename property_type::area_type area_type;

    area_type const zero = 0;
    std::size_t const min_num_points = core_detail::closure::minimum_ring_size
        <
            geometry::closure
                <
                    typename boost::range_value
                        <
                            RingCollection const
                        >::type
                >::value
        >::value;


    for (iterator it = boost::begin(map);
        it != boost::end(map);
        ++it)
    {
        if (! it->second.discarded
            && it->second.parent.source_index == -1)
        {
            GeometryOut result;
            convert_and_add(result, geometry1, geometry2, collection,
                    it->first, it->second.reversed, false);

            // Add children
            for (typename std::vector<ring_identifier>::const_iterator child_it
                        = it->second.children.begin();
                child_it != it->second.children.end();
                ++child_it)
            {
                iterator mit = map.find(*child_it);
                if (mit != map.end()
                    && ! mit->second.discarded)
                {
                    convert_and_add(result, geometry1, geometry2, collection,
                            *child_it, mit->second.reversed, true);
                }
            }

            // Only add rings if they satisfy minimal requirements.
            // This cannot be done earlier (during traversal), not
            // everything is figured out yet (sum of positive/negative rings)
            if (geometry::num_points(result) >= min_num_points
                && math::larger(geometry::area(result), zero))
            {
                *out++ = result;
            }
        }
    }
    return out;
}



template
<
    typename GeometryOut,
    typename SelectionMap,
    typename Geometry,
    typename RingCollection,
    typename OutputIterator
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry const& geometry,
            RingCollection const& collection,
            OutputIterator out)
{
    Geometry empty;
    return add_rings<GeometryOut>(map, geometry, empty, collection, out);
}


template <typename Turn, typename Operation>
#ifdef BOOST_GEOMETRY_DEBUG_TRAVERSE
inline void debug_traverse(Turn const& turn, Operation op, 
                std::string const& header)
{
    std::cout << header
        << " at " << op.seg_id
        << " meth: " << method_char(turn.method)
        << " op: " << operation_char(op.operation)
        << " vis: " << visited_char(op.visited)
        << " of:  " << operation_char(turn.operations[0].operation)
        << operation_char(turn.operations[1].operation)
        << " " << geometry::wkt(turn.point)
        << std::endl;

    if (boost::contains(header, "Finished"))
    {
        std::cout << std::endl;
    }
}
#else
inline void debug_traverse(Turn const& , Operation, const char*)
{
}



template <typename Info, typename Turn>
inline void set_visited_for_continue(Info& info, Turn const& turn)
{
    // On "continue", set "visited" for ALL directions
    if (turn.operation == detail::overlay::operation_continue)
    {
        for (typename boost::range_iterator
            <
                typename Info::container_type
            >::type it = boost::begin(info.operations);
            it != boost::end(info.operations);
            ++it)
        {
            if (it->visited.none())
            {
                it->visited.set_visited();
            }
        }
    }
}



template
<
    bool Reverse1, bool Reverse2,
    typename GeometryOut,
    typename G1,
    typename G2,
    typename Turns,
    typename IntersectionInfo
>
inline bool assign_next_ip(G1 const& g1, G2 const& g2,
            Turns& turns,
            typename boost::range_iterator<Turns>::type& ip,
            GeometryOut& current_output,
            IntersectionInfo& info,
            segment_identifier& seg_id)
{
    info.visited.set_visited();
    set_visited_for_continue(*ip, info);

    // If there is no next IP on this segment
    if (info.enriched.next_ip_index < 0)
    {
        if (info.enriched.travels_to_vertex_index < 0 
            || info.enriched.travels_to_ip_index < 0)
        {
            return false;
        }

        BOOST_ASSERT(info.enriched.travels_to_vertex_index >= 0);
        BOOST_ASSERT(info.enriched.travels_to_ip_index >= 0);

        if (info.seg_id.source_index == 0)
        {
            geometry::copy_segments<Reverse1>(g1, info.seg_id,
                    info.enriched.travels_to_vertex_index,
                    current_output);
        }
        else
        {
            geometry::copy_segments<Reverse2>(g2, info.seg_id,
                    info.enriched.travels_to_vertex_index,
                    current_output);
        }
        seg_id = info.seg_id;
        ip = boost::begin(turns) + info.enriched.travels_to_ip_index;
    }
    else
    {
        ip = boost::begin(turns) + info.enriched.next_ip_index;
        seg_id = info.seg_id;
    }

    detail::overlay::append_no_duplicates(current_output, ip->point);
    return true;
}



inline bool select_source(operation_type operation, int source1, int source2)
{
    return (operation == operation_intersection && source1 != source2)
        || (operation == operation_union && source1 == source2)
        ;
}



template
<
    typename Turn,
    typename Iterator
>
inline bool select_next_ip(operation_type operation,
            Turn& turn,
            segment_identifier const& seg_id,
            Iterator& selected)
{
    if (turn.discarded)
    {
        return false;
    }
    bool has_tp = false;
    selected = boost::end(turn.operations);
    for (Iterator it = boost::begin(turn.operations);
        it != boost::end(turn.operations);
        ++it)
    {
        if (it->visited.started())
        {
            selected = it;
            //std::cout << " RETURN";
            return true;
        }

        // In some cases there are two alternatives.
        // For "ii", take the other one (alternate)
        //           UNLESS the other one is already visited
        // For "uu", take the same one (see above);
        // For "cc", take either one, but if there is a starting one,
        //           take that one.
        if (   (it->operation == operation_continue
                && (! has_tp || it->visited.started()
                    )
                )
            || (it->operation == operation
                && ! it->visited.finished()
                && (! has_tp
                    || select_source(operation,
                            it->seg_id.source_index, seg_id.source_index)
                    )
                )
            )
        {
            selected = it;
            debug_traverse(turn, *it, " Candidate");
            has_tp = true;
        }
    }

    if (has_tp)
    {
       debug_traverse(turn, *selected, "  Accepted");
    }


    return has_tp;
}


    template <typename T>
    inline bool check_edge(T const& p, T const& q, T& t1, T& t2) const
    {
        bool visible = true;

        if(p < 0)
        {
            T const r = q / p;
            if (r > t2)
                visible = false;
            else if (r > t1)
                t1 = r;
        }
        else if(p > 0)
        {
            T const r = q / p;
            if (r < t1)
                visible = false;
            else if (r < t2)
                t2 = r;
        }
        else
        {
            if (q < 0)
                visible = false;
        }

        return visible;
    }


    inline bool clip_segment(Box const& b, segment_type& s, bool& sp1_clipped, bool& sp2_clipped) const
    {
        typedef typename select_coordinate_type<Box, Point>::type coordinate_type;

        coordinate_type t1 = 0;
        coordinate_type t2 = 1;

        coordinate_type const dx = get<1, 0>(s) - get<0, 0>(s);
        coordinate_type const dy = get<1, 1>(s) - get<0, 1>(s);

        coordinate_type const p1 = -dx;
        coordinate_type const p2 = dx;
        coordinate_type const p3 = -dy;
        coordinate_type const p4 = dy;

        coordinate_type const q1 = get<0, 0>(s) - get<min_corner, 0>(b);
        coordinate_type const q2 = get<max_corner, 0>(b) - get<0, 0>(s);
        coordinate_type const q3 = get<0, 1>(s) - get<min_corner, 1>(b);
        coordinate_type const q4 = get<max_corner, 1>(b) - get<0, 1>(s);

        if (check_edge(p1, q1, t1, t2)      // left
            && check_edge(p2, q2, t1, t2)   // right
            && check_edge(p3, q3, t1, t2)   // bottom
            && check_edge(p4, q4, t1, t2))   // top
        {
            sp1_clipped = t1 > 0;
            sp2_clipped = t2 < 1;

            if (sp2_clipped)
            {
                set<1, 0>(s, get<0, 0>(s) + t2 * dx);
                set<1, 1>(s, get<0, 1>(s) + t2 * dy);
            }

            if(sp1_clipped)
            {
                set<0, 0>(s, get<0, 0>(s) + t1 * dx);
                set<0, 1>(s, get<0, 1>(s) + t1 * dy);
            }

            return true;
        }

        return false;
    }


    template<typename Linestring, typename OutputIterator>
    inline void apply(Linestring& line_out, OutputIterator out) const
    {
        if (!boost::empty(line_out))
        {
            *out = line_out;
            ++out;
            geometry::clear(line_out);
        }
    }

template
<
    typename OutputLinestring,
    typename OutputIterator,
    typename Range,
    typename Box,
    typename Strategy
>
OutputIterator clip_range_with_box(Box const& b, Range const& range,
            OutputIterator out, Strategy const& strategy)
{
    if (boost::begin(range) == boost::end(range))
    {
        return out;
    }

    typedef typename point_type<OutputLinestring>::type point_type;

    OutputLinestring line_out;

    typedef typename boost::range_iterator<Range const>::type iterator_type;
    iterator_type vertex = boost::begin(range);
    for(iterator_type previous = vertex++;
            vertex != boost::end(range);
            ++previous, ++vertex)
    {
        point_type p1, p2;
        geometry::convert(*previous, p1);
        geometry::convert(*vertex, p2);

        // Clip the segment. Five situations:
        // 1. Segment is invisible, finish line if any (shouldn't occur)
        // 2. Segment is completely visible. Add (p1)-p2 to line
        // 3. Point 1 is invisible (clipped), point 2 is visible. Start new line from p1-p2...
        // 4. Point 1 is visible, point 2 is invisible (clipped). End the line with ...p2
        // 5. Point 1 and point 2 are both invisible (clipped). Start/finish an independant line p1-p2
        //
        // This results in:
        // a. if p1 is clipped, start new line
        // b. if segment is partly or completely visible, add the segment
        // c. if p2 is clipped, end the line

        bool c1 = false;
        bool c2 = false;
        model::referring_segment<point_type> s(p1, p2);

        if (!strategy.clip_segment(b, s, c1, c2))
        {
            strategy.apply(line_out, out);
        }
        else
        {
            // a. If necessary, finish the line and add a start a new one
            if (c1)
            {
                strategy.apply(line_out, out);
            }

            // b. Add p1 only if it is the first point, then add p2
            if (boost::empty(line_out))
            {
                detail::overlay::append_no_duplicates(line_out, p1, true);
            }
            detail::overlay::append_no_duplicates(line_out, p2);

            // c. If c2 is clipped, finish the line
            if (c2)
            {
                strategy.apply(line_out, out);
            }
        }

    }

    // Add last part
    strategy.apply(line_out, out);
    return out;
}


template <typename Turns>
inline void clear_visit_info(Turns& turns)
{
    typedef typename boost::range_value<Turns>::type tp_type;

    for (typename boost::range_iterator<Turns>::type
        it = boost::begin(turns);
        it != boost::end(turns);
        ++it)
    {
        for (typename boost::range_iterator
            <
                typename tp_type::container_type
            >::type op_it = boost::begin(it->operations);
            op_it != boost::end(it->operations);
            ++op_it)
        {
            op_it->visited.clear();
        }
        it->discarded = false;
    }
}

    
    inline backtrack_state() : m_good(true) {}
         
    inline void reset() { m_good = true; }

    inline bool good() const { return m_good; }

        inline state()
            : m_checked()
        {}


    template <typename Operation, typename Rings, typename Turns>
    static inline void apply(std::size_t size_at_start, 
                Rings& rings, typename boost::range_value<Rings>::type& ring,
                Turns& turns, Operation& operation,
                std::string const& ,
                Geometry1 const& geometry1,
                Geometry2 const& geometry2,
                state_type& state
                )
    {
        state.m_good = false;
        
        // Check self-intersections and throw exception if appropriate
        if (! state.m_checked)
        {
            state.m_checked = true;
            has_self_intersections(geometry1);
            has_self_intersections(geometry2);
        }

        // Make bad output clean
        rings.resize(size_at_start);
        ring.clear();

        // Reject this as a starting point
        operation.visited.set_rejected();

        // And clear all visit info
        clear_visit_info(turns);
    }


    static inline void apply(Ring const& ring,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& current_output)
    {
        cview_type cview(ring);
        rview_type view(cview);

        // The problem: sometimes we want to from "3" to "2"
        // -> end = "3" -> end == begin
        // This is not convenient with iterators.

        // So we use the ever-circling iterator and determine when to step out

        int const from_index = seg_id.segment_index + 1;

        // Sanity check
        BOOST_ASSERT(from_index < int(boost::size(view)));

        ec_iterator it(boost::begin(view), boost::end(view),
                    boost::begin(view) + from_index);

        // [2..4] -> 4 - 2 + 1 = 3 -> {2,3,4} -> OK
        // [4..2],size=6 -> 6 - 4 + 2 + 1 = 5 -> {4,5,0,1,2} -> OK
        // [1..1], travel the whole ring round
        typedef typename boost::range_difference<Ring>::type size_type;
        size_type const count = from_index <= to_index
            ? to_index - from_index + 1
            : int(boost::size(view)) - from_index + to_index + 1;

        for (size_type i = 0; i < count; ++i, ++it)
        {
            detail::overlay::append_no_duplicates(current_output, *it);
        }
    }


    static inline void apply(LineString const& ls,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& current_output)
    {
        int const from_index = seg_id.segment_index + 1;

        // Sanity check
        if (from_index > to_index || from_index < 0 || to_index >= int(boost::size(ls)))
        {
            return;
        }

        typedef typename boost::range_difference<LineString>::type size_type;
        size_type const count = to_index - from_index + 1;

        typename boost::range_iterator<LineString const>::type it = boost::begin(ls) + from_index;

        for (size_type i = 0; i < count; ++i, ++it)
        {
            detail::overlay::append_no_duplicates(current_output, *it);
        }
    }

    static inline void apply(Polygon const& polygon,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& current_output)
    {
        // Call ring-version with the right ring
        copy_segments_ring
            <
                typename geometry::ring_type<Polygon>::type,
                Reverse,
                SegmentIdentifier,
                RangeOut
            >::apply
                (
                    seg_id.ring_index < 0
                    ? geometry::exterior_ring(polygon)
                    : geometry::interior_rings(polygon)[seg_id.ring_index],
                    seg_id, to_index,
                    current_output
                );
    }

    static inline void apply(Box const& box,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& current_output)
    {
        int index = seg_id.segment_index + 1;
        BOOST_ASSERT(index < 5);

        int const count = index <= to_index
            ? to_index - index + 1
            : 5 - index + to_index + 1;

        // Create array of points, the fifth one closes it
        boost::array<typename point_type<Box>::type, 5> bp;
        assign_box_corners_oriented<Reverse>(box, bp);
        bp[4] = bp[0];

        // (possibly cyclic) copy to output
        //    (see comments in ring-version)
        for (int i = 0; i < count; i++, index++)
        {
            detail::overlay::append_no_duplicates(current_output, bp[index % 5]);

        }
    }

template
<
    bool Reverse,
    typename Geometry,
    typename SegmentIdentifier,
    typename RangeOut
>
inline void copy_segments(Geometry const& geometry,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& range_out)
{
    concept::check<Geometry const>();

    dispatch::copy_segments
        <
            typename tag<Geometry>::type,
            Geometry,
            Reverse,
            SegmentIdentifier,
            RangeOut
        >::apply(geometry, seg_id, to_index, range_out);
}

    inline segment_identifier()
        : source_index(-1)
        , multi_index(-1)
        , ring_index(-1)
        , segment_index(-1)
    {}


    inline segment_identifier(int src, int mul, int rin, int seg)
        : source_index(src)
        , multi_index(mul)
        , ring_index(rin)
        , segment_index(seg)
    {}


    inline bool operator<(segment_identifier const& other) const
    {
        return source_index != other.source_index ? source_index < other.source_index
            : multi_index !=other.multi_index ? multi_index < other.multi_index
            : ring_index != other.ring_index ? ring_index < other.ring_index
            : segment_index < other.segment_index
            ;
    }


    inline bool operator==(segment_identifier const& other) const
    {
        return source_index == other.source_index
            && segment_index == other.segment_index
            && ring_index == other.ring_index
            && multi_index == other.multi_index
            ;
    }

    template
    <
        typename Segment1, typename Segment2,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Segment1 const& segment1,
            Segment2 const& segment2, OutputIterator out,
            Strategy const& )
    {
        typedef typename point_type<PointOut>::type point_type;

        // Get the intersection point (or two points)
        segment_intersection_points<point_type> is
            = strategy::intersection::relate_cartesian_segments
            <
                policies::relate::segments_intersection_points
                    <
                        Segment1,
                        Segment2,
                        segment_intersection_points<point_type>
                    >
            >::apply(segment1, segment2);

        for (std::size_t i = 0; i < is.count; i++)
        {
            PointOut p;
            geometry::convert(is.intersections[i], p);
            *out++ = p;
        }
        return out;
    }

    template
    <
        typename Linestring1, typename Linestring2,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linestring1 const& linestring1,
            Linestring2 const& linestring2, OutputIterator out,
            Strategy const& )
    {
        typedef typename point_type<PointOut>::type point_type;

        typedef detail::overlay::turn_info<point_type> turn_info;
        std::deque<turn_info> turns;

        geometry::get_intersection_points(linestring1, linestring2, turns);

        for (typename boost::range_iterator<std::deque<turn_info> const>::type
            it = boost::begin(turns); it != boost::end(turns); ++it)
        {
            PointOut p;
            geometry::convert(it->point, p);
            *out++ = p;
        }
        return out;
    }


    template
    <
        typename LineString, typename Areal,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(LineString const& linestring, Areal const& areal,
            OutputIterator out,
            Strategy const& )
    {
        if (boost::size(linestring) == 0)
        {
            return out;
        }

        typedef detail::overlay::follow
                <
                    LineStringOut,
                    LineString,
                    Areal,
                    OverlayType
                > follower;

        typedef typename point_type<LineStringOut>::type point_type;

        typedef detail::overlay::traversal_turn_info<point_type> turn_info;
        std::deque<turn_info> turns;

        detail::get_turns::no_interrupt_policy policy;
        geometry::get_turns
            <
                false,
                (OverlayType == overlay_intersection ? ReverseAreal : !ReverseAreal),
                detail::overlay::calculate_distance_policy
            >(linestring, areal, turns, policy);

        if (turns.empty())
        {
            // No intersection points, it is either completely 
            // inside (interior + borders)
            // or completely outside

            // Use border point (on a segment) to check this
            // (because turn points might skip some cases)
            point_type border_point;
            if (! geometry::point_on_border(border_point, linestring, true))
            {
                return out;
            }


            if (follower::included(border_point, areal))
            {
                LineStringOut copy;
                geometry::convert(linestring, copy);
                *out++ = copy;
            }
            return out;
        }

#if defined(BOOST_GEOMETRY_DEBUG_FOLLOW)
        int index = 0;
        BOOST_FOREACH(turn_info const& turn, turns)
        {
            debug_follow(turn, turn.operations[0], index++);
        }
#endif

        return follower::apply
                (
                    linestring, areal,
                    geometry::detail::overlay::operation_intersection,
                    turns, out
                );
    }

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                Geometry2 const& g2, OutputIterator out,
                Strategy const& strategy)
    {
        return intersection_insert
            <
                Geometry2, Geometry1, GeometryOut,
                OverlayType,
                Reverse2, Reverse1, ReverseOut
            >::apply(g2, g1, out, strategy);
    }



template
<
    typename GeometryOut,
    bool ReverseSecond,
    overlay_type OverlayType,
    typename Geometry1, typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    return boost::mpl::if_c
        <
            geometry::reverse_dispatch<Geometry1, Geometry2>::type::value,
            geometry::dispatch::intersection_insert_reversed
            <
                Geometry1, Geometry2,
                GeometryOut,
                OverlayType,
                overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
                overlay::do_reverse<geometry::point_order<Geometry2>::value, ReverseSecond>::value,
                overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value
            >,
            geometry::dispatch::intersection_insert
            <
                Geometry1, Geometry2,
                GeometryOut,
                OverlayType,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, ReverseSecond>::value
            >
        >::type::apply(geometry1, geometry2, out, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator intersection_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    return detail::intersection::insert
        <
            GeometryOut, false, overlay_intersection
        >(geometry1, geometry2, out, strategy);
}

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator intersection_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    typedef strategy_intersection
        <
            typename cs_tag<GeometryOut>::type,
            Geometry1,
            Geometry2,
            typename geometry::point_type<GeometryOut>::type
        > strategy;

    return intersection_insert<GeometryOut>(geometry1, geometry2, out,
                strategy());
}


    template <typename Range>
    static inline bool apply(Range const&)
    {
        return false;
    }



    template <typename Geometry, typename Section>
    static inline bool neighbouring(Section const& section,
            int index1, int index2)
    {
        // About n-2:
        //   (square: range_count=5, indices 0,1,2,3
        //    -> 0-3 are adjacent, don't check on intersections)
        // Also tested for open polygons, and/or duplicates
        // About first condition: will be optimized by compiler (static)
        // It checks if it is areal (box,ring,(multi)polygon
        int const n = int(section.range_count);

        boost::ignore_unused_variable_warning(n);
        boost::ignore_unused_variable_warning(index1);
        boost::ignore_unused_variable_warning(index2);

        return boost::is_same
                    <
                        typename tag_cast
                            <
                                typename geometry::point_type<Geometry1>::type, 
                                areal_tag
                            >::type, 
                        areal_tag
                    >::value
               && index1 == 0 
               && index2 >= n - 2
                ;
    }

    static inline bool apply(
            int source_id1, Geometry1 const& geometry1, Section1 const& sec1,
            int source_id2, Geometry2 const& geometry2, Section2 const& sec2,
            bool skip_larger,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        boost::ignore_unused_variable_warning(interrupt_policy);

        cview_type1 cview1(range_by_section(geometry1, sec1));
        cview_type2 cview2(range_by_section(geometry2, sec2));
        view_type1 view1(cview1);
        view_type2 view2(cview2);

        range1_iterator begin_range_1 = boost::begin(view1);
        range1_iterator end_range_1 = boost::end(view1);

        range2_iterator begin_range_2 = boost::begin(view2);
        range2_iterator end_range_2 = boost::end(view2);

        int const dir1 = sec1.directions[0];
        int const dir2 = sec2.directions[0];
        int index1 = sec1.begin_index;
        int ndi1 = sec1.non_duplicate_index;

        bool const same_source =
            source_id1 == source_id2
                    && sec1.ring_id.multi_index == sec2.ring_id.multi_index
                    && sec1.ring_id.ring_index == sec2.ring_id.ring_index;

        range1_iterator prev1, it1, end1;

        get_start_point_iterator(sec1, view1, prev1, it1, end1,
                    index1, ndi1, dir1, sec2.bounding_box);

        // We need a circular iterator because it might run through the closing point.
        // One circle is actually enough but this one is just convenient.
        ever_circling_iterator<range1_iterator> next1(begin_range_1, end_range_1, it1, true);
        next1++;

        // Walk through section and stop if we exceed the other box
        // section 2:    [--------------]
        // section 1: |----|---|---|---|---|
        for (prev1 = it1++, next1++;
            it1 != end1 && ! exceeding<0>(dir1, *prev1, sec2.bounding_box);
            ++prev1, ++it1, ++index1, ++next1, ++ndi1)
        {
            ever_circling_iterator<range1_iterator> nd_next1(
                    begin_range_1, end_range_1, next1, true);
            advance_to_non_duplicate_next(nd_next1, it1, sec1);

            int index2 = sec2.begin_index;
            int ndi2 = sec2.non_duplicate_index;

            range2_iterator prev2, it2, end2;

            get_start_point_iterator(sec2, view2, prev2, it2, end2,
                        index2, ndi2, dir2, sec1.bounding_box);
            ever_circling_iterator<range2_iterator> next2(begin_range_2, end_range_2, it2, true);
            next2++;

            for (prev2 = it2++, next2++;
                it2 != end2 && ! exceeding<0>(dir2, *prev2, sec1.bounding_box);
                ++prev2, ++it2, ++index2, ++next2, ++ndi2)
            {
                bool skip = same_source;
                if (skip)
                {
                    // If sources are the same (possibly self-intersecting):
                    // skip if it is a neighbouring segment.
                    // (including first-last segment
                    //  and two segments with one or more degenerate/duplicate
                    //  (zero-length) segments in between)

                    // Also skip if index1 < index2 to avoid getting all
                    // intersections twice (only do this on same source!)

                    skip = (skip_larger && index1 >= index2)
                        || ndi2 == ndi1 + 1
                        || neighbouring<Geometry1>(sec1, index1, index2)
                        ;
                }

                if (! skip)
                {
                    // Move to the "non duplicate next"
                    ever_circling_iterator<range2_iterator> nd_next2(
                            begin_range_2, end_range_2, next2, true);
                    advance_to_non_duplicate_next(nd_next2, it2, sec2);

                    typedef typename boost::range_value<Turns>::type turn_info;
                    typedef typename turn_info::point_type ip;

                    turn_info ti;
                    ti.operations[0].seg_id = segment_identifier(source_id1,
                                        sec1.ring_id.multi_index, sec1.ring_id.ring_index, index1),
                    ti.operations[1].seg_id = segment_identifier(source_id2,
                                        sec2.ring_id.multi_index, sec2.ring_id.ring_index, index2),

                    ti.operations[0].other_id = ti.operations[1].seg_id;
                    ti.operations[1].other_id = ti.operations[0].seg_id;

                    std::size_t const size_before = boost::size(turns);

                    TurnPolicy::apply(*prev1, *it1, *nd_next1, *prev2, *it2, *nd_next2,
                            ti, std::back_inserter(turns));

                    if (InterruptPolicy::enabled)
                    {
                        if (interrupt_policy.apply(
                            std::make_pair(boost::begin(turns) + size_before,
                                boost::end(turns))))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }



    template <size_t Dim, typename Point, typename Box>
    static inline bool preceding(int dir, Point const& point, Box const& box)
    {
        return (dir == 1  && get<Dim>(point) < get<min_corner, Dim>(box))
            || (dir == -1 && get<Dim>(point) > get<max_corner, Dim>(box));
    }


    template <size_t Dim, typename Point, typename Box>
    static inline bool exceeding(int dir, Point const& point, Box const& box)
    {
        return (dir == 1  && get<Dim>(point) > get<max_corner, Dim>(box))
            || (dir == -1 && get<Dim>(point) < get<min_corner, Dim>(box));
    }


    template <typename Iterator, typename RangeIterator, typename Section>
    static inline void advance_to_non_duplicate_next(Iterator& next,
            RangeIterator const& it, Section const& section)
    {
        // To see where the next segments bend to, in case of touch/intersections
        // on end points, we need (in case of degenerate/duplicate points) an extra
        // iterator which moves to the REAL next point, so non duplicate.
        // This needs an extra comparison (disjoint).
        // (Note that within sections, non duplicate points are already asserted,
        //   by the sectionalize process).

        // So advance to the "non duplicate next"
        // (the check is defensive, to avoid endless loops)
        std::size_t check = 0;
        while(! detail::disjoint::disjoint_point_point(*it, *next)
            && check++ < section.range_count)
        {
            next++;
        }
    }

    template <typename Range, typename Section, typename Box>
    static inline void get_start_point_iterator(Section & section,
            Range const& range,
            typename boost::range_iterator<Range const>::type& it,
            typename boost::range_iterator<Range const>::type& prev,
            typename boost::range_iterator<Range const>::type& end,
            int& index, int& ndi,
            int dir, Box const& other_bounding_box)
    {
        it = boost::begin(range) + section.begin_index;
        end = boost::begin(range) + section.end_index + 1;

        // Mimic section-iterator:
        // Skip to point such that section interects other box
        prev = it++;
        for(; it != end && preceding<0>(dir, *it, other_bounding_box);
            prev = it++, index++, ndi++)
        {}
        // Go back one step because we want to start completely preceding
        it = prev;
    }

    template <typename Box, typename InputItem>
    static inline void apply(Box& total, InputItem const& item)
    {
        geometry::expand(total, item.bounding_box);
    }

    template <typename Box, typename InputItem>
    static inline bool apply(Box const& box, InputItem const& item)
    {
        return ! detail::disjoint::disjoint_box_box(box, item.bounding_box);
    }


    section_visitor(int id1, Geometry1 const& g1,
            int id2, Geometry2 const& g2,
            Turns& turns, InterruptPolicy& ip)
        : m_source_id1(id1), m_geometry1(g1)
        , m_source_id2(id2), m_geometry2(g2)
        , m_turns(turns)
        , m_interrupt_policy(ip)
    {}


    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box, sec2.bounding_box))
        {
            return get_turns_in_sections
                    <
                        Geometry1,
                        Geometry2,
                        Reverse1, Reverse2,
                        Section, Section,
                        Turns,
                        TurnPolicy,
                        InterruptPolicy
                    >::apply(
                            m_source_id1, m_geometry1, sec1,
                            m_source_id2, m_geometry2, sec2,
                            false,
                            m_turns, m_interrupt_policy);
        }
        return true;
    }

    static inline void apply(
            int source_id1, Geometry1 const& geometry1,
            int source_id2, Geometry2 const& geometry2,
            Turns& turns, InterruptPolicy& interrupt_policy)
    {
        // First create monotonic sections...
        typedef typename boost::range_value<Turns>::type ip_type;
        typedef typename ip_type::point_type point_type;
        typedef model::box<point_type> box_type;
        typedef typename geometry::sections<box_type, 2> sections_type;

        sections_type sec1, sec2;

        geometry::sectionalize<Reverse1>(geometry1, sec1, 0);
        geometry::sectionalize<Reverse2>(geometry2, sec2, 1);

        // ... and then partition them, intersecting overlapping sections in visitor method
        section_visitor
            <
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                Turns, TurnPolicy, InterruptPolicy
            > visitor(source_id1, geometry1, source_id2, geometry2, turns, interrupt_policy);

        geometry::partition
            <
                box_type, get_section_box, ovelaps_section_box
            >::apply(sec1, sec2, visitor);
    }



    static inline void apply(
                int source_id1, Range const& range,
                int source_id2, Box const& box,
                Turns& turns,
                InterruptPolicy& interrupt_policy,
                int multi_index = -1, int ring_index = -1)
    {
        if (boost::size(range) <= 1)
        {
            return;
        }

        boost::array<box_point_type,4> bp;
        assign_box_corners_oriented<ReverseBox>(box, bp);

        cview_type cview(range);
        view_type view(cview);

        iterator_type it = boost::begin(view);

        ever_circling_iterator<iterator_type> next(
                boost::begin(view), boost::end(view), it, true);
        next++;
        next++;

        //bool first = true;

        //char previous_side[2] = {0, 0};

        int index = 0;

        for (iterator_type prev = it++;
            it != boost::end(view);
            prev = it++, next++, index++)
        {
            segment_identifier seg_id(source_id1,
                        multi_index, ring_index, index);

            /*if (first)
            {
                previous_side[0] = get_side<0>(box, *prev);
                previous_side[1] = get_side<1>(box, *prev);
            }

            char current_side[2];
            current_side[0] = get_side<0>(box, *it);
            current_side[1] = get_side<1>(box, *it);

            // There can NOT be intersections if
            // 1) EITHER the two points are lying on one side of the box (! 0 && the same)
            // 2) OR same in Y-direction
            // 3) OR all points are inside the box (0)
            if (! (
                (current_side[0] != 0 && current_side[0] == previous_side[0])
                || (current_side[1] != 0 && current_side[1] == previous_side[1])
                || (current_side[0] == 0
                        && current_side[1] == 0
                        && previous_side[0] == 0
                        && previous_side[1] == 0)
                  )
                )*/
            if (true)
            {
                get_turns_with_box(seg_id, source_id2,
                        *prev, *it, *next,
                        bp[0], bp[1], bp[2], bp[3],
                        turns, interrupt_policy);
                // Future performance enhancement: 
                // return if told by the interrupt policy 
            }
        }
    }

    template<std::size_t Index, typename Point>
    static inline int get_side(Box const& box, Point const& point)
    {
        // Inside -> 0
        // Outside -> -1 (left/below) or 1 (right/above)
        // On border -> -2 (left/lower) or 2 (right/upper)
        // The only purpose of the value is to not be the same,
        // and to denote if it is inside (0)

        typename coordinate_type<Point>::type const& c = get<Index>(point);
        typename coordinate_type<Box>::type const& left = get<min_corner, Index>(box);
        typename coordinate_type<Box>::type const& right = get<max_corner, Index>(box);

        if (geometry::math::equals(c, left)) return -2;
        else if (geometry::math::equals(c, right)) return 2;
        else if (c < left) return -1;
        else if (c > right) return 1;
        else return 0;
    }


    static inline void get_turns_with_box(segment_identifier const& seg_id, int source_id2,
            // Points from a range:
            point_type const& rp0,
            point_type const& rp1,
            point_type const& rp2,
            // Points from the box
            box_point_type const& bp0,
            box_point_type const& bp1,
            box_point_type const& bp2,
            box_point_type const& bp3,
            // Output
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        boost::ignore_unused_variable_warning(interrupt_policy);

        // Depending on code some relations can be left out

        typedef typename boost::range_value<Turns>::type turn_info;

        turn_info ti;
        ti.operations[0].seg_id = seg_id;
        ti.operations[0].other_id = ti.operations[1].seg_id;
        ti.operations[1].other_id = seg_id;

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 0);
        TurnPolicy::apply(rp0, rp1, rp2, bp0, bp1, bp2,
                ti, std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 1);
        TurnPolicy::apply(rp0, rp1, rp2, bp1, bp2, bp3,
                ti, std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 2);
        TurnPolicy::apply(rp0, rp1, rp2, bp2, bp3, bp0,
                ti, std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 3);
        TurnPolicy::apply(rp0, rp1, rp2, bp3, bp0, bp1,
                ti, std::back_inserter(turns));

        if (InterruptPolicy::enabled)
        {
            interrupt_policy.apply(turns);
        }

    }

    static inline void apply(
            int source_id1, Polygon const& polygon,
            int source_id2, Box const& box,
            Turns& turns, InterruptPolicy& interrupt_policy,
            int multi_index = -1)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        typedef detail::get_turns::get_turns_cs
            <
                ring_type, Box,
                Reverse, ReverseBox,
                Turns,
                TurnPolicy,
                InterruptPolicy
            > intersector_type;

        intersector_type::apply(
                source_id1, geometry::exterior_ring(polygon),
                source_id2, box, turns, interrupt_policy,
                multi_index, -1);

        int i = 0;

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(polygon);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings);
            ++it, ++i)
        {
            intersector_type::apply(
                    source_id1, *it,
                    source_id2, box, turns, interrupt_policy,
                    multi_index, i);
        }

    }

    static inline void apply(
            int source_id1, Geometry1 const& g1,
            int source_id2, Geometry2 const& g2,
            Turns& turns, InterruptPolicy& interrupt_policy)
    {
        get_turns
            <
                GeometryTag2, GeometryTag1,
                Geometry2, Geometry1,
                Reverse2, Reverse1,
                Turns, TurnPolicy,
                InterruptPolicy
            >::apply(source_id2, g2, source_id1, g1, turns, interrupt_policy);
    }

template
<
    bool Reverse1, bool Reverse2,
    typename AssignPolicy,
    typename Geometry1,
    typename Geometry2,
    typename Turns,
    typename InterruptPolicy
>
inline void get_turns(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
{
    concept::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2 const>();

    typedef typename strategy_intersection
        <
            typename cs_tag<Geometry1>::type,
            Geometry1,
            Geometry2,
            typename boost::range_value<Turns>::type
        >::segment_intersection_strategy_type segment_intersection_strategy_type;

    typedef detail::overlay::get_turn_info
        <
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type,
            typename boost::range_value<Turns>::type,
            AssignPolicy
        > TurnPolicy;

    boost::mpl::if_c
        <
            reverse_dispatch<Geometry1, Geometry2>::type::value,
            dispatch::get_turns_reversed
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                Turns, TurnPolicy,
                InterruptPolicy
            >,
            dispatch::get_turns
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                Turns, TurnPolicy,
                InterruptPolicy
            >
        >::type::apply(
            0, geometry1,
            1, geometry2,
            turns, interrupt_policy);
}




    template <typename OutputIterator>
    static inline OutputIterator apply(
                Point1 const& pi, Point1 const& pj, Point1 const& pk,
                Point2 const& qi, Point2 const& qj, Point2 const& qk,
                TurnInfo const& ,
                OutputIterator out)
    {
        typedef model::referring_segment<Point1 const> segment_type1;
        typedef model::referring_segment<Point1 const> segment_type2;
        segment_type1 p1(pi, pj), p2(pj, pk);
        segment_type2 q1(qi, qj), q2(qj, qk);

        //
        typename strategy::return_type result = strategy::apply(p1, q1);

        for (std::size_t i = 0; i < result.template get<0>().count; i++)
        {

            TurnInfo tp;
            geometry::convert(result.template get<0>().intersections[i], tp.point);
            *out++ = tp;
        }

        return out;
    }





template
<
    typename Geometry1,
    typename Geometry2,
    typename Turns
>
inline void get_intersection_points(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            Turns& turns)
{
    concept::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2 const>();

    typedef detail::get_intersection_points::get_turn_without_info
                        <
                            typename point_type<Geometry1>::type,
                            typename point_type<Geometry2>::type,
                            typename boost::range_value<Turns>::type
                        > TurnPolicy;

    typedef typename strategy_intersection
        <
            typename cs_tag<Geometry1>::type,
            Geometry1,
            Geometry2,
            typename boost::range_value<Turns>::type
        >::segment_intersection_strategy_type segment_intersection_strategy_type;

    detail::get_turns::no_interrupt_policy interrupt_policy;

    boost::mpl::if_c
        <
            reverse_dispatch<Geometry1, Geometry2>::type::value,
            dispatch::get_turns_reversed
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                false, false,
                Turns, TurnPolicy,
                //segment_intersection_strategy_type,
                detail::get_turns::no_interrupt_policy
            >,
            dispatch::get_turns
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                false, false,
                Turns, TurnPolicy,
                //segment_intersection_strategy_type,
                detail::get_turns::no_interrupt_policy
            >
        >::type::apply(
            0, geometry1,
            1, geometry2,
            turns, interrupt_policy);
}




template
<
    typename Item,
    typename Geometry1, typename Geometry2,
    typename RingCollection
>
static inline bool within_selected_input(Item const& item2, ring_identifier const& ring_id,
        Geometry1 const& geometry1, Geometry2 const& geometry2,
        RingCollection const& collection)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    switch (ring_id.source_index)
    {
        case 0 :
            return geometry::within(item2.point,
                get_ring<tag1>::apply(ring_id, geometry1));
            break;
        case 1 :
            return geometry::within(item2.point,
                get_ring<tag2>::apply(ring_id, geometry2));
            break;
        case 2 :
            return geometry::within(item2.point,
                get_ring<void>::apply(ring_id, collection));
            break;
    }
    return false;
}


    inline ring_info_helper()
        : real_area(0), abs_area(0)
    {}

    template <typename Box, typename InputItem>
    static inline void apply(Box& total, InputItem const& item)
    {
        geometry::expand(total, item.envelope);
    }

    template <typename Box, typename InputItem>
    static inline bool apply(Box const& box, InputItem const& item)
    {
        return ! geometry::detail::disjoint::disjoint_box_box(box, item.envelope);
    }



    inline assign_visitor(Geometry1 const& g1, Geometry2 const& g2, Collection const& c,
                RingMap& map, bool check)
        : m_geometry1(g1)
        , m_geometry2(g2)
        , m_collection(c)
        , m_ring_map(map)
        , m_check_for_orientation(check)
    {}


    template <typename Item>
    inline void apply(Item const& outer, Item const& inner, bool first = true)
    {
        if (first && outer.real_area < 0)
        {
            // Reverse arguments
            apply(inner, outer, false);
            return;
        }

        if (math::larger(outer.real_area, 0))
        {
            if (inner.real_area < 0 || m_check_for_orientation)
            {
                ring_info_type& inner_in_map = m_ring_map[inner.id];

                if (geometry::within(inner_in_map.point, outer.envelope)
                   && within_selected_input(inner_in_map, outer.id, m_geometry1, m_geometry2, m_collection)
                   )
                {
                    // Only assign parent if that parent is smaller (or if it is the first)
                    if (inner_in_map.parent.source_index == -1
                        || outer.abs_area < inner_in_map.parent_area)
                    {
                        inner_in_map.parent = outer.id;
                        inner_in_map.parent_area = outer.abs_area;
                    }
                }
            }
        }
    }





template
<
    typename Geometry1, typename Geometry2,
    typename RingCollection,
    typename RingMap
>
inline void assign_parents(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RingCollection const& collection,
            RingMap& ring_map,
            bool check_for_orientation = false)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    typedef typename RingMap::mapped_type ring_info_type;
    typedef typename ring_info_type::point_type point_type;
    typedef model::box<point_type> box_type;

    typedef typename RingMap::iterator map_iterator_type;

    {
        typedef ring_info_helper<point_type> helper;
        typedef std::vector<helper> vector_type;
        typedef typename boost::range_iterator<vector_type const>::type vector_iterator_type;

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        boost::timer timer;
#endif


        std::size_t count_total = ring_map.size();
        std::size_t count_positive = 0;
        std::size_t index_positive = 0; // only used if count_positive>0
        std::size_t index = 0;

        // Copy to vector (with new approach this might be obsolete as well, using the map directly)
        vector_type vector(count_total);

        for (map_iterator_type it = boost::begin(ring_map);
            it != boost::end(ring_map); ++it, ++index)
        {
            vector[index] = helper(it->first, it->second.get_area());
            helper& item = vector[index];
            switch(it->first.source_index)
            {
                case 0 :
                    geometry::envelope(get_ring<tag1>::apply(it->first, geometry1),
                            item.envelope);
                    break;
                case 1 :
                    geometry::envelope(get_ring<tag2>::apply(it->first, geometry2),
                            item.envelope);
                    break;
                case 2 :
                    geometry::envelope(get_ring<void>::apply(it->first, collection),
                            item.envelope);
                    break;
            }
            if (item.real_area > 0)
            {
                count_positive++;
                index_positive = index;
            }
        }

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << " ap: created helper vector: " << timer.elapsed() << std::endl;
#endif

        if (! check_for_orientation)
        {
            if (count_positive == count_total)
            {
                // Optimization for only positive rings
                // -> no assignment of parents or reversal necessary, ready here.
                return;
            }

            if (count_positive == 1)
            {
                // Optimization for one outer ring
                // -> assign this as parent to all others (all interior rings)
                // In unions, this is probably the most occuring case and gives
                //    a dramatic improvement (factor 5 for star_comb testcase)
                ring_identifier id_of_positive = vector[index_positive].id;
                ring_info_type& outer = ring_map[id_of_positive];
                std::size_t index = 0;
                for (vector_iterator_type it = boost::begin(vector);
                    it != boost::end(vector); ++it, ++index)
                {
                    if (index != index_positive)
                    {
                        ring_info_type& inner = ring_map[it->id];
                        inner.parent = id_of_positive;
                        outer.children.push_back(it->id);
                    }
                }
                return;
            }
        }

        assign_visitor
            <
                Geometry1, Geometry2,
                RingCollection, RingMap
            > visitor(geometry1, geometry2, collection, ring_map, check_for_orientation);

        geometry::partition
            <
                box_type, ring_info_helper_get_box, ring_info_helper_ovelaps_box
            >::apply(vector, visitor);

#ifdef BOOST_GEOMETRY_TIME_OVERLAY
        std::cout << " ap: quadradic loop: " << timer.elapsed() << std::endl;
        std::cout << " ap: check_for_orientation " << check_for_orientation << std::endl;
#endif
    }

    if (check_for_orientation)
    {
        for (map_iterator_type it = boost::begin(ring_map);
            it != boost::end(ring_map); ++it)
        {
            if (geometry::math::equals(it->second.get_area(), 0))
            {
                it->second.discarded = true;
            }
            else if (it->second.parent.source_index >= 0 && it->second.get_area() > 0)
            {
                // Discard positive inner ring with parent
                it->second.discarded = true;
                it->second.parent.source_index = -1;
            }
            else if (it->second.parent.source_index < 0 && it->second.get_area() < 0)
            {
                // Reverse negative ring without parent
                it->second.reversed = true;
            }
        }
    }

    // Assign childlist
    for (map_iterator_type it = boost::begin(ring_map);
        it != boost::end(ring_map); ++it)
    {
        if (it->second.parent.source_index >= 0)
        {
            ring_map[it->second.parent].children.push_back(it->first);
        }
    }
}


template
<
    typename Geometry,
    typename RingCollection,
    typename RingMap
>
inline void assign_parents(Geometry const& geometry,
            RingCollection const& collection,
            RingMap& ring_map,
            bool check_for_orientation)
{
    // Call it with an empty geometry
    // (ring_map should be empty for source_id==1)

    Geometry empty;
    assign_parents(geometry, empty, collection, ring_map, check_for_orientation);
}


    template 
    <
        typename Info,
        typename Point1,
        typename Point2,
        typename IntersectionInfo,
        typename DirInfo
    >
    static inline void apply(Info& info, Point1 const& p1, Point2 const& p2,
                IntersectionInfo const&, DirInfo const&)
    {
        info.operations[0].enriched.distance
                    = geometry::comparable_distance(info.point, p1);
        info.operations[1].enriched.distance
                    = geometry::comparable_distance(info.point, p2);
    }



    template <typename Range>
    static inline bool apply(Range const&)
    {
        return false;
    }


    inline self_section_visitor(Geometry const& g,
            Turns& turns, InterruptPolicy& ip)
        : m_geometry(g)
        , m_turns(turns)
        , m_interrupt_policy(ip)
    {}


    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box, sec2.bounding_box)
                && ! sec1.duplicate
                && ! sec2.duplicate)
        {
            detail::get_turns::get_turns_in_sections
                    <
                        Geometry, Geometry,
                        false, false,
                        Section, Section,
                        Turns, TurnPolicy,
                        InterruptPolicy
                    >::apply(
                            0, m_geometry, sec1,
                            0, m_geometry, sec2,
                            false,
                            m_turns, m_interrupt_policy);
        }
        if (m_interrupt_policy.has_intersections)
        {
            // TODO: we should give partition an interrupt policy.
            // Now we throw, and catch below, to stop the partition loop.
            throw self_ip_exception();
        }
        return true;
    }

    static inline bool apply(
            Geometry const& geometry,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        typedef model::box
            <
                typename geometry::point_type<Geometry>::type
            > box_type;
        typedef typename geometry::sections
            <
                box_type, 1
            > sections_type;

        sections_type sec;
        geometry::sectionalize<false>(geometry, sec);

        self_section_visitor
            <
                Geometry,
                Turns, TurnPolicy, InterruptPolicy
            > visitor(geometry, turns, interrupt_policy);

        try
        {
            geometry::partition
                <
                    box_type, 
                    detail::get_turns::get_section_box, 
                    detail::get_turns::ovelaps_section_box
                >::apply(sec, visitor);
        }
        catch(self_ip_exception const& )
        {
            return false;
        }

        return true;
    }

template
<
    typename AssignPolicy,
    typename Geometry,
    typename Turns,
    typename InterruptPolicy
>
inline void self_turns(Geometry const& geometry,
            Turns& turns, InterruptPolicy& interrupt_policy)
{
    concept::check<Geometry const>();

    typedef typename strategy_intersection
        <
            typename cs_tag<Geometry>::type,
            Geometry,
            Geometry,
            typename boost::range_value<Turns>::type
        >::segment_intersection_strategy_type strategy_type;

    typedef detail::overlay::get_turn_info
                        <
                            typename point_type<Geometry>::type,
                            typename point_type<Geometry>::type,
                            typename boost::range_value<Turns>::type,
                            detail::overlay::assign_null_policy
                        > TurnPolicy;

    dispatch::self_get_turn_points
            <
                typename tag<Geometry>::type,
                Geometry,
                Turns,
                TurnPolicy,
                InterruptPolicy
            >::apply(geometry, turns, interrupt_policy);
}



template
<
    overlay_type OverlayType,
    typename Geometry1, typename Geometry2,
    typename IntersectionMap, typename SelectionMap
>
inline void update_selection_map(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            IntersectionMap const& intersection_map,
            SelectionMap const& map_with_all, SelectionMap& selection_map)
{
    selection_map.clear();

    for (typename SelectionMap::const_iterator it = boost::begin(map_with_all);
        it != boost::end(map_with_all);
        ++it)
    {
        /*
        int union_code = it->second.within_code * -1;
        bool is_first = it->first.source_index == 0;
        std::cout << it->first << " " << it->second.area
            << ": " << it->second.within_code
            << " union: " << union_code
            << " intersection: " << (it->second.within_code * 1)
            << " G1-G2: " << (union_code * (is_first ? 1 : -1))
            << " G2-G1: " << (union_code * (is_first ? -1 : 1))
            << " -> " << (decide<OverlayType>::include(it->first, it->second) ? "INC" : "")
            << decide<OverlayType>::reverse(it->first, it->second)
            << std::endl;
        */

        bool found = intersection_map.find(it->first) != intersection_map.end();
        if (! found)
        {
            ring_identifier const id = it->first;
            typename SelectionMap::mapped_type properties = it->second; // Copy by value

            // Calculate the "within code" (previously this was done earlier but is
            // must efficienter here - it can be even more efficient doing it all at once,
            // using partition, TODO)
            // So though this is less elegant than before, it avoids many unused point-in-poly calculations
            switch(id.source_index)
            {
                case 0 :
                    properties.within_code
                        = geometry::within(properties.point, geometry2) ? 1 : -1;
                    break;
                case 1 :
                    properties.within_code
                        = geometry::within(properties.point, geometry1) ? 1 : -1;
                    break;
            }

            if (decide<OverlayType>::include(id, properties))
            {
                properties.reversed = decide<OverlayType>::reversed(id, properties);
                selection_map[id] = properties;
            }
        }
    }
}

template
<
    overlay_type OverlayType,
    typename Geometry1, typename Geometry2,
    typename IntersectionMap, typename SelectionMap
>
inline void select_rings(Geometry1 const& geometry1, Geometry2 const& geometry2,
            IntersectionMap const& intersection_map, 
            SelectionMap& selection_map, bool midpoint)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    SelectionMap map_with_all;
    dispatch::select_rings<tag1, Geometry1>::apply(geometry1, geometry2,
                ring_identifier(0, -1, -1), map_with_all, midpoint);
    dispatch::select_rings<tag2, Geometry2>::apply(geometry2, geometry1,
                ring_identifier(1, -1, -1), map_with_all, midpoint);

    update_selection_map<OverlayType>(geometry1, geometry2, intersection_map,
                map_with_all, selection_map);
}


template
<
    overlay_type OverlayType,
    typename Geometry,
    typename IntersectionMap, typename SelectionMap
>
inline void select_rings(Geometry const& geometry,
            IntersectionMap const& intersection_map, 
            SelectionMap& selection_map, bool midpoint)
{
    typedef typename geometry::tag<Geometry>::type tag;

    SelectionMap map_with_all;
    dispatch::select_rings<tag, Geometry>::apply(geometry, 
                ring_identifier(0, -1, -1), map_with_all, midpoint);

    update_selection_map<OverlayType>(geometry, geometry, intersection_map, 
                map_with_all, selection_map);
}


    static inline bool apply(Range const& range,
            SegmentIdentifier const& seg_id, bool second,
            PointOut& point)
    {
        int index = seg_id.segment_index;
        if (second)
        {
            index++;
            if (index >= int(boost::size(range)))
            {
                index = 0;
            }
        }

        // Exception?
        if (index >= int(boost::size(range)))
        {
            return false;
        }

        cview_type cview(range);
        rview_type view(cview);


        geometry::convert(*(boost::begin(view) + index), point);
        return true;
    }

    static inline bool apply(Polygon const& polygon,
            SegmentIdentifier const& seg_id, bool second,
            PointOut& point)
    {
        // Call ring-version with the right ring
        return copy_segment_point_range
            <
                typename geometry::ring_type<Polygon>::type,
                Reverse,
                SegmentIdentifier,
                PointOut
            >::apply
                (
                    seg_id.ring_index < 0
                    ? geometry::exterior_ring(polygon)
                    : geometry::interior_rings(polygon)[seg_id.ring_index],
                    seg_id, second,
                    point
                );
    }

    static inline bool apply(Box const& box,
            SegmentIdentifier const& seg_id, bool second,
            PointOut& point)
    {
        int index = seg_id.segment_index;
        if (second)
        {
            index++;
        }

        boost::array<typename point_type<Box>::type, 4> bp;
        assign_box_corners_oriented<Reverse>(box, bp);
        point = bp[index % 4];
        return true;
    }

template<bool Reverse, typename Geometry, typename SegmentIdentifier, typename PointOut>
inline bool copy_segment_point(Geometry const& geometry,
            SegmentIdentifier const& seg_id, bool second,
            PointOut& point_out)
{
    concept::check<Geometry const>();

    return dispatch::copy_segment_point
        <
            typename tag<Geometry>::type,
            Geometry,
            Reverse,
            SegmentIdentifier,
            PointOut
        >::apply(geometry, seg_id, second, point_out);
}

template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1, typename Geometry2,
    typename SegmentIdentifier,
    typename PointOut
>
inline bool copy_segment_point(Geometry1 const& geometry1, Geometry2 const& geometry2,
            SegmentIdentifier const& seg_id, bool second,
            PointOut& point_out)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    if (seg_id.source_index == 0)
    {
        return dispatch::copy_segment_point
            <
                typename tag<Geometry1>::type,
                Geometry1,
                Reverse1,
                SegmentIdentifier,
                PointOut
            >::apply(geometry1, seg_id, second, point_out);
    }
    else if (seg_id.source_index == 1)
    {
        return dispatch::copy_segment_point
            <
                typename tag<Geometry2>::type,
                Geometry2,
                Reverse2,
                SegmentIdentifier,
                PointOut
            >::apply(geometry2, seg_id, second, point_out);
    }
    // Exception?
    return false;
}

template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1, typename Geometry2,
    typename SegmentIdentifier,
    typename PointOut
>
inline bool copy_segment_points(Geometry1 const& geometry1, Geometry2 const& geometry2,
            SegmentIdentifier const& seg_id,
            PointOut& point1, PointOut& point2)
{
    concept::check<Geometry1 const>();
    concept::check<Geometry2 const>();

    return copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, false, point1)
        && copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, true,  point2);
}

    
template <typename Turn, typename Operation>
static inline bool is_entering(Turn const& /* TODO remove this parameter */, Operation const& op)
{
    // (Blocked means: blocked for polygon/polygon intersection, because
    // they are reversed. But for polygon/line it is similar to continue)
    return op.operation == operation_intersection
        || op.operation == operation_continue
        || op.operation == operation_blocked
        ;
}


template 
<
    typename Turn, 
    typename Operation, 
    typename LineString, 
    typename Polygon
>
static inline bool last_covered_by(Turn const& turn, Operation const& op, 
                LineString const& linestring, Polygon const& polygon)
{
    // Check any point between the this one and the first IP 
    typedef typename geometry::point_type<LineString>::type point_type;
    point_type point_in_between;
    detail::point_on_border::midpoint_helper
        <
            point_type,
            0, dimension<point_type>::value
        >::apply(point_in_between, linestring[op.seg_id.segment_index], turn.point);

    return geometry::covered_by(point_in_between, polygon);
}



template 
<
    typename Turn, 
    typename Operation, 
    typename LineString, 
    typename Polygon
>
static inline bool is_leaving(Turn const& turn, Operation const& op, 
                bool entered, bool first, 
                LineString const& linestring, Polygon const& polygon)
{
    if (op.operation == operation_union)
    {
        return entered 
            || turn.method == method_crosses
            || (first && last_covered_by(turn, op, linestring, polygon))
            ;
    }
    return false;
}



template 
<
    typename Turn, 
    typename Operation, 
    typename LineString, 
    typename Polygon
>
static inline bool is_staying_inside(Turn const& turn, Operation const& op, 
                bool entered, bool first, 
                LineString const& linestring, Polygon const& polygon)
{
    if (turn.method == method_crosses)
    {
        // The normal case, this is completely covered with entering/leaving 
        // so stay out of this time consuming "covered_by"
        return false;
    }

    if (is_entering(turn, op))
    {
        return entered || (first && last_covered_by(turn, op, linestring, polygon));
    }

    return false;
}


template 
<
    typename Turn, 
    typename Operation, 
    typename Linestring, 
    typename Polygon
>
static inline bool was_entered(Turn const& turn, Operation const& op, bool first,
                Linestring const& linestring, Polygon const& polygon)
{
    if (first && (turn.method == method_collinear || turn.method == method_equal))
    {
        return last_covered_by(turn, op, linestring, polygon);
    }
    return false;
}

        inline int operation_order(Turn const& turn) const
        {
            operation_type const& operation = turn.operations[0].operation;
            switch(operation)
            {
                case operation_opposite : return 0;
                case operation_none : return 0;
                case operation_union : return 1;
                case operation_intersection : return 2;
                case operation_blocked : return 3;
                case operation_continue : return 4;
            }
            return -1;
        };


        inline bool use_operation(Turn const& left, Turn const& right) const
        {
            // If they are the same, OK. 
            return operation_order(left) < operation_order(right);
        }


        inline bool use_distance(Turn const& left, Turn const& right) const
        {
            return geometry::math::equals(left.operations[0].enriched.distance, right.operations[0].enriched.distance)
                ? use_operation(left, right)
                : left.operations[0].enriched.distance < right.operations[0].enriched.distance
                ;
        }


        inline bool operator()(Turn const& left, Turn const& right) const
        {
            segment_identifier const& sl = left.operations[0].seg_id;
            segment_identifier const& sr = right.operations[0].seg_id;

            return sl == sr
                ? use_distance(left, right)
                : sl < sr
                ;

        }


    template <typename Point, typename Geometry>
    static inline bool included(Point const& point, Geometry const& geometry)
    {
        return following::action_selector<OverlayType>::included(point, geometry);
    }


    template<typename Turns, typename OutputIterator>
    static inline OutputIterator apply(LineString const& linestring, Polygon const& polygon,
                detail::overlay::operation_type ,  // TODO: this parameter might be redundant
                Turns& turns, OutputIterator out)
    {
        typedef typename boost::range_iterator<Turns>::type turn_iterator;
        typedef typename boost::range_value<Turns>::type turn_type;
        typedef typename boost::range_iterator
            <
                typename turn_type::container_type
            >::type turn_operation_iterator_type;

        typedef following::action_selector<OverlayType> action;

        // Sort intersection points on segments-along-linestring, and distance
        // (like in enrich is done for poly/poly)
        std::sort(boost::begin(turns), boost::end(turns), sort_on_segment<turn_type>());

        LineStringOut current_piece;
        geometry::segment_identifier current_segment_id(0, -1, -1, -1);

        // Iterate through all intersection points (they are ordered along the line)
        bool entered = false;
        bool first = true;
        for (turn_iterator it = boost::begin(turns); it != boost::end(turns); ++it)
        {
            turn_operation_iterator_type iit = boost::begin(it->operations);

            if (following::was_entered(*it, *iit, first, linestring, polygon))
            {
                debug_traverse(*it, *iit, "-> Was entered");
                entered = true;
            }

            if (following::is_staying_inside(*it, *iit, entered, first, linestring, polygon))
            {
                debug_traverse(*it, *iit, "-> Staying inside");

                entered = true;
            }
            else if (following::is_entering(*it, *iit))
            {
                debug_traverse(*it, *iit, "-> Entering");

                entered = true;
                action::enter(current_piece, linestring, current_segment_id, iit->seg_id.segment_index, it->point, *iit, out);
            }
            else if (following::is_leaving(*it, *iit, entered, first, linestring, polygon))
            {
                debug_traverse(*it, *iit, "-> Leaving");

                entered = false;
                action::leave(current_piece, linestring, current_segment_id, iit->seg_id.segment_index, it->point, *iit, out);
            }
            first = false;
        }

        if (action::is_entered(entered))
        {
            geometry::copy_segments<false>(linestring, current_segment_id,
                    boost::size(linestring) - 1,
                    current_piece);
        }

        // Output the last one, if applicable
        if (current_piece.size() > 1)
        {
            *out++ = current_piece;
        }
        return out;
    }


    inline enrichment_info()
        : travels_to_vertex_index(-1)
        , travels_to_ip_index(-1)
        , next_ip_index(-1)
        , distance(distance_type())
    {}


    inline collected_vector()
    {}


    inline collected_vector(T const& px, T const& py,
            T const& pdx, T const& pdy)
        : x(px)
        , y(py)
        , dx(pdx)
        , dy(pdy)
        , dx_0(T())
        , dy_0(T())
    {}

    inline bool operator<(collected_vector<T> const& other) const
    {
        if (math::equals(x, other.x))
        {
            if (math::equals(y, other.y))
            {
                if (math::equals(dx, other.dx))
                {
                    return dy < other.dy;
                }
                return dx < other.dx;
            }
            return y < other.y;
        }
        return x < other.x;
    }


    inline bool same_direction(collected_vector<T> const& other) const
    {
        // For high precision arithmetic, we have to be 
        // more relaxed then using ==
        // Because 2/sqrt( (0,0)<->(2,2) ) == 1/sqrt( (0,0)<->(1,1) ) 
        // is not always true (at least, it is not for ttmath)
        return math::equals_with_epsilon(dx, other.dx)
            && math::equals_with_epsilon(dy, other.dy);
    }

    inline bool operator==(collected_vector<T> const& other) const
    {
        return math::equals(x, other.x)
            && math::equals(y, other.y)
            && same_direction(other);
    }


    static inline void apply(Collection& collection, Range const& range)
    {
        if (boost::size(range) < 2)
        {
            return;
        }

        typedef typename boost::range_iterator<Range const>::type iterator;

        bool first = true;
        iterator it = boost::begin(range);

        for (iterator prev = it++;
            it != boost::end(range);
            prev = it++)
        {
            typename boost::range_value<Collection>::type v;

            v.x = get<0>(*prev);
            v.y = get<1>(*prev);
            v.dx = get<0>(*it) - v.x;
            v.dy = get<1>(*it) - v.y;
            v.dx_0 = v.dx;
            v.dy_0 = v.dy;

            // Normalize the vector -> this results in points+direction
            // and is comparible between geometries
            calculation_type magnitude = sqrt(
                boost::numeric_cast<calculation_type>(v.dx * v.dx + v.dy * v.dy));

            // Avoid non-duplicate points (AND division by zero)
            if (magnitude > 0)
            {
                v.dx /= magnitude;
                v.dy /= magnitude;

                // Avoid non-direction changing points
                if (first || ! v.same_direction(collection.back()))
                {
                    collection.push_back(v);
                }
                first = false;
            }
        }

        // If first one has same direction as last one, remove first one
        if (boost::size(collection) > 1 
            && collection.front().same_direction(collection.back()))
        {
            collection.erase(collection.begin());
        }
    }


    static inline void apply(Collection& collection, Box const& box)
    {
        typename point_type<Box>::type lower_left, lower_right,
                upper_left, upper_right;
        geometry::detail::assign_box_corners(box, lower_left, lower_right,
                upper_left, upper_right);

        typedef typename boost::range_value<Collection>::type item;

        collection.push_back(item(get<0>(lower_left), get<1>(lower_left), 0, 1));
        collection.push_back(item(get<0>(upper_left), get<1>(upper_left), 1, 0));
        collection.push_back(item(get<0>(upper_right), get<1>(upper_right), 0, -1));
        collection.push_back(item(get<0>(lower_right), get<1>(lower_right), -1, 0));
    }

    static inline void apply(Collection& collection, Polygon const& polygon)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        typedef range_collect_vectors<ring_type, Collection> per_range;
        per_range::apply(collection, exterior_ring(polygon));

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(polygon);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            per_range::apply(collection, *it);
        }
    }

    static inline void apply(Collection& collection, MultiGeometry const& multi)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            SinglePolicy::apply(collection, *it);
        }
    }

    static inline void apply(Collection&, Geometry const&)
    {}

template <typename Collection, typename Geometry>
inline void collect_vectors(Collection& collection, Geometry const& geometry)
{
    concept::check<Geometry const>();

    dispatch::collect_vectors
        <
            typename tag<Geometry>::type,
            Collection,
            Geometry
        >::apply(collection, geometry);
}

    static inline Range const& apply(Range const& range, Section const& )
    {
        return range;
    }


    inline section()
        : id(-1)
        , begin_index(-1)
        , end_index(-1)
        , count(0)
        , range_count(0)
        , duplicate(false)
        , non_duplicate_index(-1)
    {
        assign_inverse(bounding_box);
        for (register std::size_t i = 0; i < DimensionCount; i++)
        {
            directions[i] = 0;
        }
    }


    static inline void apply(Segment const& seg,
                int directions[DimensionCount])
    {
        coordinate_type const diff =
            geometry::get<1, Dimension>(seg) - geometry::get<0, Dimension>(seg);

        coordinate_type zero = coordinate_type();
        directions[Dimension] = diff > zero ? 1 : diff < zero ? -1 : 0;

        get_direction_loop
            <
                Segment, Dimension + 1, DimensionCount
            >::apply(seg, directions);
    }

    static inline void apply(Segment const&, int [DimensionCount])
    {}

    static inline void apply(T const source[DimensionCount],
                T target[DimensionCount])
    {
        target[Dimension] = source[Dimension];
        copy_loop<T, Dimension + 1, DimensionCount>::apply(source, target);
    }

    static inline void apply(T const [DimensionCount], T [DimensionCount])
    {}

    static inline bool apply(T const source[DimensionCount],
                T const target[DimensionCount])
    {
        bool const not_equal = target[Dimension] != source[Dimension];

        return not_equal
            ? false
            : compare_loop
                <
                    T, Dimension + 1, DimensionCount
                >::apply(source, target);
    }

    static inline bool apply(T const [DimensionCount],
                T const [DimensionCount])
    {

        return true;
    }


    static inline bool apply(Segment const& seg)
    {
        if (! geometry::math::equals
                (
                    geometry::get<0, Dimension>(seg), 
                    geometry::get<1, Dimension>(seg)
                )
            )
        {
            return false;
        }

        return check_duplicate_loop
            <
                Segment, Dimension + 1, DimensionCount
            >::apply(seg);
    }

    static inline bool apply(Segment const&)
    {
        return true;
    }

    static inline void apply(T dims[DimensionCount], int const value)
    {
        dims[Dimension] = value;
        assign_loop<T, Dimension + 1, DimensionCount>::apply(dims, value);
    }

    static inline void apply(T [DimensionCount], int const)
    {
    }


    static inline void apply(Sections& sections, section_type& section,
                int& index, int& ndi,
                Range const& range,
                ring_identifier ring_id)
    {
        if (int(boost::size(range)) <= index)
        {
            return;
        }

        if (index == 0)
        {
            ndi = 0;
        }

        iterator_type it = boost::begin(range);
        it += index;

        for(iterator_type previous = it++;
            it != boost::end(range);
            ++previous, ++it, index++)
        {
            segment_type segment(*previous, *it);

            int direction_classes[DimensionCount] = {0};
            get_direction_loop
                <
                    segment_type, 0, DimensionCount
                >::apply(segment, direction_classes);

            // if "dir" == 0 for all point-dimensions, it is duplicate.
            // Those sections might be omitted, if wished, lateron
            bool duplicate = false;

            if (direction_classes[0] == 0)
            {
                // Recheck because ALL dimensions should be checked,
                // not only first one.
                // (DimensionCount might be < dimension<P>::value)
                if (check_duplicate_loop
                    <
                        segment_type, 0, geometry::dimension<Point>::type::value
                    >::apply(segment)
                    )
                {
                    duplicate = true;

                    // Change direction-info to force new section
                    // Note that wo consecutive duplicate segments will generate
                    // only one duplicate-section.
                    // Actual value is not important as long as it is not -1,0,1
                    assign_loop
                    <
                        int, 0, DimensionCount
                    >::apply(direction_classes, -99);
                }
            }

            if (section.count > 0
                && (!compare_loop
                        <
                            int, 0, DimensionCount
                        >::apply(direction_classes, section.directions)
                    || section.count > MaxCount
                    )
                )
            {
                sections.push_back(section);
                section = section_type();
            }

            if (section.count == 0)
            {
                section.begin_index = index;
                section.ring_id = ring_id;
                section.duplicate = duplicate;
                section.non_duplicate_index = ndi;
                section.range_count = boost::size(range);

                copy_loop
                    <
                        int, 0, DimensionCount
                    >::apply(direction_classes, section.directions);
                geometry::expand(section.bounding_box, *previous);
            }

            geometry::expand(section.bounding_box, *it);
            section.end_index = index + 1;
            section.count++;
            if (! duplicate)
            {
                ndi++;
            }
        }
    }


    static inline void apply(Range const& range, Sections& sections,
                ring_identifier ring_id)
    {
        typedef model::referring_segment<Point const> segment_type;

        cview_type cview(range);
        view_type view(cview);

        std::size_t const n = boost::size(view);
        if (n == 0)
        {
            // Zero points, no section
            return;
        }

        if (n == 1)
        {
            // Line with one point ==> no sections
            return;
        }

        int index = 0;
        int ndi = 0; // non duplicate index

        typedef typename boost::range_value<Sections>::type section_type;
        section_type section;

        sectionalize_part
            <
                view_type, Point, Sections,
                DimensionCount, MaxCount
            >::apply(sections, section, index, ndi,
                        view, ring_id);

        // Add last section if applicable
        if (section.count > 0)
        {
            sections.push_back(section);
        }
    }

    static inline void apply(Polygon const& poly, Sections& sections,
                ring_identifier ring_id)
    {
        typedef typename point_type<Polygon>::type point_type;
        typedef typename ring_type<Polygon>::type ring_type;
        typedef sectionalize_range
            <
                ring_type, closure<Polygon>::value, Reverse,
                point_type, Sections, DimensionCount, MaxCount
            > sectionalizer_type;

        ring_id.ring_index = -1;
        sectionalizer_type::apply(exterior_ring(poly), sections, ring_id);//-1, multi_index);

        ring_id.ring_index++;
        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings);
             ++it, ++ring_id.ring_index)
        {
            sectionalizer_type::apply(*it, sections, ring_id);
        }
    }

    static inline void apply(Box const& box, Sections& sections, ring_identifier const& ring_id)
    {
        typedef typename point_type<Box>::type point_type;

        assert_dimension<Box, 2>();

        // Add all four sides of the 2D-box as separate section.
        // Easiest is to convert it to a polygon.
        // However, we don't have the polygon type
        // (or polygon would be a helper-type).
        // Therefore we mimic a linestring/std::vector of 5 points

        // TODO: might be replaced by assign_box_corners_oriented 
        // or just "convert"
        point_type ll, lr, ul, ur;
        geometry::detail::assign_box_corners(box, ll, lr, ul, ur);

        std::vector<point_type> points;
        points.push_back(ll);
        points.push_back(ul);
        points.push_back(ur);
        points.push_back(lr);
        points.push_back(ll);

        sectionalize_range
            <
                std::vector<point_type>, closed, false,
                point_type,
                Sections,
                DimensionCount,
                MaxCount
            >::apply(points, sections, ring_id);
    }


template <typename Sections>
inline void set_section_unique_ids(Sections& sections)
{
    // Set ID's.
    int index = 0;
    for (typename boost::range_iterator<Sections>::type it = boost::begin(sections);
        it != boost::end(sections);
        ++it)
    {
        it->id = index++;
    }
}


template <typename Sections>
inline void enlargeSections(Sections& sections)
{
    // Robustness issue. Increase sections a tiny bit such that all points are really within (and not on border)
    // Reason: turns might, rarely, be missed otherwise (case: "buffer_mp1")
    // Drawback: not really, range is now completely inside the section. Section is a tiny bit too large,
    // which might cause (a small number) of more comparisons
    // TODO: make dimension-agnostic
    for (typename boost::range_iterator<Sections>::type it = boost::begin(sections);
        it != boost::end(sections);
        ++it)
    {
        typedef typename boost::range_value<Sections>::type section_type;
        typedef typename section_type::box_type box_type;
        typedef typename geometry::coordinate_type<box_type>::type coordinate_type;
        coordinate_type const reps = math::relaxed_epsilon(10.0);
        geometry::set<0, 0>(it->bounding_box, geometry::get<0, 0>(it->bounding_box) - reps);
        geometry::set<0, 1>(it->bounding_box, geometry::get<0, 1>(it->bounding_box) - reps);
        geometry::set<1, 0>(it->bounding_box, geometry::get<1, 0>(it->bounding_box) + reps);
        geometry::set<1, 1>(it->bounding_box, geometry::get<1, 1>(it->bounding_box) + reps);
    }
}

template<bool Reverse, typename Geometry, typename Sections>
inline void sectionalize(Geometry const& geometry, Sections& sections, int source_index = 0)
{
    concept::check<Geometry const>();

    // TODO: review use of this constant (see below) as causing problems with GCC 4.6 --mloskot
    // A maximum of 10 segments per section seems to give the fastest results
    //static std::size_t const max_segments_per_section = 10;
    typedef dispatch::sectionalize
        <
            typename tag<Geometry>::type,
            Geometry,
            Reverse,
            Sections,
            Sections::value,
            10 // TODO: max_segments_per_section
        > sectionalizer_type;

    sections.clear();
    ring_identifier ring_id;
    ring_id.source_index = source_index;
    sectionalizer_type::apply(geometry, sections, ring_id);
    detail::sectionalize::set_section_unique_ids(sections);
    detail::sectionalize::enlargeSections(sections);
}


    static inline bool apply(Point const& left, Point const& right)
    {
        coordinate_type const& cleft = geometry::get<Dimension>(left);
        coordinate_type const& cright = geometry::get<Dimension>(right);

        if (geometry::math::equals(cleft, cright))
        {
            return compare_loop
                <
                    Direction, Point, Strategy,
                    Dimension + 1, DimensionCount
                >::apply(left, right);
        }
        else
        {
            compare_type compare;
            return compare(cleft, cright);
        }
    }

    static inline bool apply(Point const&, Point const&)
    {
        // On coming here, points are equal. Return true if
        // direction = 0 (equal), false if -1/1 (greater/less)
        return Direction == 0;
    }

    inline bool operator()(Point const& left, Point const& right) const
    {
        return detail::compare::compare_loop
            <
                Direction, Point, Strategy,
                0, geometry::dimension<Point>::type::value
            >::apply(left, right);
    }

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename geometry::coordinate_type<Point>::type coordinate_type;

        coordinate_type const& cleft = get<Dimension>(left);
        coordinate_type const& cright = get<Dimension>(right);
        return compare(cleft, cright);
    }


    template <typename R>
    static inline return_type segments_intersect(side_info const&,
                    R const& r,
                    coordinate_type const& dx1, coordinate_type const& dy1,
                    coordinate_type const& , coordinate_type const& ,
                    S1 const& s1, S2 const& )
    {
        typedef typename geometry::coordinate_type
            <
                typename return_type::point_type
            >::type return_coordinate_type;

        coordinate_type const s1x = get<0, 0>(s1);
        coordinate_type const s1y = get<0, 1>(s1);

        return_type result;
        result.count = 1;
        set<0>(result.intersections[0],
            boost::numeric_cast<return_coordinate_type>(R(s1x) + r * R(dx1)));
        set<1>(result.intersections[0],
            boost::numeric_cast<return_coordinate_type>(R(s1y) + r * R(dy1)));

        return result;
    }


    static inline return_type collinear_touch(coordinate_type const& x,
                coordinate_type const& y, int, int)
    {
        return_type result;
        result.count = 1;
        set<0>(result.intersections[0], x);
        set<1>(result.intersections[0], y);
        return result;
    }


    template <typename S>
    static inline return_type collinear_inside(S const& s, int index1 = 0, int index2 = 1)
    {
        return_type result;
        result.count = 2;
        set<0>(result.intersections[index1], get<0, 0>(s));
        set<1>(result.intersections[index1], get<0, 1>(s));
        set<0>(result.intersections[index2], get<1, 0>(s));
        set<1>(result.intersections[index2], get<1, 1>(s));
        return result;
    }


    template <typename S>
    static inline return_type collinear_interior_boundary_intersect(S const& s, bool a_in_b,
                int, int, bool opposite)
    {
        int index1 = opposite && ! a_in_b ? 1 : 0;
        return collinear_inside(s, index1, 1 - index1);
    }


    static inline return_type collinear_a_in_b(S1 const& s, bool)
    {
        return collinear_inside(s);
    }

    static inline return_type collinear_b_in_a(S2 const& s, bool opposite)
    {
        int index1 = opposite ? 1 : 0;
        return collinear_inside(s, index1, 1 - index1);
    }


    static inline return_type collinear_overlaps(
                coordinate_type const& x1, coordinate_type const& y1,
                coordinate_type const& x2, coordinate_type const& y2,
                int, int, bool)
    {
        return_type result;
        result.count = 2;
        set<0>(result.intersections[0], x1);
        set<1>(result.intersections[0], y1);
        set<0>(result.intersections[1], x2);
        set<1>(result.intersections[1], y2);
        return result;
    }


    static inline return_type segment_equal(S1 const& s, bool)
    {
        return_type result;
        result.count = 2;
        // TODO: order of IP's
        set<0>(result.intersections[0], get<0, 0>(s));
        set<1>(result.intersections[0], get<0, 1>(s));
        set<0>(result.intersections[1], get<1, 0>(s));
        set<1>(result.intersections[1], get<1, 1>(s));
        return result;
    }


    static inline return_type disjoint()
    {
        return return_type();
    }

    static inline return_type error(std::string const&)
    {
        return return_type();
    }


    static inline return_type collinear_disjoint()
    {
        return return_type();
    }


    static inline return_type degenerate(S1 const& s, bool)
    {
        return_type result;
        result.count = 1;
        set<0>(result.intersections[0], get<0, 0>(s));
        set<1>(result.intersections[0], get<0, 1>(s));
        return result;
    }


    inline direction_type(side_info const& s, char h,
                int ha, int hb,
                int da = 0, int db = 0,
                bool op = false)
        : how(h)
        , opposite(op)
        , how_a(ha)
        , how_b(hb)
        , dir_a(da)
        , dir_b(db)
        , sides(s)
    {
        arrival[0] = ha;
        arrival[1] = hb;
    }


    inline direction_type(char h, bool op, int ha = 0, int hb = 0)
        : how(h)
        , opposite(op)
        , how_a(ha)
        , how_b(hb)
        , dir_a(0)
        , dir_b(0)
    {
        arrival[0] = ha;
        arrival[1] = hb;
    }



    template <typename R>
    static inline return_type segments_intersect(side_info const& sides,
                    R const&,
                    coordinate_type const& dx1, coordinate_type const& dy1,
                    coordinate_type const& dx2, coordinate_type const& dy2,
                    S1 const& s1, S2 const& s2)
    {
        bool const ra0 = sides.get<0,0>() == 0;
        bool const ra1 = sides.get<0,1>() == 0;
        bool const rb0 = sides.get<1,0>() == 0;
        bool const rb1 = sides.get<1,1>() == 0;

        return
            // opposite and same starting point (FROM)
            ra0 && rb0 ? calculate_side<1>(sides, dx1, dy1, s1, s2, 'f', -1, -1)

            // opposite and point to each other (TO)
            : ra1 && rb1 ? calculate_side<0>(sides, dx1, dy1, s1, s2, 't', 1, 1)

            // not opposite, forming an angle, first a then b,
            // directed either both left, or both right
            // Check side of B2 from A. This is not calculated before
            : ra1 && rb0 ? angle<1>(sides, dx1, dy1, s1, s2, 'a', 1, -1)

            // not opposite, forming a angle, first b then a,
            // directed either both left, or both right
            : ra0 && rb1 ? angle<0>(sides, dx1, dy1, s1, s2, 'a', -1, 1)

            // b starts from interior of a
            : rb0 ? starts_from_middle(sides, dx1, dy1, s1, s2, 'B', 0, -1)

            // a starts from interior of b (#39)
            : ra0 ? starts_from_middle(sides, dx1, dy1, s1, s2, 'A', -1, 0)

            // b ends at interior of a, calculate direction of A from IP
            : rb1 ? b_ends_at_middle(sides, dx2, dy2, s1, s2)

            // a ends at interior of b
            : ra1 ? a_ends_at_middle(sides, dx1, dy1, s1, s2)

            // normal intersection
            : calculate_side<1>(sides, dx1, dy1, s1, s2, 'i', -1, -1)
            ;
    }


    static inline return_type collinear_touch(
                coordinate_type const& ,
                coordinate_type const& , int arrival_a, int arrival_b)
    {
        // Though this is 'collinear', we handle it as To/From/Angle because it is the same.
        // It only does NOT have a direction.
        side_info sides;
        //int const arrive = how == 'T' ? 1 : -1;
        bool opposite = arrival_a == arrival_b;
        return
            ! opposite
            ? return_type(sides, 'a', arrival_a, arrival_b)
            : return_type(sides, arrival_a == 0 ? 't' : 'f', arrival_a, arrival_b, 0, 0, true);
    }


    template <typename S>
    static inline return_type collinear_interior_boundary_intersect(S const& , bool,
                    int arrival_a, int arrival_b, bool opposite)
    {
        return_type r('c', opposite);
        r.arrival[0] = arrival_a;
        r.arrival[1] = arrival_b;
        return r;
    }


    static inline return_type collinear_a_in_b(S1 const& , bool opposite)
    {
        return_type r('c', opposite);
        r.arrival[0] = 1;
        r.arrival[1] = -1;
        return r;
    }

    static inline return_type collinear_b_in_a(S2 const& , bool opposite)
    {
        return_type r('c', opposite);
        r.arrival[0] = -1;
        r.arrival[1] = 1;
        return r;
    }


    static inline return_type collinear_overlaps(
                    coordinate_type const& , coordinate_type const& ,
                    coordinate_type const& , coordinate_type const& ,
                    int arrival_a, int arrival_b, bool opposite)
    {
        return_type r('c', opposite);
        r.arrival[0] = arrival_a;
        r.arrival[1] = arrival_b;
        return r;
    }


    static inline return_type segment_equal(S1 const& , bool opposite)
    {
        return return_type('e', opposite);
    }


    static inline return_type degenerate(S1 const& , bool)
    {
        return return_type('0', false);
    }


    static inline return_type disjoint()
    {
        return return_type('d', false);
    }


    static inline return_type collinear_disjoint()
    {
        return return_type('d', false);
    }


    static inline return_type error(std::string const&)
    {
        // Return "E" to denote error
        // This will throw an error in get_turn_info
        // TODO: change to enum or similar
        return return_type('E', false);
    }


    static inline bool is_left
        (
            coordinate_type const& ux, 
            coordinate_type const& uy,
            coordinate_type const& vx,
            coordinate_type const& vy
        )
    {
        // This is a "side calculation" as in the strategies, but here terms are precalculated
        // We might merge this with side, offering a pre-calculated term (in fact already done using cross-product)
        // Waiting for implementing spherical...

        rtype const zero = rtype();
        return geometry::detail::determinant<rtype>(ux, uy, vx, vy) > zero;
    }


    template <std::size_t I>
    static inline return_type calculate_side(side_info const& sides,
                coordinate_type const& dx1, coordinate_type const& dy1,
                S1 const& s1, S2 const& s2,
                char how, int how_a, int how_b)
    {
        coordinate_type dpx = get<I, 0>(s2) - get<0, 0>(s1);
        coordinate_type dpy = get<I, 1>(s2) - get<0, 1>(s1);

        return is_left(dx1, dy1, dpx, dpy)
            ? return_type(sides, how, how_a, how_b, -1, 1)
            : return_type(sides, how, how_a, how_b, 1, -1);
    }


    template <std::size_t I>
    static inline return_type angle(side_info const& sides,
                coordinate_type const& dx1, coordinate_type const& dy1,
                S1 const& s1, S2 const& s2,
                char how, int how_a, int how_b)
    {
        coordinate_type dpx = get<I, 0>(s2) - get<0, 0>(s1);
        coordinate_type dpy = get<I, 1>(s2) - get<0, 1>(s1);

        return is_left(dx1, dy1, dpx, dpy)
            ? return_type(sides, how, how_a, how_b, 1, 1)
            : return_type(sides, how, how_a, how_b, -1, -1);
    }



    static inline return_type starts_from_middle(side_info const& sides,
                coordinate_type const& dx1, coordinate_type const& dy1,
                S1 const& s1, S2 const& s2,
                char which,
                int how_a, int how_b)
    {
        // Calculate ARROW of b segment w.r.t. s1
        coordinate_type dpx = get<1, 0>(s2) - get<0, 0>(s1);
        coordinate_type dpy = get<1, 1>(s2) - get<0, 1>(s1);

        int dir = is_left(dx1, dy1, dpx, dpy) ? 1 : -1;

        // From other perspective, then reverse
        bool const is_a = which == 'A';
        if (is_a)
        {
            dir = -dir;
        }

        return return_type(sides, 's',
            how_a,
            how_b,
            is_a ? dir : -dir,
            ! is_a ? dir : -dir);
    }

    static inline return_type a_ends_at_middle(side_info const& sides,
                coordinate_type const& dx, coordinate_type const& dy,
                S1 const& s1, S2 const& s2)
    {
        coordinate_type dpx = get<1, 0>(s2) - get<0, 0>(s1);
        coordinate_type dpy = get<1, 1>(s2) - get<0, 1>(s1);

        // Ending at the middle, one ARRIVES, the other one is NEUTRAL
        // (because it both "arrives"  and "departs"  there
        return is_left(dx, dy, dpx, dpy)
            ? return_type(sides, 'm', 1, 0, 1, 1)
            : return_type(sides, 'm', 1, 0, -1, -1);
    }



    static inline return_type b_ends_at_middle(side_info const& sides,
                coordinate_type const& dx, coordinate_type const& dy,
                S1 const& s1, S2 const& s2)
    {
        coordinate_type dpx = get<1, 0>(s1) - get<0, 0>(s2);
        coordinate_type dpy = get<1, 1>(s1) - get<0, 1>(s2);

        return is_left(dx, dy, dpx, dpy)
            ? return_type(sides, 'm', 0, 1, 1, 1)
            : return_type(sides, 'm', 0, 1, -1, -1);
    }


    static inline return_type rays_intersect(bool on_segment,
                    double ra, double rb,
                    coordinate_type const& dx1, coordinate_type const& dy1,
                    coordinate_type const& dx2, coordinate_type const& dy2,
                    coordinate_type const& wx, coordinate_type const& wy,
                    S1 const& s1, S2 const& s2)
    {
        if(on_segment)
        {
            // 0 <= ra <= 1 and 0 <= rb <= 1
            // Now check if one of them is 0 or 1, these are "touch" cases
            bool a = math::equals(ra, 0.0) || math::equals(ra, 1.0);
            bool b = math::equals(rb, 0.0) || math::equals(rb, 1.0);
            if (a && b)
            {
                // Touch boundary/boundary: i-i == -1, i-b == -1, b-b == 0
                // Opposite: if both are equal they touch in opposite direction
                return de9im_segment(ra,rb,
                        -1, -1, 1,
                        -1,  0, 0,
                         1,  0, 2, false, math::equals(ra,rb));
            }
            else if (a || b)
            {
                // Touch boundary/interior: i-i == -1, i-b == -1 or 0, b-b == -1
                int A = a ? 0 : -1;
                int B = b ? 0 : -1;
                return de9im_segment(ra,rb,
                        -1,  B, 1,
                         A, -1, 0,
                         1,  0, 2);
            }

            // Intersects: i-i == 0, i-b == -1, i-e == 1
            return de9im_segment(ra,rb,
                     0, -1, 1,
                    -1, -1, 0,
                     1,  0, 2);
        }

        // Not on segment, disjoint
        return de9im_segment(ra,rb,
                -1, -1, 1,
                -1, -1, 0,
                 1,  0, 2);
    }


    static inline return_type collinear_touch(coordinate_type const& x,
                coordinate_type const& y, bool opposite, char)
    {
        return de9im_segment(0,0,
                -1, -1, 1,
                -1,  0, 0,
                 1,  0, 2,
                true, opposite);
    }


    template <typename S>
    static inline return_type collinear_interior_boundary_intersect(S const& s,
                bool a_within_b, bool opposite)
    {
        return a_within_b
            ? de9im_segment(0,0,
                 1, -1, -1,
                 0,  0, -1,
                 1,  0, 2,
                true, opposite)
            : de9im_segment(0,0,
                 1,  0, 1,
                -1,  0, 0,
                -1, -1, 2,
                true, opposite);
    }




    static inline return_type collinear_a_in_b(S1 const& s, bool opposite)
    {
        return de9im_segment(0,0,
                1, -1, -1,
                0, -1, -1,
                1,  0,  2,
                true, opposite);
    }

    static inline return_type collinear_b_in_a(S2 const& s, bool opposite)
    {
        return de9im_segment(0,0,
                 1,  0,  1,
                -1, -1,  0,
                -1, -1,  2,
                true, opposite);
    }


    static inline return_type collinear_overlaps(
                    coordinate_type const& x1, coordinate_type const& y1,
                    coordinate_type const& x2, coordinate_type const& y2, bool opposite)
    {
        return de9im_segment(0,0,
                1,  0, 1,
                0, -1, 0,
                1,  0, 2,
                true, opposite);
    }


    static inline return_type segment_equal(S1 const& s, bool opposite)
    {
        return de9im_segment(0,0,
                 1, -1, -1,
                -1,  0, -1,
                -1, -1,  2,
                 true, opposite);
    }


    static inline return_type degenerate(S1 const& segment, bool a_degenerate)
    {
            return a_degenerate
                ? de9im_segment(0,0,
                     0, -1, -1,
                    -1, -1, -1,
                     1,  0,  2,
                     false, false, false, true)
                : de9im_segment(0,0,
                     0, -1,  1,
                    -1, -1,  0,
                    -1, -1,  2,
                     false, false, false, true);
    }


    static inline return_type collinear_disjoint()
    {
        return de9im_segment(0,0,
                -1, -1, 1,
                -1, -1, 0,
                 1,  0, 2,
                true);
    }


    template <typename R>
    static inline return_type segments_intersect(side_info const& sides,
                    R const& r,
                    coordinate_type const& dx1, coordinate_type const& dy1,
                    coordinate_type const& dx2, coordinate_type const& dy2,
                    segment_type1 const& s1, segment_type2 const& s2)
    {
        return boost::make_tuple
            (
                Policy1::segments_intersect(sides, r,
                    dx1, dy1, dx2, dy2, s1, s2),
                Policy2::segments_intersect(sides, r,
                    dx1, dy1, dx2, dy2, s1, s2)
            );
    }


    static inline return_type collinear_touch(coordinate_type const& x,
                coordinate_type const& y, int arrival_a, int arrival_b)
    {
        return boost::make_tuple
            (
                Policy1::collinear_touch(x, y, arrival_a, arrival_b),
                Policy2::collinear_touch(x, y, arrival_a, arrival_b)
            );
    }


    template <typename S>
    static inline return_type collinear_interior_boundary_intersect(S const& segment,
                bool a_within_b,
                int arrival_a, int arrival_b, bool opposite)
    {
        return boost::make_tuple
            (
                Policy1::collinear_interior_boundary_intersect(segment, a_within_b, arrival_a, arrival_b, opposite),
                Policy2::collinear_interior_boundary_intersect(segment, a_within_b, arrival_a, arrival_b, opposite)
            );
    }


    static inline return_type collinear_a_in_b(segment_type1 const& segment,
                bool opposite)
    {
        return boost::make_tuple
            (
                Policy1::collinear_a_in_b(segment, opposite),
                Policy2::collinear_a_in_b(segment, opposite)
            );
    }

    static inline return_type collinear_b_in_a(segment_type2 const& segment,
                    bool opposite)
    {
        return boost::make_tuple
            (
                Policy1::collinear_b_in_a(segment, opposite),
                Policy2::collinear_b_in_a(segment, opposite)
            );
    }



    static inline return_type collinear_overlaps(
                    coordinate_type const& x1, coordinate_type const& y1,
                    coordinate_type const& x2, coordinate_type const& y2,
                    int arrival_a, int arrival_b, bool opposite)
    {
        return boost::make_tuple
            (
                Policy1::collinear_overlaps(x1, y1, x2, y2, arrival_a, arrival_b, opposite),
                Policy2::collinear_overlaps(x1, y1, x2, y2, arrival_a, arrival_b, opposite)
            );
    }


    static inline return_type segment_equal(segment_type1 const& s,
                bool opposite)
    {
        return boost::make_tuple
            (
                Policy1::segment_equal(s, opposite),
                Policy2::segment_equal(s, opposite)
            );
    }


    static inline return_type degenerate(segment_type1 const& segment,
                bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::degenerate(segment, a_degenerate),
                Policy2::degenerate(segment, a_degenerate)
            );
    }


    static inline return_type disjoint()
    {
        return boost::make_tuple
            (
                Policy1::disjoint(),
                Policy2::disjoint()
            );
    }


    static inline return_type error(std::string const& msg)
    {
        return boost::make_tuple
            (
                Policy1::error(msg),
                Policy2::error(msg)
            );
    }


    static inline return_type collinear_disjoint()
    {
        return boost::make_tuple
            (
                Policy1::collinear_disjoint(),
                Policy2::collinear_disjoint()
            );
    }

    inline operator Iterator() const
    {
        return this->base();
    }


    explicit inline ever_circling_iterator(Iterator begin, Iterator end,
            bool skip_first = false)
      : m_begin(begin)
      , m_end(end)
      , m_skip_first(skip_first)
    {
        this->base_reference() = begin;
    }


    explicit inline ever_circling_iterator(Iterator begin, Iterator end, Iterator start,
            bool skip_first = false)
      : m_begin(begin)
      , m_end(end)
      , m_skip_first(skip_first)
    {
        this->base_reference() = start;
    }

    inline void moveto(Iterator it)
    {
        this->base_reference() = it;
        check_end();
    }


    inline void increment(bool possibly_skip = true)
    {
        (this->base_reference())++;
        check_end(possibly_skip);
    }


    inline void check_end(bool possibly_skip = true)
    {
        if (this->base() == this->m_end)
        {
            this->base_reference() = this->m_begin;
            if (m_skip_first && possibly_skip)
            {
                increment(false);
            }
        }
    }

    explicit inline ever_circling_range_iterator(Range& range)
        : m_range(&range)
        , m_iterator(boost::begin(range))
        , m_size(boost::size(range))
        , m_index(0)
    {}

    explicit inline ever_circling_range_iterator()
        : m_range(NULL)
        , m_size(0)
        , m_index(0)
    {}


    inline ever_circling_range_iterator<Range>& operator=(ever_circling_range_iterator<Range> const& source)
    {
        m_range = source.m_range;
        m_iterator = source.m_iterator;
        m_size = source.m_size;
        m_index = source.m_index;
        return *this;
    }

    explicit inline closing_iterator(Range& range)
        : m_range(&range)
        , m_iterator(boost::begin(range))
        , m_end(boost::end(range))
        , m_size(boost::size(range))
        , m_index(0)
    {}

    explicit inline closing_iterator(Range& range, bool)
        : m_range(&range)
        , m_iterator(boost::end(range))
        , m_end(boost::end(range))
        , m_size(boost::size(range))
        , m_index(m_size + 1)
    {}

    explicit inline closing_iterator()
        : m_range(NULL)
        , m_size(0)
        , m_index(0)
    {}


    inline closing_iterator<Range>& operator=(closing_iterator<Range> const& source)
    {
        m_range = source.m_range;
        m_iterator = source.m_iterator;
        m_end = source.m_end;
        m_size = source.m_size;
        m_index = source.m_index;
        return *this;
    }

    explicit inline closing_view(Range& r)
        : m_range(r)
    {}


    inline const_iterator begin() const { return const_iterator(m_range); }

    inline const_iterator end() const { return const_iterator(m_range, true); }

    explicit segment_view(Segment const& segment)
        : detail::points_view<point_type, 2>(copy_policy(segment))
    {}

        inline copy_policy(Segment const& segment)
            : m_segment(segment)
        {}

        
        inline void apply(point_type* points) const
        {
            geometry::detail::assign_point_from_index<0>(m_segment, points[0]);
            geometry::detail::assign_point_from_index<1>(m_segment, points[1]);
        }


    explicit inline identity_view(Range& r)
        : m_range(r)
    {}


    inline const_iterator begin() const { return boost::begin(m_range); }

    inline const_iterator end() const { return boost::end(m_range); }

    explicit box_view(Box const& box)
        : detail::points_view<point_type, 5>(copy_policy(box))
    {}

        inline copy_policy(Box const& box)
            : m_box(box)
        {}

        
        inline void apply(point_type* points) const
        {
            detail::assign_box_corners_oriented<!Clockwise>(m_box, points);
            points[4] = points[0];
        }

        inline points_iterator(Point const* p)
            : m_points(p)
            , m_index(0) 
        {}

        inline points_iterator(Point const* p, bool)
            : m_points(p)
            , m_index(MaxSize) 
        {}

        inline points_iterator()
            : m_points(NULL)
            , m_index(MaxSize) 
        {}


        inline Point const& dereference() const
        {
            if (m_index >= 0 && m_index < MaxSize)
            {
                return m_points[m_index];
            }
            
            // If it index larger (or smaller) return first point
            // (assuming initialized)
            return m_points[0];
        }


        inline bool equal(points_iterator const& other) const
        {
            return other.m_index == this->m_index;
        }


        inline void increment()
        {
            m_index++;
        }


        inline void decrement()
        {
            m_index--;
        }


        inline difference_type distance_to(points_iterator const& other) const
        {
            return other.m_index - this->m_index;
        }

        
        inline void advance(difference_type n)
        {
            m_index += n;
        }


    const_iterator begin() const { return const_iterator(m_points); }

    const_iterator end() const { return const_iterator(m_points, true); }


    template <typename CopyPolicy>
    explicit points_view(CopyPolicy const& copy)
    {
       copy.apply(m_points);
    }

    template <typename MultiGeometry, typename Strategy>
    static inline void apply(MultiGeometry const& multi, MultiGeometry& out,
                    double max_distance, Strategy const& strategy)
    {
        traits::resize<MultiGeometry>::apply(out, boost::size(multi));

        typename boost::range_iterator<MultiGeometry>::type it_out
                = boost::begin(out);
        for (typename boost::range_iterator<MultiGeometry const>::type it_in
                    = boost::begin(multi);
            it_in != boost::end(multi);
            ++it_in, ++it_out)
        {
            Policy::apply(*it_in, *it_out, max_distance, strategy);
        }
    }

    template<typename MultiLinestring, typename Box>
    static inline void apply(MultiLinestring const& mp, Box& mbr)
    {
        assign_inverse(mbr);
        for (typename boost::range_iterator<MultiLinestring const>::type
                    it = mp.begin();
            it != mp.end();
            ++it)
        {
            envelope_range_additional(*it, mbr);
        }
    }

    template<typename MultiPolygon, typename Box>
    static inline void apply(MultiPolygon const& mp, Box& mbr)
    {
        assign_inverse(mbr);
        for (typename boost::range_const_iterator<MultiPolygon>::type
                    it = mp.begin();
            it != mp.end();
            ++it)
        {
            envelope_range_additional(exterior_ring(*it), mbr);
        }
    }

    template <typename Point, typename Strategy>
    static inline void apply(Point const& point,
            Strategy const& strategy, typename Strategy::state_type& state)
    {
        strategy.apply(point, state);
    }

    template <typename Multi, typename Point, typename Strategy>
    static inline void apply(Multi const& multi, Point& centroid,
            Strategy const& strategy)
    {
#if ! defined(BOOST_GEOMETRY_CENTROID_NO_THROW)
        // If there is nothing in any of the ranges, it is not possible
        // to calculate the centroid
        if (geometry::num_points(multi) == 0)
        {
            throw centroid_exception();
        }
#endif

        typename Strategy::state_type state;

        for (typename boost::range_iterator<Multi const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy, state);
        }
        Strategy::result(state, centroid);
    }

    template <typename Strategy>
    static inline typename Strategy::return_type
    apply(MultiGeometry const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   typename Strategy::return_type,
                   area<typename boost::range_value<MultiGeometry>::type>
               >(multi, strategy);
    }

    template <typename MultiGeometry, typename Functor>
    static inline void apply(MultiGeometry& multi, Functor& f)
    {
        for(BOOST_AUTO_TPL(it, boost::begin(multi)); it != boost::end(multi); ++it)
        {
            Policy::apply(*it, f);
        }
    }

    template <typename Multi1, typename Multi2, typename S>
    static inline bool apply(Multi1 const& multi1, Multi2& multi2, S const& strategy)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            if (! Policy::apply(*it1, *it2, strategy))
            {
                return false;
            }
        }

        return true;
    }

    template <typename Strategy>
    static inline bool apply(Point const& point, 
                MultiPolygon const& multi_polygon, Strategy const& strategy)
    {
        return detail::within::geometry_multi_within_code
            <
                Point,
                MultiPolygon,
                Strategy,
                detail::within::point_in_polygon
                        <
                            Point,
                            typename boost::range_value<MultiPolygon>::type,
                            order_as_direction
                                <
                                    geometry::point_order<MultiPolygon>::value
                                >::value,
                            geometry::closure<MultiPolygon>::value,
                            Strategy
                        >
            >::apply(point, multi_polygon, strategy) >= 0;
    }

    static inline std::size_t apply(MultiGeometry const& multi_geometry)
    {
        return boost::size(multi_geometry);
    }

    template <typename MultiGeometry, typename ComparePolicy>
    static inline void apply(MultiGeometry& multi, ComparePolicy const& compare)
    {
        for (typename boost::range_iterator<MultiGeometry>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, compare);
        }
    }

    static inline int apply(Geometry const& geometry,
            MultiGeometry const& multi,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type it
                    = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            // Geometry coding on multi: 1 (within) if within one of them;
            // 0 (touch) if on border of one of them
            int const code = Policy::apply(geometry, *it, strategy);
            if (code != -1)
            {
                return code;
            }
        }
        return -1;
    }

    template <typename Strategy>
    static inline bool apply(Point const& point, 
                MultiPolygon const& multi_polygon, Strategy const& strategy)
    {
        return detail::within::geometry_multi_within_code
            <
                Point,
                MultiPolygon,
                Strategy,
                detail::within::point_in_polygon
                        <
                            Point,
                            typename boost::range_value<MultiPolygon>::type,
                            order_as_direction
                                <
                                    geometry::point_order<MultiPolygon>::value
                                >::value,
                            geometry::closure<MultiPolygon>::value,
                            Strategy
                        >
            >::apply(point, multi_polygon, strategy) == 1;
    }

    template
    <
        typename MultiLinestring1, typename MultiLinestring2,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring1 const& ml1,
            MultiLinestring2 const& ml2, OutputIterator out,
            Strategy const& strategy)
    {
        // Note, this loop is quadratic w.r.t. number of linestrings per input.
        // Future Enhancement: first do the sections of each, then intersect.
        for (typename boost::range_iterator
                <
                    MultiLinestring1 const
                >::type it1 = boost::begin(ml1);
            it1 != boost::end(ml1);
            ++it1)
        {
            for (typename boost::range_iterator
                    <
                        MultiLinestring2 const
                    >::type it2 = boost::begin(ml2);
                it2 != boost::end(ml2);
                ++it2)
            {
                out = intersection_linestring_linestring_point<PointOut>
                      ::apply(*it1, *it2, out, strategy);
            }
        }

        return out;
    }

    template
    <
        typename Linestring, typename MultiLinestring,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linestring const& linestring,
            MultiLinestring const& ml, OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_linestring_linestring_point<PointOut>
                  ::apply(linestring, *it, out, strategy);
        }

        return out;
    }

    template
    <
        typename MultiLinestring, typename Areal,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& ml, Areal const& areal,
            OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_of_linestring_with_areal
                <
                    ReverseAreal, LineStringOut, OverlayType
                >::apply(*it, areal, out, strategy);
        }

        return out;

    }

    template
    <
        typename Areal, typename MultiLinestring,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Areal const& areal, MultiLinestring const& ml,
            OutputIterator out,
            Strategy const& strategy)
    {
        return intersection_of_multi_linestring_with_areal
            <
                ReverseAreal, LineStringOut, OverlayType
            >::apply(ml, areal, out, strategy);
    }

    template
    <
        typename MultiLinestring, typename Box,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& multi_linestring,
            Box const& box, OutputIterator out, Strategy const& )
    {
        typedef typename point_type<LinestringOut>::type point_type;
        strategy::intersection::liang_barsky<Box, point_type> lb_strategy;
        for (typename boost::range_iterator<MultiLinestring const>::type it
            = boost::begin(multi_linestring);
            it != boost::end(multi_linestring); ++it)
        {
            out = detail::intersection::clip_range_with_box
                <LinestringOut>(box, *it, out, lb_strategy);
        }
        return out;
    }

    static inline std::size_t apply(MultiPolygon const& multi_polygon)
    {
        std::size_t n = 0;
        for (typename boost::range_iterator<MultiPolygon const>::type
            it = boost::begin(multi_polygon);
            it != boost::end(multi_polygon);
            ++it)
        {
            n += geometry::num_interior_rings(*it);
        }
        return n;
    }

    static inline void apply(Single const& single, Multi& multi)
    {
        traits::resize<Multi>::apply(multi, 1);
        Policy::apply(single, *boost::begin(multi));
    }

    static inline void apply(Multi1 const& multi1, Multi2& multi2)
    {
        traits::resize<Multi2>::apply(multi2, boost::size(multi1));

        typename boost::range_iterator<Multi1 const>::type it1
                = boost::begin(multi1);
        typename boost::range_iterator<Multi2>::type it2
                = boost::begin(multi2);

        for (; it1 != boost::end(multi1); ++it1, ++it2)
        {
            Policy::apply(*it1, *it2);
        }
    }

    template <typename MultiGeometry>
    static inline size_t apply(MultiGeometry const& geometry, bool add_for_open)
    {
        typedef typename boost::range_value<MultiGeometry>::type geometry_type;
        typedef typename boost::range_iterator
            <
                MultiGeometry const
            >::type iterator_type;

        std::size_t n = 0;
        for (iterator_type it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            n += dispatch::num_points<geometry_type>::apply(*it, add_for_open);
        }
        return n;
    }

    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    static inline void apply(MultiGeometry& multi, Predicate const& predicate)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, predicate);
        }
    }

    static inline bool apply(Point& point, MultiGeometry const& multi, bool midpoint)
    {
        // Take a point on the first multi-geometry
        // (i.e. the first that is not empty)
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            if (Policy::apply(point, *it, midpoint))
            {
                return true;
            }
        }
        return false;
    }

    static inline void apply(
                    typename add_const_if_c<IsConst, Multi>::type& multi,
                    Actor& actor)
    {
        for(BOOST_AUTO_TPL(it, boost::begin(multi)); it != boost::end(multi); ++it)
        {
            geometry::detail::for_each_range(*it, actor);
        }
    }

    template <typename ReturnType, typename Policy, typename MultiGeometry, typename Strategy>
    static inline ReturnType apply(MultiGeometry const& geometry, Strategy const& strategy)
    {
        ReturnType sum = ReturnType();
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }

    static inline void apply(MultiGeometry const& multi_geometry,
            SegmentIdentifier const& seg_id, int to_index,
            RangeOut& current_output)
    {

        BOOST_ASSERT
            (
                seg_id.multi_index >= 0
                && seg_id.multi_index < int(boost::size(multi_geometry))
            );

        // Call the single-version
        Policy::apply(multi_geometry[seg_id.multi_index],
                    seg_id, to_index, current_output);
    }

    static inline void apply(
            int source_id1, Multi const& multi,
            int source_id2, Box const& box,
            Turns& turns, InterruptPolicy& interrupt_policy)
    {
        typedef typename boost::range_iterator
            <
                Multi const
            >::type iterator_type;

        int i = 0;
        for (iterator_type it = boost::begin(multi);
             it != boost::end(multi);
             ++it, ++i)
        {
            // Call its single version
            get_turns_polygon_cs
                <
                    typename boost::range_value<Multi>::type, Box,
                    Reverse, ReverseBox,
                    Turns, TurnPolicy, InterruptPolicy
                >::apply(source_id1, *it, source_id2, box,
                            turns, interrupt_policy, i);
        }
    }

        template <typename Geometry, typename Map>
        static inline void apply(Multi const& multi, Geometry const& geometry,
                    ring_identifier id, Map& map, bool midpoint)
        {
            typedef typename boost::range_iterator
                <
                    Multi const
                >::type iterator_type;

            typedef select_rings<polygon_tag, typename boost::range_value<Multi>::type> per_polygon;

            id.multi_index = 0;
            for (iterator_type it = boost::begin(multi); it != boost::end(multi); ++it)
            {
                id.ring_index = -1;
                per_polygon::apply(*it, geometry, id, map, midpoint);
                id.multi_index++;
            }
        }

    static inline bool apply(MultiGeometry const& multi,
                SegmentIdentifier const& seg_id, bool second,
                PointOut& point)
    {

        BOOST_ASSERT
            (
                seg_id.multi_index >= 0
                && seg_id.multi_index < int(boost::size(multi))
            );

        // Call the single-version
        return Policy::apply(multi[seg_id.multi_index], seg_id, second, point);
    }

    static inline void apply(MultiGeometry const& multi, Sections& sections, ring_identifier ring_id)
    {
        ring_id.multi_index = 0;
        for (typename boost::range_iterator<MultiGeometry const>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it, ++ring_id.multi_index)
        {
            Policy::apply(*it, sections, ring_id);
        }
    }



    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                MultiGeometry const& multi,
                dsv_settings const& settings)
    {
        os << settings.list_open;

        bool first = true;
        for(iterator it = boost::begin(multi);
            it != boost::end(multi);
            ++it, first = false)
        {
            os << (first ? "" : settings.list_separator);
            dispatch_one::apply(os, *it, settings);
        }
        os << settings.list_close;
    }

    static inline void apply(std::string const& wkt, MultiGeometry& geometry)
    {
        traits::clear<MultiGeometry>::apply(geometry);

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it;
        if (initialize<MultiGeometry>(tokens, PrefixPolicy::apply(), wkt, it))
        {
            handle_open_parenthesis(it, tokens.end(), wkt);

            // Parse sub-geometries
            while(it != tokens.end() && *it != ")")
            {
                traits::resize<MultiGeometry>::apply(geometry, boost::size(geometry) + 1);
                Parser
                    <
                        typename boost::range_value<MultiGeometry>::type
                    >::apply(it, tokens.end(), wkt, geometry.back());
                if (it != tokens.end() && *it == ",")
                {
                    // Skip "," after multi-element is parsed
                    ++it;
                }
            }

            handle_close_parenthesis(it, tokens.end(), wkt);
        }
        
        check_end(it, tokens.end(), wkt);
    }

    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
        std::string const& wkt, P& point)
    {
        parsing_assigner<P, 0, dimension<P>::value>::apply(it, end, point, wkt);
    }

    static inline void apply(std::string const& wkt, MultiGeometry& geometry)
    {
        traits::clear<MultiGeometry>::apply(geometry);

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it;

        if (initialize<MultiGeometry>(tokens, PrefixPolicy::apply(), wkt, it))
        {
            handle_open_parenthesis(it, tokens.end(), wkt);

            // If first point definition starts with "(" then parse points as (x y)
            // otherwise as "x y"
            bool using_brackets = (it != tokens.end() && *it == "(");
            
            while(it != tokens.end() && *it != ")")
            {
                traits::resize<MultiGeometry>::apply(geometry, boost::size(geometry) + 1);
                
                if (using_brackets)
                {
                    point_parser
                        <
                            typename boost::range_value<MultiGeometry>::type
                        >::apply(it, tokens.end(), wkt, geometry.back());
                }
                else
                {
                    noparenthesis_point_parser
                        <
                            typename boost::range_value<MultiGeometry>::type
                        >::apply(it, tokens.end(), wkt, geometry.back());
                }
                    
                if (it != tokens.end() && *it == ",")
                {
                    // Skip "," after point is parsed
                    ++it;
                }
            }
            
            handle_close_parenthesis(it, tokens.end(), wkt);
        }
        
        check_end(it, tokens.end(), wkt);
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Multi const& geometry)
    {
        os << PrefixPolicy::apply();
        // TODO: check EMPTY here
        os << "(";

        for (typename boost::range_iterator<Multi const>::type
                    it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            if (it != boost::begin(geometry))
            {
                os << ",";
            }
            StreamPolicy::apply(os, *it);
        }

        os << ")";
    }

    static inline const char* apply() { return ""; }

    static inline const char* apply() { return "MULTIPOINT"; }

    static inline const char* apply() { return "MULTILINESTRING"; }

    static inline const char* apply() { return "MULTIPOLYGON"; }

    inline multi_point()
        : base_type()
    {}

    template <typename Iterator>
    inline multi_point(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

        inline sum()
            : count(0)
        {
            assign_zero(centroid);
        }


    static inline void apply(Point const& p, sum& state)
    {
        add_point(state.centroid, p);
        state.count++;
    }


    static inline void result(sum const& state, PointCentroid& centroid)
    {
        centroid = state.centroid;
        divide_value(centroid, state.count);
    }

template <typename Geometry, int Dimensions>
inline void assert_dimension()
{
    BOOST_STATIC_ASSERT((
        boost::mpl::equal_to
        <
            geometry::dimension<Geometry>,
            boost::mpl::int_<Dimensions>
        >::type::value
        ));
}

template <typename Geometry, int Dimensions>
inline void assert_dimension_less_equal()
{
    BOOST_STATIC_ASSERT(( dimension<Geometry>::type::value <= Dimensions ));
}


template <typename Geometry, int Dimensions>
inline void assert_dimension_greater_equal()
{
    BOOST_STATIC_ASSERT(( dimension<Geometry>::type::value >= Dimensions ));
}

template <typename G1, typename G2>
inline void assert_dimension_equal()
{
    BOOST_STATIC_ASSERT(( dimension<G1>::type::value == dimension<G2>::type::value ));
}

    static inline CoordinateType get(Geometry const& geometry)
    {
        return traits::indexed_access<Geometry, Index, Dimension>::get(geometry);
    }

    static inline void set(Geometry& b, CoordinateType const& value)
    {
        traits::indexed_access<Geometry, Index, Dimension>::set(b, value);
    }

    static inline CoordinateType get(Geometry const* geometry)
    {
        return traits::indexed_access<typename boost::remove_pointer<Geometry>::type, Index, Dimension>::get(*geometry);
    }

    static inline void set(Geometry* geometry, CoordinateType const& value)
    {
        traits::indexed_access<typename boost::remove_pointer<Geometry>::type, Index, Dimension>::set(*geometry, value);
    }

template <std::size_t Dimension, typename Geometry>
inline void set(Geometry& geometry
        , typename coordinate_type<Geometry>::type const& value
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_dimension* dummy = 0
#endif        
        )
{
    boost::ignore_unused_variable_warning(dummy);

    typedef core_dispatch::access
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Dimension,
            typename boost::is_pointer<Geometry>::type
        > coord_access_type;

    coord_access_type::set(geometry, value);
}

    static inline void apply(typename rvalue_type<Range>::type range)
    {
        range.clear();
    }


    static inline void apply(typename rvalue_type<Range>::type range,
                 item_type const& item)
    {
        range.push_back(item);
    }

    static inline void apply(typename rvalue_type<Range>::type range,
                std::size_t new_size)
    {
        range.resize(new_size);
    }


    static inline coordinate_type get(Geometry const& geometry)
    {
        return boost::numeric_cast
            <
                coordinate_type
            >(geometry::get<Dimension>(geometry) * geometry::math::d2r);
    }


    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Dimension>(geometry, boost::numeric_cast
            <
                coordinate_type
            >(radians * geometry::math::r2d));
    }


    static inline coordinate_type get(Geometry const& geometry)
    {
        return geometry::get<Dimension>(geometry);
    }


    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Dimension>(geometry, radians);
    }

template <std::size_t Dimension, typename Geometry>
inline void set_from_radian(Geometry& geometry,
            typename fp_coordinate_type<Geometry>::type const& radians)
{
    detail::radian_access<Dimension, Geometry,
            typename coordinate_system<Geometry>::type>::set(geometry, radians);
}


    inline empty_input_exception() {}


    virtual char const* what() const throw()
    {
        return "Boost.Geometry Empty-Input exception";
    }

    static inline void apply(Geometry& geometry, std::string const& wkt)
    {
        read_wkt<typename tag<Geometry>::type, Geometry>::apply(wkt, geometry);
    }


template <typename Format, typename Geometry>
inline void read(Geometry& geometry, std::string const& wkt)
{
    geometry::concept::check<Geometry>();
    dispatch::read<Format, Geometry>::apply(geometry, wkt);
}


    dsv_settings(std::string const& sep
            , std::string const& open
            , std::string const& close
            , std::string const& psep
            , std::string const& lopen
            , std::string const& lclose
            , std::string const& lsep
            )
        : coordinate_separator(sep)
        , point_open(open)
        , point_close(close)
        , point_separator(psep)
        , list_open(lopen)
        , list_close(lclose)
        , list_separator(lsep)
    {}

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& point,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Dimension>(point);

        stream_coordinate
            <
                Point, Dimension + 1, Count
            >::apply(os, point, settings);
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&,
            Point const&,
            dsv_settings const& )
    {
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << (Dimension > 0 ? settings.coordinate_separator : "")
            << get<Index, Dimension>(geometry);
        stream_indexed
            <
                Geometry, Index, Dimension + 1, Count
            >::apply(os, geometry, settings);
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&, Geometry const&,
            dsv_settings const& )
    {
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Point const& p,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_coordinate<Point, 0, dimension<Point>::type::value>::apply(os, p, settings);
        os << settings.point_close;
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Range const& range,
            dsv_settings const& settings)
    {
        typedef typename boost::range_iterator<Range const>::type iterator_type;

        bool first = true;

        os << settings.list_open;

        for (iterator_type it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            os << (first ? "" : settings.point_separator)
                << settings.point_open;

            stream_coordinate
                <
                    point_type, 0, dimension<point_type>::type::value
                >::apply(os, *it, settings);
            os << settings.point_close;

            first = false;
        }

        os << settings.list_close;
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Polygon const& poly,
                dsv_settings const& settings)
    {
        typedef typename ring_type<Polygon>::type ring;

        os << settings.list_open;

        dsv_range<ring>::apply(os, exterior_ring(poly), settings);

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            os << settings.list_separator;
            dsv_range<ring>::apply(os, *it, settings);
        }
        os << settings.list_close;
    }


    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.point_open;
        stream_indexed
            <
                Geometry, Index, 0, dimension<Geometry>::type::value
            >::apply(os, geometry, settings);
        os << settings.point_close;
    }


    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
            Geometry const& geometry,
            dsv_settings const& settings)
    {
        os << settings.list_open;
        dsv_per_index<Geometry, 0>::apply(os, geometry, settings);
        os << settings.point_separator;
        dsv_per_index<Geometry, 1>::apply(os, geometry, settings);
        os << settings.list_close;
    }


    inline dsv_manipulator(Geometry const& g,
            dsv_settings const& settings)
        : m_geometry(g)
        , m_settings(settings)
    {}

template <typename Geometry>
inline detail::dsv::dsv_manipulator<Geometry> dsv(Geometry const& geometry
    , std::string const& coordinate_separator = ", "
    , std::string const& point_open = "("
    , std::string const& point_close = ")"
    , std::string const& point_separator = ", "
    , std::string const& list_open = "("
    , std::string const& list_close = ")"
    , std::string const& list_separator = ", "
    )
{
    concept::check<Geometry const>();

    return detail::dsv::dsv_manipulator<Geometry>(geometry,
        detail::dsv::dsv_settings(coordinate_separator,
            point_open, point_close, point_separator,
            list_open, list_close, list_separator));
}

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Point const& p, std::string const& style, int size)
    {
        os << "<circle cx=\"" << geometry::get<0>(p)
            << "\" cy=\"" << geometry::get<1>(p)
            << "\" r=\"" << (size < 0 ? 5 : size)
            << "\" style=\"" << style << "\"/>";
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Box const& box, std::string const& style, int )
    {
        // Prevent invisible boxes, making them >=1, using "max"
        BOOST_USING_STD_MAX();

        typedef typename coordinate_type<Box>::type ct;
        ct x = geometry::get<geometry::min_corner, 0>(box);
        ct y = geometry::get<geometry::min_corner, 1>(box);
        ct width = max BOOST_PREVENT_MACRO_SUBSTITUTION(1,
                    geometry::get<geometry::max_corner, 0>(box) - x);
        ct height = max BOOST_PREVENT_MACRO_SUBSTITUTION (1,
                    geometry::get<geometry::max_corner, 1>(box) - y);

        os << "<rect x=\"" << x << "\" y=\"" << y
           << "\" width=\"" << width << "\" height=\"" << height
           << "\" style=\"" << style << "\"/>";
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Range const& range, std::string const& style, int )
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        bool first = true;

        os << "<" << Policy::prefix() << " points=\"";

        for (iterator it = boost::begin(range);
            it != boost::end(range);
            ++it, first = false)
        {
            os << (first ? "" : " " )
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }
        os << "\" style=\"" << style << Policy::style() << "\"/>";
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Polygon const& polygon, std::string const& style, int )
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;
        typedef typename boost::range_iterator<ring_type const>::type iterator_type;

        bool first = true;
        os << "<g fill-rule=\"evenodd\"><path d=\"";

        ring_type const& ring = geometry::exterior_ring(polygon);
        for (iterator_type it = boost::begin(ring);
            it != boost::end(ring);
            ++it, first = false)
        {
            os << (first ? "M" : " L") << " "
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }

        // Inner rings:
        {
            typename interior_return_type<Polygon const>::type rings
                        = interior_rings(polygon);
            for (BOOST_AUTO_TPL(rit, boost::begin(rings));
                rit != boost::end(rings); ++rit)
            {
                first = true;
                for (BOOST_AUTO_TPL(it, boost::begin(*rit)); it != boost::end(*rit);
                    ++it, first = false)
                {
                    os << (first ? "M" : " L") << " "
                        << geometry::get<0>(*it)
                        << ","
                        << geometry::get<1>(*it);
                }
            }
        }
        os << " z \" style=\"" << style << "\"/></g>";

    }

    static inline const char* prefix() { return "polyline"; }

    static inline const char* style() { return ";fill:none"; }

    static inline const char* prefix() { return "polygon"; }

    static inline const char* style() { return ""; }


    inline svg_manipulator(G const& g, std::string const& style, int size)
        : m_geometry(g)
        , m_style(style)
        , m_size(size)
    {}

template <typename Geometry>
inline svg_manipulator<Geometry> svg(Geometry const& geometry, std::string const& style, int size = -1)
{
    concept::check<Geometry const>();

    return svg_manipulator<Geometry>(geometry, style, size);
}

    template <typename TransformStrategy>
    static inline void apply(std::ostream& stream,
                std::string const& style, int size,
                Range1 const& range, TransformStrategy const& strategy)
    {
        Range2 irange;
        geometry::transform(range, irange, strategy);
        stream << geometry::svg(irange, style, size) << std::endl;
    }


    void init_matrix()
    {
        if (! m_matrix)
        {
            m_matrix.reset(new transformer_type(m_bounding_box,
                            m_width, m_height));

            m_stream << "<?xml version=\"1.0\" standalone=\"no\"?>"
                << std::endl
                << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\""
                << std::endl
                << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
                << std::endl
                << "<svg " << m_width_height << " version=\"1.1\""
                << std::endl
                << "xmlns=\"http://www.w3.org/2000/svg\">"
                << std::endl;
        }
    }

    explicit svg_mapper(std::ostream& stream, int width, int height
        , std::string const& width_height = "width=\"100%\" height=\"100%\"")
        : m_stream(stream)
        , m_width(width)
        , m_height(height)
        , m_width_height(width_height)
    {
        assign_inverse(m_bounding_box);
    }

    virtual ~svg_mapper()
    {
        m_stream << "</svg>" << std::endl;
    }

    template <typename Geometry>
    void add(Geometry const& geometry)
    {
        if (num_points(geometry) > 0)
        {
            expand(m_bounding_box,
                return_envelope
                    <
                        model::box<Point>
                    >(geometry));
        }
    }

    template <typename Geometry>
    void map(Geometry const& geometry, std::string const& style,
                int size = -1)
    {
        BOOST_MPL_ASSERT_MSG
        (
            ( boost::is_same
                <
                    Point,
                    typename point_type<Geometry>::type
                >::value )
            , POINT_TYPES_ARE_NOT_SAME_FOR_MAPPER_AND_MAP
            , (types<Point, typename point_type<Geometry>::type>)
        );


        init_matrix();
        svg_map(m_stream, style, size, geometry, *m_matrix);
    }

    template <typename TextPoint>
    void text(TextPoint const& point, std::string const& s,
                std::string const& style,
                int offset_x = 0, int offset_y = 0, int lineheight = 10)
    {
        init_matrix();
        detail::svg::svg_point_type map_point;
        transform(point, map_point, *m_matrix);
        m_stream
            << "<text style=\"" << style << "\""
            << " x=\"" << get<0>(map_point) + offset_x << "\""
            << " y=\"" << get<1>(map_point) + offset_y << "\""
            << ">";
        if (s.find("\n") == std::string::npos)
        {
             m_stream  << s;
        }
        else
        {
            // Multi-line modus

            std::vector<std::string> splitted;
            boost::split(splitted, s, boost::is_any_of("\n"));
            for (std::vector<std::string>::const_iterator it
                = splitted.begin();
                it != splitted.end();
                ++it, offset_y += lineheight)
            {
                 m_stream
                    << "<tspan x=\"" << get<0>(map_point) + offset_x
                    << "\""
                    << " y=\"" << get<1>(map_point) + offset_y
                    << "\""
                    << ">" << *it << "</tspan>";
            }
        }
        m_stream << "</text>" << std::endl;
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        MultiGeometry const& multi, std::string const& style, int size)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(os, *it, style, size);
        }

    }

    template <typename Iterator>
    read_wkt_exception(std::string const& msg,
            Iterator const& it, Iterator const& end, std::string const& wkt)
        : message(msg)
        , wkt(wkt)
    {
        if (it != end)
        {
            source = " at '";
            source += it->c_str();
            source += "'";
        }
        complete = message + source + " in '" + wkt.substr(0, 100) + "'";
    }


    virtual ~read_wkt_exception() throw() {}


    virtual const char* what() const throw()
    {
        return complete.c_str();
    }

    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
            Point& point, std::string const& wkt)
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        // Stop at end of tokens, or at "," ot ")"
        bool finished = (it == end || *it == "," || *it == ")");

        try
        {
            // Initialize missing coordinates to default constructor (zero)
            // OR
            // Use lexical_cast for conversion to double/int
            // Note that it is much slower than atof. However, it is more standard
            // and in parsing the change in performance falls probably away against
            // the tokenizing
            set<Dimension>(point, finished
                    ? coordinate_type()
                    : coordinate_cast<coordinate_type>::apply(*it));
        }
        catch(boost::bad_lexical_cast const& blc)
        {
            throw read_wkt_exception(blc.what(), it, end, wkt);
        }
        catch(std::exception const& e)
        {
            throw read_wkt_exception(e.what(), it, end, wkt);
        }
        catch(...)
        {
            throw read_wkt_exception("", it, end, wkt);
        }

        parsing_assigner<Point, Dimension + 1, DimensionCount>::apply(
                        (finished ? it : ++it), end, point, wkt);
    }

    static inline void apply(tokenizer::iterator&, tokenizer::iterator, Point&,
                std::string const&)
    {
    }




template <typename Iterator>
inline void handle_open_parenthesis(Iterator& it,
            Iterator const& end, std::string const& wkt)
{
    if (it == end || *it != "(")
    {
        throw read_wkt_exception("Expected '('", it, end, wkt);
    }
    ++it;
}



template <typename Iterator>
inline void handle_close_parenthesis(Iterator& it,
            Iterator const& end, std::string const& wkt)
{
    if (it != end && *it == ")")
    {
        ++it;
    }
    else
    {
        throw read_wkt_exception("Expected ')'", it, end, wkt);
    }
}


template <typename Iterator>
inline void check_end(Iterator& it,
            Iterator const& end, std::string const& wkt)
{
    if (it != end)
    {
        throw read_wkt_exception("Too much tokens", it, end, wkt);
    }
}

    template <typename OutputIterator>
    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
        std::string const& wkt, OutputIterator out)
    {
        handle_open_parenthesis(it, end, wkt);

        Point point;

        // Parse points until closing parenthesis

        while (it != end && *it != ")")
        {
            parsing_assigner
                <
                    Point,
                    0,
                    dimension<Point>::value
                >::apply(it, end, point, wkt);
            out = point;
            ++out;
            if (it != end && *it == ",")
            {
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }


    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
        std::string const& wkt, Geometry out)
    {
        handle_open_parenthesis(it, end, wkt);

        point_type point;

        // Parse points until closing parenthesis

        while (it != end && *it != ")")
        {
            parsing_assigner
                <
                    point_type,
                    0,
                    dimension<point_type>::value
                >::apply(it, end, point, wkt);

            geometry::append(out, point);
            if (it != end && *it == ",")
            {
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
        std::string const& wkt, P& point)
    {
        handle_open_parenthesis(it, end, wkt);
        parsing_assigner<P, 0, dimension<P>::value>::apply(it, end, point, wkt);
        handle_close_parenthesis(it, end, wkt);
    }

    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
                std::string const& wkt, Geometry& geometry)
    {
        container_appender<Geometry&>::apply(it, end, wkt, geometry);
    }

    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
                std::string const& wkt, Ring& ring)
    {
        // A ring should look like polygon((x y,x y,x y...))
        // So handle the extra opening/closing parentheses
        // and in between parse using the container-inserter
        handle_open_parenthesis(it, end, wkt);
        container_appender<Ring&>::apply(it, end, wkt, ring);
        handle_close_parenthesis(it, end, wkt);
    }


    static inline void apply(tokenizer::iterator& it, tokenizer::iterator end,
                std::string const& wkt, Polygon& poly)
    {

        handle_open_parenthesis(it, end, wkt);

        int n = -1;

        // Stop at ")"
        while (it != end && *it != ")")
        {
            // Parse ring
            if (++n == 0)
            {
                appender::apply(it, end, wkt, exterior_ring(poly));
            }
            else
            {
                typename ring_type<Polygon>::type ring;
                appender::apply(it, end, wkt, ring);
                traits::push_back
                    <
                        typename boost::remove_reference
                        <
                            typename traits::interior_mutable_type<Polygon>::type
                        >::type
                    >::apply(interior_rings(poly), ring);
            }

            if (it != end && *it == ",")
            {
                // Skip "," after ring is parsed
                ++it;
            }
        }

        handle_close_parenthesis(it, end, wkt);
    }

    static inline void apply(std::string const& wkt, Box& box)
    {
        bool should_close = false;
        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();
        if (it != end && boost::iequals(*it, "POLYGON"))
        {
            ++it;
            bool has_empty, has_z, has_m;
            handle_empty_z_m(it, end, has_empty, has_z, has_m);
            if (has_empty)
            {
                assign_zero(box);
                return;
            }
            handle_open_parenthesis(it, end, wkt);
            should_close = true;
        }
        else if (it != end && boost::iequals(*it, "BOX"))
        {
            ++it;
        }
        else
        {
            throw read_wkt_exception("Should start with 'POLYGON' or 'BOX'", wkt);
        }

        typedef typename point_type<Box>::type point_type;
        std::vector<point_type> points;
        container_inserter<point_type>::apply(it, end, wkt, std::back_inserter(points));

        if (should_close)
        {
            handle_close_parenthesis(it, end, wkt);
        }
        check_end(it, end, wkt);

        int index = 0;
        int n = boost::size(points);
        if (n == 2)
        {
            index = 1;
        }
        else if (n == 4 || n == 5)
        {
            // In case of 4 or 5 points, we do not check the other ones, just
            // take the opposite corner which is always 2
            index = 2;
        }
        else
        {
            throw read_wkt_exception("Box should have 2,4 or 5 points", wkt);
        }

        geometry::detail::assign_point_to_index<min_corner>(points.front(), box);
        geometry::detail::assign_point_to_index<max_corner>(points[index], box);
    }

    static inline void apply(std::string const& wkt, Segment& segment)
    {
        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();
        if (it != end &&
            (boost::iequals(*it, "SEGMENT")
            || boost::iequals(*it, "LINESTRING") ))
        {
            ++it;
        }
        else
        {
            throw read_wkt_exception("Should start with 'LINESTRING' or 'SEGMENT'", wkt);
        }

        typedef typename point_type<Segment>::type point_type;
        std::vector<point_type> points;
        container_inserter<point_type>::apply(it, end, wkt, std::back_inserter(points));

        check_end(it, end, wkt);

        if (boost::size(points) == 2)
        {
            geometry::detail::assign_point_to_index<0>(points.front(), segment);
            geometry::detail::assign_point_to_index<1>(points.back(), segment);
        }
        else
        {
            throw read_wkt_exception("Segment should have 2 points", wkt);
        }

    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os, P const& p)
    {
        os << (I > 0 ? " " : "") << get<I>(p);
        stream_coordinate<P, I + 1, Count>::apply(os, p);
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>&, P const&)
    {}

    static inline const char* apply() { return "LINESTRING("; }

    static inline const char* apply() { return "POLYGON(("; }

    static inline const char* apply() { return "("; }

    static inline const char* apply() { return ")"; }

    static inline const char* apply() { return "))"; }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os, Point const& p)
    {
        os << Policy::apply() << "(";
        stream_coordinate<Point, 0, dimension<Point>::type::value>::apply(os, p);
        os << ")";
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Range const& range)
    {
        typedef typename boost::range_iterator<Range const>::type iterator_type;

        bool first = true;

        os << PrefixPolicy::apply();

        // TODO: check EMPTY here

        for (iterator_type it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            os << (first ? "" : ",");
            stream_coordinate
                <
                    point_type, 0, dimension<point_type>::type::value
                >::apply(os, *it);
            first = false;
        }

        os << SuffixPolicy::apply();
    }

    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Polygon const& poly)
    {
        typedef typename ring_type<Polygon const>::type ring;

        os << PrefixPolicy::apply();
        // TODO: check EMPTY here
        os << "(";
        wkt_sequence<ring>::apply(os, exterior_ring(poly));

        typename interior_return_type<Polygon const>::type rings
                    = interior_rings(poly);
        for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
        {
            os << ",";
            wkt_sequence<ring>::apply(os, *it);
        }
        os << ")";
    }


    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Box const& box)
    {
        // Convert to ring, then stream
        typedef model::ring<point_type> ring_type;
        ring_type ring;
        geometry::convert(box, ring);
        os << "POLYGON(";
        wkt_sequence<ring_type>::apply(os, ring);
        os << ")";
    }


        inline wkt_box()
        {
            // Only streaming of boxes with two dimensions is support, otherwise it is a polyhedron!
            //assert_dimension<B, 2>();
        }


    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Segment const& segment)
    {
        // Convert to two points, then stream
        typedef boost::array<point_type, 2> sequence;

        sequence points;
        geometry::detail::assign_point_from_index<0>(segment, points[0]);
        geometry::detail::assign_point_from_index<1>(segment, points[1]);

        // In Boost.Geometry a segment is represented
        // in WKT-format like (for 2D): LINESTRING(x y,x y)
        os << "LINESTRING";
        wkt_sequence<sequence>::apply(os, points);
    }


        inline wkt_segment()
        {}

    template <typename OutputStream>
    static inline void apply(OutputStream& os, Geometry const& geometry)
    {
        wkt<Geometry>::apply(os, geometry);
    }


    inline wkt_manipulator(Geometry const& g)
        : m_geometry(g)
    {}

template <typename Geometry>
inline wkt_manipulator<Geometry> wkt(Geometry const& geometry)
{
    concept::check<Geometry const>();

    return wkt_manipulator<Geometry>(geometry);
}

    static inline const char* apply() { return ""; }

    static inline const char* apply() { return "MULTIPOINT"; }

    static inline const char* apply() { return "MULTILINESTRING"; }

    static inline const char* apply() { return "MULTIPOLYGON"; }

    static inline const char* apply() { return "POINT"; }

    static inline const char* apply() { return "POLYGON"; }

    static inline const char* apply() { return "LINESTRING"; }


    inline explicit insert_iterator(Container & c)
        : container(&c)
    {}

    
    insert_iterator & operator=(typename Container::value_type const& value)
    {
        container->insert(value);
        return *this;
    }


    insert_iterator & operator* ()
    {
        return *this;
    }


    insert_iterator & operator++ ()
    {
        return *this;
    }


    insert_iterator operator++(int)
    {
        return *this;
    }

template <typename Container>
insert_iterator<Container> inserter(Container & c)
{
    return insert_iterator<Container>(c);
}

    static bool apply(Geometry const& g1, Geometry const& g2)
    {
        return geometry::equals(g1, g2);
    }

    static bool apply(T const& v1, T const& v2)
    {
        return v1 == v2;
    }

    inline static bool apply(Tuple const& t1, Tuple const& t2)
    {
        typedef typename boost::tuples::element<I, Tuple>::type T;
        return
            equals<
                T, typename geometry::traits::tag<T>::type
            >::apply(boost::get<I>(t1), boost::get<I>(t2))
            &&
            tuple_equals<Tuple, I+1, N>::apply(t1, t2);
    }

    inline static bool apply(Tuple const&, Tuple const&)
    {
        return true;
    }

    bool operator()(Value const& l, Value const& r) const
    {
        return detail::equals<Value, typename geometry::traits::tag<Value>::type>::apply(l ,r);
    }

    inline static bool apply(Tuple const& t1, Tuple const& t2)
    {
        typedef typename std::tuple_element<I, Tuple>::type T;
        return
            equals<
                T, typename geometry::traits::tag<T>::type
            >::apply(std::get<I>(t1), std::get<I>(t2))
            &&
            std_tuple_equals<Tuple, I+1, N>::apply(t1, t2);
    }

    inline static bool apply(Tuple const&, Tuple const&)
    {
        return true;
    }


inline size_t default_min_elements_d()
{
    return (std::numeric_limits<size_t>::max)();
}


inline size_t default_min_elements_d_calc(size_t max_elements, size_t min_elements)
{
    if ( default_min_elements_d() == min_elements )
    {
        // TODO - assert MaxElements <= (std::numeric_limits<size_t>::max)()/3
        size_t raw_value = (max_elements * 3) / 10;
        return 1 <= raw_value ? raw_value : 1;
    }
    
    return min_elements;
}


inline size_t default_rstar_reinserted_elements_d()
{
    return (std::numeric_limits<size_t>::max)();
}


inline size_t default_rstar_reinserted_elements_d_calc(size_t max_elements, size_t reinserted_elements)
{
    if ( default_rstar_reinserted_elements_d() == reinserted_elements )
    {
        // TODO - assert MaxElements <= (std::numeric_limits<size_t>::max)()/3
        return (max_elements * 3) / 10;
    }
    
    return reinserted_elements;
}


    static size_t get_max_elements() { return MaxElements; }

    static size_t get_min_elements() { return MinElements; }


    static size_t get_max_elements() { return MaxElements; }

    static size_t get_min_elements() { return MinElements; }


    static size_t get_max_elements() { return MaxElements; }

    static size_t get_min_elements() { return MinElements; }

    static size_t get_reinserted_elements() { return ReinsertedElements; }

    static size_t get_overlap_cost_threshold() { return OverlapCostThreshold; }

    dynamic_linear(size_t max_elements,
                   size_t min_elements = detail::default_min_elements_d())
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_linear");
    }


    size_t get_max_elements() const { return m_max_elements; }

    size_t get_min_elements() const { return m_min_elements; }

    dynamic_quadratic(size_t max_elements,
                      size_t min_elements = detail::default_min_elements_d())
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_quadratic");
    }


    size_t get_max_elements() const { return m_max_elements; }

    size_t get_min_elements() const { return m_min_elements; }

    dynamic_rstar(size_t max_elements,
                  size_t min_elements = detail::default_min_elements_d(),
                  size_t reinserted_elements = detail::default_rstar_reinserted_elements_d(),
                  size_t overlap_cost_threshold = 32)
        : m_max_elements(max_elements)
        , m_min_elements(detail::default_min_elements_d_calc(max_elements, min_elements))
        , m_reinserted_elements(detail::default_rstar_reinserted_elements_d_calc(max_elements, reinserted_elements))
        , m_overlap_cost_threshold(overlap_cost_threshold)
    {
        if (!(0 < m_min_elements && 2*m_min_elements <= m_max_elements+1))
            detail::throw_invalid_argument("invalid min or/and max parameters of dynamic_rstar");
    }


    size_t get_max_elements() const { return m_max_elements; }

    size_t get_min_elements() const { return m_min_elements; }

    size_t get_reinserted_elements() const { return m_reinserted_elements; }

    size_t get_overlap_cost_threshold() const { return m_overlap_cost_threshold; }

    result_type operator()(Value const& v) const
    {
        return v;
    }


    translator(IndexableGetter const& i, EqualTo const& e)
        : IndexableGetter(i), EqualTo(e)
    {}


    template <typename Value>
    result_type operator()(Value const& value) const
    {
        return IndexableGetter::operator()(value);
    }


    template <typename Value>
    bool equals(Value const& v1, Value const& v2) const
    {
        return EqualTo::operator()(v1, v2);
    }


    static inline void check_capacity(Varray const& v, size_type s)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(s <= v.capacity(), "size too big");

        ::boost::ignore_unused_variable_warning(v);
        ::boost::ignore_unused_variable_warning(s);
    }


    static inline void throw_out_of_bounds(Varray const& v, size_type i)
    {
//#ifndef BOOST_NO_EXCEPTIONS
        if ( v.size() <= i )
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of bounds"));
//#else // BOOST_NO_EXCEPTIONS
//        BOOST_GEOMETRY_INDEX_ASSERT(i < v.size(), "index out of bounds");
//#endif // BOOST_NO_EXCEPTIONS

        ::boost::ignore_unused_variable_warning(v);
        ::boost::ignore_unused_variable_warning(i);
    }


    static inline void check_index(Varray const& v, size_type i)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(i < v.size(), "index out of bounds");

        ::boost::ignore_unused_variable_warning(v);
        ::boost::ignore_unused_variable_warning(i);
    }


    static inline void check_not_empty(Varray const& v)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(!v.empty(), "the container is empty");
        
        ::boost::ignore_unused_variable_warning(v);
    }


    static inline void check_iterator_end_neq(Varray const& v, const_iterator position)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(v.begin() <= position && position < v.end(), "iterator out of bounds");

        ::boost::ignore_unused_variable_warning(v);
        ::boost::ignore_unused_variable_warning(position);
    }


    static inline void check_iterator_end_eq(Varray const& v, const_iterator position)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(v.begin() <= position && position <= v.end(), "iterator out of bounds");

        ::boost::ignore_unused_variable_warning(v);
        ::boost::ignore_unused_variable_warning(position);
    }

    varray()
        : m_size(0)
    {}

    explicit varray(size_type count)
        : m_size(0)
    {
        this->resize(count);                                                        // may throw
    }

    template <typename Iterator>
    varray(Iterator first, Iterator last)
        : m_size(0)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator
        
        this->assign(first, last);                                                    // may throw
    }

    varray(varray const& other)
        : m_size(other.size())
    {
        namespace sv = varray_detail;
        sv::uninitialized_copy(other.begin(), other.end(), this->begin());          // may throw
    }

    varray & operator=(BOOST_COPY_ASSIGN_REF(varray) other)
    {
        this->assign(other.begin(), other.end());                                     // may throw

        return *this;
    }

    varray(BOOST_RV_REF(varray) other)
    {
        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    template <std::size_t C>
    varray(BOOST_RV_REF_2_TEMPL_ARGS(varray, value_type, C) other)
        : m_size(other.m_size)
    {
        errh::check_capacity(*this, other.size());                                  // may throw

        typedef typename
        vt::use_memop_in_swap_and_move use_memop_in_swap_and_move;

        this->move_ctor_dispatch(other, use_memop_in_swap_and_move());
    }

    ~varray()
    {
        namespace sv = varray_detail;
        sv::destroy(this->begin(), this->end());
    }

    void swap(varray & other)
    {
        typedef typename
        vt::use_optimized_swap use_optimized_swap;

        this->swap_dispatch(other, use_optimized_swap());
    }

    void resize(size_type count)
    {
        namespace sv = varray_detail;
        typedef typename vt::disable_trivial_init dti;

        if ( count < m_size )
        {
            sv::destroy(this->begin() + count, this->end());
        }
        else
        {
            errh::check_capacity(*this, count);                                     // may throw

            sv::uninitialized_fill(this->end(), this->begin() + count, dti()); // may throw
        }
        m_size = count; // update end
    }

    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    void push_back(value_type const& value)
    {
        typedef typename vt::disable_trivial_init dti;

        errh::check_capacity(*this, m_size + 1);                                    // may throw
        
        namespace sv = varray_detail;
        sv::construct(dti(), this->end(), value);                                          // may throw
        ++m_size; // update end
    }

    void pop_back()
    {
        errh::check_not_empty(*this);

        namespace sv = varray_detail;
        sv::destroy(this->end() - 1);
        --m_size; // update end
    }

    iterator insert(iterator position, value_type const& value)
    {
        typedef typename vt::disable_trivial_init dti;
        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, m_size + 1);                                    // may throw

        if ( position == this->end() )
        {
            sv::construct(dti(), position, value);                                  // may throw
            ++m_size; // update end
        }
        else
        {
            // TODO - should move be used only if it's nonthrowing?
            value_type & r = *(this->end() - 1);
            sv::construct(dti(), this->end(), boost::move(r));                      // may throw
            ++m_size; // update end
            sv::move_backward(position, this->end() - 2, this->end() - 1);          // may throw
            sv::assign(position, value);                                            // may throw
        }

        return position;
    }

    template <typename Iterator>
    iterator insert(iterator position, Iterator first, Iterator last)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->insert_dispatch(position, first, last, traversal());

        return position;
    }

    iterator erase(iterator position)
    {
        namespace sv = varray_detail;

        errh::check_iterator_end_neq(*this, position);

        //TODO - add empty check?
        //errh::check_empty(*this);

        sv::move(position + 1, this->end(), position);                              // may throw
        sv::destroy(this->end() - 1);
        --m_size;

        return position;
    }

    iterator erase(iterator first, iterator last)
    {
        namespace sv = varray_detail;

        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);
        
        difference_type n = std::distance(first, last);
        
        //TODO - add invalid range check?
        //BOOST_ASSERT_MSG(0 <= n, "invalid range");
        //TODO - add this->size() check?
        //BOOST_ASSERT_MSG(n <= this->size(), "invalid range");

        sv::move(last, this->end(), first);                                         // may throw
        sv::destroy(this->end() - n, this->end());
        m_size -= n;

        return first;
    }

    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversal<Iterator>)); // Make sure you passed a ForwardIterator

        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        this->assign_dispatch(first, last, traversal());                            // may throw
    }

    void clear()
    {
        namespace sv = varray_detail;
        sv::destroy(this->begin(), this->end());
        m_size = 0; // update end
    }

    reference at(size_type i)
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    const_reference at(size_type i) const
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    reference operator[](size_type i)
    {
        // TODO: Remove bounds check? std::vector and std::array operator[] don't check.
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    const_reference operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    reference front()
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    const_reference front() const
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    reference back()
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    const_reference back() const
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    Value * data()
    {
        return boost::addressof(*(this->ptr()));
    }

    const Value * data() const
    {
        return boost::addressof(*(this->ptr()));
    }

    iterator begin() { return this->ptr(); }

    const_iterator begin() const { return this->ptr(); }

    const_iterator cbegin() const { return this->ptr(); }

    iterator end() { return this->begin() + m_size; }

    const_iterator end() const { return this->begin() + m_size; }

    const_iterator cend() const { return this->cbegin() + m_size; }

    reverse_iterator rbegin() { return reverse_iterator(this->end()); }

    const_reverse_iterator crbegin() const { return reverse_iterator(this->end()); }

    reverse_iterator rend() { return reverse_iterator(this->begin()); }

    const_reverse_iterator crend() const { return reverse_iterator(this->begin()); }

    static size_type capacity() { return Capacity; }

    static size_type max_size() { return Capacity; }

    size_type size() const { return m_size; }

    bool empty() const { return 0 == m_size; }

    template <std::size_t C>
    void move_ctor_dispatch(varray<value_type, C> & other, boost::true_type /*use_memop*/)
    {
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        m_size = other.m_size;
    }

    template <std::size_t C>
    void move_assign_dispatch(varray<value_type, C> & other, boost::true_type /*use_memop*/)
    {
        this->clear();

        ::memcpy(this->data(), other.data(), sizeof(Value) * other.m_size);
        std::swap(m_size, other.m_size);
    }

    template <std::size_t C>
    void swap_dispatch(varray<value_type, C> & other, boost::true_type const& /*use_optimized_swap*/)
    {
        typedef typename
        boost::mpl::if_c<
            Capacity < C,
            aligned_storage_type,
            typename varray<value_type, C>::aligned_storage_type
        >::type
        storage_type;
        
        storage_type temp;
        Value * temp_ptr = reinterpret_cast<Value*>(temp.address());

        ::memcpy(temp_ptr, this->data(), sizeof(Value) * this->size());
        ::memcpy(this->data(), other.data(), sizeof(Value) * other.size());
        ::memcpy(other.data(), temp_ptr, sizeof(Value) * this->size());

        std::swap(m_size, other.m_size);
    }

    void swap_dispatch_impl(iterator first_sm, iterator last_sm, iterator first_la, iterator last_la, boost::true_type const& /*use_memop*/)
    {
        //BOOST_ASSERT_MSG(std::distance(first_sm, last_sm) <= std::distance(first_la, last_la));

        namespace sv = varray_detail;
        for (; first_sm != last_sm ; ++first_sm, ++first_la)
        {
            boost::aligned_storage<
                sizeof(value_type),
                boost::alignment_of<value_type>::value
            > temp_storage;
            value_type * temp_ptr = reinterpret_cast<value_type*>(temp_storage.address());

            ::memcpy(temp_ptr, boost::addressof(*first_sm), sizeof(value_type));
            ::memcpy(boost::addressof(*first_sm), boost::addressof(*first_la), sizeof(value_type));
            ::memcpy(boost::addressof(*first_la), temp_ptr, sizeof(value_type));
        }

        ::memcpy(first_sm, first_la, sizeof(value_type) * std::distance(first_la, last_la));
    }

    template <typename Iterator>
    void insert_dispatch(iterator position, Iterator first, Iterator last, boost::random_access_traversal_tag const&)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversal<Iterator>)); // Make sure you passed a RandomAccessIterator
        
        errh::check_iterator_end_eq(*this, position);
        
        typename boost::iterator_difference<Iterator>::type
            count = std::distance(first, last);

        errh::check_capacity(*this, m_size + count);                                             // may throw

        if ( position == this->end() )
        {
            namespace sv = varray_detail;

            sv::uninitialized_copy(first, last, position);                                      // may throw
            m_size += count; // update end
        }
        else
        {
            this->insert_in_the_middle(position, first, last, count);                           // may throw
        }
    }

    template <typename Iterator, typename Traversal>
    void insert_dispatch(iterator position, Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        errh::check_iterator_end_eq(*this, position);

        if ( position == this->end() )
        {
            namespace sv = varray_detail;

            std::ptrdiff_t d = std::distance(position, this->begin() + Capacity);
            std::size_t count = sv::uninitialized_copy_s(first, last, position, d);                     // may throw
            
            errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? m_size + count : Capacity + 1);  // may throw

            m_size += count;
        }
        else
        {
            typename boost::iterator_difference<Iterator>::type
                count = std::distance(first, last);
            
            errh::check_capacity(*this, m_size + count);                                                // may throw

            this->insert_in_the_middle(position, first, last, count);                                   // may throw
        }
    }

    template <typename Iterator>
    void insert_in_the_middle(iterator position, Iterator first, Iterator last, difference_type count)
    {
        namespace sv = varray_detail;

        difference_type to_move = std::distance(position, this->end());

        // TODO - should following lines check for exception and revert to the old size?

        if ( count < to_move )
        {
            sv::uninitialized_move(this->end() - count, this->end(), this->end());              // may throw
            m_size += count; // update end
            sv::move_backward(position, position + to_move - count, this->end() - count);       // may throw
            sv::copy(first, last, position);                                                    // may throw
        }
        else
        {
            Iterator middle_iter = first;
            std::advance(middle_iter, to_move);

            sv::uninitialized_copy(middle_iter, last, this->end());                             // may throw
            m_size += count - to_move; // update end
            sv::uninitialized_move(position, position + to_move, position + count);             // may throw
            m_size += to_move; // update end
            sv::copy(first, middle_iter, position);                                             // may throw
        }
    }

    template <typename Iterator>
    void assign_dispatch(Iterator first, Iterator last, boost::random_access_traversal_tag const& /*not_random_access*/)
    {
        namespace sv = varray_detail;

        typename boost::iterator_difference<Iterator>::type
            s = std::distance(first, last);

        errh::check_capacity(*this, s);                                     // may throw

        if ( m_size <= static_cast<size_type>(s) )
        {
            sv::copy(first, first + m_size, this->begin());                 // may throw
            // TODO - perform uninitialized_copy first?
            sv::uninitialized_copy(first + m_size, last, this->end());      // may throw
        }
        else
        {
            sv::copy(first, last, this->begin());                           // may throw
            sv::destroy(this->begin() + s, this->end());
        }
        m_size = s; // update end
    }

    template <typename Iterator, typename Traversal>
    void assign_dispatch(Iterator first, Iterator last, Traversal const& /*not_random_access*/)
    {
        namespace sv = varray_detail;

        size_type s = 0;
        iterator it = this->begin();

        for ( ; it != this->end() && first != last ; ++it, ++first, ++s )
            *it = *first;                                                                                   // may throw

        sv::destroy(it, this->end());

        std::ptrdiff_t d = std::distance(it, this->begin() + Capacity);
        std::size_t count = sv::uninitialized_copy_s(first, last, it, d);                                   // may throw
        s += count;

        errh::check_capacity(*this, count <= static_cast<std::size_t>(d) ? s : Capacity + 1);               // may throw

        m_size = s; // update end
    }


    pointer ptr()
    {
        return pointer(static_cast<Value*>(m_storage.address()));
    }


    const_pointer ptr() const
    {
        return const_pointer(static_cast<const Value*>(m_storage.address()));
    }

    varray() {}

    explicit varray(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    varray(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    varray(varray const& /*other*/)
    {
        //errh::check_capacity(*this, count);
    }

    template <std::size_t C>
    varray(varray<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
    }

    template <typename Iterator>
    varray(Iterator first, Iterator last)
    {
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    varray & operator=(varray const& /*other*/)
    {
        //errh::check_capacity(*this, other.size());
        return *this;
    }

    template <size_t C>
    varray & operator=(varray<value_type, C> const& other)
    {
        errh::check_capacity(*this, other.size());                                  // may throw
        return *this;
    }

    ~varray() {}

    void resize(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    void resize(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    void reserve(size_type count)
    {
        errh::check_capacity(*this, count);                                         // may throw
    }

    void push_back(value_type const&)
    {
        errh::check_capacity(*this, 1);                                             // may throw
    }

    void pop_back()
    {
        errh::check_not_empty(*this);
    }

    void insert(iterator position, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, 1);                                             // may throw
    }

    void insert(iterator position, size_type count, value_type const&)
    {
        errh::check_iterator_end_eq(*this, position);
        errh::check_capacity(*this, count);                                         // may throw
    }

    template <typename Iterator>
    void insert(iterator, Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    void erase(iterator position)
    {
        errh::check_iterator_end_neq(*this, position);
    }

    void erase(iterator first, iterator last)
    {
        errh::check_iterator_end_eq(*this, first);
        errh::check_iterator_end_eq(*this, last);

        //BOOST_ASSERT_MSG(0 <= n, "invalid range");
    }

    template <typename Iterator>
    void assign(Iterator first, Iterator last)
    {
        // TODO - add MPL_ASSERT, check if Iterator is really an iterator
        typedef typename boost::iterator_traversal<Iterator>::type traversal;
        errh::check_capacity(*this, std::distance(first, last));                    // may throw
    }

    void assign(size_type count, value_type const&)
    {
        errh::check_capacity(*this, count);                                     // may throw
    }

    void clear() {}

    reference at(size_type i)
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    const_reference at(size_type i) const
    {
        errh::throw_out_of_bounds(*this, i);                                   // may throw
        return *(this->begin() + i);
    }

    reference operator[](size_type i)
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    const_reference operator[](size_type i) const
    {
        errh::check_index(*this, i);
        return *(this->begin() + i);
    }

    reference front()
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    const_reference front() const
    {
        errh::check_not_empty(*this);
        return *(this->begin());
    }

    reference back()
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    const_reference back() const
    {
        errh::check_not_empty(*this);
        return *(this->end() - 1);
    }

    Value * data() { return boost::addressof(*(this->ptr())); }

    const Value * data() const { return boost::addressof(*(this->ptr())); }

    iterator begin() { return this->ptr(); }

    const_iterator begin() const { return this->ptr(); }

    const_iterator cbegin() const { return this->ptr(); }

    iterator end() { return this->begin(); }

    const_iterator end() const { return this->begin(); }

    const_iterator cend() const { return this->cbegin(); }

    reverse_iterator rbegin() { return reverse_iterator(this->end()); }

    const_reverse_iterator crbegin() const { return reverse_iterator(this->end()); }

    reverse_iterator rend() { return reverse_iterator(this->begin()); }

    const_reverse_iterator crend() const { return reverse_iterator(this->begin()); }

    size_type capacity() const { return 0; }

    size_type max_size() const { return 0; }

    size_type size() const { return 0; }

    bool empty() const { return true; }

    pointer ptr()
    {
        return pointer(reinterpret_cast<Value*>(this));
    }


    const_pointer ptr() const
    {
        return const_pointer(reinterpret_cast<const Value*>(this));
    }

template<typename V, std::size_t C1, std::size_t C2>
bool operator== (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template<typename V, std::size_t C1, std::size_t C2>
bool operator!= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(x==y);
}

template<typename V, std::size_t C1, std::size_t C2>
bool operator< (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<typename V, std::size_t C1, std::size_t C2>
bool operator> (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return y<x;
}

template<typename V, std::size_t C1, std::size_t C2>
bool operator<= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(y<x);
}

template<typename V, std::size_t C1, std::size_t C2>
bool operator>= (varray<V, C1> const& x, varray<V, C2> const& y)
{
    return !(x<y);
}

template<typename V, std::size_t C1, std::size_t C2>
inline void swap(varray<V, C1> & x, varray<V, C2> & y)
{
    x.swap(y);
}

    to_nearest(T const& v) : value(v) {}

    to_centroid(T const& v) : value(v) {}

    to_furthest(T const& v) : value(v) {}

    static inline T const& value(T const& v) { return v; }

    static inline T & value(T & v) { return v; }

    static inline T const& value(to_nearest<T> const& r) { return r.value; }

    static inline T & value(to_nearest<T> & r) { return r.value; }

    static inline T const& value(to_centroid<T> const& r) { return r.value; }

    static inline T & value(to_centroid<T> & r) { return r.value; }

    static inline T const& value(to_furthest<T> const& r) { return r.value; }

    static inline T & value(to_furthest<T> & r) { return r.value; }

    satisfies_impl(Fun f) : fun(f) {}

    satisfies_impl(Fun const& f) : fun(f) {}


    satisfies(Fun const& f) : base(f) {}

    spatial_predicate(Geometry const& g) : geometry(g) {}

    nearest(PointOrRelation const& por, unsigned k)
        : point_or_relation(por)
        , count(k)
    {}

    path(SegmentOrLinestring const& g, unsigned k)
        : geometry(g)
        , count(k)
    {}

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::within(g2, g1);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::covered_by(g1, g2);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::covered_by(g2, g1);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::disjoint(g1, g2);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::intersects(g1, g2);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::overlaps(g1, g2);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::touches(g1, g2);
    }

    template <typename G1, typename G2>
    static inline bool apply(G1 const& g1, G2 const& g2)
    {
        return geometry::within(g1, g2);
    }

    static type const& get(T const& p) { return p; }

    template <typename Value, typename Indexable>
    static inline bool apply(TuplePredicates const& p, Value const& v, Indexable const& i)
    {
        return
        predicate_check<
            typename boost::tuples::element<First, TuplePredicates>::type,
            Tag
        >::apply(boost::get<First>(p), v, i) &&
        predicates_check_tuple<TuplePredicates, Tag, First+1, Last>::apply(p, v, i);
    }

    template <typename Value, typename Indexable>
    static inline bool apply(TuplePredicates const& , Value const& , Indexable const& )
    {
        return true;
    }


    template <typename Value, typename Indexable>
    static inline bool apply(Predicate const& p, Value const& v, Indexable const& i)
    {
        return predicate_check<Predicate, Tag>::apply(p, v, i);
    }


template <typename Tag, unsigned First, unsigned Last, typename Predicates, typename Value, typename Indexable>
inline bool predicates_check(Predicates const& p, Value const& v, Indexable const& i)
{
    return detail::predicates_check_impl<Predicates, Tag, First, Last>
        ::apply(p, v, i);
}


template <typename I>
void destroy_dispatch(I /*first*/, I /*last*/,
                      boost::true_type const& /*has_trivial_destructor*/)
{}


template <typename I>
void destroy(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(first, last, has_trivial_destructor<value_type>());
}


template <typename I>
void destroy(I pos)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(pos, has_trivial_destructor<value_type>());
}


template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}


template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;
    
    return copy_dispatch(first, last, dst, use_memmove());                       // may throw
}


template <typename I, typename O>
inline
O uninitialized_copy_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}


template <typename I, typename F>
inline
F uninitialized_copy(I first, I last, F dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, F>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<F>::type
        >
    >::type
    use_memcpy;

    return uninitialized_copy_dispatch(first, last, dst, use_memcpy());          // may throw
}


template <typename I, typename O>
inline
O uninitialized_move_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}


template <typename I, typename O>
inline
O uninitialized_move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memcpy;

    return uninitialized_move_dispatch(first, last, dst, use_memcpy());         // may throw
}


template <typename I, typename O>
inline
O move_dispatch(I first, I last, O dst,
                boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}


template <typename I, typename O>
inline
O move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;

    return move_dispatch(first, last, dst, use_memmove());                      // may throw
}


template <typename BDI, typename BDO>
inline
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<BDI>::type value_type;
    typename boost::iterator_difference<BDI>::type d = std::distance(first, last);

    BDO foo(dst - d);
    ::memmove(boost::addressof(*foo), boost::addressof(*first), sizeof(value_type) * d);
    return foo;
}


template <typename BDI, typename BDO>
inline
BDO move_backward(BDI first, BDI last, BDO dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<BDI, BDO>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<BDO>::type
        >
    >::type
    use_memmove;

    return move_backward_dispatch(first, last, dst, use_memmove());             // may throw
}


template <typename I, typename O>
inline
O uninitialized_move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<true> const& /*use_move*/)
{ return uninitialized_move(first, last, dst); }


template <typename I, typename O>
inline
O uninitialized_move_if_noexcept(I first, I last, O dst)
{
    typedef typename has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    >::type use_move;

    return uninitialized_move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}


template <typename I, typename O>
inline
O move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<true> const& /*use_move*/)
{ return move(first, last, dst); }


template <typename I, typename O>
inline
O move_if_noexcept(I first, I last, O dst)
{
    typedef typename has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    >::type use_move;

    return move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}


template <typename I>
inline
void uninitialized_fill_dispatch(I /*first*/, I /*last*/,
                                 boost::true_type const& /*has_trivial_constructor*/,
                                 boost::true_type const& /*disable_trivial_init*/)
{}


template <typename I, typename DisableTrivialInit>
inline
void uninitialized_fill(I first, I last, DisableTrivialInit const& disable_trivial_init)
{
    typedef typename boost::iterator_value<I>::type value_type;
    uninitialized_fill_dispatch(first, last, boost::has_trivial_constructor<value_type>(), disable_trivial_init);     // may throw
}


template <typename DisableTrivialInit, typename I>
inline
void construct(DisableTrivialInit const&, I pos)
{
    typedef typename ::boost::iterator_value<I>::type value_type;
    typedef typename ::boost::mpl::and_<
        boost::has_trivial_constructor<value_type>,
        DisableTrivialInit
    >::type dont_init;

    construct_dispatch(dont_init(), pos);                                                // may throw
}


template <typename DisableTrivialInit, typename I, typename P>
inline
void construct(DisableTrivialInit const&,
               I pos, P const& p)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, P>,
        ::boost::has_trivial_copy<P>
    >::type
    use_memcpy;

    construct_dispatch(pos, p, use_memcpy());                                   // may throw
}


template <typename I, typename V>
inline
void assign_dispatch(I pos, V const& v,
                     boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}


template <typename I, typename V>
inline
void assign(I pos, V const& v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_assign<V>
    >::type
    use_memcpy;

    assign_dispatch(pos, v, use_memcpy());                                        // may throw
}


template <typename I, typename F>
inline std::size_t uninitialized_copy_s(I first, I last, F dest, std::size_t max_count)
{
    std::size_t count = 0;
    F it = dest;

    BOOST_TRY
    {
        for ( ; first != last ; ++it, ++first, ++count )
        {
            if ( max_count <= count )
                return (std::numeric_limits<std::size_t>::max)();

            // dummy 0 as DisableTrivialInit
            construct(0, it, *first);                                              // may throw
        }
    }
    BOOST_CATCH(...)
    {
        destroy(dest, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return count;
}

    scoped_destructor(T * ptr) : m_ptr(ptr) {}


    ~scoped_destructor()
    {
        if(m_ptr)
            destroy(m_ptr);
    }


    void release() { m_ptr = 0; }


    static type apply(Tuple const& tup, T const& t)
    {
        return
        type(
            boost::get<I>(tup),
            push_back_impl<Tuple, T, I+1, N>::apply(tup, t)
        );
    }


    static type apply(Tuple const&, T const& t)
    {
        return type(t, boost::tuples::null_type());
    }


    inline pushable_array()
        : m_size(0)
    {}


    inline explicit pushable_array(size_type s)
        : m_size(s)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(s <= Capacity, "size too big");
    }


    inline void resize(size_type s)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(s <= Capacity, "size too big");
        m_size = s;
    }


    inline void reserve(size_type /*s*/)
    {
        //BOOST_GEOMETRY_INDEX_ASSERT(s <= Capacity, "size too big");
        // do nothing
    }


    inline Element & operator[](size_type i)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(i < m_size, "index of the element outside the container");
        return m_array[i];
    }


    inline Element const& operator[](size_type i) const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(i < m_size, "index of the element outside the container");
        return m_array[i];
    }


    inline Element const& front() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_size, "there are no elements in the container");
        return m_array.front();
    }


    inline Element & front()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_size, "there are no elements in the container");
        return m_array.front();
    }


    inline Element const& back() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_size, "there are no elements in the container");
        return *(begin() + (m_size - 1));
    }


    inline Element & back()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_size, "there are no elements in the container");
        return *(begin() + (m_size - 1));
    }


    inline iterator begin()
    {
        return m_array.begin();
    }


    inline iterator end()
    {
        return m_array.begin() + m_size;
    }


    inline const_iterator begin() const
    {
        return m_array.begin();
    }


    inline const_iterator end() const
    {
        return m_array.begin() + m_size;
    }


    inline reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }


    inline reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }


    inline const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }


    inline const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }


    inline void clear()
    {
        m_size = 0;
    }


    inline void push_back(Element const& v)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_size < Capacity, "can't further increase the size of the container");
        m_array[m_size] = v;
        ++m_size;
    }


    inline void pop_back()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_size, "there are no elements in the container");
        --m_size;
    }


    inline bool empty() const
    {
        return m_size == 0;
    }

    
    inline size_t size() const
    {
        return m_size;
    }


    inline size_t capacity() const
    {
        return Capacity;
    }


template<class T>
static inline void assign_cond(T & l, T const& r, boost::mpl::bool_<true> const&)
{
    l = r;
}


template<class T>
static inline void move_cond(T & l, T & r, boost::mpl::bool_<true> const&)
{
    l = ::boost::move(r);
}


template <typename T> inline
void swap_cond(T & l, T & r, boost::mpl::bool_<true> const&)
{
    ::boost::swap(l, r);
}


inline void throw_runtime_error(const char * str)
{
    throw std::runtime_error(str);
}


inline void throw_logic_error(const char * str)
{
    throw std::logic_error(str);
}


inline void throw_invalid_argument(const char * str)
{
    throw std::invalid_argument(str);
}


inline void throw_length_error(const char * str)
{
    throw std::length_error(str);
}


    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        RelativeDistance ray_d = geometry::get<I>(p1) - geometry::get<I>(p0);
        RelativeDistance tn = ( geometry::get<min_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        RelativeDistance tf = ( geometry::get<max_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        if ( tf < tn )
            ::std::swap(tn, tf);

        if ( t_near < tn )
            t_near = tn;
        if ( tf < t_far )
            t_far = tf;

        return 0 <= t_far && t_near <= t_far;
    }


    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return box_segment_intersection<Box, Point, CurrentDimension - 1>::apply(b, p0, p1, t_near, t_far)
            && for_dim::apply(b, p0, p1, t_near, t_far);
    }


    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return for_dim::apply(b, p0, p1, t_near, t_far);
    }


template <typename Indexable, typename Point, typename RelativeDistance> inline
bool segment_intersection(Indexable const& b,
                          Point const& p0,
                          Point const& p1,
                          RelativeDistance & relative_distance)
{
    // TODO check Indexable and Point concepts

    return dispatch::segment_intersection<
            Indexable, Point,
            typename tag<Indexable>::type
        >::apply(b, p0, p1, relative_distance);
}


    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return simple_margin_for_each_dimension<Box, CurrentDimension - 1>::apply(b) +
            geometry::get<max_corner, CurrentDimension - 1>(b) - geometry::get<min_corner, CurrentDimension - 1>(b);
    }

    static inline typename default_margin_result<Box>::type apply(Box const& b)
    {
        return geometry::get<max_corner, 0>(b) - geometry::get<min_corner, 0>(b);
    }


template <typename Geometry>
typename default_margin_result<Geometry>::type comparable_margin(Geometry const& g)
{
    return dispatch::comparable_margin<
        Geometry,
        typename tag<Geometry>::type
    >::apply(g);
}


template <typename Geometry, typename Bounds>
inline void bounds(Geometry const& g, Bounds & b)
{
    concept::check_concepts_and_equal_dimensions<Geometry const, Bounds>();
    dispatch::bounds<Geometry, Bounds>::apply(g, b);
}


    inline static result_type apply(Point const& pt, PointIndexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }


    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type diff = 0;

        if ( pt_c < ind_c_min )
            diff = ind_c_min - pt_c;
        else if ( ind_c_max < pt_c )
            diff = pt_c - ind_c_max;

        return diff * diff;
    }


template <typename Indexable, typename SegmentOrLinestring> inline
bool path_intersection(Indexable const& b,
                       SegmentOrLinestring const& path,
                       typename default_path_intersection_distance_type<Indexable, SegmentOrLinestring>::type & comparable_distance)
{
    // TODO check Indexable and Linestring concepts

    return dispatch::path_intersection<
            Indexable, SegmentOrLinestring,
            typename tag<Indexable>::type,
            typename tag<SegmentOrLinestring>::type
        >::apply(b, path, comparable_distance);
}


    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return content_box<Box, CurrentDimension - 1>::apply(b) *
            ( get<max_corner, CurrentDimension - 1>(b) - get<min_corner, CurrentDimension - 1>(b) );
    }

    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return get<max_corner, 0>(b) - get<min_corner, 0>(b);
    }


template <typename Indexable>
typename default_content_result<Indexable>::type content(Indexable const& b)
{
    return dispatch::content<Indexable,
                             typename tag<Indexable>::type
                            >::apply(b);
}


    inline static result_type apply(Point const& pt, BoxIndexable const& i, result_type const& maxd)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        indexable_coord_t ind_c_avg = ind_c_min + (ind_c_max - ind_c_min) / 2;
        // TODO: awulkiew - is (ind_c_min + ind_c_max) / 2 safe?

        // TODO: awulkiew - optimize! don't calculate 2x pt_c <= ind_c_avg
        // take particular case pt_c == ind_c_avg into account

        result_type closer_comp = 0;
        if ( pt_c <= ind_c_avg )
            closer_comp = detail::diff_abs(pt_c, ind_c_min); // unsigned values protection
        else
            closer_comp = ind_c_max - pt_c;
        
        result_type further_comp = 0;
        if ( ind_c_avg <= pt_c )
            further_comp = pt_c - ind_c_min;
        else
            further_comp = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return (maxd + closer_comp * closer_comp) - further_comp * further_comp;
    }


    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i) +
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i);
    }


    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i);
    }


    inline static result_type apply(Point const& pt, PointIndexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }


    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);
        
        indexable_coord_t ind_c_avg = ind_c_min + (ind_c_max - ind_c_min) / 2;
        // TODO: awulkiew - is (ind_c_min + ind_c_max) / 2 safe?

        result_type diff = detail::diff_abs(ind_c_avg, pt_c);

        return diff * diff;
    }


template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<true> const& /*is_integral*/)
{
    return v1 < v2 ? v2 - v1 : v1 - v2;
}


template <typename T>
inline T diff_abs(T const& v1, T const& v2)
{
    typedef boost::mpl::bool_<
        boost::is_integral<T>::value
    > is_integral;
    return diff_abs_dispatch(v1, v2, is_integral());
}


    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type further_diff = 0;

        if ( (ind_c_min + ind_c_max) / 2 <= pt_c )
            further_diff = pt_c - ind_c_min;
        else
            further_diff = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return further_diff * further_diff;
    }


    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        result_type r1 = smallest_for_indexable<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        result_type r2 = smallest_for_indexable_dimension<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        return r1 < r2 ? r1 : r2;
    }


    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        return
            smallest_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i, data);
    }


    static inline bool apply(Box const& b)
    {
        return is_valid_box<Box, Dimension - 1>::apply(b) &&
            ( get<min_corner, Dimension - 1>(b) <= get<max_corner, Dimension - 1>(b) );
    }

    static inline bool apply(Box const& b)
    {
        return get<min_corner, 0>(b) <= get<max_corner, 0>(b);
    }


template <typename Indexable>
inline bool is_valid(Indexable const& b)
{
    return dispatch::is_valid<Indexable, typename tag<Indexable>::type>::apply(b);
}

    template <typename Box>
    static inline void apply(Box const& box, typename coordinate_type<Box>::type & length, std::size_t & dim_index)
    {
        biggest_edge<Dimension-1>::apply(box, length, dim_index);
        typename coordinate_type<Box>::type curr
            = geometry::get<max_corner, Dimension-1>(box) - geometry::get<min_corner, Dimension-1>(box);
        if ( length < curr )
        {
            dim_index = Dimension - 1;
            length = curr;
        }
    }

    template <typename Box>
    static inline void apply(Box const& box, typename coordinate_type<Box>::type & length, std::size_t & dim_index)
    {
        dim_index = 0;
        length = geometry::get<max_corner, 0>(box) - geometry::get<min_corner, 0>(box);
    }

    template <typename PointEntry>
    bool operator()(PointEntry const& e1, PointEntry const& e2) const
    {
        return geometry::get<I>(e1.first) < geometry::get<I>(e2.first);
    }

    template <typename EIt, typename Box>
    static inline void apply(EIt first, EIt median, EIt last, Box const& box, Box & left, Box & right, std::size_t dim_index)
    {
        if ( I == dim_index )
        {
            std::partial_sort(first, median, last, point_entries_comparer<I>());

            geometry::convert(box, left);
            geometry::convert(box, right);
            typename coordinate_type<Box>::type edge_len
                = geometry::get<max_corner, I>(box) - geometry::get<min_corner, I>(box);
            typename coordinate_type<Box>::type median
                = geometry::get<min_corner, I>(box) + edge_len / 2;
            geometry::set<max_corner, I>(left, median);
            geometry::set<min_corner, I>(right, median);
        }
        else
            partial_sort_and_half_boxes<I+1, Dimension>::apply(first, median, last, box, left, right, dim_index);
    }

    template <typename EIt, typename Box>
    static inline void apply(EIt , EIt , EIt , Box const& , Box & , Box & , std::size_t ) {}

    template <typename InIt> inline static
    node_pointer apply(InIt first, InIt last, size_type & values_count, size_type & leafs_level,
                       parameters_type const& parameters, Translator const& translator, Allocators & allocators)
    {
        typedef typename std::iterator_traits<InIt>::difference_type diff_type;
            
        diff_type diff = std::distance(first, last);
        if ( diff <= 0 )
            return node_pointer(0);

        typedef std::pair<point_type, InIt> entry_type;
        std::vector<entry_type> entries;

        values_count = static_cast<size_type>(diff);
        entries.reserve(values_count);
        
        Box hint_box;
        geometry::assign_inverse(hint_box);
        for ( ; first != last ; ++first )
        {
            geometry::expand(hint_box, translator(*first));

            point_type pt;
            geometry::centroid(translator(*first), pt);
            entries.push_back(std::make_pair(pt, first));
        }

        subtree_elements_counts subtree_counts = calculate_subtree_elements_counts(values_count, parameters, leafs_level);
        internal_element el = per_level(entries.begin(), entries.end(), hint_box, values_count, subtree_counts,
                                        parameters, translator, allocators);

        return el.second;
    }

        subtree_elements_counts(std::size_t ma, std::size_t mi) : maxc(ma), minc(mi) {}


    template <typename EIt> inline static
    internal_element per_level(EIt first, EIt last, Box const& hint_box, std::size_t values_count, subtree_elements_counts const& subtree_counts,
                               parameters_type const& parameters, Translator const& translator, Allocators & allocators)
    {
        BOOST_ASSERT(0 < std::distance(first, last) && static_cast<std::size_t>(std::distance(first, last)) == values_count);

        if ( subtree_counts.maxc <= 1 )
        {
            // ROOT or LEAF
            BOOST_ASSERT(values_count <= parameters.get_max_elements());
            // if !root check m_parameters.get_min_elements() <= count

            // create new leaf node
            node_pointer n = rtree::create_node<Allocators, leaf>::apply(allocators);                       // MAY THROW (A)
            node_auto_ptr auto_remover(n, allocators);
            leaf & l = rtree::get<leaf>(*n);

            // reserve space for values
            rtree::elements(l).reserve(values_count);                                                       // MAY THROW (A)
            // calculate values box and copy values
            Box elements_box;
            geometry::assign_inverse(elements_box);
            for ( ; first != last ; ++first )
            {
                rtree::elements(l).push_back(*(first->second));                                             // MAY THROW (A?,C)
                geometry::expand(elements_box, translator(*(first->second)));
            }

            auto_remover.release();
            return internal_element(elements_box, n);
        }

        // calculate next max and min subtree counts
        subtree_elements_counts next_subtree_counts = subtree_counts;
        next_subtree_counts.maxc /= parameters.get_max_elements();
        next_subtree_counts.minc /= parameters.get_max_elements();

        // create new internal node
        node_pointer n = rtree::create_node<Allocators, internal_node>::apply(allocators);                  // MAY THROW (A)
        node_auto_ptr auto_remover(n, allocators);
        internal_node & in = rtree::get<internal_node>(*n);

        // reserve space for values
        std::size_t nodes_count = calculate_nodes_count(values_count, subtree_counts);
        rtree::elements(in).reserve(nodes_count);                                                           // MAY THROW (A)
        // calculate values box and copy values
        Box elements_box;
        geometry::assign_inverse(elements_box);

        per_level_packets(first, last, hint_box, values_count, subtree_counts, next_subtree_counts,
                          rtree::elements(in), elements_box,
                          parameters, translator, allocators);

        auto_remover.release();
        return internal_element(elements_box, n);
    }


    template <typename EIt> inline static
    void per_level_packets(EIt first, EIt last, Box const& hint_box,
                           std::size_t values_count,
                           subtree_elements_counts const& subtree_counts,
                           subtree_elements_counts const& next_subtree_counts,
                           internal_elements & elements, Box & elements_box,
                           parameters_type const& parameters, Translator const& translator, Allocators & allocators)
    {
        BOOST_ASSERT(0 < std::distance(first, last) && static_cast<std::size_t>(std::distance(first, last)) == values_count);

        BOOST_ASSERT_MSG( subtree_counts.minc <= values_count, "too small number of elements");

        // only one packet
        if ( values_count <= subtree_counts.maxc )
        {
            // the end, move to the next level
            internal_element el = per_level(first, last, hint_box, values_count, next_subtree_counts,
                                            parameters, translator, allocators);

            // in case if push_back() do throw here
            // and even if this is not probable (previously reserved memory, nonthrowing pairs copy)
            // this case is also tested by exceptions test.
            node_auto_ptr auto_remover(el.second, allocators);
            // this container should have memory allocated, reserve() called outside
            elements.push_back(el);                                                 // MAY THROW (A?,C) - however in normal conditions shouldn't
            auto_remover.release();

            geometry::expand(elements_box, el.first);
            return;
        }
        
        std::size_t median_count = calculate_median_count(values_count, subtree_counts);
        EIt median = first + median_count;

        coordinate_type greatest_length;
        std::size_t greatest_dim_index = 0;
        pack_utils::biggest_edge<dimension>::apply(hint_box, greatest_length, greatest_dim_index);
        Box left, right;
        pack_utils::partial_sort_and_half_boxes<0, dimension>
            ::apply(first, median, last, hint_box, left, right, greatest_dim_index);
        
        per_level_packets(first, median, left,
                          median_count, subtree_counts, next_subtree_counts,
                          elements, elements_box,
                          parameters, translator, allocators);
        per_level_packets(median, last, right,
                          values_count - median_count, subtree_counts, next_subtree_counts,
                          elements, elements_box,
                          parameters, translator, allocators);
    }


    inline static
    subtree_elements_counts calculate_subtree_elements_counts(std::size_t elements_count, parameters_type const& parameters, size_type & leafs_level)
    {
        (void)parameters;

        subtree_elements_counts res(1, 1);
        leafs_level = 0;

        std::size_t smax = parameters.get_max_elements();
        for ( ; smax < elements_count ; smax *= parameters.get_max_elements(), ++leafs_level )
            res.maxc = smax;

        res.minc = parameters.get_min_elements() * (res.maxc / parameters.get_max_elements());

        return res;
    }


    inline static
    std::size_t calculate_nodes_count(std::size_t count,
                                      subtree_elements_counts const& subtree_counts)
    {
        std::size_t n = count / subtree_counts.maxc;
        std::size_t r = count % subtree_counts.maxc;

        if ( 0 < r && r < subtree_counts.minc )
        {
            std::size_t count_minus_min = count - subtree_counts.minc;
            n = count_minus_min / subtree_counts.maxc;
            r = count_minus_min % subtree_counts.maxc;
            ++n;
        }

        if ( 0 < r )
            ++n;

        return n;
    }


    inline static
    std::size_t calculate_median_count(std::size_t count,
                                       subtree_elements_counts const& subtree_counts)
    {
        // e.g. for max = 5, min = 2, count = 52, subtree_max = 25, subtree_min = 10

        std::size_t n = count / subtree_counts.maxc; // e.g. 52 / 25 = 2
        std::size_t r = count % subtree_counts.maxc; // e.g. 52 % 25 = 2
        std::size_t median_count = (n / 2) * subtree_counts.maxc; // e.g. 2 / 2 * 25 = 25

        if ( 0 != r ) // e.g. 0 != 2
        {
            if ( subtree_counts.minc <= r ) // e.g. 10 <= 2 == false
            {
                //BOOST_ASSERT_MSG(0 < n, "unexpected value");
                median_count = ((n+1)/2) * subtree_counts.maxc; // if calculated ((2+1)/2) * 25 which would be ok, but not in all cases
            }
            else // r < subtree_counts.second  // e.g. 2 < 10 == true
            {
                std::size_t count_minus_min = count - subtree_counts.minc; // e.g. 52 - 10 = 42
                n = count_minus_min / subtree_counts.maxc; // e.g. 42 / 25 = 1
                r = count_minus_min % subtree_counts.maxc; // e.g. 42 % 25 = 17
                if ( r == 0 )                               // e.g. false
                {
                    // n can't be equal to 0 because then there wouldn't be any element in the other node
                    //BOOST_ASSERT_MSG(0 < n, "unexpected value");
                    median_count = ((n+1)/2) * subtree_counts.maxc;     // if calculated ((1+1)/2) * 25 which would be ok, but not in all cases
                }
                else
                {
                    if ( n == 0 )                                        // e.g. false
                        median_count = r;                                // if calculated -> 17 which is wrong!
                    else
                        median_count = ((n+2)/2) * subtree_counts.maxc; // e.g. ((1+2)/2) * 25 = 25
                }
            }
        }

        return median_count;
    }


    template <typename Predicates> inline
    query_range(index::rtree<Value, Options, IndexableGetter, EqualTo, Allocator> const& rtree,
                Predicates const& pred)
    {
        rtree.query(pred, std::back_inserter(m_result));
    }


    inline iterator begin() { return m_result.begin(); }

    inline iterator end() { return m_result.end(); }

    inline const_iterator begin() const { return m_result.begin(); }

    inline const_iterator end() const { return m_result.end(); }


    reference operator*() const
    {
        BOOST_ASSERT_MSG(false, "iterator not dereferencable");
        pointer p(0);
        return *p;
    }


    const value_type * operator->() const
    {
        BOOST_ASSERT_MSG(false, "iterator not dereferencable");
        const value_type * p = 0;
        return p;
    }


    end_query_iterator & operator++()
    {
        BOOST_ASSERT_MSG(false, "iterator not incrementable");
        return *this;
    }


    end_query_iterator operator++(int)
    {
        BOOST_ASSERT_MSG(false, "iterator not incrementable");
        return *this;
    }


    inline spatial_query_iterator(Translator const& t, Predicates const& p)
        : m_visitor(t, p)
    {}


    inline spatial_query_iterator(node_pointer root, Translator const& t, Predicates const& p)
        : m_visitor(t, p)
    {
        detail::rtree::apply_visitor(m_visitor, *root);
        m_visitor.increment();
    }


    reference operator*() const
    {
        return m_visitor.dereference();
    }


    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }


    spatial_query_iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }


    spatial_query_iterator operator++(int)
    {
        spatial_query_iterator temp = *this;
        this->operator++();
        return temp;
    }


    inline distance_query_iterator(Translator const& t, Predicates const& p)
        : m_visitor(t, p)
    {}


    inline distance_query_iterator(node_pointer root, Translator const& t, Predicates const& p)
        : m_visitor(t, p)
    {
        detail::rtree::apply_visitor(m_visitor, *root);
        m_visitor.increment();
    }


    reference operator*() const
    {
        return m_visitor.dereference();
    }


    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }


    distance_query_iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }


    distance_query_iterator operator++(int)
    {
        distance_query_iterator temp = *this;
        this->operator++();
        return temp;
    }


    static inline void apply(std::ostream & os, Point const& p)
    {
        print_point<Point, Dimension - 1>::apply(os, p);

        os << ", " << geometry::get<Dimension - 1>(p);
    }

    static inline void apply(std::ostream & os, Point const& p)
    {
        os << geometry::get<0>(p);
    }


    static inline void apply(std::ostream & os, Box const& b)
    {
        print_corner<Box, Corner, Dimension - 1>::apply(os, b);

        os << ", " << geometry::get<Corner, Dimension - 1>(b);
    }

    static inline void apply(std::ostream & os, Box const& b)
    {
        os << geometry::get<Corner, 0>(b);
    }


template <typename Indexable> inline
void print_indexable(std::ostream & os, Indexable const& i)
{
    dispatch::print_indexable<
        Indexable,
        typename tag<Indexable>::type
    >::apply(os, i);
}


    inline print(std::ostream & o, Translator const& t)
        : os(o), tr(t), level(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        spaces(level) << "INTERNAL NODE - L:" << level << " Ch:" << elements.size() << " @:" << &n << '\n';
        
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            spaces(level);
            detail::utilities::print_indexable(os, it->first);
            os << " ->" << it->second << '\n';
        }

        size_t level_backup = level;
        ++level;

        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }

        level = level_backup;
    }


    inline std::ostream & spaces(size_t level)
    {
        for ( size_t i = 0 ; i < 2 * level ; ++i )
            os << ' ';
        return os;
    }


template <typename Rtree> inline
void print(std::ostream & os, Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::print<
        typename RTV::value_type,
        typename RTV::options_type,
        typename RTV::translator_type,
        typename RTV::box_type,
        typename RTV::allocators_type
    > print_v(os, rtv.translator());
    rtv.apply_visitor(print_v);
}


    inline statistics()
        : level(0)
        , levels(1) // count root
        , nodes(0)
        , leaves(0)
        , values(0)
        , values_min(0)
        , values_max(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);
        
        ++nodes; // count node

        size_t const level_backup = level;
        ++level;

        levels += level++ > levels ? 1 : 0; // count level (root already counted)
                
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }
        
        level = level_backup;
    }

    are_boxes_ok(Translator const& tr, bool exact_match)
        : result(false), m_tr(tr), m_is_root(true), m_exact_match(exact_match)
    {}


    void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if (elements.empty())
        {
            result = false;
            return;
        }

        Box box_bckup = m_box;
        bool is_root_bckup = m_is_root;

        m_is_root = false;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() ; ++it)
        {
            m_box = it->first;

            rtree::apply_visitor(*this, *it->second);

            if ( result == false )
                return;
        }

        m_box = box_bckup;
        m_is_root = is_root_bckup;

        Box box_exp;
        geometry::convert(elements.front().first, box_exp);
        for( typename elements_type::const_iterator it = elements.begin() + 1;
            it != elements.end() ; ++it)
        {
            geometry::expand(box_exp, it->first);
        }
        
        if ( m_exact_match )
            result = m_is_root || geometry::equals(box_exp, m_box);
        else
            result = m_is_root || geometry::covered_by(box_exp, m_box);
    }


template <typename Rtree> inline
bool are_boxes_ok(Rtree const& tree, bool exact_match = true)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_boxes_ok<
        typename RTV::value_type,
        typename RTV::options_type,
        typename RTV::translator_type,
        typename RTV::box_type,
        typename RTV::allocators_type
    > v(rtv.translator(), exact_match);
    
    rtv.apply_visitor(v);

    return v.result;
}

    inline are_levels_ok()
        : result(true), m_leafs_level((std::numeric_limits<size_t>::max)()), m_current_level(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if (elements.empty())
        {
            result = false;
            return;
        }

        size_t current_level_backup = m_current_level;
        ++m_current_level;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() ; ++it)
        {
            rtree::apply_visitor(*this, *it->second);

            if ( result == false )
                return;
        }

        m_current_level = current_level_backup;
    }


template <typename Rtree> inline
bool are_levels_ok(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_levels_ok<
        typename RTV::value_type,
        typename RTV::options_type,
        typename RTV::box_type,
        typename RTV::allocators_type
    > v;
    
    rtv.apply_visitor(v);

    return v.result;
}
    

    view(Rtree const& rt) : m_rtree(rt) {}


    template <typename Visitor>
    void apply_visitor(Visitor & vis) const
    {
        m_rtree.apply_visitor(vis);
    }

    translator_type translator() const
    {
        return m_rtree.translator();
    }

    size_type depth() const
    {
        return m_rtree.depth();
    }

    static inline void apply(Point const& p, typename coordinate_type<Point>::type z)
    {
        glBegin(GL_POINT);
        glVertex3f(geometry::get<0>(p), geometry::get<1>(p), z);
        glEnd();
    }

    static inline void apply(Box const& b, typename coordinate_type<Box>::type z)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3f(geometry::get<min_corner, 0>(b), geometry::get<min_corner, 1>(b), z);
        glVertex3f(geometry::get<max_corner, 0>(b), geometry::get<min_corner, 1>(b), z);
        glVertex3f(geometry::get<max_corner, 0>(b), geometry::get<max_corner, 1>(b), z);
        glVertex3f(geometry::get<min_corner, 0>(b), geometry::get<max_corner, 1>(b), z);
        glEnd();
    }


template <typename Indexable> inline
void gl_draw_indexable(Indexable const& i, typename coordinate_type<Indexable>::type z)
{
    dispatch::gl_draw_indexable<
        Indexable,
        typename tag<Indexable>::type
    >::apply(i, z);
}


    inline gl_draw(Translator const& t,
                   size_t level_first = 0,
                   size_t level_last = (std::numeric_limits<size_t>::max)(),
                   typename coordinate_type<Box>::type z_coord_level_multiplier = 1
    )
        : tr(t)
        , level_f(level_first)
        , level_l(level_last)
        , z_mul(z_coord_level_multiplier)
        , level(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if ( level_f <= level )
        {
            size_t level_rel = level - level_f;

            if ( level_rel == 0 )
                glColor3f(0.75f, 0.0f, 0.0f);
            else if ( level_rel == 1 )
                glColor3f(0.0f, 0.75f, 0.0f);
            else if ( level_rel == 2 )
                glColor3f(0.0f, 0.0f, 0.75f);
            else if ( level_rel == 3 )
                glColor3f(0.75f, 0.75f, 0.0f);
            else if ( level_rel == 4 )
                glColor3f(0.75f, 0.0f, 0.75f);
            else if ( level_rel == 5 )
                glColor3f(0.0f, 0.75f, 0.75f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            for (typename elements_type::const_iterator it = elements.begin();
                it != elements.end(); ++it)
            {
                detail::utilities::gl_draw_indexable(it->first, level_rel * z_mul);
            }
        }
        
        size_t level_backup = level;
        ++level;

        if ( level < level_l )
        {
            for (typename elements_type::const_iterator it = elements.begin();
                it != elements.end(); ++it)
            {
                rtree::apply_visitor(*this, *it->second);
            }
        }

        level = level_backup;
    }


template <typename Rtree> inline
void gl_draw(Rtree const& tree,
             size_t level_first = 0,
             size_t level_last = (std::numeric_limits<size_t>::max)(),
             typename coordinate_type<
                    typename Rtree::bounds_type
                >::type z_coord_level_multiplier = 1
             )
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    if ( !tree.empty() )
    {
        glColor3f(0.75f, 0.75f, 0.75f);
        detail::utilities::gl_draw_indexable(tree.bounds(), 0);
    }

    visitors::gl_draw<
        typename RTV::value_type,
        typename RTV::options_type,
        typename RTV::translator_type,
        typename RTV::box_type,
        typename RTV::allocators_type
    > gl_draw_v(rtv.translator(), level_first, level_last, z_coord_level_multiplier);

    rtv.apply_visitor(gl_draw_v);
}


    template <typename Elements, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_index,
                             margin_type & sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename Elements::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
        typedef typename tag<indexable_type>::type indexable_tag;

        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == parameters.get_max_elements() + 1, "wrong number of elements");

        // copy elements
        Elements elements_copy(elements);                                                                       // MAY THROW, STRONG (alloc, copy)
        
        // sort elements
        element_axis_corner_less<element_type, Translator, indexable_tag, Corner, AxisIndex> elements_less(translator);
        std::sort(elements_copy.begin(), elements_copy.end(), elements_less);                                   // MAY THROW, BASIC (copy)

        // init outputs
        choosen_index = parameters.get_min_elements();
        sum_of_margins = 0;
        smallest_overlap = (std::numeric_limits<content_type>::max)();
        smallest_content = (std::numeric_limits<content_type>::max)();

        // calculate sum of margins for all distributions
        size_t index_last = parameters.get_max_elements() - parameters.get_min_elements() + 2;
        for ( size_t i = parameters.get_min_elements() ; i < index_last ; ++i )
        {
            // TODO - awulkiew: may be optimized - box of group 1 may be initialized with
            // box of min_elems number of elements and expanded for each iteration by another element

            Box box1 = rtree::elements_box<Box>(elements_copy.begin(), elements_copy.begin() + i, translator);
            Box box2 = rtree::elements_box<Box>(elements_copy.begin() + i, elements_copy.end(), translator);
            
            sum_of_margins += index::detail::comparable_margin(box1) + index::detail::comparable_margin(box2);

            content_type ovl = index::detail::intersection_content(box1, box2);
            content_type con = index::detail::content(box1) + index::detail::content(box2);

            // TODO - shouldn't here be < instead of <= ?
            if ( ovl < smallest_overlap || (ovl == smallest_overlap && con <= smallest_content) )
            {
                choosen_index = i;
                smallest_overlap = ovl;
                smallest_content = con;
            }
        }

        ::boost::ignore_unused_variable_warning(parameters);
    }


    template <typename Elements, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_axis,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & smallest_sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename rtree::element_indexable_type<typename Elements::value_type, Translator>::type element_indexable_type;

        choose_split_axis_and_index<Parameters, Box, Dimension - 1>::
            apply(elements, choosen_axis, choosen_corner, choosen_index,
                  smallest_sum_of_margins, smallest_overlap, smallest_content,
                  parameters, translator);                                                                  // MAY THROW, STRONG

        margin_type sum_of_margins = 0;

        size_t corner = min_corner;
        size_t index = 0;

        content_type overlap_val = (std::numeric_limits<content_type>::max)();
        content_type content_val = (std::numeric_limits<content_type>::max)();

        choose_split_axis_and_index_for_axis<
            Parameters,
            Box,
            Dimension - 1,
            typename tag<element_indexable_type>::type
        >::apply(elements, corner, index, sum_of_margins, overlap_val, content_val, parameters, translator); // MAY THROW, STRONG

        if ( sum_of_margins < smallest_sum_of_margins )
        {
            choosen_axis = Dimension - 1;
            choosen_corner = corner;
            choosen_index = index;
            smallest_sum_of_margins = sum_of_margins;
            smallest_overlap = overlap_val;
            smallest_content = content_val;
        }
    }


    template <typename Elements, typename Translator>
    static inline void apply(Elements const& elements,
                             size_t & choosen_axis,
                             size_t & choosen_corner,
                             size_t & choosen_index,
                             margin_type & smallest_sum_of_margins,
                             content_type & smallest_overlap,
                             content_type & smallest_content,
                             Parameters const& parameters,
                             Translator const& translator)
    {
        typedef typename rtree::element_indexable_type<typename Elements::value_type, Translator>::type element_indexable_type;

        choosen_axis = 0;

        choose_split_axis_and_index_for_axis<
            Parameters,
            Box,
            0,
            typename tag<element_indexable_type>::type
        >::apply(elements, choosen_corner, choosen_index, smallest_sum_of_margins, smallest_overlap, smallest_content, parameters, translator); // MAY THROW
    }


    template <typename Elements, typename Translator>
    static inline void apply(Elements & elements, const size_t axis, const size_t index, Translator const& tr)
    {
        if ( axis < Dimension - 1 )
        {
            partial_sort<Corner, Dimension - 1>::apply(elements, axis, index, tr);                          // MAY THROW, BASIC (copy)
        }
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(axis == Dimension - 1, "unexpected axis value");

            typedef typename Elements::value_type element_type;
            typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
            typedef typename tag<indexable_type>::type indexable_tag;

            element_axis_corner_less<element_type, Translator, indexable_tag, Corner, Dimension - 1> less(tr);
            std::partial_sort(elements.begin(), elements.begin() + index, elements.end(), less);            // MAY THROW, BASIC (copy)
        }
    }

    template <typename Elements, typename Translator>
    static inline void apply(Elements & elements,
                             const size_t BOOST_GEOMETRY_INDEX_ASSERT_UNUSED_PARAM(axis),
                             const size_t index,
                             Translator const& tr)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(axis == 0, "unexpected axis value");

        typedef typename Elements::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
        typedef typename tag<indexable_type>::type indexable_tag;

        element_axis_corner_less<element_type, Translator, indexable_tag, Corner, 0> less(tr);
        std::partial_sort(elements.begin(), elements.begin() + index, elements.end(), less);                // MAY THROW, BASIC (copy)
    }


    template <typename Node>
    static inline void apply(
        Node & n,
        Node & second_node,
        Box & box1,
        Box & box2,
        parameters_type const& parameters,
        Translator const& translator,
        Allocators & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        
        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);

        size_t split_axis = 0;
        size_t split_corner = 0;
        size_t split_index = parameters.get_min_elements();
        margin_type smallest_sum_of_margins = (std::numeric_limits<margin_type>::max)();
        content_type smallest_overlap = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        rstar::choose_split_axis_and_index<
            typename Options::parameters_type,
            Box,
            dimension
        >::apply(elements1,
                 split_axis, split_corner, split_index,
                 smallest_sum_of_margins, smallest_overlap, smallest_content,
                 parameters, translator);                                                               // MAY THROW, STRONG

        // TODO: awulkiew - get rid of following static_casts?

        BOOST_GEOMETRY_INDEX_ASSERT(split_axis < dimension, "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(split_corner == static_cast<size_t>(min_corner) || split_corner == static_cast<size_t>(max_corner), "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(parameters.get_min_elements() <= split_index && split_index <= parameters.get_max_elements() - parameters.get_min_elements() + 1, "unexpected value");
        
        // copy original elements
        elements_type elements_copy(elements1);                                                         // MAY THROW, STRONG
        elements_type elements_backup(elements1);                                                       // MAY THROW, STRONG

        // TODO: awulkiew - check if std::partial_sort produces the same result as std::sort
        if ( split_corner == static_cast<size_t>(min_corner) )
            rstar::partial_sort<min_corner, dimension>
                ::apply(elements_copy, split_axis, split_index, translator);                            // MAY THROW, BASIC (copy)
        else
            rstar::partial_sort<max_corner, dimension>
                ::apply(elements_copy, split_axis, split_index, translator);                            // MAY THROW, BASIC (copy)

        BOOST_TRY
        {
            // copy elements to nodes
            elements1.assign(elements_copy.begin(), elements_copy.begin() + split_index);               // MAY THROW, BASIC
            elements2.assign(elements_copy.begin() + split_index, elements_copy.end());                 // MAY THROW, BASIC

            // calculate boxes
            box1 = rtree::elements_box<Box>(elements1.begin(), elements1.end(), translator);
            box2 = rtree::elements_box<Box>(elements2.begin(), elements2.end(), translator);
        }
        BOOST_CATCH(...)
        {
            //elements_copy.clear();
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<Value, Options, Translator, Box, Allocators>::apply(elements_backup, allocators);
            //elements_backup.clear();

            BOOST_RETHROW                                                                                 // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }

    template <typename Indexable>
    static inline size_t apply(internal_node & n,
                               Indexable const& indexable,
                               parameters_type const& parameters,
                               size_t node_relative_level)
    {
        ::boost::ignore_unused_variable_warning(parameters);

        children_type & children = rtree::elements(n);
        
        // children are leafs
        if ( node_relative_level <= 1 )
        {
            /*if ( 0 < parameters.get_overlap_cost_threshold() &&
                 parameters.get_overlap_cost_threshold() < children.size() )
                return choose_by_nearly_minimum_overlap_cost(children, indexable, parameters.get_overlap_cost_threshold());
            else
                return choose_by_minimum_overlap_cost(children, indexable);*/

            return choose_by_minimum_overlap_cost(children, indexable, parameters.get_overlap_cost_threshold());
        }
        // children are internal nodes
        else
            return choose_by_minimum_content_cost(children, indexable);
    }

    template <typename Indexable>
    static inline size_t choose_by_minimum_overlap_cost(children_type const& children,
                                                        Indexable const& indexable,
                                                        size_t overlap_cost_threshold)
    {
        const size_t children_count = children.size();

        content_type min_content_diff = (std::numeric_limits<content_type>::max)();
        content_type min_content = (std::numeric_limits<content_type>::max)();
        size_t choosen_index = 0;

        // create container of children sorted by content enlargement needed to include the new value
        typedef boost::tuple<size_t, content_type, content_type> child_contents;

        typename rtree::container_from_elements_type<children_type, child_contents>::type children_contents;
        children_contents.resize(children_count);

        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            // expanded child node's box
            Box box_exp(ch_i.first);
            geometry::expand(box_exp, indexable);

            // areas difference
            content_type content = index::detail::content(box_exp);
            content_type content_diff = content - index::detail::content(ch_i.first);

            children_contents[i] = boost::make_tuple(i, content_diff, content);

            if ( content_diff < min_content_diff ||
                 (content_diff == min_content_diff && content < min_content) )
            {
                min_content_diff = content_diff;
                min_content = content;
                choosen_index = i;
            }
        }

        // is this assumption ok? if min_content_diff == 0 there is no overlap increase?

        if ( min_content_diff < -std::numeric_limits<double>::epsilon() || std::numeric_limits<double>::epsilon() < min_content_diff )
        {
            if ( 0 < overlap_cost_threshold && overlap_cost_threshold < children.size() )
            {
                // calculate nearly minimum overlap cost

                // sort by content_diff
                std::partial_sort(children_contents.begin(), children_contents.begin() + overlap_cost_threshold, children_contents.end(), content_diff_less);
                choosen_index = choose_by_minimum_overlap_cost_sorted_by_content(children, indexable, children_count, overlap_cost_threshold, children_contents);
            }
            else
            {
                // calculate minimum overlap cost

                choosen_index = choose_by_minimum_overlap_cost_unsorted_by_content(children, indexable, children_count, children_contents);
            }
        }

        return choosen_index;
    }


    template <typename Indexable, typename ChildrenContents>
    static inline size_t choose_by_minimum_overlap_cost_unsorted_by_content(children_type const& children,
                                                                            Indexable const& indexable,
                                                                            size_t children_count,
                                                                            ChildrenContents const& children_contents)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(children_contents.size() == children_count, "unexpected number of elements");

        // choose index with smallest overlap change value, or content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_overlap_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // for each child node
        for (size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            Box box_exp(ch_i.first);
            // calculate expanded box of child node ch_i
            geometry::expand(box_exp, indexable);

            content_type overlap_diff = 0;

            // calculate overlap
            for ( size_t j = 0 ; j < children_count ; ++j )
            {
                if ( i != j )
                {
                    child_type const& ch_j = children[j];

                    content_type overlap_exp = index::detail::intersection_content(box_exp, ch_j.first);
                    if ( overlap_exp < -std::numeric_limits<content_type>::epsilon() || std::numeric_limits<content_type>::epsilon() < overlap_exp )
                    {
                        overlap_diff += overlap_exp - index::detail::intersection_content(ch_i.first, ch_j.first);
                    }
                }
            }

            content_type content = boost::get<2>(children_contents[i]);
            content_type content_diff = boost::get<1>(children_contents[i]);

            // update result
            if ( overlap_diff < smallest_overlap_diff ||
                ( overlap_diff == smallest_overlap_diff && ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
                ) )
            {
                smallest_overlap_diff = overlap_diff;
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }

    
    template <typename Indexable, typename ChildrenContents>
    static inline size_t choose_by_minimum_overlap_cost_sorted_by_content(children_type const& children,
                                                                          Indexable const& indexable,
                                                                          size_t children_count,
                                                                          size_t overlap_cost_threshold,
                                                                          ChildrenContents const& children_contents)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(overlap_cost_threshold < children_count, "unexpected value");
        BOOST_GEOMETRY_INDEX_ASSERT(children_count == children_contents.size(), "unexpected number of elements");

        // for overlap_cost_threshold child nodes find the one with smallest overlap value
        size_t choosen_index = 0;
        content_type smallest_overlap_diff = (std::numeric_limits<content_type>::max)();

        // for each node
        for (size_t i = 0 ; i < overlap_cost_threshold ; ++i )
        {
            size_t child_index = boost::get<0>(children_contents[i]);

            typedef typename children_type::value_type child_type;
            child_type const& ch_i = children[child_index];

            Box box_exp(ch_i.first);
            // calculate expanded box of child node ch_i
            geometry::expand(box_exp, indexable);

            content_type overlap_diff = 0;

            // calculate overlap
            for ( size_t j = 0 ; j < children_count ; ++j )
            {
                if ( child_index != j )
                {
                    child_type const& ch_j = children[j];

                    content_type overlap_exp = index::detail::intersection_content(box_exp, ch_j.first);
                    if ( overlap_exp < -std::numeric_limits<content_type>::epsilon() || std::numeric_limits<content_type>::epsilon() < overlap_exp )
                    {
                        overlap_diff += overlap_exp - index::detail::intersection_content(ch_i.first, ch_j.first);
                    }
                }
            }

            // update result
            if ( overlap_diff < smallest_overlap_diff )
            {
                smallest_overlap_diff = overlap_diff;
                choosen_index = child_index;
            }
        }

        return choosen_index;
    }


    static inline bool content_diff_less(boost::tuple<size_t, content_type, content_type> const& p1, boost::tuple<size_t, content_type, content_type> const& p2)
    {
        return boost::get<1>(p1) < boost::get<1>(p2) ||
               (boost::get<1>(p1) == boost::get<1>(p2) && boost::get<2>(p1) < boost::get<2>(p2));
    }


    template <typename Indexable>
    static inline size_t choose_by_minimum_content_cost(children_type const& children, Indexable const& indexable)
    {
        size_t children_count = children.size();

        // choose index with smallest content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_content_diff = (std::numeric_limits<content_type>::max)();
        content_type smallest_content = (std::numeric_limits<content_type>::max)();

        // choose the child which requires smallest box expansion to store the indexable
        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            // expanded child node's box
            Box box_exp(ch_i.first);
            geometry::expand(box_exp, indexable);

            // areas difference
            content_type content = index::detail::content(box_exp);
            content_type content_diff = content - index::detail::content(ch_i.first);

            // update the result
            if ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
            {
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }


    template <typename ResultElements, typename Node>
    static inline void apply(ResultElements & result_elements,
                             Node & n,
                             internal_node_pointer parent,
                             size_t current_child_index,
                             parameters_type const& parameters,
                             Translator const& translator,
                             Allocators & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        typedef typename geometry::point_type<Box>::type point_type;
        // TODO: awulkiew - change second point_type to the point type of the Indexable?
        typedef typename geometry::default_distance_result<point_type>::type distance_type;

        elements_type & elements = rtree::elements(n);

        const size_t elements_count = parameters.get_max_elements() + 1;
        const size_t reinserted_elements_count = (::std::min)(parameters.get_reinserted_elements(), elements_count - parameters.get_min_elements());

        BOOST_GEOMETRY_INDEX_ASSERT(parent, "node shouldn't be the root node");
        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "unexpected elements number");
        BOOST_GEOMETRY_INDEX_ASSERT(0 < reinserted_elements_count, "wrong value of elements to reinsert");

        // calculate current node's center
        point_type node_center;
        geometry::centroid(rtree::elements(*parent)[current_child_index].first, node_center);

        // fill the container of centers' distances of children from current node's center
        typedef typename index::detail::rtree::container_from_elements_type<
            elements_type,
            std::pair<distance_type, element_type>
        >::type sorted_elements_type;
        sorted_elements_type sorted_elements;
        // If constructor is used instead of resize() MS implementation leaks here
        sorted_elements.reserve(elements_count);                                                         // MAY THROW, STRONG (V, E: alloc, copy)
        
        for ( typename elements_type::const_iterator it = elements.begin() ;
              it != elements.end() ; ++it )
        {
            point_type element_center;
            geometry::centroid( rtree::element_indexable(*it, translator), element_center);
            sorted_elements.push_back(std::make_pair(
                geometry::comparable_distance(node_center, element_center),
                *it));                                                                                  // MAY THROW (V, E: copy)
        }

        // sort elements by distances from center
        std::partial_sort(
            sorted_elements.begin(),
            sorted_elements.begin() + reinserted_elements_count,
            sorted_elements.end(),
            distances_dsc<distance_type, element_type>);                                                // MAY THROW, BASIC (V, E: copy)

        // copy elements which will be reinserted
        result_elements.clear();
        result_elements.reserve(reinserted_elements_count);                                             // MAY THROW, STRONG (V, E: alloc, copy)
        for ( typename sorted_elements_type::const_iterator it = sorted_elements.begin() ;
              it != sorted_elements.begin() + reinserted_elements_count ; ++it )
        {
            result_elements.push_back(it->second);                                                      // MAY THROW (V, E: copy)
        }

        BOOST_TRY
        {
            // copy remaining elements to the current node
            elements.clear();
            elements.reserve(elements_count - reinserted_elements_count);                                // SHOULDN'T THROW (new_size <= old size)
            for ( typename sorted_elements_type::const_iterator it = sorted_elements.begin() + reinserted_elements_count;
                  it != sorted_elements.end() ; ++it )
            {
                elements.push_back(it->second);                                                         // MAY THROW (V, E: copy)
            }
        }
        BOOST_CATCH(...)
        {
            elements.clear();

            for ( typename sorted_elements_type::iterator it = sorted_elements.begin() ;
                  it != sorted_elements.end() ; ++it )
            {
                destroy_element<Value, Options, Translator, Box, Allocators>::apply(it->second, allocators);
            }

            BOOST_RETHROW                                                                                 // RETHROW
        }
        BOOST_CATCH_END

        ::boost::ignore_unused_variable_warning(parameters);
    }

    template <typename Distance, typename El>
    static inline bool distances_asc(
        std::pair<Distance, El> const& d1,
        std::pair<Distance, El> const& d2)
    {
        return d1.first < d2.first;
    }

    
    template <typename Distance, typename El>
    static inline bool distances_dsc(
        std::pair<Distance, El> const& d1,
        std::pair<Distance, El> const& d2)
    {
        return d1.first > d2.first;
    }


    inline level_insert_base(node_pointer & root,
                             size_t & leafs_level,
                             Element const& element,
                             parameters_type const& parameters,
                             Translator const& translator,
                             Allocators & allocators,
                             size_t relative_level)
        : base(root, leafs_level, element, parameters, translator, allocators, relative_level)
        , result_relative_level(0)
    {}


    template <typename Node>
    inline void handle_possible_reinsert_or_split_of_root(Node &n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(result_elements.empty(), "reinsert should be handled only once for level");

        result_relative_level = base::m_leafs_level - base::m_traverse_data.current_level;

        // overflow
        if ( base::m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            // node isn't root node
            if ( !base::m_traverse_data.current_is_root() )
            {
                // NOTE: exception-safety
                // After an exception result_elements may contain garbage, don't use it
                rstar::remove_elements_to_reinsert<Value, Options, Translator, Box, Allocators>::apply(
                    result_elements, n,
                    base::m_traverse_data.parent, base::m_traverse_data.current_child_index,
                    base::m_parameters, base::m_translator, base::m_allocators);                            // MAY THROW, BASIC (V, E: alloc, copy)
            }
            // node is root node
            else
            {
                BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<Node>(*base::m_root_node), "node should be the root node");
                base::split(n);                                                                             // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
    }


    template <typename Node>
    inline void handle_possible_split(Node &n) const
    {
        // overflow
        if ( base::m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            base::split(n);                                                                                 // MAY THROW (V, E: alloc, copy, N: alloc)
        }
    }


    template <typename Node>
    inline void recalculate_aabb_if_necessary(Node &n) const
    {
        if ( !result_elements.empty() && !base::m_traverse_data.current_is_root() )
        {
            // calulate node's new box
            base::m_traverse_data.current_element().first =
                elements_box<Box>(rtree::elements(n).begin(), rtree::elements(n).end(), base::m_translator);
        }
    }


    inline level_insert(node_pointer & root,
                        size_t & leafs_level,
                        Element const& element,
                        parameters_type const& parameters,
                        Translator const& translator,
                        Allocators & allocators,
                        size_t relative_level)
        : base(root, leafs_level, element, parameters, translator, allocators, relative_level)
    {}


    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");

        if ( base::m_traverse_data.current_level < base::m_level )
        {
            // next traversing step
            base::traverse(*this, n);                                                                       // MAY THROW (E: alloc, copy, N: alloc)

            // further insert
            if ( 0 < InsertIndex )
            {
                BOOST_GEOMETRY_INDEX_ASSERT(0 < base::m_level, "illegal level value, level shouldn't be the root level for 0 < InsertIndex");

                if ( base::m_traverse_data.current_level == base::m_level - 1 )
                {
                    base::handle_possible_reinsert_or_split_of_root(n);                                     // MAY THROW (E: alloc, copy, N: alloc)
                }
            }
        }
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level, "unexpected level");

            BOOST_TRY
            {
                // push new child node
                rtree::elements(n).push_back(base::m_element);                                              // MAY THROW, STRONG (E: alloc, copy)
            }
            BOOST_CATCH(...)
            {
                // NOTE: exception-safety
                // if the insert fails above, the element won't be stored in the tree, so delete it

                rtree::visitors::destroy<Value, Options, Translator, Box, Allocators> del_v(base::m_element.second, base::m_allocators);
                rtree::apply_visitor(del_v, *base::m_element.second);

                BOOST_RETHROW                                                                                 // RETHROW
            }
            BOOST_CATCH_END

            // first insert
            if ( 0 == InsertIndex )
            {
                base::handle_possible_reinsert_or_split_of_root(n);                                         // MAY THROW (E: alloc, copy, N: alloc)
            }
            // not the first insert
            else
            {
                base::handle_possible_split(n);                                                             // MAY THROW (E: alloc, N: alloc)
            }
        }

        base::recalculate_aabb_if_necessary(n);
    }


    inline void operator()(leaf &)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "this visitor can't be used for a leaf");
    }


    inline level_insert(node_pointer & root,
                        size_t & leafs_level,
                        Value const& v,
                        parameters_type const& parameters,
                        Translator const& translator,
                        Allocators & allocators,
                        size_t relative_level)
        : base(root, leafs_level, v, parameters, translator, allocators, relative_level)
    {}


    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level, "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_level, "unexpected level");

        // next traversing step
        base::traverse(*this, n);                                                                       // MAY THROW (V, E: alloc, copy, N: alloc)

        BOOST_GEOMETRY_INDEX_ASSERT(0 < base::m_level, "illegal level value, level shouldn't be the root level for 0 < InsertIndex");
        
        if ( base::m_traverse_data.current_level == base::m_level - 1 )
        {
            base::handle_possible_reinsert_or_split_of_root(n);                                         // MAY THROW (E: alloc, copy, N: alloc)
        }

        base::recalculate_aabb_if_necessary(n);
    }


    inline void operator()(leaf & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level == base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level ||
                                    base::m_level == (std::numeric_limits<size_t>::max)(),
                                    "unexpected level");
        
        rtree::elements(n).push_back(base::m_element);                                                  // MAY THROW, STRONG (V: alloc, copy)

        base::handle_possible_split(n);                                                                 // MAY THROW (V: alloc, copy, N: alloc)
    }


    inline level_insert(node_pointer & root,
                        size_t & leafs_level,
                        Value const& v,
                        parameters_type const& parameters,
                        Translator const& translator,
                        Allocators & allocators,
                        size_t relative_level)
        : base(root, leafs_level, v, parameters, translator, allocators, relative_level)
    {}


    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level < base::m_level,
                                    "unexpected level");

        // next traversing step
        base::traverse(*this, n);                                                                       // MAY THROW (V: alloc, copy, N: alloc)

        base::recalculate_aabb_if_necessary(n);
    }


    inline void operator()(leaf & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_traverse_data.current_level == base::m_leafs_level,
                                    "unexpected level");
        BOOST_GEOMETRY_INDEX_ASSERT(base::m_level == base::m_traverse_data.current_level ||
                                    base::m_level == (std::numeric_limits<size_t>::max)(),
                                    "unexpected level");

        rtree::elements(n).push_back(base::m_element);                                                  // MAY THROW, STRONG (V: alloc, copy)

        base::handle_possible_reinsert_or_split_of_root(n);                                             // MAY THROW (V: alloc, copy, N: alloc)
        
        base::recalculate_aabb_if_necessary(n);
    }

    inline insert(node_pointer & root,
                  size_t & leafs_level,
                  Element const& element,
                  parameters_type const& parameters,
                  Translator const& translator,
                  Allocators & allocators,
                  size_t relative_level = 0)
        : m_root(root), m_leafs_level(leafs_level), m_element(element)
        , m_parameters(parameters), m_translator(translator)
        , m_relative_level(relative_level), m_allocators(allocators)
    {}


    inline void operator()(internal_node & BOOST_GEOMETRY_INDEX_ASSERT_UNUSED_PARAM(n))
    {
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_root), "current node should be the root");

        // Distinguish between situation when reinserts are required and use adequate visitor, otherwise use default one
        if ( m_parameters.get_reinserted_elements() > 0 )
        {
            rstar::level_insert<0, Element, Value, Options, Translator, Box, Allocators> lins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(lins_v, *m_root);                                                              // MAY THROW (V, E: alloc, copy, N: alloc)

            if ( !lins_v.result_elements.empty() )
            {
                recursive_reinsert(lins_v.result_elements, lins_v.result_relative_level);                       // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
        else
        {
            visitors::insert<Element, Value, Options, Translator, Box, Allocators, insert_default_tag> ins_v(
                m_root, m_leafs_level, m_element, m_parameters, m_translator, m_allocators, m_relative_level);

            rtree::apply_visitor(ins_v, *m_root); 
        }
    }

    template <typename Elements>
    inline void recursive_reinsert(Elements & elements, size_t relative_level)
    {
        typedef typename Elements::value_type element_type;

        // reinsert children starting from the minimum distance
        typename Elements::reverse_iterator it = elements.rbegin();
        for ( ; it != elements.rend() ; ++it)
        {
            rstar::level_insert<1, element_type, Value, Options, Translator, Box, Allocators> lins_v(
                m_root, m_leafs_level, *it, m_parameters, m_translator, m_allocators, relative_level);

            BOOST_TRY
            {
                rtree::apply_visitor(lins_v, *m_root);                                                          // MAY THROW (V, E: alloc, copy, N: alloc)
            }
            BOOST_CATCH(...)
            {
                ++it;
                for ( ; it != elements.rend() ; ++it)
                    rtree::destroy_element<Value, Options, Translator, Box, Allocators>::apply(*it, m_allocators);
                BOOST_RETHROW                                                                                     // RETHROW
            }
            BOOST_CATCH_END

            BOOST_GEOMETRY_INDEX_ASSERT(relative_level + 1 == lins_v.result_relative_level, "unexpected level");

            // non-root relative level
            if ( lins_v.result_relative_level < m_leafs_level && !lins_v.result_elements.empty())
            {
                recursive_reinsert(lins_v.result_elements, lins_v.result_relative_level);                   // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
    }


    explicit inline copy(Allocators & allocators)
        : result(0)
        , m_allocators(allocators)
    {}


    inline void operator()(internal_node & n)
    {
        node_pointer raw_new_node = rtree::create_node<Allocators, internal_node>::apply(m_allocators);      // MAY THROW, STRONG (N: alloc)
        node_auto_ptr new_node(raw_new_node, m_allocators);

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        elements_type & elements_dst = rtree::elements(rtree::get<internal_node>(*new_node));

        for (typename elements_type::iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);                                                   // MAY THROW (V, E: alloc, copy, N: alloc) 

            // for exception safety
            node_auto_ptr auto_result(result, m_allocators);

            elements_dst.push_back( rtree::make_ptr_pair(it->first, result) );                          // MAY THROW, STRONG (E: alloc, copy)

            auto_result.release();
        }

        result = new_node.get();
        new_node.release();
    }


    inline spatial_query(Translator const& t, Predicates const& p, OutIter out_it)
        : tr(t), pred(p), out_iter(out_it), found_count(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check<index::detail::bounds_tag, 0, predicates_len>(pred, 0, it->first) )
                rtree::apply_visitor(*this, *it->second);
        }
    }


    inline spatial_query_incremental(Translator const& t, Predicates const& p)
        : m_translator(::boost::addressof(t))
        , m_pred(p)
        , m_values(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_internal_stack.push_back(std::make_pair(elements.begin(), elements.end()));
    }


    const_reference dereference() const
    {
        BOOST_ASSERT_MSG(m_values, "not dereferencable");
        return *m_current;
    }


    void increment()
    {
        if ( m_values )
            ++m_current;

        for (;;)
        {
            // if leaf is choosen, move to the next value in leaf
            if ( m_values )
            {
                if ( m_current != m_last )
                {
                    // return if next value is found
                    Value const& v = *m_current;
                    if ( index::detail::predicates_check<index::detail::value_tag, 0, predicates_len>(m_pred, v, (*m_translator)(v)) )
                        return;

                    ++m_current;
                }
                // no more values, clear current leaf
                else
                {
                    m_values = 0;
                }
            }
            // if leaf isn't choosen, move to the next leaf
            else
            {
                // return if there is no more nodes to traverse
                if ( m_internal_stack.empty() )
                    return;

                // no more children in current node, remove it from stack
                if ( m_internal_stack.back().first == m_internal_stack.back().second )
                {
                    m_internal_stack.pop_back();
                    continue;
                }

                internal_iterator it = m_internal_stack.back().first;
                ++m_internal_stack.back().first;

                // next node is found, push it to the stack
                if ( index::detail::predicates_check<index::detail::bounds_tag, 0, predicates_len>(m_pred, 0, it->first) )
                    rtree::apply_visitor(*this, *(it->second));
            }
        }
    }


    bool is_end() const
    {
        return 0 == m_values;
    }

    inline children_box(Box & result, Translator const& tr)
        : m_result(result), m_tr(tr)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_result = rtree::elements_box<Box>(elements.begin(), elements.end(), m_tr);
    }


    inline explicit distance_query_result(size_t k, OutIt out_it)
        : m_count(k), m_out_it(out_it)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 < m_count, "Number of neighbors should be greater than 0");

        m_neighbors.reserve(m_count);
    }


    inline void store(Value const& val, distance_type const& curr_comp_dist)
    {
        if ( m_neighbors.size() < m_count )
        {
            m_neighbors.push_back(std::make_pair(curr_comp_dist, val));

            if ( m_neighbors.size() == m_count )
                std::make_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
        }
        else
        {
            if ( curr_comp_dist < m_neighbors.front().first )
            {
                std::pop_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
                m_neighbors.back().first = curr_comp_dist;
                m_neighbors.back().second = val;
                std::push_heap(m_neighbors.begin(), m_neighbors.end(), neighbors_less);
            }
        }
    }


    inline bool has_enough_neighbors() const
    {
        return m_count <= m_neighbors.size();
    }


    inline distance_type greatest_comparable_distance() const
    {
        // greatest distance is in the first neighbor only
        // if there is at least m_count values found
        // this is just for safety reasons since is_comparable_distance_valid() is checked earlier
        // TODO - may be replaced by ASSERT
        return m_neighbors.size() < m_count
            ? (std::numeric_limits<distance_type>::max)()
            : m_neighbors.front().first;
    }


    inline size_t finish()
    {
        typedef typename std::vector< std::pair<distance_type, Value> >::const_iterator neighbors_iterator;
        for ( neighbors_iterator it = m_neighbors.begin() ; it != m_neighbors.end() ; ++it, ++m_out_it )
            *m_out_it = it->second;

        return m_neighbors.size();
    }

    inline static bool neighbors_less(
        std::pair<distance_type, Value> const& p1,
        std::pair<distance_type, Value> const& p2)
    {
        return p1.first < p2.first;
    }


    inline distance_query(parameters_type const& parameters, Translator const& translator, Predicates const& pred, OutIter out_it)
        : m_parameters(parameters), m_translator(translator)
        , m_pred(pred)
        , m_result(nearest_predicate_access::get(m_pred).count, out_it)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;

        // array of active nodes
        typedef typename index::detail::rtree::container_from_elements_type<
            elements_type,
            std::pair<node_distance_type, typename Allocators::node_pointer>
        >::type active_branch_list_type;

        active_branch_list_type active_branch_list;
        active_branch_list.reserve(m_parameters.get_max_elements());
        
        elements_type const& elements = rtree::elements(n);

        // fill array of nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if current node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check<index::detail::bounds_tag, 0, predicates_len>(m_pred, 0, it->first) )
            {
                // calculate node's distance(s) for distance predicate
                node_distance_type node_distance;
                // if distance isn't ok - move to the next node
                if ( !calculate_node_distance::apply(predicate(), it->first, node_distance) )
                {
                    continue;
                }

                // if current node is further than found neighbors - don't analyze it
                if ( m_result.has_enough_neighbors() &&
                     is_node_prunable(m_result.greatest_comparable_distance(), node_distance) )
                {
                    continue;
                }

                // add current node's data into the list
                active_branch_list.push_back( std::make_pair(node_distance, it->second) );
            }
        }

        // if there aren't any nodes in ABL - return
        if ( active_branch_list.empty() )
            return;
        
        // sort array
        std::sort(active_branch_list.begin(), active_branch_list.end(), abl_less);

        // recursively visit nodes
        for ( typename active_branch_list_type::const_iterator it = active_branch_list.begin();
              it != active_branch_list.end() ; ++it )
        {
            // if current node is further than furthest neighbor, the rest of nodes also will be further
            if ( m_result.has_enough_neighbors() &&
                 is_node_prunable(m_result.greatest_comparable_distance(), it->first) )
                break;

            rtree::apply_visitor(*this, *(it->second));
        }
    }


    inline size_t finish()
    {
        return m_result.finish();
    }

    static inline bool abl_less(
        std::pair<node_distance_type, typename Allocators::node_pointer> const& p1,
        std::pair<node_distance_type, typename Allocators::node_pointer> const& p2)
    {
        return p1.first < p2.first;
    }


    template <typename Distance>
    static inline bool is_node_prunable(Distance const& greatest_dist, node_distance_type const& d)
    {
        return greatest_dist <= d;
    }

        internal_stack_element() : current_branch(0) {}


    inline distance_query_incremental(Translator const& translator, Predicates const& pred)
        : m_translator(::boost::addressof(translator))
        , m_pred(pred)
        , current_neighbor((std::numeric_limits<size_type>::max)())

        , next_closest_node_distance((std::numeric_limits<node_distance_type>::max)())
    {
        BOOST_ASSERT_MSG(0 < max_count(), "k must be greather than 0");
    }


    const_reference dereference() const
    {
        return *(neighbors[current_neighbor].second);
    }


    void increment()
    {
        for (;;)
        {
            size_type new_neighbor = current_neighbor == (std::numeric_limits<size_type>::max)() ? 0 : current_neighbor + 1;

            if ( internal_stack.empty() )
            {
                if ( new_neighbor < neighbors.size() )
                    current_neighbor = new_neighbor;
                else
                {
                    current_neighbor = (std::numeric_limits<size_type>::max)();
                    // clear() is used to disable the condition above
                    neighbors.clear();
                }

                return;
            }
            else
            {
                active_branch_list_type & branches = internal_stack.back().branches;
                typename active_branch_list_type::size_type & current_branch = internal_stack.back().current_branch;

                if ( branches.size() <= current_branch )
                {
                    internal_stack.pop_back();
                    continue;
                }

                // if there are no nodes which can have closer values, set new value
                if ( new_neighbor < neighbors.size() &&
                     // here must be < because otherwise neighbours may be sorted in different order
                     // if there is another value with equal distance
                     neighbors[new_neighbor].first < next_closest_node_distance )
                {
                    current_neighbor = new_neighbor;
                    return;
                }

                // if node is further than the furthest neighbour, following nodes also will be further
                BOOST_ASSERT_MSG(neighbors.size() <= max_count(), "unexpected neighbours count");
                if ( max_count() <= neighbors.size() &&
                     is_node_prunable(neighbors.back().first, branches[current_branch].first) )
                {
                    // stop traversing current level
                    internal_stack.pop_back();
                    continue;
                }
                else
                {
                    // new level - must increment current_branch before traversing of another level (mem reallocation)
                    ++current_branch;
                    rtree::apply_visitor(*this, *(branches[current_branch - 1].second));

                    next_closest_node_distance = calc_closest_node_distance(internal_stack.begin(), internal_stack.end());
                }
            }
        }
    }


    bool is_end() const
    {
        return (std::numeric_limits<size_type>::max)() == current_neighbor;
    }

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // add new element
        internal_stack.resize(internal_stack.size()+1);

        // fill active branch list array of nodes meeting predicates
        for ( typename elements_type::const_iterator it = elements.begin() ; it != elements.end() ; ++it )
        {
            // if current node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check<index::detail::bounds_tag, 0, predicates_len>(m_pred, 0, it->first) )
            {
                // calculate node's distance(s) for distance predicate
                node_distance_type node_distance;
                // if distance isn't ok - move to the next node
                if ( !calculate_node_distance::apply(predicate(), it->first, node_distance) )
                {
                    continue;
                }

                // if current node is further than found neighbors - don't analyze it
                if ( max_count() <= neighbors.size() &&
                     is_node_prunable(neighbors.back().first, node_distance) )
                {
                    continue;
                }

                // add current node's data into the list
                internal_stack.back().branches.push_back( std::make_pair(node_distance, it->second) );
            }
        }

        if ( internal_stack.back().branches.empty() )
            internal_stack.pop_back();
        else
            // sort array
            std::sort(internal_stack.back().branches.begin(), internal_stack.back().branches.end(), abl_less);
    }

    static inline bool abl_less(std::pair<node_distance_type, typename Allocators::node_pointer> const& p1,
                                std::pair<node_distance_type, typename Allocators::node_pointer> const& p2)
    {
        return p1.first < p2.first;
    }


    static inline bool neighbors_less(std::pair<value_distance_type, const Value *> const& p1,
                                      std::pair<value_distance_type, const Value *> const& p2)
    {
        return p1.first < p2.first;
    }


    node_distance_type
    calc_closest_node_distance(typename internal_stack_type::const_iterator first,
                               typename internal_stack_type::const_iterator last)
    {
        node_distance_type result = (std::numeric_limits<node_distance_type>::max)();
        for ( ; first != last ; ++first )
        {
            if ( first->branches.size() <= first->current_branch )
                continue;

            node_distance_type curr_dist = first->branches[first->current_branch].first;
            if ( curr_dist < result )
                result = curr_dist;
        }
        return result;
    }


    template <typename Distance>
    static inline bool is_node_prunable(Distance const& greatest_dist, node_distance_type const& d)
    {
        return greatest_dist <= d;
    }


    inline unsigned max_count() const
    {
        return nearest_predicate_access::get(m_pred).count;
    }


    inline destroy(node_pointer root_node, Allocators & allocators)
        : m_current_node(root_node)
        , m_allocators(allocators)
    {}


    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_current_node), "invalid pointers");

        node_pointer node_to_destroy = m_current_node;

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        for (typename elements_type::iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            m_current_node = it->second;
            rtree::apply_visitor(*this, *m_current_node);
            it->second = 0;
        }

        rtree::destroy_node<Allocators, internal_node>::apply(m_allocators, node_to_destroy);
    }


    inline count(Indexable const& i, Translator const& t)
        : indexable(i), tr(t), found_count(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            if ( geometry::covered_by(indexable, it->first) )
                rtree::apply_visitor(*this, *it->second);
        }
    }


    inline count(Value const& v, Translator const& t)
        : value(v), tr(t), found_count(0)
    {}


    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            if ( geometry::covered_by(tr(value), it->first) )
                rtree::apply_visitor(*this, *it->second);
        }
    }

    inline remove(node_pointer & root,
                  size_t & leafs_level,
                  Value const& value,
                  parameters_type const& parameters,
                  Translator const& translator,
                  Allocators & allocators)
        : m_value(value)
        , m_parameters(parameters)
        , m_translator(translator)
        , m_allocators(allocators)
        , m_root_node(root)
        , m_leafs_level(leafs_level)
        , m_is_value_removed(false)
        , m_parent(0)
        , m_current_child_index(0)
        , m_current_level(0)
        , m_is_underflow(false)
    {
        // TODO
        // assert - check if Value/Box is correct
    }


    inline void operator()(internal_node & n)
    {
        typedef typename rtree::elements_type<internal_node>::type children_type;
        children_type & children = rtree::elements(n);

        // traverse children which boxes intersects value's box
        size_t child_node_index = 0;
        for ( ; child_node_index < children.size() ; ++child_node_index )
        {
            if ( geometry::covered_by(m_translator(m_value), children[child_node_index].first) )
            {
                // next traversing step
                traverse_apply_visitor(n, child_node_index);                                                            // MAY THROW

                if ( m_is_value_removed )
                    break;
            }
        }

        // value was found and removed
        if ( m_is_value_removed )
        {
            typedef typename rtree::elements_type<internal_node>::type elements_type;
            typedef typename elements_type::iterator element_iterator;
            elements_type & elements = rtree::elements(n);

            // underflow occured - child node should be removed
            if ( m_is_underflow )
            {
                element_iterator underfl_el_it = elements.begin() + child_node_index;
                size_t relative_level = m_leafs_level - m_current_level;

                // move node to the container - store node's relative level as well and return new underflow state
                m_is_underflow = store_underflowed_node(elements, underfl_el_it, relative_level);                       // MAY THROW (E: alloc, copy)
            }

            // n is not root - adjust aabb
            if ( 0 != m_parent )
            {
                // underflow state should be ok here
                // note that there may be less than min_elems elements in root
                // so this condition should be checked only here
                BOOST_GEOMETRY_INDEX_ASSERT((elements.size() < m_parameters.get_min_elements()) == m_is_underflow, "unexpected state");

                rtree::elements(*m_parent)[m_current_child_index].first
                    = rtree::elements_box<Box>(elements.begin(), elements.end(), m_translator);
            }
            // n is root node
            else
            {
                BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_root_node), "node must be the root");

                // reinsert elements from removed nodes (underflows)
                reinsert_removed_nodes_elements();                                                                  // MAY THROW (V, E: alloc, copy, N: alloc)

                // shorten the tree
                if ( rtree::elements(n).size() == 1 )
                {
                    node_pointer root_to_destroy = m_root_node;
                    m_root_node = rtree::elements(n)[0].second;
                    --m_leafs_level;

                    rtree::destroy_node<Allocators, internal_node>::apply(m_allocators, root_to_destroy);
                }
            }
        }
    }


    bool is_value_removed() const
    {
        return m_is_value_removed;
    }


    void traverse_apply_visitor(internal_node &n, size_t choosen_node_index)
    {
        // save previous traverse inputs and set new ones
        internal_node_pointer parent_bckup = m_parent;
        size_t current_child_index_bckup = m_current_child_index;
        size_t current_level_bckup = m_current_level;

        m_parent = &n;
        m_current_child_index = choosen_node_index;
        ++m_current_level;

        // next traversing step
        rtree::apply_visitor(*this, *rtree::elements(n)[choosen_node_index].second);                    // MAY THROW (V, E: alloc, copy, N: alloc)

        // restore previous traverse inputs
        m_parent = parent_bckup;
        m_current_child_index = current_child_index_bckup;
        m_current_level = current_level_bckup;
    }


    bool store_underflowed_node(
            typename rtree::elements_type<internal_node>::type & elements,
            typename rtree::elements_type<internal_node>::type::iterator underfl_el_it,
            size_t relative_level)
    {
        // move node to the container - store node's relative level as well
        m_underflowed_nodes.push_back(std::make_pair(relative_level, underfl_el_it->second));           // MAY THROW (E: alloc, copy)

        BOOST_TRY
        {
            rtree::move_from_back(elements, underfl_el_it);                                             // MAY THROW (E: copy)
            elements.pop_back();
        }
        BOOST_CATCH(...)
        {
            m_underflowed_nodes.pop_back();
            BOOST_RETHROW                                                                                 // RETHROW
        }
        BOOST_CATCH_END

        // calc underflow
        return elements.size() < m_parameters.get_min_elements();
    }


    void reinsert_removed_nodes_elements()
    {
        typename UnderflowNodes::reverse_iterator it = m_underflowed_nodes.rbegin();

        BOOST_TRY
        {
            // reinsert elements from removed nodes
            // begin with levels closer to the root
            for ( ; it != m_underflowed_nodes.rend() ; ++it )
            {
                is_leaf<Value, Options, Box, Allocators> ilv;
                rtree::apply_visitor(ilv, *it->second);
                if ( ilv.result )
                {
                    reinsert_node_elements(rtree::get<leaf>(*it->second), it->first);                        // MAY THROW (V, E: alloc, copy, N: alloc)

                    rtree::destroy_node<Allocators, leaf>::apply(m_allocators, it->second);
                }
                else
                {
                    reinsert_node_elements(rtree::get<internal_node>(*it->second), it->first);               // MAY THROW (V, E: alloc, copy, N: alloc)

                    rtree::destroy_node<Allocators, internal_node>::apply(m_allocators, it->second);
                }
            }

            //m_underflowed_nodes.clear();
        }
        BOOST_CATCH(...)
        {
            // destroy current and remaining nodes
            for ( ; it != m_underflowed_nodes.rend() ; ++it )
            {
                node_auto_ptr dummy(it->second, m_allocators);
            }

            //m_underflowed_nodes.clear();

            BOOST_RETHROW                                                                                      // RETHROW
        }
        BOOST_CATCH_END
    }


    template <typename Node>
    void reinsert_node_elements(Node &n, size_t node_relative_level)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        typename elements_type::iterator it = elements.begin();
        BOOST_TRY
        {
            for ( ; it != elements.end() ; ++it )
            {
                visitors::insert<
                    typename elements_type::value_type,
                    Value, Options, Translator, Box, Allocators,
                    typename Options::insert_tag
                > insert_v(
                    m_root_node, m_leafs_level, *it,
                    m_parameters, m_translator, m_allocators,
                    node_relative_level - 1);

                rtree::apply_visitor(insert_v, *m_root_node);                                               // MAY THROW (V, E: alloc, copy, N: alloc)
            }
        }
        BOOST_CATCH(...)
        {
            ++it;
            rtree::destroy_elements<Value, Options, Translator, Box, Allocators>
                ::apply(it, elements.end(), m_allocators);
            elements.clear();
            BOOST_RETHROW                                                                                     // RETHROW
        }
        BOOST_CATCH_END
    }


    inline void operator()(internal_node const&)
    {
        result = false;
    }


    insert_traverse_data()
        : parent(0), current_child_index(0), current_level(0)
    {}


    void move_to_next_level(InternalNodePtr new_parent, size_t new_child_index)
    {
        parent = new_parent;
        current_child_index = new_child_index;
        ++current_level;
    }


    bool current_is_root() const
    {
        return 0 == parent;
    }


    elements_type & parent_elements() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(parent, "null pointer");
        return rtree::elements(*parent);
    }


    element_type & current_element() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(parent, "null pointer");
        return rtree::elements(*parent)[current_child_index];
    }


    inline insert(node_pointer & root,
                  size_t & leafs_level,
                  Element const& element,
                  parameters_type const& parameters,
                  Translator const& translator,
                  Allocators & allocators,
                  size_t relative_level = 0
    )
        : m_element(element)
        , m_parameters(parameters)
        , m_translator(translator)
        , m_relative_level(relative_level)
        , m_level(leafs_level - relative_level)
        , m_root_node(root)
        , m_leafs_level(leafs_level)
        , m_traverse_data()
        , m_allocators(allocators)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_relative_level <= leafs_level, "unexpected level value");
        BOOST_GEOMETRY_INDEX_ASSERT(m_level <= m_leafs_level, "unexpected level value");
        BOOST_GEOMETRY_INDEX_ASSERT(0 != m_root_node, "there is no root node");
        // TODO
        // assert - check if Box is correct
    }


    template <typename Visitor>
    inline void traverse(Visitor & visitor, internal_node & n)
    {
        // choose next node
        size_t choosen_node_index = rtree::choose_next_node<Value, Options, Box, Allocators, typename Options::choose_next_node_tag>::
            apply(n, rtree::element_indexable(m_element, m_translator), m_parameters, m_leafs_level - m_traverse_data.current_level);

        // expand the node to contain value
        geometry::expand(
            rtree::elements(n)[choosen_node_index].first,
            rtree::element_indexable(m_element, m_translator));

        // next traversing step
        traverse_apply_visitor(visitor, n, choosen_node_index);                                                 // MAY THROW (V, E: alloc, copy, N:alloc)
    }


    template <typename Node>
    inline void post_traverse(Node &n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_traverse_data.current_is_root() ||
                                    &n == &rtree::get<Node>(*m_traverse_data.current_element().second),
                                    "if node isn't the root current_child_index should be valid");

        // handle overflow
        if ( m_parameters.get_max_elements() < rtree::elements(n).size() )
        {
            split(n);                                                                                           // MAY THROW (V, E: alloc, copy, N:alloc)
        }
    }


    template <typename Visitor>
    inline void traverse_apply_visitor(Visitor & visitor, internal_node &n, size_t choosen_node_index)
    {
        // save previous traverse inputs and set new ones
        insert_traverse_data<internal_node, internal_node_pointer> backup_traverse_data = m_traverse_data;

        // calculate new traverse inputs
        m_traverse_data.move_to_next_level(&n, choosen_node_index);

        // next traversing step
        rtree::apply_visitor(visitor, *rtree::elements(n)[choosen_node_index].second);                          // MAY THROW (V, E: alloc, copy, N:alloc)

        // restore previous traverse inputs
        m_traverse_data = backup_traverse_data;
    }


    template <typename Node>
    inline void split(Node & n) const
    {
        typedef rtree::split<Value, Options, Translator, Box, Allocators, typename Options::split_tag> split_algo;

        typename split_algo::nodes_container_type additional_nodes;
        Box n_box;

        split_algo::apply(additional_nodes, n, n_box, m_parameters, m_translator, m_allocators);                // MAY THROW (V, E: alloc, copy, N:alloc)

        BOOST_GEOMETRY_INDEX_ASSERT(additional_nodes.size() == 1, "unexpected number of additional nodes");

        // TODO add all additional nodes
        // For kmeans algorithm:
        // elements number may be greater than node max elements count
        // split and reinsert must take node with some elements count
        // and container of additional elements (std::pair<Box, node*>s or Values)
        // and translator + allocators
        // where node_elements_count + additional_elements > node_max_elements_count
        // What with elements other than std::pair<Box, node*> ?
        // Implement template <node_tag> struct node_element_type or something like that

        // for exception safety
        node_auto_ptr additional_node_ptr(additional_nodes[0].second, m_allocators);

        // node is not the root - just add the new node
        if ( !m_traverse_data.current_is_root() )
        {
            // update old node's box
            m_traverse_data.current_element().first = n_box;
            // add new node to parent's children
            m_traverse_data.parent_elements().push_back(additional_nodes[0]);                                     // MAY THROW, STRONG (V, E: alloc, copy)
        }
        // node is the root - add level
        else
        {
            BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<Node>(*m_root_node), "node should be the root");

            // create new root and add nodes
            node_auto_ptr new_root(rtree::create_node<Allocators, internal_node>::apply(m_allocators), m_allocators); // MAY THROW, STRONG (N:alloc)

            BOOST_TRY
            {
                rtree::elements(rtree::get<internal_node>(*new_root)).push_back(rtree::make_ptr_pair(n_box, m_root_node));  // MAY THROW, STRONG (E:alloc, copy)
                rtree::elements(rtree::get<internal_node>(*new_root)).push_back(additional_nodes[0]);                 // MAY THROW, STRONG (E:alloc, copy)
            }
            BOOST_CATCH(...)
            {
                // clear new root to not delete in the ~node_auto_ptr() potentially stored old root node
                rtree::elements(rtree::get<internal_node>(*new_root)).clear();
                BOOST_RETHROW                                                                                           // RETHROW
            }
            BOOST_CATCH_END

            m_root_node = new_root.get();
            ++m_leafs_level;

            new_root.release();
        }

        additional_node_ptr.release();
    }

    template <typename Node>
    static inline void apply(node* & root_node,
                             size_t & leafs_level,
                             Node & n,
                             internal_node *parent_node,
                             size_t current_child_index,
                             Translator const& tr,
                             Allocators & allocators)
    {

    }


    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             size_t & seed1,
                             size_t & seed2)
    {
        const size_t elements_count = parameters.get_max_elements() + 1;
        BOOST_GEOMETRY_INDEX_ASSERT(elements.size() == elements_count, "wrong number of elements");
        BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements_count, "unexpected number of elements");

        content_type greatest_free_content = 0;
        seed1 = 0;
        seed2 = 1;

        for ( size_t i = 0 ; i < elements_count - 1 ; ++i )
        {
            for ( size_t j = i + 1 ; j < elements_count ; ++j )
            {
                indexable_type const& ind1 = rtree::element_indexable(elements[i], tr);
                indexable_type const& ind2 = rtree::element_indexable(elements[j], tr);

                box_type enlarged_box;
                //geometry::convert(ind1, enlarged_box);
                detail::bounds(ind1, enlarged_box);
                geometry::expand(enlarged_box, ind2);

                content_type free_content = (index::detail::content(enlarged_box) - index::detail::content(ind1)) - index::detail::content(ind2);
                
                if ( greatest_free_content < free_content )
                {
                    greatest_free_content = free_content;
                    seed1 = i;
                    seed2 = j;
                }
            }
        }

        ::boost::ignore_unused_variable_warning(parameters);
    }


    template <typename Node>
    static inline void apply(Node & n,
                             Node & second_node,
                             Box & box1,
                             Box & box2,
                             parameters_type const& parameters,
                             Translator const& translator,
                             Allocators & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
        typedef typename coordinate_type<indexable_type>::type coordinate_type;

        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);
        
        BOOST_GEOMETRY_INDEX_ASSERT(elements1.size() == parameters.get_max_elements() + 1, "unexpected elements number");

        // copy original elements
        elements_type elements_copy(elements1);                                                             // MAY THROW, STRONG (alloc, copy)
        elements_type elements_backup(elements1);                                                           // MAY THROW, STRONG (alloc, copy)
        
        // calculate initial seeds
        size_t seed1 = 0;
        size_t seed2 = 0;
        quadratic::pick_seeds<
            elements_type,
            parameters_type,
            Translator,
            Box
        >::apply(elements_copy, parameters, translator, seed1, seed2);

        // prepare nodes' elements containers
        elements1.clear();
        BOOST_GEOMETRY_INDEX_ASSERT(elements2.empty(), "second node's elements container should be empty");

        BOOST_TRY
        {
            // add seeds
            elements1.push_back(elements_copy[seed1]);                                                      // MAY THROW, STRONG (copy)
            elements2.push_back(elements_copy[seed2]);                                                      // MAY THROW, STRONG (alloc, copy)

            // calculate boxes
            //geometry::convert(rtree::element_indexable(elements_copy[seed1], translator), box1);
            detail::bounds(rtree::element_indexable(elements_copy[seed1], translator), box1);
            //geometry::convert(rtree::element_indexable(elements_copy[seed2], translator), box2);
            detail::bounds(rtree::element_indexable(elements_copy[seed2], translator), box2);

            // remove seeds
            if (seed1 < seed2)
            {
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed2);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed1);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
            }
            else
            {
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed1);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
                rtree::move_from_back(elements_copy, elements_copy.begin() + seed2);                        // MAY THROW, STRONG (copy)
                elements_copy.pop_back();
            }

            // initialize areas
            content_type content1 = index::detail::content(box1);
            content_type content2 = index::detail::content(box2);

            size_t remaining = elements_copy.size();

            // redistribute the rest of the elements
            while ( !elements_copy.empty() )
            {
                typename elements_type::reverse_iterator el_it = elements_copy.rbegin();
                bool insert_into_group1 = false;

                size_t elements1_count = elements1.size();
                size_t elements2_count = elements2.size();

                // if there is small number of elements left and the number of elements in node is lesser than min_elems
                // just insert them to this node
                if ( elements1_count + remaining <= parameters.get_min_elements() )
                {
                    insert_into_group1 = true;
                }
                else if ( elements2_count + remaining <= parameters.get_min_elements() )
                {
                    insert_into_group1 = false;
                }
                // insert the best element
                else
                {
                    // find element with minimum groups areas increses differences
                    content_type content_increase1 = 0;
                    content_type content_increase2 = 0;
                    el_it = pick_next(elements_copy.rbegin(), elements_copy.rend(),
                                      box1, box2, content1, content2, translator,
                                      content_increase1, content_increase2);

                    if ( content_increase1 < content_increase2 ||
                         ( content_increase1 == content_increase2 && ( content1 < content2 ||
                           ( content1 == content2 && elements1_count <= elements2_count ) )
                         ) )
                    {
                        insert_into_group1 = true;
                    }
                    else
                    {
                        insert_into_group1 = false;
                    }
                }

                // move element to the choosen group
                element_type const& elem = *el_it;
                indexable_type const& indexable = rtree::element_indexable(elem, translator);

                if ( insert_into_group1 )
                {
                    elements1.push_back(elem);                                                              // MAY THROW, STRONG (copy)
                    geometry::expand(box1, indexable);
                    content1 = index::detail::content(box1);
                }
                else
                {
                    elements2.push_back(elem);                                                              // MAY THROW, STRONG (alloc, copy)
                    geometry::expand(box2, indexable);
                    content2 = index::detail::content(box2);
                }

                BOOST_GEOMETRY_INDEX_ASSERT(!elements_copy.empty(), "expected more elements");
                typename elements_type::iterator el_it_base = el_it.base();
                rtree::move_from_back(elements_copy, --el_it_base);                                         // MAY THROW, STRONG (copy)
                elements_copy.pop_back();

                BOOST_GEOMETRY_INDEX_ASSERT(0 < remaining, "expected more remaining elements");
                --remaining;
            }
        }
        BOOST_CATCH(...)
        {
            //elements_copy.clear();
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<Value, Options, Translator, Box, Allocators>::apply(elements_backup, allocators);
            //elements_backup.clear();

            BOOST_RETHROW                                                                                     // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }


    template <typename It>
    static inline It pick_next(It first, It last,
                               Box const& box1, Box const& box2,
                               content_type const& content1, content_type const& content2,
                               Translator const& translator,
                               content_type & out_content_increase1, content_type & out_content_increase2)
    {
        typedef typename boost::iterator_value<It>::type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;

        content_type greatest_content_incrase_diff = 0;
        It out_it = first;
        out_content_increase1 = 0;
        out_content_increase2 = 0;
        
        // find element with greatest difference between increased group's boxes areas
        for ( It el_it = first ; el_it != last ; ++el_it )
        {
            indexable_type const& indexable = rtree::element_indexable(*el_it, translator);

            // calculate enlarged boxes and areas
            Box enlarged_box1(box1);
            Box enlarged_box2(box2);
            geometry::expand(enlarged_box1, indexable);
            geometry::expand(enlarged_box2, indexable);
            content_type enlarged_content1 = index::detail::content(enlarged_box1);
            content_type enlarged_content2 = index::detail::content(enlarged_box2);

            content_type content_incrase1 = (enlarged_content1 - content1);
            content_type content_incrase2 = (enlarged_content2 - content2);

            content_type content_incrase_diff = content_incrase1 < content_incrase2 ?
                content_incrase2 - content_incrase1 : content_incrase1 - content_incrase2;

            if ( greatest_content_incrase_diff < content_incrase_diff )
            {
                greatest_content_incrase_diff = content_incrase_diff;
                out_it = el_it;
                out_content_increase1 = content_incrase1;
                out_content_increase2 = content_incrase2;
            }
        }

        return out_it;
    }


template <typename R, typename T>
inline R difference_dispatch(T const& from, T const& to, ::boost::mpl::bool_<false> const& /*is_unsigned*/)
{
    return to - from;
}


template <typename R, typename T>
inline R difference(T const& from, T const& to)
{
    BOOST_MPL_ASSERT_MSG(!boost::is_unsigned<R>::value, RESULT_CANT_BE_UNSIGNED, (R));

    typedef ::boost::mpl::bool_<
        boost::is_unsigned<T>::value
    > is_unsigned;

    return difference_dispatch<R>(from, to, is_unsigned());
}


    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        pick_seeds_impl<Elements, Parameters, Translator, Dimension - 1>::apply(elements, parameters, tr, separation, seed1, seed2);

        separation_type current_separation;
        size_t s1, s2;
        find_norm_sep::apply(elements, parameters, tr, current_separation, s1, s2);

        // in the old implementation different operator was used: <= (y axis prefered)
        if ( separation < current_separation )
        {
            separation = current_separation;
            seed1 = s1;
            seed2 = s2;
        }
    }


    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             separation_type & separation,
                             size_t & seed1,
                             size_t & seed2)
    {
        find_norm_sep::apply(elements, parameters, tr, separation, seed1, seed2);
    }


    static inline void apply(Elements const& elements,
                             Parameters const& parameters,
                             Translator const& tr,
                             size_t & seed1,
                             size_t & seed2)
    {
        separation_type separation = 0;
        pick_seeds_impl<Elements, Parameters, Translator, dimension>::apply(elements, parameters, tr, separation, seed1, seed2);
    }


    template <typename Node>
    static inline void apply(Node & n,
                             Node & second_node,
                             Box & box1,
                             Box & box2,
                             parameters_type const& parameters,
                             Translator const& translator,
                             Allocators & allocators)
    {
        typedef typename rtree::elements_type<Node>::type elements_type;
        typedef typename elements_type::value_type element_type;
        typedef typename rtree::element_indexable_type<element_type, Translator>::type indexable_type;
        typedef typename coordinate_type<indexable_type>::type coordinate_type;
        typedef typename index::detail::default_content_result<Box>::type content_type;

        elements_type & elements1 = rtree::elements(n);
        elements_type & elements2 = rtree::elements(second_node);
        const size_t elements1_count = parameters.get_max_elements() + 1;

        BOOST_GEOMETRY_INDEX_ASSERT(elements1.size() == elements1_count, "unexpected number of elements");

        // copy original elements
        elements_type elements_copy(elements1);                                                             // MAY THROW, STRONG (alloc, copy)

        // calculate initial seeds
        size_t seed1 = 0;
        size_t seed2 = 0;
        linear::pick_seeds<
            elements_type,
            parameters_type,
            Translator
        >::apply(elements_copy, parameters, translator, seed1, seed2);

        // prepare nodes' elements containers
        elements1.clear();
        BOOST_GEOMETRY_INDEX_ASSERT(elements2.empty(), "unexpected container state");

        BOOST_TRY
        {
            // add seeds
            elements1.push_back(elements_copy[seed1]);                                                      // MAY THROW, STRONG (copy)
            elements2.push_back(elements_copy[seed2]);                                                      // MAY THROW, STRONG (alloc, copy)

            // calculate boxes
            detail::bounds(rtree::element_indexable(elements_copy[seed1], translator), box1);
            detail::bounds(rtree::element_indexable(elements_copy[seed2], translator), box2);

            // initialize areas
            content_type content1 = index::detail::content(box1);
            content_type content2 = index::detail::content(box2);

            BOOST_GEOMETRY_INDEX_ASSERT(2 <= elements1_count, "unexpected elements number");
            size_t remaining = elements1_count - 2;

            // redistribute the rest of the elements
            for ( size_t i = 0 ; i < elements1_count ; ++i )
            {
                if (i != seed1 && i != seed2)
                {
                    element_type const& elem = elements_copy[i];
                    indexable_type const& indexable = rtree::element_indexable(elem, translator);

                    // if there is small number of elements left and the number of elements in node is lesser than min_elems
                    // just insert them to this node
                    if ( elements1.size() + remaining <= parameters.get_min_elements() )
                    {
                        elements1.push_back(elem);                                                          // MAY THROW, STRONG (copy)
                        geometry::expand(box1, indexable);
                        content1 = index::detail::content(box1);
                    }
                    else if ( elements2.size() + remaining <= parameters.get_min_elements() )
                    {
                        elements2.push_back(elem);                                                          // MAY THROW, STRONG (alloc, copy)
                        geometry::expand(box2, indexable);
                        content2 = index::detail::content(box2);
                    }
                    // choose better node and insert element
                    else
                    {
                        // calculate enlarged boxes and areas
                        Box enlarged_box1(box1);
                        Box enlarged_box2(box2);
                        geometry::expand(enlarged_box1, indexable);
                        geometry::expand(enlarged_box2, indexable);
                        content_type enlarged_content1 = index::detail::content(enlarged_box1);
                        content_type enlarged_content2 = index::detail::content(enlarged_box2);

                        content_type content_increase1 = enlarged_content1 - content1;
                        content_type content_increase2 = enlarged_content2 - content2;

                        // choose group which box content have to be enlarged least or has smaller content or has fewer elements
                        if ( content_increase1 < content_increase2 ||
                                ( content_increase1 == content_increase2 &&
                                    ( content1 < content2 ||
                                        ( content1 == content2 && elements1.size() <= elements2.size() ) ) ) )
                        {
                            elements1.push_back(elem);                                                      // MAY THROW, STRONG (copy)
                            box1 = enlarged_box1;
                            content1 = enlarged_content1;
                        }
                        else
                        {
                            elements2.push_back(elem);                                                      // MAY THROW, STRONG (alloc, copy)
                            box2 = enlarged_box2;
                            content2 = enlarged_content2;
                        }
                    }
                
                    BOOST_GEOMETRY_INDEX_ASSERT(0 < remaining, "unexpected value");
                    --remaining;
                }
            }
        }
        BOOST_CATCH(...)
        {
            elements1.clear();
            elements2.clear();

            rtree::destroy_elements<Value, Options, Translator, Box, Allocators>::apply(elements_copy, allocators);
            //elements_copy.clear();

            BOOST_RETHROW                                                                                     // RETHROW, BASIC
        }
        BOOST_CATCH_END
    }

    virtual ~dynamic_node() {}


    virtual ~dynamic_visitor() {}


    virtual ~dynamic_visitor() {}


template <typename Derived, typename Parameters, typename Value, typename Box, typename Allocators, typename Tag>
inline Derived & get(dynamic_node<Value, Parameters, Box, Allocators, Tag> & n)
{
    BOOST_GEOMETRY_INDEX_ASSERT(dynamic_cast<Derived*>(&n), "can't cast to a Derived type");
    return static_cast<Derived&>(n);
}


template <typename Visitor, typename Visitable>
inline void apply_visitor(Visitor & v, Visitable & n)
{
    BOOST_GEOMETRY_INDEX_ASSERT(&n, "null ptr");
    n.apply_visitor(v);
}


    template <typename Alloc>
    inline static_internal_node(Alloc const&) {}


    template <typename Alloc>
    inline static_leaf(Alloc const&) {}


    inline allocators()
        : node_allocator_type()
    {}


    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : node_allocator_type(alloc)
    {}


    inline allocators(BOOST_FWD_REF(allocators) a)
        : node_allocator_type(boost::move(a.node_allocator()))
    {}


    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        node_allocator() = boost::move(a.node_allocator());
        return *this;
    }

    inline allocators & operator=(allocators const& a)
    {
        node_allocator() = a.node_allocator();
        return *this;
    }


    void swap(allocators & a)
    {
        boost::swap(node_allocator(), a.node_allocator());
    }


    bool operator==(allocators const& a) const { return node_allocator() == a.node_allocator(); }

    template <typename Alloc>
    bool operator==(Alloc const& a) const { return node_allocator() == node_allocator_type(a); }


    Allocator allocator() const { return Allocator(node_allocator()); }


    node_allocator_type & node_allocator() { return *this; }

    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
        >::template apply(allocators.node_allocator());
    }


    template <typename Al>
    inline static_internal_node(Al const& al)
        : elements(al)
    {}


     template <typename Al>
    inline static_leaf(Al const& al)
        : elements(al)
    {}


    inline allocators()
        : node_allocator_type()
    {}


    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : node_allocator_type(alloc)
    {}


    inline allocators(BOOST_FWD_REF(allocators) a)
        : node_allocator_type(boost::move(a.node_allocator()))
    {}


    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        node_allocator() = boost::move(a.node_allocator());
        return *this;
    }

    inline allocators & operator=(allocators const& a)
    {
        node_allocator() = a.node_allocator();
        return *this;
    }


    void swap(allocators & a)
    {
        boost::swap(node_allocator(), a.node_allocator());
    }


    bool operator==(allocators const& a) const { return node_allocator() == a.node_allocator(); }

    template <typename Alloc>
    bool operator==(Alloc const& a) const { return node_allocator() == node_allocator_type(a); }


    Allocator allocator() const { return Allocator(node_allocator()); }


    node_allocator_type & node_allocator() { return *this; }

    template <typename AllocNode>
    static inline VariantPtr apply(AllocNode & alloc_node)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p = Al::allocate(alloc_node, 1);

        if ( 0 == p )
            throw_runtime_error("boost::geometry::index::rtree node creation failed");

        auto_deallocator<AllocNode> deallocator(alloc_node, p);

        Al::construct(alloc_node, boost::addressof(*p), Node(alloc_node)); // implicit cast to Variant

        deallocator.release();
        return p;
    }

    template <typename AllocNode, typename VariantPtr>
    static inline void apply(AllocNode & alloc_node, VariantPtr n)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;

        Al::destroy(alloc_node, boost::addressof(*n));
        Al::deallocate(alloc_node, n, 1);
    }

    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator());
    }

    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_static_node<
            static_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator(), n);
    }


    template <typename Al>
    inline dynamic_internal_node(Al const& al)
        : elements(al)
    {}


    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, false> & v) { v(*this); }


    template <typename Al>
    inline dynamic_leaf(Al const& al)
        : elements(al)
    {}


    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, false> & v) { v(*this); }


template <typename Node>
inline typename elements_type<Node>::type &
elements(Node & n)
{
    return n.elements;
}


template <typename Node>
inline typename elements_type<Node>::type const&
elements(Node const& n)
{
    return n.elements;
}


    inline allocators()
        : internal_node_allocator_type()
        , leaf_allocator_type()
    {}


    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : internal_node_allocator_type(alloc)
        , leaf_allocator_type(alloc)
    {}


    inline allocators(BOOST_FWD_REF(allocators) a)
        : internal_node_allocator_type(boost::move(a.internal_node_allocator()))
        , leaf_allocator_type(boost::move(a.leaf_allocator()))
    {}


    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        internal_node_allocator() = ::boost::move(a.internal_node_allocator());
        leaf_allocator() = ::boost::move(a.leaf_allocator());
        return *this;
    }

    inline allocators & operator=(allocators const& a)
    {
        internal_node_allocator() = a.internal_node_allocator();
        leaf_allocator() = a.leaf_allocator();
        return *this;
    }


    void swap(allocators & a)
    {
        boost::swap(internal_node_allocator(), a.internal_node_allocator());
        boost::swap(leaf_allocator(), a.leaf_allocator());
    }


    bool operator==(allocators const& a) const { return leaf_allocator() == a.leaf_allocator(); }

    template <typename Alloc>
    bool operator==(Alloc const& a) const { return leaf_allocator() == leaf_allocator_type(a); }


    Allocator allocator() const { return Allocator(leaf_allocator()); }


    internal_node_allocator_type & internal_node_allocator() { return *this; }

    template <typename AllocNode>
    static inline BaseNodePtr apply(AllocNode & alloc_node)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p = Al::allocate(alloc_node, 1);

        if ( 0 == p )
            throw_runtime_error("boost::geometry::index::rtree node creation failed");

        auto_deallocator<AllocNode> deallocator(alloc_node, p);

        Al::construct(alloc_node, boost::addressof(*p), alloc_node);

        deallocator.release();
        return p;
    }

    template <typename AllocNode, typename BaseNodePtr>
    static inline void apply(AllocNode & alloc_node, BaseNodePtr n)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p(&static_cast<Node&>(rtree::get<Node>(*n)));
        Al::destroy(alloc_node, boost::addressof(*p));
        Al::deallocate(alloc_node, p, 1);
    }

    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_dynamic_node<
            typename Allocators::node_pointer,
            dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.internal_node_allocator());
    }

    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_dynamic_node<
            dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.internal_node_allocator(), n);
    }


template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          boost::variant<
                              static_leaf<Value, Parameters, Box, Allocators, Tag>,
                              static_internal_node<Value, Parameters, Box, Allocators, Tag>
                          > & n)
{
    boost::apply_visitor(v, n);
}

    inline auto_deallocator(Alloc & a, pointer p) : m_alloc(a), m_ptr(p) {}

    inline ~auto_deallocator() { if ( m_ptr ) boost::container::allocator_traits<Alloc>::deallocate(m_alloc, m_ptr, 1); }

    inline void release() { m_ptr = 0; }

    inline pointer ptr() { return m_ptr; }


template <typename Box, typename FwdIter, typename Translator>
inline Box elements_box(FwdIter first, FwdIter last, Translator const& tr)
{
    Box result;

    if ( first == last )
    {
        geometry::assign_inverse(result);
        return result;
    }

    detail::bounds(element_indexable(*first, tr), result);
    ++first;

    for ( ; first != last ; ++first )
        geometry::expand(result, element_indexable(*first, tr));

    return result;
}


    inline static void apply(typename internal_node::elements_type::value_type & element, Allocators & allocators)
    {
         node_auto_ptr dummy(element.second, allocators);
         element.second = 0;
    }


    inline static void apply(typename internal_node::elements_type & elements, Allocators & allocators)
    {
        for ( size_t i = 0 ; i < elements.size() ; ++i )
        {
            node_auto_ptr dummy(elements[i].second, allocators);
            elements[i].second = 0;
        }
    }


    inline static void apply(node & node, Allocators & allocators)
    {
        rtree::visitors::is_leaf<Value, Options, Box, Allocators> ilv;
        rtree::apply_visitor(ilv, node);
        if ( ilv.result )
        {
            apply(rtree::get<leaf>(node), allocators);
        }
        else
        {
            apply(rtree::get<internal_node>(node), allocators);
        }
    }


template <typename Container, typename Iterator>
void move_from_back(Container & container, Iterator it)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!container.empty(), "cannot copy from empty container");
    Iterator back_it = container.end();
    --back_it;
    if ( it != back_it )
    {
        *it = boost::move(*back_it);                                                             // MAY THROW (copy)
    }
}

    ptr_pair(First const& f, Pointer s) : first(f), second(s) {}


template <typename First, typename Pointer> inline
ptr_pair<First, Pointer>
make_ptr_pair(First const& f, Pointer s)
{
    return ptr_pair<First, Pointer>(f, s);
}

    exclusive_ptr_pair(First const& f, Pointer s) : first(f), second(s) {}

    exclusive_ptr_pair(BOOST_RV_REF(exclusive_ptr_pair) p) : first(p.first), second(p.second) { p.second = 0; }

    exclusive_ptr_pair & operator=(BOOST_RV_REF(exclusive_ptr_pair) p) { first = p.first; second = p.second; p.second = 0; return *this; }


template <typename First, typename Pointer> inline
exclusive_ptr_pair<First, Pointer>
make_exclusive_ptr_pair(First const& f, Pointer s)
{
    return exclusive_ptr_pair<First, Pointer>(f, s);
}


    template <typename Alloc>
    inline dynamic_internal_node(Alloc const&) {}


    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_static_tag, false> & v) { v(*this); }


    template <typename Alloc>
    inline dynamic_leaf(Alloc const&) {}


    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_static_tag, false> & v) { v(*this); }


    inline allocators()
        : internal_node_allocator_type()
        , leaf_allocator_type()
    {}


    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : internal_node_allocator_type(alloc)
        , leaf_allocator_type(alloc)
    {}


    inline allocators(BOOST_FWD_REF(allocators) a)
        : internal_node_allocator_type(boost::move(a.internal_node_allocator()))
        , leaf_allocator_type(boost::move(a.leaf_allocator()))
    {}


    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        internal_node_allocator() = ::boost::move(a.internal_node_allocator());
        leaf_allocator() = ::boost::move(a.leaf_allocator());
        return *this;
    }

    inline allocators & operator=(allocators const& a)
    {
        internal_node_allocator() = a.internal_node_allocator();
        leaf_allocator() = a.leaf_allocator();
        return *this;
    }


    void swap(allocators & a)
    {
        boost::swap(internal_node_allocator(), a.internal_node_allocator());
        boost::swap(leaf_allocator(), a.leaf_allocator());
    }


    bool operator==(allocators const& a) const { return leaf_allocator() == a.leaf_allocator(); }

    template <typename Alloc>
    bool operator==(Alloc const& a) const { return leaf_allocator() == leaf_allocator_type(a); }


    Allocator allocator() const { return Allocator(leaf_allocator()); }


    internal_node_allocator_type & internal_node_allocator() { return *this; }

    node_auto_ptr(pointer ptr, Allocators & allocators)
        : m_ptr(ptr)
        , m_allocators(allocators)
    {}


    ~node_auto_ptr()
    {
        reset();
    }


    void reset(pointer ptr = 0)
    {
        if ( m_ptr )
        {
            detail::rtree::visitors::destroy<Value, Options, Translator, Box, Allocators> del_v(m_ptr, m_allocators);
            detail::rtree::apply_visitor(del_v, *m_ptr);
        }
        m_ptr = ptr;
    }


    void release()
    {
        m_ptr = 0;
    }


    pointer get() const
    {
        return m_ptr;
    }


    node & operator*() const
    {
        return *m_ptr;
    }


    pointer operator->() const
    {
        return m_ptr;
    }


    template <typename Predicates>
    inline query_range(
        Index const&,
        Predicates const&)
    {}


    inline iterator begin() { return 0; }

    inline iterator end() { return 0; }

    inline const_iterator begin() const { return 0; }

    inline const_iterator end() const { return 0; }

    inline explicit query(Predicates const& pred)
        : predicates(pred)
    {}


template<typename Index, typename Predicates>
index::adaptors::detail::query_range<Index>
operator|(
    Index const& si,
    index::adaptors::detail::query<Predicates> const& f)
{
    return index::adaptors::detail::query_range<Index>(si, f.predicates);
}

template <typename Predicates>
detail::query<Predicates>
queried(Predicates const& pred)
{
    return detail::query<Predicates>(pred);
}

    inline ring()
        : base_type()
    {}

    template <typename Iterator>
    inline ring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

    inline segment()
    {}


    inline segment(Point const& p1, Point const& p2)
    {
        this->first = p1;
        this->second = p2;
    }


    inline referring_segment(point_type& p1, point_type& p2)
        : first(p1)
        , second(p2)
    {}


    static inline coordinate_type get(segment_type const& s)
    {
        return geometry::get<Dimension>(s.first);
    }


    static inline void set(segment_type& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.first, value);
    }

    inline point_xy()
        : model::point<CoordinateType, 2, CoordinateSystem>()
    {}

    inline point_xy(CoordinateType const& x, CoordinateType const& y)
        : model::point<CoordinateType, 2, CoordinateSystem>(x, y)
    {}

    inline CoordinateType const& x() const
    { return this->template get<0>(); }

    inline CoordinateType const& y() const
    { return this->template get<1>(); }

    inline void x(CoordinateType const& v)
    { this->template set<0>(v); }

    inline void y(CoordinateType const& v)
    { this->template set<1>(v); }

    static inline CoordinateType get(
        model::d2::point_xy<CoordinateType, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }


    static inline void set(model::d2::point_xy<CoordinateType, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }


    inline box() {}

    inline box(Point const& min_corner, Point const& max_corner)
    {
        geometry::convert(min_corner, m_min_corner);
        geometry::convert(max_corner, m_max_corner);
    }


    inline Point const& min_corner() const { return m_min_corner; }

    inline Point const& max_corner() const { return m_max_corner; }


    inline Point& min_corner() { return m_min_corner; }

    inline Point& max_corner() { return m_max_corner; }


    static inline coordinate_type get(model::box<Point> const& b)
    {
        return geometry::get<Dimension>(b.min_corner());
    }


    static inline void set(model::box<Point>& b, coordinate_type const& value)
    {
        geometry::set<Dimension>(b.min_corner(), value);
    }

    inline point()
    {}

    inline point(CoordinateType const& v0, CoordinateType const& v1 = 0, CoordinateType const& v2 = 0)
    {
        if (DimensionCount >= 1) m_values[0] = v0;
        if (DimensionCount >= 2) m_values[1] = v1;
        if (DimensionCount >= 3) m_values[2] = v2;
    }

    template <std::size_t K>
    inline CoordinateType const& get() const
    {
        BOOST_STATIC_ASSERT(K < DimensionCount);
        return m_values[K];
    }

    template <std::size_t K>
    inline void set(CoordinateType const& value)
    {
        BOOST_STATIC_ASSERT(K < DimensionCount);
        m_values[K] = value;
    }

    static inline CoordinateType get(
        model::point<CoordinateType, DimensionCount, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }


    static inline void set(
        model::point<CoordinateType, DimensionCount, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }

    inline linestring()
        : base_type()
    {}

    template <typename Iterator>
    inline linestring(Iterator begin, Iterator end)
        : base_type(begin, end)
    {}

    static inline CoordinateType get(CoordinateType const p[DimensionCount])
    {
        return p[Dimension];
    }


    static inline void set(CoordinateType p[DimensionCount],
        CoordinateType const& value)
    {
        p[Dimension] = value;
    }


    explicit inline hole_iterator(Polygon& polygon, ith_type const it)
        : m_polygon(polygon)
        , m_base(it)
    {
    }


    inline RingProxy dereference() const
    {
        return RingProxy(m_polygon, this->m_base);
    }


    inline void increment() { ++m_base; }

    inline void decrement() { --m_base; }

    inline void advance(difference_type n)
    {
        for (int i = 0; i < n; i++)
        {
            ++m_base;
        }
    }


    inline bool equal(hole_iterator<Polygon, RingProxy> const& other) const
    {
        return this->m_base == other.m_base;
    }


    inline holes_proxy(Polygon& p)
        : polygon(p)
    {}


    inline void clear()
    {
        Polygon empty;
        // Clear the holes
        polygon.set_holes
            (
                boost::polygon::begin_holes(empty),
                boost::polygon::end_holes(empty)
            );
    }


    inline void resize(std::size_t new_size)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        temporary_copy.resize(new_size);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }


    template <typename Ring>
    inline void push_back(Ring const& ring)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        boost::polygon::polygon_data<coordinate_type> added;
        boost::polygon::set_points(added, ring.begin(), ring.end());
        temporary_copy.push_back(added);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}


template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}


template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}

    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy)
    {
        proxy.clear();
    }

    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }

    template <typename Ring>
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, Ring const& ring)
    {
        proxy.push_back(ring);
    }

    template <typename Ring, typename Point>
    static inline void push_back(Ring& ring, Point const& point)
    {
        // Boost.Polygon's polygons are not appendable. So create a temporary vector,
        // add a record and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<Point> temporary_vector
            (
                boost::polygon::begin_points(ring),
                boost::polygon::end_points(ring)
            );
        temporary_vector.push_back(point);
        boost::polygon::set_points(ring, temporary_vector.begin(), temporary_vector.end());
    }

    template <typename Ring, typename Point>
    static inline void push_back(Ring& ring, Point const& point)
    {
    }


    inline ring_proxy(Polygon& p)
        : m_polygon_pointer(&p)
        , m_do_hole(false)
    {}

    inline ring_proxy()
        : m_polygon_pointer(&m_polygon_for_default_constructor)
        , m_do_hole(false)
    {}



    iterator_type begin() const
    {
        return m_do_hole
            ? boost::polygon::begin_points(*m_hole_it)
            : boost::polygon::begin_points(*m_polygon_pointer)
            ;
    }


    iterator_type end() const
    {
        return m_do_hole
            ? boost::polygon::end_points(*m_hole_it)
            : boost::polygon::end_points(*m_polygon_pointer)
            ;
    }

    void clear()
    {
        Polygon p;
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            boost::polygon::set_points(*m_polygon_pointer,
                boost::polygon::begin_points(p),
                boost::polygon::end_points(p));
        }
    }


    void resize(std::size_t new_size)
    {
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            // TODO: implement this by resizing the container
        }
    }




    template <typename Point>
    void push_back(Point const& point)
    {
        if (m_do_hole)
        {
            //detail::modify<is_mutable>::push_back(*m_hole_it, point);
            //std::cout << "HOLE: " << typeid(*m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(hole_iterator_type).name() << std::endl;

            // Note, ths does NOT work because hole_iterator_type is defined
            // as a const_iterator by Boost.Polygon

        }
        else
        {
            detail::modify<is_mutable>::push_back(*m_polygon_pointer, point);
        }
    }

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.begin();
}


template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.begin();
}


template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.end();
}


template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.end();
}

    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy)
    {
        proxy.clear();
    }

    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }

    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy,
        typename boost::polygon::polygon_traits<Polygon>::point_type const& point)
    {
        proxy.push_back(point);
    }

        static void apply()
        {
            Geometry* s = 0;
            geometry::set<Index, Dimension>(*s, geometry::get<Index, Dimension>(*s));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }

        static void apply() {}

        static void apply()
        {
            const Geometry* s = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*s));
            boost::ignore_unused_variable_warning(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }

        static void apply() {}

        static inline void apply()
        {
            polygon_type* poly = 0;
            polygon_type const* cpoly = poly;

            ring_mutable_type e = traits::exterior_ring<PolygonType>::get(*poly);
            interior_mutable_type i = traits::interior_rings<PolygonType>::get(*poly);
            ring_const_type ce = traits::exterior_ring<PolygonType>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<PolygonType>::get(*cpoly);

            boost::ignore_unused_variable_warning(e);
            boost::ignore_unused_variable_warning(i);
            boost::ignore_unused_variable_warning(ce);
            boost::ignore_unused_variable_warning(ci);
            boost::ignore_unused_variable_warning(poly);
            boost::ignore_unused_variable_warning(cpoly);
        }

        static inline void apply()
        {
            const_polygon_type const* cpoly = 0;

            ring_const_type ce = traits::exterior_ring<const_polygon_type>::get(*cpoly);
            interior_const_type ci = traits::interior_rings<const_polygon_type>::get(*cpoly);

            boost::ignore_unused_variable_warning(ce);
            boost::ignore_unused_variable_warning(ci);
            boost::ignore_unused_variable_warning(cpoly);
        }

        static void apply()
        {
            Geometry* b = 0;
            geometry::set<Index, Dimension>(*b, geometry::get<Index, Dimension>(*b));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }

        static void apply() {}

        static void apply()
        {
            const Geometry* b = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*b));
            boost::ignore_unused_variable_warning(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }

        static void apply() {}

        static void apply()
        {
            P* p = 0;
            geometry::set<Dimension>(*p, geometry::get<Dimension>(*p));
            dimension_checker<P, Dimension+1, DimensionCount>::apply();
        }

        static void apply() {}

        static void apply()
        {
            const P* p = 0;
            ctype coord(geometry::get<Dimension>(*p));
            boost::ignore_unused_variable_warning(coord);
            dimension_checker<P, Dimension+1, DimensionCount>::apply();
        }

        static void apply() {}

template <typename Geometry>
inline void check()
{
    detail::checker<Geometry> c;
    boost::ignore_unused_variable_warning(c);
}

template <typename Geometry1, typename Geometry2>
inline void check_concepts_and_equal_dimensions()
{
    check<Geometry1>();
    check<Geometry2>();
    assert_dimension_equal<Geometry1, Geometry2>();
}


    inline de9im()
        : ii(-1), ib(-1), ie(-1)
        , bi(-1), bb(-1), be(-1)
        , ei(-1), eb(-1), ee(-1)
    {
    }


    inline de9im(int ii0, int ib0, int ie0,
        int bi0, int bb0, int be0,
        int ei0, int eb0, int ee0)
        : ii(ii0), ib(ib0), ie(ie0)
        , bi(bi0), bb(bb0), be(be0)
        , ei(ei0), eb(eb0), ee(ee0)
    {}


    inline bool equals() const
    {
        return ii >= 0 && ie < 0 && be < 0 && ei < 0 && eb < 0;
    }


    inline bool disjoint() const
    {
        return ii < 0 && ib < 0 && bi < 0 && bb < 0;
    }


    inline bool intersects() const
    {
        return ii >= 0 || bb >= 0 || bi >= 0 || ib >= 0;
    }


    inline bool touches() const
    {
        return ii < 0 && (bb >= 0 || bi >= 0 || ib >= 0);
    }


    inline bool crosses() const
    {
        return (ii >= 0 && ie >= 0) || (ii == 0);
    }


    inline bool overlaps() const
    {
        return ii >= 0 && ie >= 0 && ei >= 0;
    }


    inline bool within() const
    {
        return ii >= 0 && ie < 0 && be < 0;
    }


    inline bool contains() const
    {
        return ii >= 0 && ei < 0 && eb < 0;
    }



    static inline char as_char(int v)
    {
        return v >= 0 && v < 10 ? ('0' + char(v)) : '-';
    }


    inline de9im_segment()
        : de9im()
        , collinear(false)
        , opposite(false)
        , parallel(false)
        , degenerate(false)
    {}


    inline de9im_segment(double a, double b,
        int ii0, int ib0, int ie0,
        int bi0, int bb0, int be0,
        int ei0, int eb0, int ee0,
        bool c = false, bool o = false, bool p = false, bool d = false)
        : de9im(ii0, ib0, ie0, bi0, bb0, be0, ei0, eb0, ee0)
        , collinear(c)
        , opposite(o)
        , parallel(p)
        , degenerate(d)
        , ra(a), rb(b)
    {}


    segment_intersection_points()
        : count(0)
    {}

    inline side_info(int side_a1 = 0, int side_a2 = 0,
            int side_b1 = 0, int side_b2 = 0)
    {
        sides[0].first = side_a1;
        sides[0].second = side_a2;
        sides[1].first = side_b1;
        sides[1].second = side_b2;
    }


    template <int Which>
    inline void set(int first, int second)
    {
        sides[Which].first = first;
        sides[Which].second = second;
    }


    template <int Which, int Index>
    inline void correct_to_zero()
    {
        if (Index == 0)
        {
            sides[Which].first = 0;
        }
        else
        {
            sides[Which].second = 0;
        }
    }


    template <int Which, int Index>
    inline int get() const
    {
        return Index == 0 ? sides[Which].first : sides[Which].second;
    }

    template <int Which>
    inline bool same() const
    {
        return sides[Which].first * sides[Which].second == 1;
    }


    inline bool collinear() const
    {
        return sides[0].first == 0
            && sides[0].second == 0
            && sides[1].first == 0
            && sides[1].second == 0;
    }


    inline bool crossing() const
    {
        return sides[0].first * sides[0].second == -1
            && sides[1].first * sides[1].second == -1;
    }


    inline bool touching() const
    {
        return (sides[0].first * sides[1].first == -1
            && sides[0].second == 0 && sides[1].second == 0)
            || (sides[1].first * sides[0].first == -1
            && sides[1].second == 0 && sides[0].second == 0);
    }


    template <int Which>
    inline bool one_touching() const
    {
        // This is normally a situation which can't occur:
        // If one is completely left or right, the other cannot touch
        return one_zero<Which>()
            && sides[1 - Which].first * sides[1 - Which].second == 1;
    }


    inline bool meeting() const
    {
        // Two of them (in each segment) zero, two not
        return one_zero<0>() && one_zero<1>();
    }


    template <int Which>
    inline bool zero() const
    {
        return sides[Which].first == 0 && sides[Which].second == 0;
    }


    template <int Which>
    inline bool one_zero() const
    {
        return (sides[Which].first == 0 && sides[Which].second != 0)
            || (sides[Which].first != 0 && sides[Which].second == 0);
    }


    inline bool one_of_all_zero() const
    {
        int const sum = std::abs(sides[0].first)
                + std::abs(sides[0].second)
                + std::abs(sides[1].first)
                + std::abs(sides[1].second);
        return sum == 3;
    }



    template <int Which>
    inline int zero_index() const
    {
        return sides[Which].first == 0 ? 0 : 1;
    }


    inline void reverse()
    {
        std::swap(sides[0], sides[1]);
    }

    template <typename T>
    static inline void transform(Src const& source, Dst& dest, T value)
    {
        typedef typename select_coordinate_type<Src, Dst>::type coordinate_type;

        F<coordinate_type> function;
        set<D>(dest, boost::numeric_cast<coordinate_type>(function(get<D>(source), value)));
        transform_coordinates<Src, Dst, D + 1, N, F>::transform(source, dest, value);
    }

    inline bool apply(P const& p1, P& p2) const
    {
        p2 = p1;
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        // Defensive check, dimensions are equal, selected by specialization
        assert_dimension_equal<P1, P2>();

        geometry::convert(p1, p2);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        // Spherical coordinates always have 2 coordinates measured in angles
        // The optional third one is distance/height, provided in another strategy
        // Polar coordinates having one angle, will be also in another strategy
        assert_dimension<P1, 2>();
        assert_dimension<P2, 2>();

        detail::transform_coordinates<P1, P2, 0, 2, F>::transform(p1, p2, math::d2r);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();

        detail::transform_coordinates<P1, P2, 0, 2, F>::transform(p1, p2, math::d2r);
        // Copy height or other third dimension
        set<2>(p2, get<2>(p1));
        return true;
    }

    template <typename P, typename T, typename R>
    inline void spherical_polar_to_cartesian(T phi, T theta, R r, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_spherical_coordinates
        // http://www.vias.org/comp_geometry/math_coord_convert_3d.htm
        // https://moodle.polymtl.ca/file.php/1183/Autres_Documents/Derivation_for_Spherical_Co-ordinates.pdf
        // http://en.citizendium.org/wiki/Spherical_polar_coordinates
        
        // Phi = first, theta is second, r is third, see documentation on cs::spherical

        // (calculations are splitted to implement ttmath)

        T r_sin_theta = r;
        T r_cos_theta = r;
        r_sin_theta *= sin(theta);
        r_cos_theta *= cos(theta);

        set<0>(p, r_sin_theta * cos(phi));
        set<1>(p, r_sin_theta * sin(phi));
        set<2>(p, r_cos_theta);
    }

    template <typename P, typename T, typename R>
    inline void spherical_equatorial_to_cartesian(T lambda, T delta, R r, P& p)
    {
        assert_dimension<P, 3>();

        // http://mathworld.wolfram.com/GreatCircle.html
        // http://www.spenvis.oma.be/help/background/coortran/coortran.html WRONG
        
        T r_cos_delta = r;
        T r_sin_delta = r;
        r_cos_delta *= cos(delta);
        r_sin_delta *= sin(delta);

        set<0>(p, r_cos_delta * cos(lambda));
        set<1>(p, r_cos_delta * sin(lambda));
        set<2>(p, r_sin_delta);
    }

    template <typename P, typename T>
    inline bool cartesian_to_spherical2(T x, T y, T z, P& p)
    {
        assert_dimension<P, 2>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates

#if defined(BOOST_GEOMETRY_TRANSFORM_CHECK_UNIT_SPHERE)
        // TODO: MAYBE ONLY IF TO BE CHECKED?
        T const r = /*sqrt not necessary, sqrt(1)=1*/ (x * x + y * y + z * z);

        // Unit sphere, so r should be 1
        if (geometry::math::abs(r - 1.0) > T(1e-6))
        {
            return false;
        }
        // end todo
#endif

        set_from_radian<0>(p, atan2(y, x));
        set_from_radian<1>(p, acos(z));
        return true;
    }

    
    template <typename P, typename T>
    inline bool cartesian_to_spherical_equatorial2(T x, T y, T z, P& p)
    {
        assert_dimension<P, 2>();

        set_from_radian<0>(p, atan2(y, x));
        set_from_radian<1>(p, asin(z));
        return true;
    }

    

    template <typename P, typename T>
    inline bool cartesian_to_spherical3(T x, T y, T z, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates
        T const r = sqrt(x * x + y * y + z * z);
        set<2>(p, r);
        set_from_radian<0>(p, atan2(y, x));
        if (r > 0.0)
        {
            set_from_radian<1>(p, acos(z / r));
            return true;
        }
        return false;
    }


    template <typename P, typename T>
    inline bool cartesian_to_spherical_equatorial3(T x, T y, T z, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates
        T const r = sqrt(x * x + y * y + z * z);
        set<2>(p, r);
        set_from_radian<0>(p, atan2(y, x));
        if (r > 0.0)
        {
            set_from_radian<1>(p, asin(z / r));
            return true;
        }
        return false;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 2>();
        detail::spherical_polar_to_cartesian(get_as_radian<0>(p1), get_as_radian<1>(p1), 1.0, p2);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 2>();
        detail::spherical_equatorial_to_cartesian(get_as_radian<0>(p1), get_as_radian<1>(p1), 1.0, p2);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        detail::spherical_polar_to_cartesian(
                    get_as_radian<0>(p1), get_as_radian<1>(p1), get<2>(p1), p2);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        detail::spherical_equatorial_to_cartesian(
                    get_as_radian<0>(p1), get_as_radian<1>(p1), get<2>(p1), p2);
        return true;
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical2(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical_equatorial2(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical3(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }

    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical_equatorial3(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }

        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            // 1: inspect and define both arguments of apply
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type ptype1;

            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type ptype2;

            // 2) check if apply-arguments fulfill point concept
            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<ptype1>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<ptype2>)
                );


            // 3) must define meta-function return_type
            typedef typename strategy::distance::services::return_type<Strategy>::type rtype;

            // 4) must define meta-function "similar_type"
            typedef typename strategy::distance::services::similar_type
                <
                    Strategy, ptype2, ptype1
                >::type stype;

            // 5) must define meta-function "comparable_type"
            typedef typename strategy::distance::services::comparable_type
                <
                    Strategy
                >::type ctype;

            // 6) must define meta-function "tag"
            typedef typename strategy::distance::services::tag
                <
                    Strategy
                >::type tag;

            // 7) must implement apply with arguments
            Strategy* str = 0;
            ptype1 *p1 = 0;
            ptype2 *p2 = 0;
            rtype r = str->apply(*p1, *p2);

            // 8) must define (meta)struct "get_similar" with apply
            stype s = strategy::distance::services::get_similar
                <
                    Strategy,
                    ptype2, ptype1
                >::apply(*str);

            // 9) must define (meta)struct "get_comparable" with apply
            ctype c = strategy::distance::services::get_comparable
                <
                    Strategy
                >::apply(*str);

            // 10) must define (meta)struct "result_from_distance" with apply
            r = strategy::distance::services::result_from_distance
                <
                    Strategy
                >::apply(*str, 1.0);

            boost::ignore_unused_variable_warning(str);
            boost::ignore_unused_variable_warning(s);
            boost::ignore_unused_variable_warning(c);
            boost::ignore_unused_variable_warning(r);
        }

        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type ptype;

            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type sptype;

            // 2) check if apply-arguments fulfill point concept
            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<ptype>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<sptype>)
                );


            // 3) must define meta-function return_type
            typedef typename strategy::distance::services::return_type<Strategy>::type rtype;

            // 4) must define underlying point-distance-strategy
            typedef typename strategy::distance::services::strategy_point_point<Strategy>::type stype;
            BOOST_CONCEPT_ASSERT
                (
                    (concept::PointDistanceStrategy<stype>)
                );


            Strategy *str = 0;
            ptype *p = 0;
            sptype *sp1 = 0;
            sptype *sp2 = 0;

            rtype r = str->apply(*p, *sp1, *sp2);

            boost::ignore_unused_variable_warning(str);
            boost::ignore_unused_variable_warning(r);
        }

        static void apply()
        {
            Strategy const* str;

            return_type* rt;
            //point_type const* p;
            segment_type1 const* s1;
            segment_type2 const* s2;

            // 4) must implement a method apply
            //    having two segments
            *rt = str->apply(*s1, *s2);

        }

        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            namespace ft = boost::function_types;
            typedef typename ft::parameter_types
                <
                    ApplyMethod
                >::type parameter_types;

            typedef typename boost::mpl::if_
                <
                    ft::is_member_function_pointer<ApplyMethod>,
                    boost::mpl::int_<1>,
                    boost::mpl::int_<0>
                >::type base_index;

            // 1: inspect and define both arguments of apply
            typedef typename boost::remove_const
                <
                    typename boost::remove_reference
                    <
                        typename boost::mpl::at
                            <
                                parameter_types,
                                base_index
                            >::type
                    >::type
                >::type point_type;



            BOOST_CONCEPT_ASSERT
                (
                    (concept::PointSegmentDistanceStrategy<ds_type>)
                );

            Strategy *str = 0;
            std::vector<point_type> const* v1 = 0;
            std::vector<point_type> * v2 = 0;

            // 2) must implement method apply with arguments
            //    - Range
            //    - OutputIterator
            //    - floating point value
            str->apply(*v1, std::back_inserter(*v2), 1.0);

            boost::ignore_unused_variable_warning(str);
        }

        template <typename ApplyMethod, typename ResultMethod>
        static void apply(ApplyMethod const&, ResultMethod const& )
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type segment_point_type;

            // CHECK: apply-arguments should both fulfill point concept
            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<segment_point_type>)
                );

            // CHECK: return types (result: int, apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool, typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_APPLY
                    , (bool)
                );
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            int, typename boost::function_types::result_type<ResultMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_RESULT
                    , (int)
                );


            // CHECK: calling method apply and result
            Strategy const* str = 0;
            state_type* st = 0;
            point_type const* p = 0;
            segment_point_type const* sp = 0;

            bool b = str->apply(*p, *sp, *sp, *st);
            int r = str->result(*st);

            boost::ignore_unused_variable_warning(r);
            boost::ignore_unused_variable_warning(b);
            boost::ignore_unused_variable_warning(str);
        }

        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type;

            // CHECK: apply-arguments should fulfill point/box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstBox<box_type>)
                );

            // CHECK: return types (apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool, 
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            point_type const* p = 0;
            box_type const* bx = 0;

            bool b = str->apply(*p, *bx);

            boost::ignore_unused_variable_warning(b);
            boost::ignore_unused_variable_warning(str);
        }

        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type box_type1;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type2;

            // CHECK: apply-arguments should both fulfill box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstBox<box_type1>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concept::ConstBox<box_type2>)
                );

            // CHECK: return types (apply: bool)
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool, 
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            box_type1 const* b1 = 0;
            box_type2 const* b2 = 0;

            bool b = str->apply(*b1, *b2);

            boost::ignore_unused_variable_warning(b);
            boost::ignore_unused_variable_warning(str);
        }

template <typename FirstTag, typename SecondTag, typename CastedTag, typename Strategy>
inline void check()
{
    dispatch::check_within<FirstTag, SecondTag, CastedTag, Strategy> c;
    boost::ignore_unused_variable_warning(c);
}

        static void apply()
        {
            Strategy *str = 0;
            state_type *st = 0;

            // 4) must implement a static method apply,
            // getting two segment-points
            spoint_type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 5) must implement a static method result
            //  getting the centroid
            point_type *c = 0;
            bool r = str->result(*st, *c);

            boost::ignore_unused_variable_warning(str);
            boost::ignore_unused_variable_warning(r);
        }

        static void apply()
        {
            Strategy const* str;

            state_type* st;
            geometry_type* sp;
            std::vector<point_type> *v;

            // 4) must implement a method apply, iterating over a range
            str->apply(*sp, *st);

            // 5) must implement a method result, with an output iterator
            str->result(*st, std::back_inserter(*v), true);
        }

        static void apply()
        {
            Strategy const* str = 0;
            state_type *st = 0;

            // 4) must implement a method apply with the following signature
            spoint_type const* sp = 0;
            str->apply(*sp, *sp, *st);

            // 5) must implement a static method result with the following signature
            return_type r = str->result(*st);

            boost::ignore_unused_variable_warning(r);
            boost::ignore_unused_variable_warning(str);
        }

        inline sums()
            : count(0)
            , sum_a2(calculation_type())
            , sum_x(calculation_type())
            , sum_y(calculation_type())
        {
            typedef calculation_type ct;
        }


    static inline void apply(PointOfSegment const& p1,
            PointOfSegment const& p2, sums& state)
    {
        /* Algorithm:
        For each segment:
        begin
            ai = x1 * y2 - x2 * y1;
            sum_a2 += ai;
            sum_x += ai * (x1 + x2);
            sum_y += ai * (y1 + y2);
        end
        return POINT(sum_x / (3 * sum_a2), sum_y / (3 * sum_a2) )
        */

        // Get coordinates and promote them to calculation_type
        calculation_type const x1 = boost::numeric_cast<calculation_type>(get<0>(p1));
        calculation_type const y1 = boost::numeric_cast<calculation_type>(get<1>(p1));
        calculation_type const x2 = boost::numeric_cast<calculation_type>(get<0>(p2));
        calculation_type const y2 = boost::numeric_cast<calculation_type>(get<1>(p2));
        calculation_type const ai = geometry::detail::determinant<calculation_type>(p1, p2);
        state.count++;
        state.sum_a2 += ai;
        state.sum_x += ai * (x1 + x2);
        state.sum_y += ai * (y1 + y2);
    }


    static inline bool result(sums const& state, Point& centroid)
    {
        calculation_type const zero = calculation_type();
        if (state.count > 0 && ! math::equals(state.sum_a2, zero))
        {
            calculation_type const v3 = 3;
            calculation_type const a3 = v3 * state.sum_a2;

            typedef typename geometry::coordinate_type
                <
                    Point
                >::type coordinate_type;

            set<0>(centroid,
                boost::numeric_cast<coordinate_type>(state.sum_x / a3));
            set<1>(centroid,
                boost::numeric_cast<coordinate_type>(state.sum_y / a3));
            return true;
        }

        return false;
    }


    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename boost::mpl::if_c
            <
                boost::is_void<CalculationType>::type::value,
                typename select_most_precise
                    <
                        typename select_most_precise
                            <
                                typename coordinate_type<P1>::type,
                                typename coordinate_type<P2>::type
                            >::type,
                        typename coordinate_type<P>::type
                    >::type,
                CalculationType
            >::type coordinate_type;

        coordinate_type const x = get<0>(p);
        coordinate_type const y = get<1>(p);

        coordinate_type const sx1 = get<0>(p1);
        coordinate_type const sy1 = get<1>(p1);
        coordinate_type const sx2 = get<0>(p2);
        coordinate_type const sy2 = get<1>(p2);

        // Promote float->double, small int->int
        typedef typename select_most_precise
            <
                coordinate_type,
                double
            >::type promoted_type;

        promoted_type const dx = sx2 - sx1;
        promoted_type const dy = sy2 - sy1;
        promoted_type const dpx = x - sx1;
        promoted_type const dpy = y - sy1;

        promoted_type const s 
            = geometry::detail::determinant<promoted_type>
                (
                    dx, dy, 
                    dpx, dpy
                );

        promoted_type const zero = promoted_type();
        return math::equals(s, zero) ? 0 
            : s > zero ? 1 
            : -1;
    }


        inline flags()
            : inside_flag(false)
            , first(true)
            , yflag0(false)
        {}


    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            flags& state)
    {
        calculation_type const tx = get<0>(point);
        calculation_type const ty = get<1>(point);
        calculation_type const x0 = get<0>(seg1);
        calculation_type const y0 = get<1>(seg1);
        calculation_type const x1 = get<0>(seg2);
        calculation_type const y1 = get<1>(seg2);

        if (state.first)
        {
            state.first = false;
            state.yflag0 = y0 >= ty;
        }


        bool yflag1 = y1 >= ty;
        if (state.yflag0 != yflag1)
        {
            if ( ((y1-ty) * (x0-x1) >= (x1-tx) * (y0-y1)) == yflag1 )
            {
                state.inside_flag = ! state.inside_flag;
            }
        }
        state.yflag0 = yflag1;
        return true;
    }


    static inline int result(flags const& state)
    {
        return state.inside_flag ? 1 : -1;
    }


template <std::size_t Dimension, typename Segment, typename T>
static inline void segment_arrange(Segment const& s, T& s_1, T& s_2, bool& swapped)
{
    s_1 = get<0, Dimension>(s);
    s_2 = get<1, Dimension>(s);
    if (s_1 > s_2)
    {
        std::swap(s_1, s_2);
        swapped = true;
    }
}

    static inline return_type apply(segment_type1 const& a, segment_type2 const& b)
    {
        coordinate_type const dx_a = get<1, 0>(a) - get<0, 0>(a); // distance in x-dir
        coordinate_type const dx_b = get<1, 0>(b) - get<0, 0>(b);
        coordinate_type const dy_a = get<1, 1>(a) - get<0, 1>(a); // distance in y-dir
        coordinate_type const dy_b = get<1, 1>(b) - get<0, 1>(b);
        return apply(a, b, dx_a, dy_a, dx_b, dy_b);
    }

    template <typename T>
    static inline bool robustness_verify_r(
                segment_type1 const& a, segment_type2 const& b,
                T& r)
    {
        T const zero = 0;
        T const one = 1;
        if (r < zero || r > one)
        {
            if (verify_disjoint<0>(a, b) || verify_disjoint<1>(a, b))
            {
                // Can still be disjoint (even if not one is left or right from another)
                // This is e.g. in case #snake4 of buffer test.
                return false;
            }

            //std::cout << "ROBUSTNESS: correction of r " << r << std::endl;
            // sides.debug();

            // ROBUSTNESS: the r value can in epsilon-cases much larger than 1, while (with perfect arithmetic)
            // it should be one. It can be 1.14 or even 1.98049 or 2 (while still intersecting)

            // If segments are crossing (we can see that with the sides)
            // and one is inside the other, there must be an intersection point.
            // We correct for that.
            // This is (only) in case #ggl_list_20110820_christophe in unit tests

            // If segments are touching (two sides zero), of course they should intersect
            // This is (only) in case #buffer_rt_i in the unit tests)

            // If one touches in the middle, they also should intersect (#buffer_rt_j)

            // Note that even for ttmath r is occasionally > 1, e.g. 1.0000000000000000000000036191231203575

            if (r > one)
            {
                r = one;
            }
            else if (r < zero)
            {
                r = zero;
            }
        }
        return true;
    }


    static inline void robustness_verify_collinear(
                segment_type1 const& , segment_type2 const& ,
                bool a_is_point, bool b_is_point, 
                side_info& sides,
                bool& collinear)
    {
        if ((sides.zero<0>() && ! b_is_point && ! sides.zero<1>()) || (sides.zero<1>() && ! a_is_point && ! sides.zero<0>()))
        {
            // If one of the segments is collinear, the other must be as well.
            // So handle it as collinear.
            // (In float/double epsilon margins it can easily occur that one or two of them are -1/1)
            // sides.debug();
            sides.set<0>(0,0);
            sides.set<1>(0,0);
            collinear = true;
        }
    }


    static inline void robustness_verify_meeting(
                segment_type1 const& a, segment_type2 const& b,
                side_info& sides,
                bool& collinear, bool& collinear_use_first)
    {
        if (sides.meeting())
        {
            // If two segments meet each other at their segment-points, two sides are zero,
            // the other two are not (unless collinear but we don't mean those here).
            // However, in near-epsilon ranges it can happen that two sides are zero
            // but they do not meet at their segment-points.
            // In that case they are nearly collinear and handled as such.
            if (! point_equals
                    (
                        select(sides.zero_index<0>(), a),
                        select(sides.zero_index<1>(), b)
                    )
                )
            {
                sides.set<0>(0,0);
                sides.set<1>(0,0);
                collinear = true;

                if (collinear_use_first && analyse_equal<0>(a, b))
                {
                    collinear_use_first = false;
                }
                else if (! collinear_use_first && analyse_equal<1>(a, b))
                {
                    collinear_use_first = true;
                }

            }
        }
    }

    static inline bool robustness_verify_same_side(
                segment_type1 const& a, segment_type2 const& b,
                side_info& sides)
    {
        int corrected = 0;
        if (sides.one_touching<0>())
        {
            if (point_equals(
                        select(sides.zero_index<0>(), a),
                        select(0, b)
                    ))
            {
                sides.correct_to_zero<1, 0>();
                corrected = 1;
            }
            if (point_equals
                    (
                        select(sides.zero_index<0>(), a),
                        select(1, b)
                    ))
            {
                sides.correct_to_zero<1, 1>();
                corrected = 2;
            }
        }
        else if (sides.one_touching<1>())
        {
            if (point_equals(
                        select(sides.zero_index<1>(), b),
                        select(0, a)
                    ))
            {
                sides.correct_to_zero<0, 0>();
                corrected = 3;
            }
            if (point_equals
                    (
                        select(sides.zero_index<1>(), b),
                        select(1, a)
                    ))
            {
                sides.correct_to_zero<0, 1>();
                corrected = 4;
            }
        }

        return corrected == 0;
    }


    static inline bool robustness_verify_disjoint_at_one_collinear(
                segment_type1 const& a, segment_type2 const& b,
                side_info const& sides)
    {
        if (sides.one_of_all_zero())
        {
            if (verify_disjoint<0>(a, b) || verify_disjoint<1>(a, b))
            {
                return true;
            }
        }
        return false;
    }

    template <std::size_t Dimension>
    static inline bool verify_disjoint(segment_type1 const& a,
                    segment_type2 const& b)
    {
        coordinate_type a_1, a_2, b_1, b_2;
        bool a_swapped = false, b_swapped = false;
        detail::segment_arrange<Dimension>(a, a_1, a_2, a_swapped);
        detail::segment_arrange<Dimension>(b, b_1, b_2, b_swapped);
        return math::smaller(a_2, b_1) || math::larger(a_1, b_2);
    }


        inline summation() : sum(return_type())
        {
            // Strategy supports only 2D areas
            assert_dimension<PointOfSegment, 2>();
        }

        inline return_type area() const
        {
            return_type result = sum;
            return_type const two = 2;
            result /= two;
            return result;
        }


    static inline void apply(PointOfSegment const& p1,
                PointOfSegment const& p2,
                summation& state)
    {
        // SUM += x2 * y1 - x1 * y2;
        state.sum += detail::determinant<return_type>(p2, p1);
    }


    static inline return_type result(summation const& state)
    {
        return state.area();
    }

    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value > min_value && value < max_value;
    }

    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value >= min_value && value <= max_value;
    }

    static inline bool apply(Point const& point, Box const& box)
    {
        if (! SubStrategy::apply(get<Dimension>(point), 
                    get<min_corner, Dimension>(box), 
                    get<max_corner, Dimension>(box))
            )
        {
            return false;
        }
        
        return relate_point_box_loop
            <
                SubStrategy,
                Point, Box,
                Dimension + 1, DimensionCount
            >::apply(point, box);
    }

    static inline bool apply(Point const& , Box const& )
    {
        return true;
    }

    static inline bool apply(Point const& point, Box const& box) 
    {
        return relate_point_box_loop
            <
                SubStrategy,
                Point, Box, 
                0, dimension<Point>::type::value
            >::apply(point, box);
    }


    inline weighted_length_sums()
        : length(Type())
    {
        geometry::assign_zero(average_sum);
    }


    static inline void apply(PointOfSegment const& p1,
            PointOfSegment const& p2, state_type& state)
    {
        distance_type const d = geometry::distance(p1, p2);
        state.length += d;

        typename state_type::work_point weighted_median;
        geometry::assign_zero(weighted_median);
        geometry::add_point(weighted_median, p1);
        geometry::add_point(weighted_median, p2);
        geometry::multiply_value(weighted_median, d/2);
        geometry::add_point(state.average_sum, weighted_median);
    }


    static inline bool result(state_type const& state, Point& centroid)
    {
        distance_type const zero = distance_type();
        if (! geometry::math::equals(state.length, zero))
        {
            assign_zero(centroid);
            add_point(centroid, state.average_sum);
            divide_value(centroid, state.length);
            return true;
        }

        return false;
    }

            inline crossings()
                : crosses(false)
            {}


    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            crossings& state)
    {
        calculation_type const& px = get<0>(point);
        calculation_type const& py = get<1>(point);
        calculation_type const& x1 = get<0>(seg1);
        calculation_type const& y1 = get<1>(seg1);
        calculation_type const& x2 = get<0>(seg2);
        calculation_type const& y2 = get<1>(seg2);

        if (
            ( (y2 <= py && py < y1) || (y1 <= py && py < y2) )
            && (px < (x1 - x2) * (py - y2) / (y1 - y2) + x2)
            )
        {
            state.crosses = ! state.crosses;
        }
        return true;
    }


    static inline int result(crossings const& state)
    {
        return state.crosses ? 1 : -1;
    }

    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min
                , BoxContainedValue const& bed_max
                , BoxContainingValue const& bing_min
                , BoxContainingValue const& bing_max)
    {
        return bed_min > bing_min && bed_max < bing_max;
    }

    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min
                , BoxContainedValue const& bed_max
                , BoxContainingValue const& bing_min
                , BoxContainingValue const& bing_max)
    {
        return bed_min >= bing_min && bed_max <= bing_max;
    }

    static inline bool apply(Box1 const& b_contained, Box2 const& b_containing)
    {
        assert_dimension_equal<Box1, Box2>();

        if (! SubStrategy::apply(
                    get<min_corner, Dimension>(b_contained), 
                    get<max_corner, Dimension>(b_contained), 
                    get<min_corner, Dimension>(b_containing), 
                    get<max_corner, Dimension>(b_containing)
                )
            )
        {
            return false;
        }

        return relate_box_box_loop
            <
                SubStrategy,
                Box1, Box2,
                Dimension + 1, DimensionCount
            >::apply(b_contained, b_containing);
    }

    static inline bool apply(Box1 const& , Box2 const& )
    {
        return true;
    }

    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return relate_box_box_loop
            <
                SubStrategy, 
                Box1, Box2, 0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }

    static inline T apply(Point1 const& p1, Point2 const& p2)
    {
        T const c1 = boost::numeric_cast<T>(get<I-1>(p1));
        T const c2 = boost::numeric_cast<T>(get<I-1>(p2));
        T const d = c1 - c2;
        return d * d + compute_pythagoras<Point1, Point2, I-1, T>::apply(p1, p2);
    }

    static inline T apply(Point1 const&, Point2 const&)
    {
        return boost::numeric_cast<T>(0);
    }


    static inline calculation_type apply(Point1 const& p1, Point2 const& p2)
    {
        BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point1>) );
        BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

        // Calculate distance using Pythagoras
        // (Leave comment above for Doxygen)

        assert_dimension_equal<Point1, Point2>();

        return detail::compute_pythagoras
            <
                Point1, Point2,
                dimension<Point1>::value,
                calculation_type
            >::apply(p1, p2);
    }

    static inline calculation_type apply(Point1 const& p1, Point2 const& p2)
    {
        calculation_type const t = comparable_type::apply(p1, p2);
        return sqrt(t);
    }

    static inline comparable_type apply(pythagoras<Point1, Point2, CalculationType> const& )
    {
        return comparable_type();
    }

    template <typename T>
    static inline return_type apply(pythagoras<Point1, Point2, CalculationType> const& , T const& value)
    {
        return return_type(value);
    }


        inline douglas_peucker_point(Point const& ap)
            : p(ap)
            , included(false)
        {}

        inline douglas_peucker_point<Point> operator=(douglas_peucker_point<Point> const& )
        {
            return douglas_peucker_point<Point>(*this);
        }



    static inline void consider(iterator_type begin,
                iterator_type end,
                return_type const& max_dist, int& n,
                distance_strategy_type const& ps_distance_strategy)
    {
        std::size_t size = end - begin;

        // size must be at least 3
        // because we want to consider a candidate point in between
        if (size <= 2)
        {
#ifdef GL_DEBUG_DOUGLAS_PEUCKER
            if (begin != end)
            {
                std::cout << "ignore between " << dsv(begin->p)
                    << " and " << dsv((end - 1)->p)
                    << " size=" << size << std::endl;
            }
            std::cout << "return because size=" << size << std::endl;
#endif
            return;
        }

        iterator_type last = end - 1;

#ifdef GL_DEBUG_DOUGLAS_PEUCKER
        std::cout << "find between " << dsv(begin->p)
            << " and " << dsv(last->p)
            << " size=" << size << std::endl;
#endif


        // Find most far point, compare to the current segment
        //geometry::segment<Point const> s(begin->p, last->p);
        return_type md(-1.0); // any value < 0
        iterator_type candidate;
        for(iterator_type it = begin + 1; it != last; ++it)
        {
            return_type dist = ps_distance_strategy.apply(it->p, begin->p, last->p);

#ifdef GL_DEBUG_DOUGLAS_PEUCKER
            std::cout << "consider " << dsv(it->p)
                << " at " << double(dist)
                << ((dist > max_dist) ? " maybe" : " no") 
                << std::endl;

#endif
            if (dist > md)
            {
                md = dist;
                candidate = it;
            }
        }

        // If a point is found, set the include flag
        // and handle segments in between recursively
        if (md > max_dist)
        {
#ifdef GL_DEBUG_DOUGLAS_PEUCKER
            std::cout << "use " << dsv(candidate->p) << std::endl;
#endif

            candidate->included = true;
            n++;

            consider(begin, candidate + 1, max_dist, n, ps_distance_strategy);
            consider(candidate, end, max_dist, n, ps_distance_strategy);
        }
    }


    template <typename Range, typename OutputIterator>
    static inline OutputIterator apply(Range const& range,
                    OutputIterator out, double max_distance)
    {
        distance_strategy_type strategy;

        // Copy coordinates, a vector of references to all points
        std::vector<dp_point_type> ref_candidates(boost::begin(range),
                        boost::end(range));

        // Include first and last point of line,
        // they are always part of the line
        int n = 2;
        ref_candidates.front().included = true;
        ref_candidates.back().included = true;

        // Get points, recursively, including them if they are further away
        // than the specified distance
        typedef typename strategy::distance::services::return_type<distance_strategy_type>::type return_type;

        consider(boost::begin(ref_candidates), boost::end(ref_candidates), max_distance, n, strategy);

        // Copy included elements to the output
        for(typename std::vector<dp_point_type>::const_iterator it
                        = boost::begin(ref_candidates);
            it != boost::end(ref_candidates);
            ++it)
        {
            if (it->included)
            {
                // copy-coordinates does not work because OutputIterator
                // does not model Point (??)
                //geometry::convert(it->p, *out);
                *out = it->p;
                out++;
            }
        }
        return out;
    }


    inline get_extremes()
        : first(true)
    {}


    inline void apply(InputRange const& range)
    {
        if (boost::size(range) == 0)
        {
            return;
        }

        // First iterate through this range
        // (this two-stage approach avoids many point copies,
        //  because iterators are kept in memory. Because iterators are
        //  not persistent (in MSVC) this approach is not applicable
        //  for more ranges together)

        RangeIterator left_it = boost::begin(range);
        RangeIterator right_it = boost::begin(range);

        for (RangeIterator it = boost::begin(range) + 1;
            it != boost::end(range);
            ++it)
        {
            if (less(*it, *left_it))
            {
                left_it = it;
            }

            if (greater(*it, *right_it))
            {
                right_it = it;
            }
        }

        // Then compare with earlier
        if (first)
        {
            // First time, assign left/right
            left = *left_it;
            right = *right_it;
            first = false;
        }
        else
        {
            // Next time, check if this range was left/right from
            // the extremes already collected
            if (less(*left_it, left))
            {
                left = *left_it;
            }

            if (greater(*right_it, right))
            {
                right = *right_it;
            }
        }
    }


    inline assign_range(point_type const& left, point_type const& right)
        : most_left(left)
        , most_right(right)
    {}


    inline void apply(InputRange const& range)
    {
        typedef SideStrategy side;

        // Put points in one of the two output sequences
        for (RangeIterator it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            // check if it is lying most_left or most_right from the line

            int dir = side::apply(most_left, most_right, *it);
            switch(dir)
            {
                case 1 : // left side
                    upper_points.push_back(*it);
                    break;
                case -1 : // right side
                    lower_points.push_back(*it);
                    break;

                // 0: on line most_left-most_right,
                //    or most_left, or most_right,
                //    -> all never part of hull
            }
        }
    }


template <typename Range>
static inline void sort(Range& range)
{
    typedef typename boost::range_value<Range>::type point_type;
    typedef geometry::less<point_type> comparator;

    std::sort(boost::begin(range), boost::end(range), comparator());
}



    inline void apply(InputGeometry const& geometry, partitions& state) const
    {
        // First pass.
        // Get min/max (in most cases left / right) points
        // This makes use of the geometry::less/greater predicates

        // For the left boundary it is important that multiple points
        // are sorted from bottom to top. Therefore the less predicate
        // does not take the x-only template parameter (this fixes ticket #6019.
        // For the right boundary it is not necessary (though also not harmful), 
        // because points are sorted from bottom to top in a later stage.
        // For symmetry and to get often more balanced lower/upper halves
        // we keep it.

        typedef typename geometry::detail::range_type<InputGeometry>::type range_type;

        typedef typename boost::range_iterator
            <
                range_type const
            >::type range_iterator;

        detail::get_extremes
            <
                range_type,
                range_iterator,
                geometry::less<point_type>,
                geometry::greater<point_type>
            > extremes;
        geometry::detail::for_each_range(geometry, extremes);

        // Bounding left/right points
        // Second pass, now that extremes are found, assign all points
        // in either lower, either upper
        detail::assign_range
            <
                range_type,
                range_iterator,
                container_type,
                typename strategy::side::services::default_strategy<cs_tag>::type
            > assigner(extremes.left, extremes.right);

        geometry::detail::for_each_range(geometry, assigner);


        // Sort both collections, first on x(, then on y)
        detail::sort(assigner.lower_points);
        detail::sort(assigner.upper_points);

        //std::cout << boost::size(assigner.lower_points) << std::endl;
        //std::cout << boost::size(assigner.upper_points) << std::endl;

        // And decide which point should be in the final hull
        build_half_hull<-1>(assigner.lower_points, state.m_lower_hull,
                extremes.left, extremes.right);
        build_half_hull<1>(assigner.upper_points, state.m_upper_hull,
                extremes.left, extremes.right);
    }



    template <typename OutputIterator>
    inline void result(partitions const& state,
                    OutputIterator out, bool clockwise)  const
    {
        if (clockwise)
        {
            output_range<iterate_forward>(state.m_upper_hull, out, false);
            output_range<iterate_reverse>(state.m_lower_hull, out, true);
        }
        else
        {
            output_range<iterate_forward>(state.m_lower_hull, out, false);
            output_range<iterate_reverse>(state.m_upper_hull, out, true);
        }
    }


    template <int Factor>
    static inline void build_half_hull(container_type const& input,
            container_type& output,
            point_type const& left, point_type const& right)
    {
        output.push_back(left);
        for(iterator it = input.begin(); it != input.end(); ++it)
        {
            add_to_hull<Factor>(*it, output);
        }
        add_to_hull<Factor>(right, output);
    }



    template <int Factor>
    static inline void add_to_hull(point_type const& p, container_type& output)
    {
        typedef typename strategy::side::services::default_strategy<cs_tag>::type side;

        output.push_back(p);
        register std::size_t output_size = output.size();
        while (output_size >= 3)
        {
            rev_iterator rit = output.rbegin();
            point_type const& last = *rit++;
            point_type const& last2 = *rit++;

            if (Factor * side::apply(*rit, last, last2) <= 0)
            {
                // Remove last two points from stack, and add last again
                // This is much faster then erasing the one but last.
                output.pop_back();
                output.pop_back();
                output.push_back(last);
                output_size--;
            }
            else
            {
                return;
            }
        }
    }



    template <iterate_direction Direction, typename OutputIterator>
    static inline void output_range(container_type const& range,
        OutputIterator out, bool skip_first)
    {
        typedef typename reversible_view<container_type const, Direction>::type view_type;
        view_type view(range);
        bool first = true;
        for (typename boost::range_iterator<view_type const>::type it = boost::begin(view);
            it != boost::end(view); ++it)
        {
            if (first && skip_first)
            {
                first = false;
            }
            else
            {
                *out = *it;
                ++out;
            }
        }
    }


        inline int code() const
        {
            return m_touches ? 0 : m_count == 0 ? -1 : 1;
        }


        inline counter()
            : m_count(0)
            , m_touches(false)
        {}



    template <size_t D>
    static inline int check_touch(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);
        if ((s1 <= p && s2 >= p) || (s2 <= p && s1 >= p))
        {
            state.m_touches = true;
        }
        return 0;
    }



    template <size_t D>
    static inline int check_segment(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);

        // Check if one of segment endpoints is at same level of point
        bool eq1 = math::equals(s1, p);
        bool eq2 = math::equals(s2, p);

        if (eq1 && eq2)
        {
            // Both equal p -> segment is horizontal (or vertical for D=0)
            // The only thing which has to be done is check if point is ON segment
            return check_touch<1 - D>(point, seg1, seg2,state);
        }

        return
              eq1 ? (s2 > p ?  1 : -1)  // Point on level s1, UP/DOWN depending on s2
            : eq2 ? (s1 > p ? -1 :  1)  // idem
            : s1 < p && s2 > p ?  2     // Point between s1 -> s2 --> UP
            : s2 < p && s1 > p ? -2     // Point between s2 -> s1 --> DOWN
            : 0;
    }


    static inline bool apply(Point const& point,
                PointOfSegment const& s1, PointOfSegment const& s2,
                counter& state)
    {
        int count = check_segment<1>(point, s1, s2, state);
        if (count != 0)
        {
            int side = strategy_side_type::apply(s1, s2, point);
            if (side == 0)
            {
                // Point is lying on segment
                state.m_touches = true;
                state.m_count = 0;
                return false;
            }

            // Side is NEG for right, POS for left.
            // The count is -2 for down, 2 for up (or -1/1)
            // Side positive thus means UP and LEFTSIDE or DOWN and RIGHTSIDE
            // See accompagnying figure (TODO)
            if (side * count > 0)
            {
                state.m_count += count;
            }
        }
        return ! state.m_touches;
    }


    static inline int result(counter const& state)
    {
        return state.code();
    }

    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = false;
            return false;
        }
        return true; // continue
    }

    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = side >= 0;
            return false;
        }
        return true; // continue
    }


    static inline bool apply(Point const& point, Box const& box)
    {
        // Create (counterclockwise) array of points, the fifth one closes it
        // Every point should be on the LEFT side (=1), or ON the border (=0),
        // So >= 1 or >= 0
        boost::array<typename point_type<Box>::type, 5> bp;
        geometry::detail::assign_box_corners_oriented<true>(box, bp);
        bp[4] = bp[0];
        
        bool result = true;
        side_strategy_type strategy;
        boost::ignore_unused_variable_warning(strategy);
        
        for (int i = 1; i < 5; i++)
        {
            int const side = strategy.apply(point, bp[i - 1], bp[i]);
            if (! Decide::apply(side, result))
            {
                return result;
            }
        }
    
        return result;
    }


        inline int code() const
        {
            return m_touches ? 0 : m_count == 0 ? -1 : 1;
        }

        inline int clockwise_oriented_code() const
        {
            return (m_sum_area > 0) ? code() : -code();
        }

        inline int oriented_code() const
        {
            return Reverse
                ? -clockwise_oriented_code()
                : clockwise_oriented_code();
        }


        inline counter()
            : m_count(0)
            , m_touches(false)
            , m_sum_area(0)
        {}


        inline void add_to_area(calculation_type triangle)
        {
            m_sum_area += triangle;
        }



    template <size_t D>
    static inline int check_touch(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);
        if ((s1 <= p && s2 >= p) || (s2 <= p && s1 >= p))
        {
            state.m_touches = true;
        }
        return 0;
    }



    template <size_t D>
    static inline int check_segment(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);


        // Check if one of segment endpoints is at same level of point
        bool eq1 = math::equals(s1, p);
        bool eq2 = math::equals(s2, p);

        if (eq1 && eq2)
        {
            // Both equal p -> segment is horizontal (or vertical for D=0)
            // The only thing which has to be done is check if point is ON segment
            return check_touch<1 - D>(point, seg1, seg2, state);
        }

        return
              eq1 ? (s2 > p ?  1 : -1)  // Point on level s1, UP/DOWN depending on s2
            : eq2 ? (s1 > p ? -1 :  1)  // idem
            : s1 < p && s2 > p ?  2     // Point between s1 -> s2 --> UP
            : s2 < p && s1 > p ? -2     // Point between s2 -> s1 --> DOWN
            : 0;
    }


    static inline bool apply(Point const& point,
                PointOfSegment const& s1, PointOfSegment const& s2,
                counter& state)
    {
        state.add_to_area(get<0>(s2) * get<1>(s1) - get<0>(s1) * get<1>(s2));

        int count = check_segment<1>(point, s1, s2, state);
        if (count != 0)
        {
            int side = strategy_side_type::apply(s1, s2, point);
            if (side == 0)
            {
                // Point is lying on segment
                state.m_touches = true;
                state.m_count = 0;
                return false;
            }

            // Side is NEG for right, POS for left.
            // The count is -2 for down, 2 for up (or -1/1)
            // Side positive thus means UP and LEFTSIDE or DOWN and RIGHTSIDE
            // See accompagnying figure (TODO)
            if (side * count > 0)
            {
                state.m_count += count;
            }
        }
        return ! state.m_touches;
    }


    static inline int result(counter const& state)
    {
        return state.oriented_code();
    }

    template <typename Transformer>
    inline inverse_transformer(Transformer const& input)
    {
        typedef boost::numeric::ublas::matrix<T> matrix_type;

        // create a working copy of the input
        matrix_type copy(input.matrix());

        // create a permutation matrix for the LU-factorization
        typedef boost::numeric::ublas::permutation_matrix<> permutation_matrix;
        permutation_matrix pm(copy.size1());

        // perform LU-factorization
        int res = boost::numeric::ublas::lu_factorize<matrix_type>(copy, pm);
        if( res == 0 )
        {
            // create identity matrix
            this->m_matrix.assign(boost::numeric::ublas::identity_matrix<T>(copy.size1()));

            // backsubstitute to get the inverse
            boost::numeric::ublas::lu_substitute(copy, pm, this->m_matrix);
        }
    }


    inline ublas_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2)
        : m_matrix(3, 3)
    {
        m_matrix(0,0) = m_0_0;   m_matrix(0,1) = m_0_1;   m_matrix(0,2) = m_0_2;
        m_matrix(1,0) = m_1_0;   m_matrix(1,1) = m_1_1;   m_matrix(1,2) = m_1_2;
        m_matrix(2,0) = m_2_0;   m_matrix(2,1) = m_2_1;   m_matrix(2,2) = m_2_2;
    }



    inline ublas_transformer() : m_matrix(3, 3) {}


    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension_greater_equal<P1, 2>();
        assert_dimension_greater_equal<P2, 2>();

        coordinate_type const& c1 = get<0>(p1);
        coordinate_type const& c2 = get<1>(p1);


        coordinate_type p2x = c1 * m_matrix(0,0) + c2 * m_matrix(0,1) + m_matrix(0,2);
        coordinate_type p2y = c1 * m_matrix(1,0) + c2 * m_matrix(1,1) + m_matrix(1,2);

        typedef typename geometry::coordinate_type<P2>::type ct2;
        set<0>(p2, boost::numeric_cast<ct2>(p2x));
        set<1>(p2, boost::numeric_cast<ct2>(p2y));

        return true;
    }

    inline ublas_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2)
        : ublas_transformer<P1, P2, 2, 2>(
                    m_0_0, m_0_1, m_0_2,
                    m_1_0, m_1_1, m_1_2,
                    m_2_0, m_2_1, m_2_2)
    {}


    inline ublas_transformer()
        : ublas_transformer<P1, P2, 2, 2>()
    {}

    inline ublas_transformer(
                ct const& m_0_0, ct const& m_0_1, ct const& m_0_2, ct const& m_0_3,
                ct const& m_1_0, ct const& m_1_1, ct const& m_1_2, ct const& m_1_3,
                ct const& m_2_0, ct const& m_2_1, ct const& m_2_2, ct const& m_2_3,
                ct const& m_3_0, ct const& m_3_1, ct const& m_3_2, ct const& m_3_3
                )
        : m_matrix(4, 4)
    {
        m_matrix(0,0) = m_0_0; m_matrix(0,1) = m_0_1; m_matrix(0,2) = m_0_2; m_matrix(0,3) = m_0_3;
        m_matrix(1,0) = m_1_0; m_matrix(1,1) = m_1_1; m_matrix(1,2) = m_1_2; m_matrix(1,3) = m_1_3;
        m_matrix(2,0) = m_2_0; m_matrix(2,1) = m_2_1; m_matrix(2,2) = m_2_2; m_matrix(2,3) = m_2_3;
        m_matrix(3,0) = m_3_0; m_matrix(3,1) = m_3_1; m_matrix(3,2) = m_3_2; m_matrix(3,3) = m_3_3;
    }


    inline ublas_transformer() : m_matrix(4, 4) {}


    inline bool apply(P1 const& p1, P2& p2) const
    {
        coordinate_type const& c1 = get<0>(p1);
        coordinate_type const& c2 = get<1>(p1);
        coordinate_type const& c3 = get<2>(p1);

        typedef typename geometry::coordinate_type<P2>::type ct2;

        set<0>(p2, boost::numeric_cast<ct2>(
            c1 * m_matrix(0,0) + c2 * m_matrix(0,1) + c3 * m_matrix(0,2) + m_matrix(0,3)));
        set<1>(p2, boost::numeric_cast<ct2>(
            c1 * m_matrix(1,0) + c2 * m_matrix(1,1) + c3 * m_matrix(1,2) + m_matrix(1,3)));
        set<2>(p2, boost::numeric_cast<ct2>(
            c1 * m_matrix(2,0) + c2 * m_matrix(2,1) + c3 * m_matrix(2,2) + m_matrix(2,3)));

        return true;
    }

    inline translate_transformer(coordinate_type const& translate_x,
                coordinate_type const& translate_y,
                coordinate_type const& = 0)
        : ublas_transformer<P1, P2, 2, 2>(
                1, 0, translate_x,
                0, 1, translate_y,
                0, 0, 1)
    {}

    inline scale_transformer(coordinate_type const& scale_x,
                coordinate_type const& scale_y,
                coordinate_type const& = 0)
        : ublas_transformer<P1, P2, 2, 2>(
                scale_x, 0,       0,
                0,       scale_y, 0,
                0,       0,       1)
    {}

    inline rotate_transformer(angle_type const& angle)
        : detail::rad_rotate_transformer
            <
                P1, P2
            >(detail::as_radian<DegreeOrRadian>::get(angle))
    {}

    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename boost::mpl::if_c
            <
                boost::is_void<CalculationType>::type::value,

                // Select at least a double...
                typename select_most_precise
                    <
                        typename select_most_precise
                            <
                                typename select_most_precise
                                    <
                                        typename coordinate_type<P1>::type,
                                        typename coordinate_type<P2>::type
                                    >::type,
                                typename coordinate_type<P>::type
                            >::type,
                        double
                    >::type,
                CalculationType
            >::type coordinate_type;

        // Convenient shortcuts
        typedef coordinate_type ct;
        ct const lambda1 = get_as_radian<0>(p1);
        ct const delta1 = get_as_radian<1>(p1);
        ct const lambda2 = get_as_radian<0>(p2);
        ct const delta2 = get_as_radian<1>(p2);
        ct const lambda = get_as_radian<0>(p);
        ct const delta = get_as_radian<1>(p);

        // Create temporary points (vectors) on unit a sphere
        ct const cos_delta1 = cos(delta1);
        ct const c1x = cos_delta1 * cos(lambda1);
        ct const c1y = cos_delta1 * sin(lambda1);
        ct const c1z = sin(delta1);

        ct const cos_delta2 = cos(delta2);
        ct const c2x = cos_delta2 * cos(lambda2);
        ct const c2y = cos_delta2 * sin(lambda2);
        ct const c2z = sin(delta2);

        // (Third point is converted directly)
        ct const cos_delta = cos(delta);
        
        // Apply the "Spherical Side Formula" as presented on my blog
        ct const dist 
            = (c1y * c2z - c1z * c2y) * cos_delta * cos(lambda) 
            + (c1z * c2x - c1x * c2z) * cos_delta * sin(lambda)
            + (c1x * c2y - c1y * c2x) * sin(delta);
        
        ct zero = ct();
        return dist > zero ? 1
            : dist < zero ? -1
            : 0;
    }

    static inline CoordinateType put_in_range(CoordinateType const& c,
            double min_border, double max_border)
    {
        CoordinateType value = c;
        while (value < min_border)
        {
            value += detail::shift<Units>::full();
        }
        while (value > max_border)
        {
            value -= detail::shift<Units>::full();
        }
        return value;
    }


    inline bool operator()(CoordinateType const& c1, CoordinateType const& c2)  const
    {
        Compare compare;

        // Check situation that one of them is e.g. std::numeric_limits.
        static const double full = detail::shift<Units>::full();
        double mx = 10.0 * full;
        if (c1 < -mx || c1 > mx || c2 < -mx || c2 > mx)
        {
            // do normal comparison, using circular is not useful
            return compare(c1, c2);
        }

        static const double half = full / 2.0;
        CoordinateType v1 = put_in_range(c1, -half, half);
        CoordinateType v2 = put_in_range(c2, -half, half);

        // Two coordinates on a circle are
        // at max <= half a circle away from each other.
        // So if it is more, shift origin.
        CoordinateType diff = geometry::math::abs(v1 - v2);
        if (diff > half)
        {
            v1 = put_in_range(v1, 0, full);
            v2 = put_in_range(v2, 0, full);
        }

        return compare(v1, v2);
    }

template <typename Point>
static inline double course(Point const& p1, Point const& p2)
{
    // http://williams.best.vwh.net/avform.htm#Crs
    double dlon = get_as_radian<0>(p2) - get_as_radian<0>(p1);
    double cos_p2lat = cos(get_as_radian<1>(p2));

    // "An alternative formula, not requiring the pre-computation of d"
    return atan2(sin(dlon) * cos_p2lat,
        cos(get_as_radian<1>(p1)) * sin(get_as_radian<1>(p2))
        - sin(get_as_radian<1>(p1)) * cos_p2lat * cos(dlon));
}

    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename boost::mpl::if_c
            <
                boost::is_void<CalculationType>::type::value,
                typename select_most_precise
                    <
                        typename select_most_precise
                            <
                                typename coordinate_type<P1>::type,
                                typename coordinate_type<P2>::type
                            >::type,
                        typename coordinate_type<P>::type
                    >::type,
                CalculationType
            >::type coordinate_type;

        double d1 = 0.001; // m_strategy.apply(sp1, p);
        double crs_AD = detail::course(p1, p);
        double crs_AB = detail::course(p1, p2);
        double XTD = asin(sin(d1) * sin(crs_AD - crs_AB));

        return math::equals(XTD, 0) ? 0 : XTD < 0 ? 1 : -1;
    }


    inline haversine(calculation_type const& r = 1.0)
        : m_radius(r)
    {}



    static inline calculation_type apply(Point1 const& p1, Point2 const& p2)
    {
        return calculate(get_as_radian<0>(p1), get_as_radian<1>(p1),
                        get_as_radian<0>(p2), get_as_radian<1>(p2));
    }


    inline calculation_type radius() const
    {
        return m_radius;
    }


    static inline calculation_type calculate(calculation_type const& lon1,
            calculation_type const& lat1,
            calculation_type const& lon2,
            calculation_type const& lat2)
    {
        return math::hav(lat2 - lat1)
                + cos(lat1) * cos(lat2) * math::hav(lon2 - lon1);
    }

    inline haversine(calculation_type const& radius = 1.0)
        : m_radius(radius)
    {}

    inline calculation_type apply(Point1 const& p1, Point2 const& p2) const
    {
        calculation_type const a = comparable_type::apply(p1, p2);
        calculation_type const c = calculation_type(2.0) * asin(sqrt(a));
        return m_radius * c;
    }

    inline calculation_type radius() const
    {
        return m_radius;
    }

    static inline comparable_type apply(this_type const& input)
    {
        return comparable_type(input.radius());
    }

    template <typename T>
    static inline return_type apply(this_type const& , T const& value)
    {
        return return_type(value);
    }



        inline excess_sum()
            : sum(0)
            , distance_over_unit_sphere(1)
        {}

        inline calculation_type area(calculation_type radius) const
        {
            return - sum * radius * radius;
        }


    inline huiller(calculation_type radius = 1.0)
        : m_radius(radius)
    {}


    inline void apply(PointOfSegment const& p1,
                PointOfSegment const& p2,
                excess_sum& state) const
    {
        if (! geometry::math::equals(get<0>(p1), get<0>(p2)))
        {
            calculation_type const half = 0.5;
            calculation_type const two = 2.0;
            calculation_type const four = 4.0;
            calculation_type const two_pi = two * geometry::math::pi<calculation_type>();
            calculation_type const half_pi = half * geometry::math::pi<calculation_type>();

            // Distance p1 p2
            calculation_type a = state.distance_over_unit_sphere.apply(p1, p2);

            // Sides on unit sphere to south pole
            calculation_type b = half_pi - geometry::get_as_radian<1>(p2);
            calculation_type c = half_pi - geometry::get_as_radian<1>(p1);

            // Semi parameter
            calculation_type s = half * (a + b + c);

            // E: spherical excess, using l'Huiller's formula
            // [tg(e / 4)]2   =   tg[s / 2]  tg[(s-a) / 2]  tg[(s-b) / 2]  tg[(s-c) / 2]
            calculation_type E = four * atan(sqrt(geometry::math::abs(tan(s / two)
                    * tan((s - a) / two)
                    * tan((s - b) / two)
                    * tan((s - c) / two))));

            E = geometry::math::abs(E);

            // In right direction: positive, add area. In left direction: negative, subtract area.
            // Longitude comparisons are not so obvious. If one is negative, other is positive,
            // we have to take the dateline into account.
            // TODO: check this / enhance this, should be more robust. See also the "grow" for ll
            // TODO: use minmax or "smaller"/"compare" strategy for this
            calculation_type lon1 = geometry::get_as_radian<0>(p1) < 0
                ? geometry::get_as_radian<0>(p1) + two_pi
                : geometry::get_as_radian<0>(p1);

            calculation_type lon2 = geometry::get_as_radian<0>(p2) < 0
                ? geometry::get_as_radian<0>(p2) + two_pi
                : geometry::get_as_radian<0>(p2);

            if (lon2 < lon1)
            {
                E = -E;
            }

            state.sum += E;
        }
    }


    inline return_type result(excess_sum const& state) const
    {
        return state.area(m_radius);
    }


    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<Dimension>(p1) * get<Dimension>(p2)
            + dot_product_maker<P1, P2, Dimension+1, DimensionCount>::apply(p1, p2);
    }


    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<DimensionCount>(p1) * get<DimensionCount>(p2);
    }

    template <typename T>
    static inline ReturnType rt(T const& v)
    {
        return boost::numeric_cast<ReturnType>(v);
    }


    static inline ReturnType apply(U const& ux, U const& uy
                                 , V const& vx, V const& vy)
    {
        return rt(ux) * rt(vy) - rt(uy) * rt(vx);
    }


template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& ux, U const& uy
                            , V const& vx, V const& vy)
{
    return calculate_determinant
        <
            ReturnType, U, V
        >::apply(ux, uy, vx, vy);
}



template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& u, V const& v)
{
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<U>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<V>) );

    return calculate_determinant
        <
            ReturnType, 
            typename geometry::coordinate_type<U>::type,
            typename geometry::coordinate_type<V>::type
        >::apply(get<0>(u), get<1>(u), get<0>(v), get<1>(v));
}


    inline value_operation(C const &value)
        : m_value(value)
    {}


    template <typename P, int I>
    inline void apply(P& point) const
    {
        set<I>(point, Function<C>()(get<I>(point), m_value));
    }


    inline point_operation(PointSrc const& point)
        : m_source_point(point)
    {}


    template <typename PointDst, int I>
    inline void apply(PointDst& dest_point) const
    {
        set<I>(dest_point,
            Function<coordinate_type>()(get<I>(dest_point), get<I>(m_source_point)));
    }


    inline value_assignment(C const &value)
        : m_value(value)
    {}


    template <typename P, int I>
    inline void apply(P& point) const
    {
        set<I>(point, m_value);
    }


    inline point_assignment(PointSrc const& point)
        : m_source_point(point)
    {}


    template <typename PointDst, int I>
    inline void apply(PointDst& dest_point) const
    {
        set<I>(dest_point, get<I>(m_source_point));
    }

template <typename Point>
inline void add_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    for_each_coordinate(p, detail::value_operation<typename coordinate_type<Point>::type, std::plus>(value));
}

template <typename Point1, typename Point2>
inline void add_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point2>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::plus>(p2));
}

template <typename Point>
inline void subtract_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    for_each_coordinate(p, detail::value_operation<typename coordinate_type<Point>::type, std::minus>(value));
}

template <typename Point1, typename Point2>
inline void subtract_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point2>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::minus>(p2));
}

template <typename Point>
inline void multiply_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    for_each_coordinate(p, detail::value_operation<typename coordinate_type<Point>::type, std::multiplies>(value));
}

template <typename Point1, typename Point2>
inline void multiply_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point2>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::multiplies>(p2));
}

template <typename Point>
inline void divide_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    for_each_coordinate(p, detail::value_operation<typename coordinate_type<Point>::type, std::divides>(value));
}

template <typename Point1, typename Point2>
inline void divide_point(Point1& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point2>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_operation<Point2, std::divides>(p2));
}

template <typename Point>
inline void assign_value(Point& p, typename detail::param<Point>::type value)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    for_each_coordinate(p, detail::value_assignment<typename coordinate_type<Point>::type>(value));
}

template <typename Point1, typename Point2>
inline void assign_point(Point1& p1, const Point2& p2)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point2>) );
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point2>) );

    for_each_coordinate(p1, detail::point_assignment<Point2>(p2));
}

    static inline bool apply(Type const& a, Type const& b)
    {
        return a == b;
    }

    static inline Type get_max(Type const& a, Type const& b, Type const& c)
    {
        return (std::max)((std::max)(a, b), c);
    }


    static inline bool apply(Type const& a, Type const& b)
    {
        if (a == b)
        {
            return true;
        }

        // See http://www.parashift.com/c++-faq-lite/newbie.html#faq-29.17,
        // FUTURE: replace by some boost tool or boost::test::close_at_tolerance
        return std::abs(a - b) <= std::numeric_limits<Type>::epsilon() * get_max(std::abs(a), std::abs(b), 1.0);
    }

    static inline bool apply(Type const& a, Type const& b)
    {
        return a < b;
    }

    static inline bool apply(Type const& a, Type const& b)
    {
        if (equals<Type, true>::apply(a, b))
        {
            return false;
        }
        return a < b;
    }

    static inline T apply()
    {
        // Default calls Boost.Math
        return boost::math::constants::pi<T>();
    }

    static inline T apply(const T& factor)
    {
        return factor * std::numeric_limits<T>::epsilon();
    }



template <typename T>
inline T pi() { return detail::define_pi<T>::apply(); }


template <typename T>
inline T relaxed_epsilon(T const& factor)
{
    return detail::relaxed_epsilon<T>::apply(factor);
}


template <typename T1, typename T2>
inline bool equals(T1 const& a, T2 const& b)
{
    typedef typename select_most_precise<T1, T2>::type select_type;
    return detail::equals
        <
            select_type,
            boost::is_floating_point<select_type>::type::value
        >::apply(a, b);
}


template <typename T1, typename T2>
inline bool equals_with_epsilon(T1 const& a, T2 const& b)
{
    typedef typename select_most_precise<T1, T2>::type select_type;
    return detail::equals_with_epsilon
        <
            select_type, 
            boost::is_floating_point<select_type>::type::value
        >::apply(a, b);
}


template <typename T1, typename T2>
inline bool smaller(T1 const& a, T2 const& b)
{
    typedef typename select_most_precise<T1, T2>::type select_type;
    return detail::smaller
        <
            select_type,
            boost::is_floating_point<select_type>::type::value
        >::apply(a, b);
}


template <typename T1, typename T2>
inline bool larger(T1 const& a, T2 const& b)
{
    typedef typename select_most_precise<T1, T2>::type select_type;
    return detail::smaller
        <
            select_type,
            boost::is_floating_point<select_type>::type::value
        >::apply(b, a);
}

template <typename T>
inline T hav(T const& theta)
{
    T const half = T(0.5);
    T const sn = sin(half * theta);
    return sn * sn;
}

template <typename T>
inline T sqr(T const& value)
{
    return value * value;
}

template<typename T>
inline T abs(const T& t)
{
    using std::abs;
    return abs(t);
}

    static inline CoordinateType apply(std::string const& source)
    {
#if defined(BOOST_GEOMETRY_NO_LEXICAL_CAST)
        return atof(source.c_str());
#else
        return boost::lexical_cast<CoordinateType>(source);
#endif
    }

    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& point, Op operation)
    {
        operation.template apply<Point, Dimension>(point);
        return coordinates_scanner
            <
                Point,
                Dimension+1,
                DimensionCount,
                IsConst
            >::apply(point, operation);
    }

    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& , Op operation)
    {
        return operation;
    }


template <typename Point, typename Op>
inline void for_each_coordinate(Point& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, false
        > scanner;

    scanner::apply(point, operation);
}


template <typename Point, typename Op>
inline Op for_each_coordinate(Point const& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concept::ConstPoint<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, true
        > scanner;

    return scanner::apply(point, operation);
}
