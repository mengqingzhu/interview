#include "qh_string.h"
#include <assert.h>

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
		len_ = 0;
		const char * pCurrent = s;
		while(*pCurrent++ != '\0') ++len_;
		if(len_ != 0){
			data_ = new char[len_ + 1];
			memcpy(data_, s, len_);
		}else
			data_ = NULL;
    }

    string::string( const char* s, size_t len )
    {
		if(len > 0){
			len_ = len;
			data_ = new char[len + 1];
			memcpy(data_, s, len);
		}else{
			len_ = 0;
			data_ = NULL;
		}
    }

    string::string( const string& rhs )
    {
		const char * t_data = rhs.data();
		len_ = rhs.size();
		if(len_ == 0) data_ = NULL;
		else{
			data_ = new char[len_ + 1];
			memcpy(data_, t_data, len_);
		}
    }

    string& string::operator=( const string& rhs )
    {
		if(this == &rhs) return *this;
		const char * t_data = rhs.data();
		if(len_ != 0) delete data_;
		len_ = rhs.size();
		if(len_ == 0) data_ = NULL;
		else{
			data_ = new char[len_ + 1];
			memcpy(data_, t_data, len_);
		}
        return *this;
    }

    string::~string()
    {
		if(len_)
			delete data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
		return data_;
    }

    const char* string::c_str() const
    {
		if(data_) data_[len_] = '\0';
		return data_;
    }

    char & string::operator[]( size_t index )
    {
		assert(index < len_);
        return data_[index];
    }
}
