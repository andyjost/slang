
    ~usage_requirements() { ((Model*)0)->~Model(); }

    virtual void failed(Model* x)
    {
        x->~Model();
    }

    virtual void failed(Model* x)
    {
        x->~Model();
    }

    static void failed() { ((Model*)0)->~Model(); }

    static void failed() { ((Model*)0)->~Model(); }
