# C++ Rvalue References Explained
By Thomas Becker

# Introduction

Rvalue references are a feature of C++ that was added with the C++11 standard.  
What makes rvalue references a bit difficult to grasp is that when you first look at them, it is not clear *what there purpose is* or *what problem they solve*.  
Therefore, I will not jump right in and explain what rvalue references are. Instead, I will start with the problems that are to be solved and then show how rvalue references provide the solution. That way, the definition of rvalue references will appear plausible and natural to you.

Rvalue references solve at least two problems:
1. **Implementing move sementics**
2. **Perfect forwarding**

If you are not familiar with these porblems, don't worry. Both of them will be explained in detail below. We'll start with move sementics. But before we're ready to go, I need to remind you of *what lvalues and rvalues are in C++*. Giving a rigorous definition is surprisingly difficult[^1], but the explanation below is good enough for the purpose at hand.

[^1]: If you are interested in a rigorous definition of rvalues and lvalues, a good place to start is Mikael Kiplelainen's [ACCU article](https://accu.org/journals/overload/12/61/kilpelainen_227/) on the subject.

The original definition of lvalue an d rvalue from the earliest C is as follows: 

> An *lvalue* is and expreesion `e` that may appear on *the left or on the right hand side of an assignment*, whereas an *rvalue* is an expression that can only appear on *the right hand side of an assignment*.

For example:

```cpp
int a = 42;
int b = 43;

// a & b are both l-values:
a = b; // OK
b = a; // OK
a = a * b; // OK

// a * b is r-value:
int c = a * b; // OK, rvalue on right hand side of assignment
a * b = 42; // Error, rvalue on left hand side of assignment
```

In C++, this is still useful as a first, intuitive approach to lvalues and rvalues.  

However, C++ with its user-defined types has introduced some subtleties regarding modifiability and assignability that cause this definition to be incorrect. There is no need for us to go further into this. Here is an alternate definition which, although it can still be argued with, will put you in a positioin to tackle rvalue references:

> <mark style="background: blue">An *lvalue* is an expression that refers to a memory location and allows us to take the address of that memory location via `&` operator</mark>. <mark style="background: red:">An *rvalue* is an expression that is not an lvalue</mark>.

For example:

```cpp
// lvalues:
int i = 42;
i = 43; // OK, i is an lvalue
int* p = &i; // OK, i is an lvalue

int& foo();
foo() = 42; // OK, foo() is an lvalue
int* p1 = &foo(); // OK, foo() is an lvalue

// rvalues:
int foobar();
int j = 0;
j = foobar(); // OK, foobar() is an rvalue
int* p2 = &foobar(); // Error, cannot take the address of an rvalue
j = 42; // OK, 42 is an rvaluek
```

# Move Sementics

Suppose `X` is a class that holds a pointer or handle to some resources, say, `m_pResource`. By a resource, I mean anything that *takes considerable effort to construct, clone, ore destruct*. A good example is `std::vector`, which holds a collection of objects that live in an array of allocated memory. Then, logically, the **copy assignment operator** for `X` look like this:

```cpp
X& X::operator=()(const X& other)
{
    // [...]
    // (1) Make a clone of what other.m_pResource refers to.
    // (2) Destruct the resource that m_pResource refers to
    // (3) Attach the clone to m_pResource
    // [...]
}
```

Similar reasoning applies to the copy constructor. 

Now suppose `X` is used as follows:

```cpp
X foo();
X x;

// [...] perhaps use x in various ways

x = foo(); // x.operator=(foo())
```

The last line above
- clones the resources from the *temporary* returned by `foo`,
- destructs the resource held by `x` and replaces it with the clone,
- destructs the *temporary* and thereby releases its resource.

Rather obviously, it would be ok, and much more efficient, to swap resource pointers (handles) between `x` and the *temporary*, and then let the *temporary*'s destructor destruct `x`'s original resource. 

In other words, in the special case where the right hand side of the assignment is an rvalue, we want the copy assignment operator to act like this:

```cpp
/// [...]
/// swap m_pResource and rhs.m_pResource
/// [...]
```

This is called **move sementics**. With C++11, this conditional behavior can be achieved via an overload:

```cpp
X& X::operator=(<mystery type> other)
{
    /// [...]
    /// swap this->m_pResource and other.m_pResource
    /// [...]
}
```

Since we're defining an overload of the copy assignment operator, our `mystery type` must essentially be a **reference**: we **certainly** want the right hand side to be passed to us by reference. 

Moreover, we expect the following behavior of the `mystery type`: when there is a choice between two overloads where one is an ordinary reference and the other is the `mystery type`, then rvalues must prefer the `mystery type`, while lvalues must prefer the ordinary reference.

If you now substitute "rvalue reference" for `mystery type` in the above, you're essentially looking at the definition of rvalue reference.

# Reference

- [C++ Rvalue References Explained/thbecker.net](http://thbecker.net/articles/rvalue_references/section_01.html)