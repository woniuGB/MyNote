# C++ 构造函数后面的冒号作用
```c++
class Foo {
	public:
		Foo(const string& newName,const string& newAge): name(newName),age(newAge){}
		
		
	private:
		string name;
		string age;
};
```
作用是用来初始化成员变量。
来看下面的语句
```c++
int main(void){
	int i(9);
	std::cout<<i<<endl;
	return 0;
}
```
是不是和上面的语法很像。
`int i(9);`和`int i = 9;`是两种初始化变量的方式。这两种方式的区别就在于，括号赋值是在给变量分配内存空间的同时对它进行初始化，而赋值运算符赋值则是先分配内存空间，然后再初始化。说到底就是初始化的时机不同。

那么干嘛要这样区分，平时我们赋值变量的时候用哪种都可以呀？
这两种区分方式呢主要是对三种数据类型比较有用：
1、常量数据类型（const 类型）
2、引用数据类型（&变量）
3、没有默认构造函数的类对象（一个类中含有另一个类）
由于常量数据的数据必须是一开始就初始化好，而不能之后再做改变；引用数据类型由于引用是和某一变量维系在一起了，所以不能之后再改变；类（A类）中的数据是另一个类（B类）的对象，而B类在定义时没有默认构造函数，那么在A类定义中的构造函数必须采用冒号赋值，否则报错。

参考：https://blog.csdn.net/weixin_45795947/article/details/105124655?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control



# 浅谈C++中指针和引用的区别
```
(1)指针：指针是一个变量，只不过这个变量存储的是一个地址，指向内存的一个存储单元；而引用跟原来的变量实质上是同一个东西，只不过是原变量的一个别名而已。如：
int a=1;int *p=&a;
int a=1;int &b=a;
上面定义了一个整形变量和一个指针变量p，该指针变量指向a的存储单元，即p的值是a存储单元的地址。
而下面2句定义了一个整形变量a和这个整形a的引用b，事实上a和b是同一个东西，在内存占有同一个存储单元。
(2)可以有const指针，但是没有const引用；
(3)指针可以有多级，但是引用只能是一级（int **p；合法 而 int &&a是不合法的）
(4)指针的值可以为空，但是引用的值不能为NULL，并且引用在定义的时候必须初始化；
(5)指针的值在初始化后可以改变，即指向其它的存储单元，而引用在进行初始化后就不会再改变了。
(6)"sizeof引用"得到的是所指向的变量(对象)的大小，而"sizeof指针"得到的是指针本身的大小；
(7)指针和引用的自增(++)运算意义不一样；
```

参考：https://www.cnblogs.com/dolphin0520/archive/2011/04/03/2004869.html
