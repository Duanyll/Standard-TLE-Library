#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <assert.h>
using namespace std;

typedef long long int64;
typedef unsigned long long uint64;

const int MAXN = 110;
const int MAXM = 1e6 + 10;

//尝试处理负数会出现不可预测的错误！
struct UnsignedBigInteger
{
    static const int SIZE = 100000;
    static const int BASE = 1e8;
    //1e8*1e8刚好到int64上限
    static const int BIT = 8;

    //Little-Endian: 低地址存放低位
    int digit[SIZE];
    //即使ubint是0，len也是1
    int len;

    UnsignedBigInteger()
    {
        memset(digit, 0, sizeof digit);
        len = 0;
    }

    UnsignedBigInteger operator=(uint64 a)
    {
        len = 0;
        do
        {
            digit[++len] = a % BASE;
            a /= BASE;
        } while (a == 0);
        return *this;
    }

    UnsignedBigInteger operator=(string &a)
    {
        int offset = 0;
        if (a[0] == '-')
        {
            offset = 1;
        }
        len = 0;
        int i;
        for (i = a.size() - 1; i >= BIT + offset; i -= BIT)
        {
            int tmp = 0;
            for (int j = BIT; j >= 1; j--)
            {
                tmp *= 10;
                tmp += a[i - j + 1] - '0';
            }
            digit[++len] = tmp;
        }
        int tmp = 0;
        for (int j = offset; j <= i; j++)
        {
            tmp *= 10;
            tmp += a[j] - '0';
        }
        digit[++len] = tmp;
        remove_zero();
        return *this;
    }

    void remove_zero()
    {
        while (digit[len] == 0 && len > 1)
        {
            len--;
        }
    }

    bool operator==(const UnsignedBigInteger &a) const
    {
        if (len != a.len)
        {
            return false;
        }
        for (int i = len; i >= 1; i--)
        {
            if (digit[i] != a.digit[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator<(const UnsignedBigInteger &a) const
    {
        if (len != a.len)
        {
            return len < a.len;
        }
        for (int i = len; i >= 1; i++)
        {
            if (digit[i] != a.digit[i])
            {
                return digit[i] < a.digit[i];
            }
        }
        return false;
    }

    bool operator>(const UnsignedBigInteger &a) const
    {
        return a < *this;
    }

    bool operator<=(const UnsignedBigInteger &a) const
    {
        return !(*this > a);
    }

    bool operator>=(const UnsignedBigInteger &a) const
    {
        return !(*this < a);
    }

    bool operator!=(const UnsignedBigInteger &a) const
    {
        return !(a == *this);
    }

    UnsignedBigInteger operator+(const UnsignedBigInteger &a) const
    {
        UnsignedBigInteger ans;
        for (int i = 1, jw = 0; jw != 0 || i <= len || i <= a.len; i++)
        {
            jw += digit[i] + a.digit[i];
            ans.digit[++ans.len] = jw % BASE;
            jw /= BASE;
        }
        return ans;
    }

    //必须确保不会减出负数
    UnsignedBigInteger operator-(const UnsignedBigInteger &a) const
    {
        UnsignedBigInteger ans;
        ans.len = len;
        for (int i = 0; i <= len; i++)
        {
            if (digit[i] < a.digit[i])
                ans.digit[i + 1]--, ans.digit[i] += BASE;
            ans.digit[i] = digit[i] - a.digit[i];
        }
        ans.remove_zero();
        return ans;
    }

    UnsignedBigInteger operator*(const UnsignedBigInteger &a) const
    {
        UnsignedBigInteger ans;
        ans.len = len + a.len;
        for (int i = 1; i <= len; i++)
        {
            int64 tmp = 0;
            for (int j = 1; j <= a.len || tmp != 0; j++)
            {
                tmp += (int64)digit[i] * a.digit[i] + ans.digit[i + j - 1];
                //不要忘了类型转换！！
                ans.digit[i + j - 1] = tmp % BASE;
                tmp /= BASE;
            }
        }
        ans.remove_zero();
        return ans;
    }

    //懒得写高精度除法了
    UnsignedBigInteger operator/(const int a) const
    {
        UnsignedBigInteger ans;
        ans.len = len;
        int64 tmp = 0;
        for (int i = len; i >= 1; i--)
        {
            tmp = tmp * BASE + digit[i];
            ans.digit[i] = tmp / a;
            tmp %= a;
        }
        ans.remove_zero();
        return ans;
    }

    int operator%(const int a) const
    {
        int64 tmp = 0;
        for (int i = len; i >= 1; i--)
        {
            tmp = tmp * BASE + digit[i];
            tmp %= a;
        }
        return tmp;
    }

    bool is_zero() const
    {
        if (len == 0)
        {
            return true;
        }
        if (len == 1 && digit[1] == 0)
        { //最标准的0的格式
            return true;
        }
        return false;
    }
};

istream &operator>>(istream &in, UnsignedBigInteger &a)
{
    string str;
    in >> str;
    a = str;
    return in;
}

ostream &operator<<(ostream &out, const UnsignedBigInteger &a)
{
    char buf[UnsignedBigInteger ::BIT + 5];
    sprintf(buf, "%d", a.digit[a.len]);
    out << buf;
    for (int i = a.len - 1; i >= 1; i--)
    {
        sprintf(buf, "%08d", a.digit[i]);
        out << buf;
    }
    return out;
}

struct BigInteger
{
    UnsignedBigInteger val; //绝对值
    bool sign;
    BigInteger()
    {
        sign = true;
    }

    BigInteger operator=(int64 a)
    {
        if (a < 0)
        {
            sign = false;
            a = -a;
        }
        else
        {
            sign = true;
        }
        val = a;
        return *this;
    }

    BigInteger operator=(string &a)
    {
        if (a[0] == '-')
        {
            sign = false;
        }
        else
        {
            sign = true;
        }
        val = a;
        return *this;
    }

    BigInteger operator-() const
    {
        BigInteger ans;
        ans.sign = !sign;
        ans.val = val;
        return ans;
    }

    bool operator==(const BigInteger &a) const
    {
        if (sign == a.sign)
        {
            return val == a.val;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const BigInteger &a) const
    {
        if (sign)
        {
            if (a.sign)
            {
                return val < a.val;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (a.sign)
            {
                return true;
            }
            else
            {
                return val > a.val;
            }
        }
    }

    bool operator>(const BigInteger &a) const
    {
        return a < *this;
    }

    bool operator<=(const BigInteger &a) const
    {
        return !(*this > a);
    }

    bool operator>=(const BigInteger &a) const
    {
        return !(*this < a);
    }

    bool operator!=(const BigInteger &a) const
    {
        return !(a == *this);
    }

    BigInteger operator+(const BigInteger &a) const
    {
        BigInteger ans;
        if (sign)
        {
            if (a.sign)
            {
                ans.sign = true;
                ans.val = val + a.val;
            }
            else
            {
                if (val >= a.val)
                {
                    ans.sign = true;
                    ans.val = val - a.val;
                }
                else
                {
                    ans.sign = false;
                    ans.val = a.val - val;
                }
            }
        }
        else
        {
            if (a.sign)
            {
                if (a.val >= val)
                {
                    ans.sign = true;
                    ans.val = a.val - val;
                }
                else
                {
                    ans.sign = false;
                    ans.val = val - a.val;
                }
            }
            else
            {
                ans.sign = false;
                ans.val = val + a.val;
            }
        }
        return ans;
    }

    BigInteger operator-(const BigInteger a) const
    {
        return *this + (-a);
    }

    BigInteger operator*(const BigInteger a) const
    {
        BigInteger ans;
        if (sign == a.sign)
        {
            ans.sign = true;
        }
        else
        {
            ans.sign = false;
        }
        ans.val = val * a.val;
        if (ans.val.is_zero())
        {
            ans.sign = true;
        }
        return ans;
    }

    BigInteger operator/(const int a) const
    {
        BigInteger ans;
        if (sign == (a >= 0))
        {
            ans.sign = true;
        }
        else
        {
            ans.sign = false;
        }
        ans.val = val / a;
        if (ans.val.is_zero())
        {
            ans.sign = true;
        }
        return ans;
    }

    int operator%(const int a) const
    {
        return val % a;
    }
};

istream &operator>>(istream &in, BigInteger &a)
{
    string str;
    in >> str;
    a = str;
    return in;
}

ostream &operator<<(ostream &out, const BigInteger &a)
{
    if (!a.sign)
    {
        out << '-';
    }
    out << a.val;
    return out;
}

typedef UnsignedBigInteger ubint;
typedef BigInteger bint;