#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
        {
			if(n == 0){
				data_ = NULL;
				size_ = 0;
				capacity_ = 0;
				return;
			}
            data_ = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
			size_ = n;
			capacity_ = n;
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
			if(&rhs == this) return *this;
			if(data_) delete data_;
			data_ = NULL;
            size_ = rhs.size();
			capacity_ = rhs.capacity();
			if(capacity_ != 0)
				data_ = new T[capacity_];
			for(size_t i = 0; i < size_; ++i){
				data_[i] = rhs[i];
			}
			return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
 		}

		size_t capacity() const
		{
			return capacity_;
		}

        // set & get
        T& operator[](size_t index) const;

        // set
        void push_back(const T& element);
        void pop_back();
        void resize(size_t n, const T& element = T());
        void reserve(size_t n);
        void clear();
        bool empty();

    private:
        T*      data_;
        size_t  size_;
		size_t	capacity_;
    };

	template<class T> T& vector<T>::operator[](size_t index) const{
		assert(index < size_);
		return data_[index];
	}

	template<class T> void vector<T>::push_back(const T& element){
		if(capacity_ == size_){
			if(size_ == 0){
				capacity_ = 1;
			}else{
				capacity_ *= 2;
			}
			T * t_data = new T[capacity_];
			for(size_t i = 0; i < size_; ++i){
				t_data[i] = data_[i];
			}
			if(data_) delete data_;
			data_ = t_data;
		}
		data_[size_++] = element;
	}

	template<class T> void vector<T>::pop_back(){
		if(size_ == 0) return;
		data_[--size_] = T();
	}

	template<class T> void vector<T>::resize(size_t n, const T& element){
		if(n > capacity_){
			capacity_ = n;
			T * t_data = new T[n];
			for(size_t i = 0; i < size_; ++i){
				t_data[i] = data_[i];
			}
			for(size_t i = size_; i < n; ++i){
				t_data[i] = element;
			}
			delete data_;
			data_ = t_data;
			size_ = n;
		}else if(n > size_){
			for(size_t i = size_; i < capacity_; ++i){
				data_[i] = element;
			}
			size_ = n;
		}else{
			for(size_t i = n; i < size_; ++i){
				data_[i] = T();
			}
			size_ = n;
		}
	}

	template<class T> void vector<T>::reserve(size_t n){
		if(capacity_ >= n) return;
		capacity_ = n;
		T * t_data = new T[n];
		for(size_t i = 0; i < size_; ++i){
			t_data[i] = data_[i];
		}
		delete data_;
		data_ = t_data;
	}

	template<class T> void vector<T>::clear(){
		for(size_t i = 0; i < size_; ++i){
			data_[i] = T();
		}
		size_ = 0;
	}

	template<class T> bool vector<T>::empty(){
		return size_ == 0;
	}
}

#endif


