
template<typename T> T* member_addr(T& data) { return &data; }

template<typename T> T* member_addr(T* data) { return data; }

template<typename T> T& member_deref(T& data) { return data; }

template<typename T> T& member_deref(T* data) { return *data; }
