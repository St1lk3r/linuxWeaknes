#include <iostream>

class Array {
public:
    Array(std::ostream& ostream)
        : Ostream_(ostream),size_(0),capacity_(2),data_(new int[capacity_]){ 
        Ostream_ << "Constructed. " << *this << std::endl;  
    }
    Array(const Array& array)
        : Ostream_(array.Ostream_),size_(array.size_),capacity_(array.capacity_){
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; i++)
            {
                data_[i] = array.data_[i];
            }
            Ostream_ << "Constructed from another Array. " << *this << std::endl;
            
        }
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0)
        : Ostream_(ostream),size_(size),capacity_(2*size_),data_(new int[capacity_]){
            for (size_t i = 0; i < size; i++)
            {
                data_[i] = defaultValue;
            }
            Ostream_ << "Constructed with default. " << *this << std::endl;
            
        }
    ~Array(){
        Ostream_ << "Destructed " << size_ << std::endl;
        delete[] data_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const{
        return capacity_;
    }
    void Reserve(size_t newCapacity){
        if(newCapacity <= capacity_){
            return;
        }
        int* newData_ = new int[newCapacity];
        capacity_ = newCapacity;
        for (size_t i = 0; i < size_; i++)
        {
            newData_[i] = data_[i];
        }
        delete[] data_;
        data_ = newData_;
        
    }
    void Resize(size_t newSize){
        if(newSize <= size_){
            size_ = newSize;
            return;
        }
        int* newData = new int[newSize];
        for (size_t i = 0; i < newSize; i++)
        {
            if(i < size_){
                newData[i] = data_[i];
            }
            else{
                newData[i] = 0;
            }
        }
        delete[] data_;
        data_ = newData;
        size_ = newSize;
        capacity_ = size_;
        
    }
    void PushBack(int value = 0){
        if(size_ == capacity_){
            int* newData_ = new int[capacity_ * 2];
            capacity_ = capacity_ * 2;
            for (size_t i = 0; i < size_; i++)
            {
                newData_[i] = data_[i];
            }
            delete[] data_;
            data_ = newData_;
        }
        data_[size_++] = value;
    }
    void PopBack(){
        size_--;
    }

    const int& operator[](const size_t i) const {
        return const_cast<Array*>(this)->operator[](i);
    };
    int& operator[](const size_t i){
        return data_[i];
    }
    explicit operator bool() const{
        return size_ != 0;
    }

    bool operator<(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_,it.size_); i++)
        {
            if(data_[i] < it.data_[i]){
                return true;
            }
        }
        return size_ < it.size_;
        
    }
    bool operator>(const Array& it) const{
        return (it < *this);
    }
    bool operator!=(const Array& it) const{
        return (*this < it) || (it < *this);
    }
    bool operator==(const Array& it) const{
        return !(*this != it);
    }
    bool operator<=(const Array& it) const{
        return (*this < it) || (*this == it);
    }
    bool operator>=(const Array& it) const{
        return (*this > it) || (*this == it);
    }

    Array& operator<<(const int value){
        PushBack(value);
        return *this;
    }
    Array& operator<<(const Array& it){
        for (size_t i = 0; i < it.size_; i++)
        {
            PushBack(it.data_[i]);
        }
        return *this;
        
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Array& array);

private:
    std::ostream& Ostream_;
    size_t size_,capacity_;
    int* data_;
    // ...
};
std::ostream& operator<<(std::ostream& ostream, const Array& array){
    ostream << "Result Array's capacity is " << array.capacity_ << " and size is " << array.size_;
    if(array.size_ == 0){
        return ostream;
    }
    ostream << ", elements are: ";
    ostream << array.data_[0];
    for (size_t i = 1; i < array.size_; i++)
    {
        ostream << ", " <<  array.data_[i];
    }
    return ostream;
    

}
