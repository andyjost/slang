
      virtual ~error_category(){}

    inline const error_category &  get_system_category() { return system_category(); }

    inline const error_category &  get_generic_category() { return generic_category(); }

    inline const error_category &  get_posix_category() { return generic_category(); }

      static void unspecified_bool_true() {}

      static void unspecified_bool_true() {}
 inline system::error_code * throws() { return 0; }


  inline system::error_code & throws()
    { return *detail::throws(); }

      inline error_code make_error_code( linux_errno e )
        { return error_code( e, system_category() ); }
