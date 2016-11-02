

    stack_t() :
        sp( 0), size( 0)
    {}


    fp_t() :
        fc_freg()
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_fp()
    {}


    stack_t() :
        sp( 0), size( 0)
    {}


    fp_t() :
        fc_freg()
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_fp()
    {}


    stack_t() :
        sp( 0), size( 0)
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_freg()
    {}


    stack_t() :
        sp( 0), size( 0)
    {}


    fp_t() :
        fp_freg(),
#ifdef _LP64
	fp_fprs(),
#endif
	fp_fsr()
    {}


    fcontext_t() :
        fc_fp(),
        fc_greg(),
        fc_stack()
    {}


    stack_t() :
        sp( 0), size( 0)
    {}


    fp_t() :
        fc_freg()
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_fp()
    {}


    stack_t() :
        sp( 0), size( 0)
    {}


    fp_t() :
        fc_freg()
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_fp()
    {}


    stack_t() :
        sp( 0), size( 0), limit( 0)
    {}


    fp_t() :
        fc_freg()
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_excpt_lst( 0),
        fc_local_storage( 0),
        fc_fp(),
        fc_dealloc( 0)
    {}


    stack_t() :
        sp( 0), size( 0), limit( 0)
    {}


    fcontext_t() :
        fc_greg(),
        fc_stack(),
        fc_local_storage( 0),
        fc_fp(),
        fc_dealloc()
    {}
