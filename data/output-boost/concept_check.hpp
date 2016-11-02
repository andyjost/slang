
        virtual void failed(Model* x)
        {
            x->~Model();
        }


  template <class Model>
  void concept_check_failed()
  {
      ((Model*)0)->~Model();
  }
