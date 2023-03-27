#include <iostream>
#include <string>
#include <memory>

class BigInt
{
public:

    BigInt(const BigInt& bi){
        if (this != &bi)
        {
            if (chunks_ != bi.chunks_) 
            {
                digits_.reset(new int32_t[bi.chunks_]);
                chunks_ = bi.chunks_;
                is_negative_ = bi.is_negative_;
            }
            std::copy(&bi.digits_[0], &bi.digits_[0] + chunks_, &digits_[0]);
        }
       
    }

     BigInt()
    {

    }

    BigInt(int32_t num)
    {
        if (num < 0)
        {
            this->is_negative_ = true;
        }
        else 
        {
            this->is_negative_ = false;
        }
        this->chunks_ = 1;
        digits_.reset(new int32_t[1]);
        this->digits_[0] = num;
    }
    BigInt(std::string &str)
    {
        if (str.length() == 0)
        {
            this->is_negative_ = false;
        }
        else 
        {
            if (str[0] == '-') {     //negative
                str = str.substr(1);
                this->is_negative_ = true;
            }
            else                     //positive
            {
                this->is_negative_ = false;
            }
        }
        int chunks = 0;
        if (str.length() % 9 != 0) {
            chunks = str.length() / 9 + 1;
        }
        else 
        {
            chunks = str.length() / 9;
        }
        
        digits_.reset(new int32_t[chunks]);
        long long counter = chunks - 1;
        this->chunks_ = chunks;
        for (long long i = str.length(); i > 0; i -= 9)
        {

            if (i < 9)
            {
                std::string futureChunk = str.substr(0, i);
                this->digits_[counter] = atoi(futureChunk.c_str());
            }
            else 
            {
                std::string futureChunk = str.substr(i - 9, 9);

                this->digits_[counter] = atoi(futureChunk.c_str());
            }
            counter--;
        }
    }

    int getChunks()
    {
        return chunks_;
    }

    BigInt& operator=(const BigInt& bi){
        if (this != &bi)
        {
            if (chunks_ != bi.chunks_) 
            {
                digits_.reset(new int32_t[bi.chunks_]);
                chunks_ = bi.chunks_;
                is_negative_ = bi.is_negative_;
            }
            std::copy(&bi.digits_[0], &bi.digits_[0] + chunks_, &digits_[0]);
        }
        return *this;
    }

    const BigInt operator +(const int32_t& rhs) 
    {
        BigInt right = rhs;
        //std::cout << "chunks:" << right.getChunks() << std::endl;
        return *this + right;
    }
    const BigInt operator -(const int32_t& rhs) 
    {
        BigInt right = rhs;
        //std::cout << "chunks:" << right.getChunks() << std::endl;
        return *this - right;
    }

    const BigInt operator +(const BigInt& right) {
        //std::cout << "Left: " << chunks_ << std::endl;
        //std::cout << "Right: " <<  right.chunks_ << std::endl;
        if (!is_negative_ )
        {
            if (!right.is_negative_)
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                maxSize++;
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                    for (int i = 0; i < maxSize - 1; i++)
                    {
                        //std::cout << "i" <<  i << std::endl;
                        //std::cout << newLeft[i] <<  0 << std::endl;
                        newLeft[i] = 0;
                    }
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {
                    newRight[maxSize - 1] = right.digits_[0];
                    //std::cout << "newRight[maxSize - 1]: " <<  maxSize - 1 << std::endl;
                    for (int i = 0; i < maxSize - 1; i++)
                    {
                        //std::cout << "i" <<  i << std::endl;
                        //std::cout << newRight[i] <<  0 << std::endl;
                        newRight[i] = 0;
                    }
                    
                }
                for (size_t i = maxSize; i > 0; --i) {
                    //std::cout << "i: " <<  i - 1 << std::endl;
                    
                    //std::cout << "Right: " <<  newRight[i-1] << std::endl;
                }

                for (size_t i = maxSize; i > 0; --i)
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                for (size_t i = maxSize; i > 0; --i) {
                    //std::cout << "i: " <<  i - 1 << std::endl;
                    //std::cout << "Left: " <<  newLeft[i-1] << std::endl;
                    //std::cout << "Right: " <<  newRight[i-1] << std::endl;
                    int32_t sum = newLeft[i-1] + newRight[i-1];
                    if (carry != 0)
                    {
                        sum += carry;
                    }
                    if (sum > 1000000000)
                    {
                        carry = sum - 1000000000;
                        sum = sum - carry;
                    }
                    this->digits_[i-1] = sum;
                }

                return *this;
            }
            else  //left postive right negative
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
       
                for (size_t i = maxSize; i > 0; --i) {

                    int32_t diff = newLeft[i-1] - carry - newRight[i-1];
             
                    if (diff < 0)
                    {
                        carry = 1;
                    }
                    if (carry != 0)
                    {
                        diff = diff + 1000000000;
                    }
                    this->digits_[i-1] = diff;
                }
                return *this;
            }
        } else    
        {
            if (!right.is_negative_)//left negative right positive
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                for (size_t i = maxSize; i > 0; --i) {

                    int32_t diff = newRight[i-1] - carry - newLeft[i-1];
                    if (diff < 0)
                    {
                        carry = 1;
                    }
                    if (carry != 0)
                    {
                        diff = diff + 1000000000;
                    }
                    this->digits_[i-1] = diff;
                }
                return *this;
            }
            else //left negative right negative
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                maxSize++;
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                for (size_t i = maxSize; i > 0; --i) {

                    int32_t sum = newLeft[i-1] + newRight[i-1];
                    if (carry != 0)
                    {
                        sum += carry;
                    }
                    if (sum > 1000000000)
                    {
                        carry = sum - 1000000000;
                        sum = sum - carry;
                    }
                    this->digits_[i-1] = sum;
                    this->is_negative_ = true;
                }

                return *this;
            }
        }
        
        return *this;
    }

    const BigInt operator -(const BigInt& right) 
    {
        //std::cout << "Start diff: " << std::endl;
        //std::cout << "Left: " << chunks_ << std::endl;
        //std::cout << "Right: " <<  right.chunks_ << std::endl;
        if (!is_negative_ )
        {
            if (!right.is_negative_)
            {
            long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {
                    newRight[maxSize - 1] = right.digits_[0];
                    for (int i = 0; i < maxSize - 1; i++)
                    {
                        newRight[i] = 0;
                    }
                    
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }

                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                for (size_t i = maxSize; i > 0; --i) {
                    int32_t diff = newLeft[i-1] - carry - newRight[i-1];
                    if (diff < 0)
                    {
                        carry = 1;
                    }
                    if (carry != 0)
                    {
                        diff = diff + 1000000000;
                    }
                    this->digits_[i-1] = diff;
                }
                return *this;
            }
            else  //left postive right negative
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                maxSize++;
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                for (size_t i = maxSize; i > 0; --i) {

                    int32_t sum = newLeft[i-1] + newRight[i-1];
                    if (carry != 0)
                    {
                        sum += carry;
                    }
                    if (sum > 1000000000)
                    {
                        carry = sum - 1000000000;
                        sum = sum - carry;
                    }
                    this->digits_[i-1] = sum;
                }

                return *this;
            }
        }
        else{
            if (right.is_negative_) 
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                //std::cout << "Left: " << chunks_ << std::endl;
                //std::cout << "Right: " <<  right.chunks_ << std::endl;
                //std::cout << "Max: " <<  maxSize << std::endl;
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        //std::cout << "counter: " << counter << std::endl;
                        //std::cout << "digits_[i]: " << digits_[i] << std::endl;
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {
                    //std::cout << "newRight[ " << (maxSize - 1) << "]"<< std::endl;
                    //std::cout << "right.digits_[0]" << right.digits_[0] << std::endl;

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                //std::cout << "Our new arrays"<< std::endl;
                for (size_t i = maxSize; i > 0; --i) {
                    //std::cout << "i: " << (i-1) << std::endl;
                    //std::cout << "Left: " << newLeft[i-1] << std::endl;
                    //std::cout << "Right: " << newRight[i-1] << std::endl;

                    int32_t diff = newRight[i-1] - carry - newLeft[i-1];
                    //std::cout << "dif: " << diff << std::endl;
                    if (diff < 0)
                    {
                        carry = 1;
                    }
                    if (carry != 0)
                    {
                        diff = diff + 1000000000;
                    }
                    this->digits_[i-1] = diff;
                }
                return *this;
            }
            else //left negative right negative
            {
                long long maxSize = 0;
                //int biggest = -1; //0 - left, 1 - right
                if (chunks_ > right.chunks_)
                {
                    maxSize = chunks_;
                    //biggest = 0;
                }
                else 
                {
                    maxSize = right.chunks_;
                    //biggest = 1;
                }
                maxSize++;
                //std::cout << "Left: " << chunks_ << std::endl;
                //std::cout << "Right: " <<  right.chunks_ << std::endl;
                //std::cout << "Max: " <<  maxSize << std::endl;
                int carry = 0;
                int32_t* newLeft = new int32_t[maxSize];
                int32_t* newRight = new int32_t[maxSize];
                for (int i = 0; i < maxSize; i++)
                    {
                        
                        newLeft[i] = 0;
                        newRight[i] = 0;
                    }
                int counter = maxSize-1;
                if (chunks_-1 == 0)
                {
                    newLeft[maxSize - 1] = digits_[0];
                }
                else {
                    for (long long i = chunks_ - 1; i >= 0; i--)
                    {
                        //std::cout << "counter: " << counter << std::endl;
                        //std::cout << "digits_[i]: " << digits_[i] << std::endl;
                        newLeft[counter] = digits_[i];
                        counter--;
                    }
                }
                counter = maxSize;
                if (right.chunks_-1 == 0)
                {
                    //std::cout << "newRight[ " << (maxSize - 1) << "]"<< std::endl;
                    //std::cout << "right.digits_[0]" << right.digits_[0] << std::endl;

                    newRight[maxSize - 1] = right.digits_[0];
                }
                else {
                    for (long long i = right.chunks_ - 1; i >= 0; i--)
                    {
                        newRight[counter] = right.digits_[i];
                        counter--;
                    }
                }
                
                digits_.reset(new int32_t[maxSize]);
                this->chunks_ = maxSize;
                //std::cout << "Our new arrays"<< std::endl;
                for (size_t i = maxSize; i > 0; --i) {
                    //std::cout << "i: " << (i-1) << std::endl;
                    //std::cout << "Left: " << newLeft[i-1] << std::endl;
                    //std::cout << "Right: " << newRight[i-1] << std::endl;

                    int32_t sum = newLeft[i-1] + newRight[i-1];
                    //std::cout << "Sum: " << sum << std::endl;
                    if (carry != 0)
                    {
                        sum += carry;
                    }
                    if (sum > 1000000000)
                    {
                        carry = sum - 1000000000;
                        sum = sum - carry;
                    }
                    this->digits_[i-1] = sum;
                    this->is_negative_ = true;
                }

                return *this;
            }
        }
        return *this;
    }

    

    /*BigInt& operator=(BigInt&& bi)
    {
        if (this != &bi)
            digits_.reset(new int32_t[bi.chunks_]);
            chunks_ = bi.chunks_;
            is_negative_ = bi.is_negative_;
            bi.chunks_ = 0;
            bi.digits_ = nullptr;
        }
        return *this;
    }*/

    

    
    const BigInt operator-() const
    {
        BigInt copy(*this);
        copy.is_negative_ = !copy.is_negative_;
        return copy;
    }

    bool operator==(const BigInt& right) {

        if (is_negative_ != right.is_negative_) 
        {
            
            return false;
        }
        if (chunks_ != right.chunks_)
        {
            return false;
        } 
        for (long long i = 0; i <= chunks_; i++)
        {
            if(digits_[i] != right.digits_[i])
            {
                return false;
            }
        }
 
        return true;
    }

    bool operator<(const BigInt& right) {
        
        //std::cout << "Left negative " << is_negative_ << std::endl;
        //std::cout << "Right negative " << right.is_negative_ << std::endl;

        if (is_negative_) 
        {
            if (!right.is_negative_)
            {
                return true;
            }
           
        }

        if (!is_negative_) 
        {
            if (right.is_negative_)
            {
                return false;
            }
           
        }

        int absBigger = -1; //0 - left, 1 - right

        //std::cout << "Left chunks " << chunks_ << std::endl;
        //std::cout << "Right chunks " << right.chunks_ << std::endl;
        
        if (chunks_ > right.chunks_)
        {
            absBigger = 0;
        } 
        else if (chunks_ < right.chunks_)
        {
            absBigger = 1;
        }
        else
        {
            for (long long i = 0; i <= chunks_; i++)
            {
                //std::cout << "Left chunks " << digits_[i] << std::endl;
                //std::cout << "Right chunks " << right.digits_[i] << std::endl;
                if(digits_[i] > right.digits_[i])
                {
                    absBigger = 0;
                }
                else if (digits_[i] < right.digits_[i])
                {
                    absBigger = 1;
                }

            }
        }
        //std::cout << "absBigger " << absBigger << std::endl;
        if (absBigger == -1) {
            return false;
        }
        //std::cout << "Checking " << std::endl;
        if (!is_negative_)
        {
            //std::cout << "both positive " << std::endl;
            if (absBigger == 0)
            {
                return false;
            }
            else return true;
        }

        if (is_negative_)
        {
            //std::cout << "both negative " << std::endl;
            if (absBigger == 0)
            {
                return true;
            }
            else return false;
        }
        return false;
    }

    bool operator>(const BigInt& right) {
        //std::cout << "Left negative " << is_negative_ << std::endl;
        //std::cout << "Right negative " << right.is_negative_ << std::endl;

        if (is_negative_) 
        {
            if (!right.is_negative_)
            {
                return false;
            }
           
        }

        if (!is_negative_) 
        {
            if (right.is_negative_)
            {
                return true;
            }
           
        }

        int absBigger = -1; //0 - left, 1 - right

        //std::cout << "Left chunks " << chunks_ << std::endl;
        //std::cout << "Right chunks " << right.chunks_ << std::endl;
        
        if (chunks_ > right.chunks_)
        {
            absBigger = 0;
        } 
        else if (chunks_ < right.chunks_)
        {
            absBigger = 1;
        }
        else
        {
            for (long long i = 0; i <= chunks_; i++)
            {
                //std::cout << "Left chunks " << digits_[i] << std::endl;
                //std::cout << "Right chunks " << right.digits_[i] << std::endl;
                if(digits_[i] > right.digits_[i])
                {
                    absBigger = 0;
                }
                else if (digits_[i] < right.digits_[i])
                {
                    absBigger = 1;
                }

            }
        }

        //std::cout << "absBigger " << absBigger << std::endl;
        if (absBigger == -1) {
            return false;
        }
        //std::cout << "Checking " << std::endl;
        if (!is_negative_)
        {
            //std::cout << "both positive " << std::endl;
            if (absBigger == 0)
            {
                return true;
            }
            else return false;
        }

        if (is_negative_)
        {
            //std::cout << "both negative " << std::endl;
            if (absBigger == 0)
            {
                return false;
            }
            else return true;
        }
        return false;
    }

    const BigInt operator *(const BigInt& right) 
    {
        BigInt result;
        int32_t c1 = chunks_;
        int32_t c2 = right.chunks_;
        result.digits_.reset(new int32_t[c1 + c2]);
        for (int i = 0; i < c1 + c2; i++)
                    {
                        
                        result.digits_[i] = 0;
                        result.digits_[i] = 0;
                    }
        for (long long i = 0; i < chunks_; ++i) {
                int carry = 0;
                for (long long j = 0; j < right.chunks_ || carry != 0; ++j) {
                        long long cur = result.digits_[i + j] +
                                digits_[i] * 1LL * (j < right.chunks_ ? right.digits_[j] : 0) + carry;
                        result.digits_[i + j] = static_cast<int32_t>(cur % 1000000000);
                        carry = static_cast<int32_t>(cur / 1000000000);
                }
        }
        digits_.reset(new int32_t[c1 + c2]);
        for (int i = 0; i < c1 + c2; i++)
        {
            digits_[i] = result.digits_[i];
        }
        is_negative_ = is_negative_ != right.is_negative_;
        return *this;
    }

    const BigInt operator *(const int32_t& rhs) 
    {
        BigInt right = rhs;
        BigInt result;
        int32_t c1 = chunks_;
        int32_t c2 = right.chunks_;
        result.digits_.reset(new int32_t[c1 + c2]);
        for (int i = 0; i < c1 + c2; i++)
                    {
                        
                        result.digits_[i] = 0;
                        result.digits_[i] = 0;
                    }
        for (long long i = 0; i < chunks_; ++i) {
                int carry = 0;
                for (long long j = 0; j < right.chunks_ || carry != 0; ++j) {
                        long long cur = result.digits_[i + j] +
                                digits_[i] * 1LL * (j < right.chunks_ ? right.digits_[j] : 0) + carry;
                        result.digits_[i + j] = static_cast<int32_t>(cur % 1000000000);
                        carry = static_cast<int32_t>(cur / 1000000000);
                }
        }
        digits_.reset(new int32_t[c1 + c2]);
        for (int i = 0; i < c1 + c2; i++)
        {
            digits_[i] = result.digits_[i];
        }
        is_negative_ = is_negative_ != right.is_negative_;
        return *this;
    }

    ~BigInt()
    {
        //std::cout << "Dtor" << std::endl;
        //delete[] digits_;
    }

    std::string to_string()
    {
        std::string res = "";
        if (is_negative_)
        {
            res += '-';
        } 
        
        
        for (long long i = 0; i < chunks_; i++)
        {
            res += std::to_string(digits_[i]);
        }
        
        return res;
    }

    friend std::ostream& operator<< (std::ostream& out, const BigInt& bigint);

private:
    std::shared_ptr<int32_t[]> digits_; //value
    bool is_negative_; //sign
    long long chunks_;

};


inline std::ostream& operator<< (std::ostream& out, const BigInt& bigint)
{
    if (bigint.is_negative_)
    {
        out << '-';
    } 
    
    
    for (long long i = 0; i < bigint.chunks_; i++)
    {
        out << bigint.digits_[i];
    }
    
    
    return out;
}


/*int main()
{
    BigInt bigint("1234567891234567891234");
    BigInt bigint1("1234567891234567891234");
    BigInt bigint2("-1234567891234567891234");
    BigInt bigint3("123456783241234567891234");
    BigInt bigint4("1234567891235567891234");
    BigInt bigint0("0");
    std::cout << bigint << std::endl;
    std::cout << bigint1 << std::endl;
    std::cout << bigint2 << std::endl;
    std::cout << bigint3 << std::endl;
    std::cout << bigint4 << std::endl;
    std::cout << bigint0 << std::endl;
    bool eq1 = (bigint == bigint1);
    bool eq2 = (bigint == bigint2);
    bool eq3 = (bigint == bigint3);
    bool eq4 = (bigint == bigint4);

    std::cout << "Check smaller for " << bigint << " and " << bigint1 << std::endl;
    bool smaller1 = (bigint < bigint1);
    std::cout << "Check smaller for " << bigint << " and " << bigint2 << std::endl;
    bool smaller2 = (bigint < bigint2);
    std::cout << "Check smaller for " << bigint << " and " << bigint3 << std::endl;
    bool smaller3 = (bigint < bigint3);
    std::cout << "Check smaller for " << bigint << " and " << bigint4 << std::endl;
    bool smaller4 = (bigint < bigint4);


    std::cout << "Check bigger for " << bigint << " and " << bigint1 << std::endl;
    bool bigger1 = (bigint > bigint1);
    std::cout << "Check bigger for " << bigint << " and " << bigint2 << std::endl;
    bool bigger2 = (bigint > bigint2);
    std::cout << "Check bigger for " << bigint << " and " << bigint3 << std::endl;
    bool bigger3 = (bigint > bigint3);
    std::cout << "Check bigger for " << bigint << " and " << bigint4 << std::endl;
    bool bigger4 = (bigint > bigint4);


    std::cout << eq1 << std::endl; //eq
    std::cout << eq2 << std::endl; //not eq
    std::cout << eq3 << std::endl; //not eq
    std::cout << eq4 << std::endl; //not eq


    std::cout << smaller1 << std::endl; //f
    std::cout << smaller2 << std::endl; //f
    std::cout << smaller3 << std::endl; //t
    std::cout << smaller4 << std::endl; //t

    std::cout << bigger1 << std::endl; //f
    std::cout << bigger2 << std::endl; //t
    std::cout << bigger3 << std::endl; //f
    std::cout << bigger4 << std::endl; //f

    BigInt neg = -bigint;
    std::cout << neg << std::endl;
    BigInt newBigint = bigint;
    std::cout << newBigint << std::endl;

    int32_t num = 5;
    BigInt newFromNum = num;
    std::cout << newFromNum << std::endl;

    BigInt sum1("1234567891");
    std::cout << sum1 << std::endl;

    BigInt sum2("12345");
    std::cout << sum2 << std::endl;

    BigInt res = sum1 + sum2;

    std::cout << "Sum res:" << std::endl;
    std::cout << res << std::endl;

    
    BigInt dif1("1234567891");
    
    std::cout << dif1 << std::endl;

    std::cout << "Diff res:" << std::endl;
    BigInt dif2("12345");
    std::cout << dif2 << std::endl;
    std::cout << "dif 2 chunks:" << dif2.getChunks() << std::endl;

    BigInt res2 = dif1 - dif2;

    std::cout << res2 << std::endl;

    BigInt sum11("1234567891");
    BigInt dif11("1234567891");
    BigInt res3 = sum11 + 12345;
    BigInt res4 = dif11 - 12345;
    std::cout << "Sum res:" << std::endl;
    std::cout << res3 << std::endl;
    std::cout << "Diff res:" << std::endl;
    std::cout << res4 << std::endl;


    BigInt mul1("12");
    BigInt mul2("2");
    BigInt res5 = mul1 * mul2;
    std::cout << "Mult res:" << std::endl;
    std::cout << res5 << std::endl;

    BigInt mul11("12");
    
    BigInt res6 = mul11 * 2;
    std::cout << "Mult res:" << std::endl;
    std::cout << res6 << std::endl;
    std::cout << res6.to_string() << std::endl;
    return 0;
}*/

