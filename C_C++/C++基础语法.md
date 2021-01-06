#C++ 构造函数后面的冒号作用
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
