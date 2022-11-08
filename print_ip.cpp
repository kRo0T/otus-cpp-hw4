#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T x) {
    uint8_t* tmp = reinterpret_cast<uint8_t*>(&x);
    for (int i=sizeof(T)-1; i>=0; i--)
    {
        std::cout << static_cast<int>(*(tmp+i));
        if (i>0)
            std::cout << ".";
    }
    std::cout<<std::endl;
}

template<typename>
struct is_container : std::false_type {};

template<typename T, typename A>
struct is_container<std::vector<T,A>> : std::true_type {};

template<typename T, typename A>
struct is_container<std::list<T,A>> : std::true_type {};

template<typename T, std::enable_if_t<is_container<T>::value, bool> = true>
void print_ip(T x) {
    for (auto iter = x.begin(); iter != x.end(); iter++) {
        if (iter != x.begin()) 
            std::cout << ".";
        std::cout << *iter;
    }
    std::cout << std::endl;
}

template<typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
void print_ip(T x)
{
    std::cout << x << std::endl;
}

template<size_t I=0, typename... T>
void print_ip(std::tuple<T...> x) {
    if constexpr (I<sizeof...(T)) {
        if constexpr (I>0)
            std::cout << ".";
        std::cout << std::get<I>(x);
        print_ip<I+1>(x);
    }
    else {
        std::cout << std::endl;
    }
}

int main()
{
    try
    {
        print_ip( int8_t{-1} ); // 255
        print_ip( int16_t{0} ); // 0.0
        print_ip( int32_t{2130706433} ); // 127.0.0.1
        print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
        print_ip( std::string{"Hello, World!"} ); // Hello, World!
        print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
        print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
        print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
