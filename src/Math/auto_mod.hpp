template<typename T>
struct auto_mod{
	T val;
	static T mod;
	auto_mod(T x){
		val = ((x % mod) + mod) % mod;
	}
		
	operator T(){
		return val;
	}
};
template<typename T>
static auto_mod<T> operator+(const auto_mod<T>& a, const auto_mod<T>& b){
	return auto_mod<T>(a.val + b.val);
}
template<typename T>	
static auto_mod<T> operator-(const auto_mod<T>& a, const auto_mod<T>& b){
	return auto_mod<T>(a.val - b.val);
}
template<typename T>		
static auto_mod<T> operator*(const auto_mod<T>& a, const auto_mod<T>& b){
	return auto_mod<T>(a.val * b.val);
}